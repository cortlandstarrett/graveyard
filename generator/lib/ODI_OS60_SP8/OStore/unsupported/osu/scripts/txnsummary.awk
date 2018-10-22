function dumpCounters() {
  if (COUNTERS[$2]) {
    printf "%s", COUNTERS[$2];
    delete COUNTERS[$2];
  }
}


function dumpTimers(TYPE)
{
  split(TXN[$2],BARRAY);
  split(COMMIT[$2],CARRAY);
  printf "%7d txn-%s: total %7.3f %7.3f %7.3f  %s %7.3f %7.3f %7.3f\n",
    $3,TYPE,
    ($5-BARRAY[5])/1000.,($6-BARRAY[6])/1000.,($7-BARRAY[7])/1000.,
    TYPE,
    ($5-CARRAY[5])/1000.,($6-CARRAY[6])/1000.,($7-CARRAY[7])/1000.;
}

BEGIN {
  SSTATUS[5] = "n_messages_received";
  SSTATUS[6] = "n_callback_messages";
  SSTATUS[7] = "n_sectors_callback";
  SSTATUS[8] = "n_sectors_succeeded";
  SSTATUS[9] = "n_sectors_read";
  SSTATUS[10] = "n_sectors_written";
  SSTATUS[11] = "n_deadlocks";
  SSTATUS[12] = "n_lock_timeouts";
  SSTATUS[13] = "n_commits";
  SSTATUS[14] = "n_2_phase_commit";
  SSTATUS[15] = "n_readonly_commits";
  SSTATUS[16] = "n_aborts";
  SSTATUS[17] = "n_2_phase_aborts";
  SSTATUS[18] = "n_notifications_sent";
  SSTATUS[19] = "n_notifications_received";
  SSTATUS[20] = "n_lock_waits";
  SSTATUS[21] = "lock_wait_time";

  EVENT[0] = "version";
  EVENT[1] = "txn-begin";           
  EVENT[2] = "txn-before-commit";   
  EVENT[3] = "txn-after-commit";    
  EVENT[4] = "txn-before-abort";    
  EVENT[5] = "txn-after-abort";     
  EVENT[6] = "txn-before-retry";    
  EVENT[7] = "txn-before-rpc";      
  EVENT[8] = "txn-before-xa";       
  EVENT[9] = "page-fault";          
  EVENT[10] = "page-fetch";         
  EVENT[11] = "page-fault-active";  
  EVENT[12] = "page-return";        
  EVENT[13] = "page-reloc-in";      
  EVENT[14] = "page-reloc-out";     
  EVENT[15] = "page-reloc-fwd";     
  EVENT[16] = "page-commit";        
  EVENT[17] = "page-upgrade";       
  EVENT[18] = "page-deadlock";      
  EVENT[19] = "page-create";        
  EVENT[20] = "db-handle";          
  EVENT[21] = "session-id";         
  EVENT[22] = "realtime-counters-duration";
  EVENT[23] = "realtime-counters-count";
  EVENT[24] = "server-status";
  EVENT[25] = "user";
  EVENT[26] = "realtime-counters-names";
  EVENT[27] = "ncounters-names";
  EVENT[28] = "ncounters-values";

  SEGALLOW  = !index(EXCEPT,"S");
  DBALLOW   = !index(EXCEPT,"D");
  CLUSALLOW = !index(EXCEPT,"C");
}

# event $1 (opcode)
#       $2 (session id)
#       $3 (clock)
{
  EVENT_TYPE = EVENT[$1];
}

# transaction event
#      $4  (txn id)                   
#      $5  (wallclock time)
#      $6  (user cpu time)
#      $7  (system cpu time)
#      $8+ (txn name)
#  EVENT[4] = "txn-before-abort";
#  EVENT[5] = "txn-after-abort";

EVENT_TYPE == "txn-begin" {
  TXN[$2] = $0;
  for (NAME in PAGES) {
    if (index(NAME,$2)) {
      delete PAGES[NAME];
    }
  }
}

