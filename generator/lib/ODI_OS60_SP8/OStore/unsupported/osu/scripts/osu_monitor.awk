function handleRollup(NAME)
{
  printf "\tF  [%d+%d+%d]",ROLLUPS[NAME,9],ROLLUPS[NAME,11],ROLLUPS[NAME,17];
  printf "\tS  [%d+%d+%d]",ROLLUPS[NAME,13],ROLLUPS[NAME,14],ROLLUPS[NAME,15];
  printf "\tE  [%d]",ROLLUPS[NAME,12];
  printf "\tR  [%d]",ROLLUPS[NAME,10];
  printf "\tU  [%d+%d]",ROLLUPS[NAME,19],ROLLUPS[NAME,16];
  for (X=9; X<=19;X++) {
    delete ROLLUPS[NAME,X];
  }
  printf "\n";
}

function filename(ID)

{
  filenameN = split(DBS[ID],TARRAY,"[\\/]");
  return TARRAY[filenameN];
}

function handleCluster(CID)
{
  split(CID,XARRAY,"\+");
  _DB = XARRAY[2];
  _SEG = XARRAY[3];
  HEADER = sprintf(" page-cluster: [%s|%d|%d]",filename(_DB),_SEG,XARRAY[4]);
  DBNAME = _DB;
  SEGNAME=sprintf("%s+%s",_DB,_SEG);

  if (CLUSALLOW) {
    printf "\t%-40s",HEADER;
    printf "\tF  [%d+%d+%d]",EVENTX[9],EVENTX[11],EVENTX[17];
    printf "\tS  [%d+%d+%d]",EVENTX[13],EVENTX[14],EVENTX[15];
    printf "\tE  [%d]",EVENTX[12];
    printf "\tR  [%d]",EVENTX[10];
    printf "\tU  [%d+%d]",EVENTX[19],EVENTX[16];
    printf "\n";
  }

  for (X = 9; X <= 19; X++) {

# rollup total count
    ROLLUPS["",X] += EVENTX[X];

# rollup segment count
    if (SEGALLOW) {
      if (!(SEGNAME in SEGMENTS)) {
	NSEGS++;
      }
      SEGMENTS[SEGNAME]++;
      ROLLUPS[SEGNAME,X] += EVENTX[X];
    }

# rollup database count
    if (DBALLOW) {
      if (!(DBNAME in DATABASES)) {
	NDBS++;
      }
      DATABASES[DBNAME]++;
      ROLLUPS[DBNAME,X] += EVENTX[X];
    }
  }
}


function dumpCounters() {
  if (COUNTERS[$2]) {
    printf "%s", COUNTERS[$2];
    delete COUNTERS[$2];
  }
}

function dumpPages() {
  N = 0;
  for (NAME in PAGES) {
    if (index(NAME,$2)) {
      for (I = 0; I < N; I++) {
	if (NAMES[I] > NAME) {
	  TEMP = NAMES[I];
	  NAMES[I] = NAME;
	  NAME = TEMP;
	}
      }
      NAMES[N++] = NAME;
    }
  }
  if (N > 0) {
#
# event counts by cluster
#
    split(NAMES[0],ARRAY,"-");
    CID = ARRAY[1];
    for (X = 9; X <= 19; X++) {
      EVENTX[X] = 0;
    }
    EVENTX[ARRAY[2]] = PAGES[NAMES[0]];

    NSEGS=0;
    NDBS=0;

    for (I = 1; I < N; I++) {
      split(NAMES[I],ARRAY,"-");
      if (CID != ARRAY[1]) {
	handleCluster(CID);
	CID=ARRAY[1];
	for (X=9; X<=19; X++) {
	  EVENTX[X] = 0;
	}
      }
      EVENTX[ARRAY[2]] = PAGES[NAMES[I]];
    }
    handleCluster(CID);

    for (I = 0; I < N; I++) {
      delete NAMES[I];
    }

# NAMES are sorted names of segments.
    if (SEGALLOW) {
      N = 0;
      for (SEGNAME in SEGMENTS) {
	delete SEGMENTS[SEGNAME];
	for (I = 0; I < N; I++) {
	  if (NAMES[I] > SEGNAME) {
	    TEMP = NAMES[I];
	    NAMES[I] = SEGNAME;
	    SEGNAME = TEMP;
	  }
	}
	NAMES[N++] = SEGNAME;
      }

      for (I = 0; I < N; I++) {
	SEGNAME=NAMES[I];
	split(SEGNAME,ARRAY,"\+");
	HEADER = sprintf(" page-segment: [%s|%d]",filename(ARRAY[1]),ARRAY[2]);
	printf "\t%-40s",HEADER;
	handleRollup(SEGNAME);
      }

      for (I = 0; I < N; I++) {
	delete NAMES[I];
      }
    }

# print rollup of database events.

    if (DBALLOW) {
      N = 0;
      for (DBNAME in DATABASES) {
	delete DATABASES[DBNAME];
	for (I = 0; I < N; I++) {
	  if (NAMES[I] > DBNAME) {
	    TEMP = NAMES[I];
	    NAMES[I] = DBNAME;
	    DBNAME = TEMP;
	  }
	}
	NAMES[N++] = DBNAME;
      }

# NAMES are sorted names of databases.
      for (I = 0; I < N; I++) {
	DBNAME=NAMES[I];
	HEADER = sprintf("page-database: [%s]",filename(DBNAME));
	ALLOW = !index(EXCEPT,"D");
	if (ALLOW) printf "\t%-40s",HEADER;
	handleRollup(DBNAME);
      }
      for (I = 0; I < N; I++) {
	delete NAMES[I];
      }
    }

# print rollup of all events in transaction.

    printf "\t%-40s","     page-txn: ";
    handleRollup("");
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
  EVENT[22] = "realtime-counters-1";
  EVENT[23] = "realtime-counters-2";
  EVENT[24] = "server-status";
  EVENT[25] = "user";
  EVENT[26] = "realtime-counters-0";
  EVENT[27] = "ncounters-0";
  EVENT[28] = "ncounters-1";

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

EVENT_TYPE == "realtime-counters-0" {

  # Remember the realtime_counter display name.

  for (N = 4; N <= NF; N++) {
    REALTIME[N] = $N;
  }
}

EVENT_TYPE == "ncounters-0" {

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

  dumpPages();
  dumpCounters();
  if (EVENT_TYPE == "txn-after-commit") {
    dumpTimers("commit");
  } else {
    dumpTimers("abort");
  }

}

# page event
#      $4  (database id)
#      $5  (segment number)
#      $6  (cluster number)
#      $7  (page number)
#      $8  (flag)
#      $9  (number of pages)
EVENT_TYPE ~ /^page-/ {
    CID = sprintf("%s+%s+%07d+%07d-%d",$2,$4,$5,$6,$1);
    PAGES[CID] += $9;
}



# dbhandle event
#      $4  (database id)
#      $5  (database name)
EVENT_TYPE ~ /^db-/ {
  DBS[$4] = $5;
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


EVENT_TYPE == "ncounters-1" {

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

EVENT_TYPE == "realtime-counters-1" {
  # realtime counts taken after each transactions (after commit or after abort).
  if (LRTCOUNT[$2,$1]) {
    LRTCOUNT[$2,0] = LRTCOUNT[$2,$1];
  }
  LRTCOUNT[$2,$1] = $0;
}

EVENT_TYPE == "realtime-counters-2" {
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