EVENT_TYPE == "realtime-counters-names" {

  # Remember the realtime_counter display name.

  for (N = 4; N <= NF; N++) {
    REALTIME[N] = $N;
  }
}

EVENT_TYPE == "ncounters-names" {

  # Remember the n_counter display name.

  for (N = 4; N <= NF; N++) {
    NCOUNTER[N] = $N;
  }
}



EVENT_TYPE == "txn-before-commit" ||
EVENT_TYPE == "txn-before-abort" {
  COMMIT[$2] = $0;
}

EVENT_TYPE == "txn-after-commit" ||
EVENT_TYPE == "txn-after-abort" {

  N = split(TXN[$2],BARRAY);
  if (N >= 8) TXNNAME=BARRAY[N];
  else        TXNNAME="";
  printf "\n%7d txn-begin: [%s] %s\n",BARRAY[3],SESSIONS[$2],TXNNAME;

  dumpCounters();
  dumpTimers(substr(EVENT_TYPE,11));
}


# session id event
#      $4  (time)
#      $5  (session name)
EVENT_TYPE ~ /^session-/ {
  if ($5) {
    SESSIONS[$2] = $5;
  } else {
    SESSIONS[$2] = $2;
  }
}

EVENT_TYPE ~ /server-status/ {
  if (LSVRMETERS[$4]) {
    split(LSVRMETERS[$4],ARRAY);
    split($0,BARRAY);
    for (N=5; N < NF; N++) {
      if (BARRAY[N] - ARRAY[N]) {
	COUNTERS[$2] = sprintf("%s%35s [%s]\t%d\n",COUNTERS[$2],SSTATUS[N],$4,(BARRAY[N]-ARRAY[N]));
      }
    }
    if (BARRAY[N] - ARRAY[N]) {
      COUNTERS[$2] = sprintf("%s%35s [%s]\t%f\n",COUNTERS[$2],SSTATUS[N],$4,(BARRAY[N]-ARRAY[N]));
    }
  } else {
    for (N=5; N < NF; N++) {
      if ($N) {
	COUNTERS[$2] = sprintf("%s%35s [%s]\t%d\n",COUNTERS[$2],SSTATUS[N],$4,$N);
      }
    }
    if ($NF > 0.0) {
      COUNTERS[$2] = sprintf("%s%35s [%s]\t%f\n",COUNTERS[$2],SSTATUS[NF],$4,$NF);
    }
  }
  LSVRMETERS[$4] = $0;
}


EVENT_TYPE == "ncounters-values" {

  # takes the delta between last seen n-counter and current n-counter.
  # This might not make sense for all counters.

  # Output (COUNTERS) only includes those that have changed.

  split(LNCOUNTERS, BARRAY);
  split($0, ARRAY);
  for (I = 4; I <= NF; I++) {
    if ((ARRAY[I] - BARRAY[I]) != 0) {
      COUNTERS[$2] = sprintf("%s%35s %6d\n",COUNTERS[$2],NCOUNTER[I],(ARRAY[I]-BARRAY[I]));
    }
  }
  LNCOUNTERS = $0;
}

EVENT_TYPE == "realtime-counters-duration" {
  # realtime counts taken after each transactions (after commit or after abort).
  if (LRTCOUNT[$2,$1]) {
    LRTCOUNT[$2,0] = LRTCOUNT[$2,$1];
  }
  LRTCOUNT[$2,$1] = $0;
}

EVENT_TYPE == "realtime-counters-count" {
#  if (LRTCOUNT[$2,$1]) {
    split(LRTCOUNT[$2,0],  CARRAY);
    split(LRTCOUNT[$2,22], BARRAY);
    split(LRTCOUNT[$2,23], ARRAY);
    for (I=4 ; I<=38; I++) {
      if ($I != ARRAY[I]) {
	COUNTERS[$2] = sprintf("%s%35s [%d]\t%.4f\n",COUNTERS[$2],REALTIME[I],($I-ARRAY[I]),(BARRAY[I]-CARRAY[I])/1000000.);
      }
    }
#  }
  LRTCOUNT[$2,23] = $0;
}
