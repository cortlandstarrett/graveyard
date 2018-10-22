BEGIN {
  DURATION = 1;
  COUNT = 2;
  OPTION="C";

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
  EVENT[26] = "realtime-counters-name";
  EVENT[27] = "ncounters-name";
  EVENT[28] = "ncounters-count";

  RPC["cluster_size_rpc"]       = "CSIZE";
  RPC["commit_rpc"]             = "COMMIT";
  RPC["create_cluster_rpc"]     = "CCLUS";
  RPC["create_huge_object_rpc"] = "HUGE";
  RPC["create_segment_rpc"]     = "CSGMT";
  RPC["delete_cluster_rpc"]     = "DCLUS";
  RPC["delete_segment_rpc"]     = "DSGMT";
  RPC["mapped_commit_rpc"]      = "MCOMT";
  RPC["mapped_return_rpc"]      = "MRETN";
  RPC["page_rpc"]               = "PAGE";
  RPC["prefetch_rpc"]           = "PREF";
  RPC["return_rpc"]             = "RETRN";
  RPC["upgrade_rpc"]            = "UPGRD";
  RPC["server_side_allocation"] = "SALOC";
  RPC["write_lock_cluster"]     = "WCLUS";
  RPC["write_lock_db"]          = "WDATA";
  RPC["write_lock_seg"]         = "WSGMT";
  RPC["read_lock_cluster"]      = "RCLUS";
  RPC["read_lock_db"]           = "RDATA";
  RPC["read_lock_seg"]          = "RSGMT";
}

{
  EVENT_TYPE = EVENT[$1];
}

EVENT_TYPE == "version" {
# check to make sure that we ran with the right arguments
  if ($5 < 6) {
    printf "this script is designed for R6 or greater.\n";
    printf "%s was run on a %d.%d.SP%d release of ObjectStore\n",FILENAME,$5,$6,$7;
    exit;
  }
  if ($8 !~ /T/) {
    printf "this script can only be run if OSU_MONITOR included TM\n";
    printf "e.g.  export OSU_MONITOR=TM\n";
    exit;
  }
  if ($8 !~ /M/) {
    printf "this script can only be run if OSU_MONITOR included TM\n";
    printf "e.g.  export OSU_MONITOR=TM\n";
    exit;
  }
  # problems doing this in BEGIN.
  if (OPT == "D") {
    OPTION = "D";
  }
}

EVENT_TYPE == "txn-begin" {
  TXNTOP[$2]++;
  TOP = TXNTOP[$2];
  TXNNAME[$2,TOP] = $NF;
  TXNNMSG[$2,TOP]   = NMSGS[$2];
  TXNSTATUS[$2,TOP] = SSTATUS[$2];  #we want to remove svrstatus4 msg
  for (NAMES in RPC) {
    TXNCNTS[$2,TOP,NAMES] = THROUGHPUT[$2,COUNT,NAMES];
    TXNDURS[$2,TOP,NAMES] = THROUGHPUT[$2,DURATION,NAMES];
  }
}


EVENT_TYPE ~ /txn-after/ {
  TXNTOP[$2]--;
}

#
# Messages not accounted for in REALTIME counters
#   . ping_proc
#   . hello
#   . open_db (...)
#   . create_db
#   . get_db_path
#   . disown
#   . something else from a nested transaction?

EVENT_TYPE == "server-status" {
#increment number of server_status4 msgs
  SSTATUS[$2]++;
  TOP=TXNTOP[$2];
  LMSGS = $5 - TXNNMSG[$2,TOP];
#correct for number of server_status4 msgs
  LMSGS = LMSGS - (SSTATUS[$2] - TXNSTATUS[$2,TOP]);

  NMSGS[$2] = $5;
  TOTAL = 0;
  for (NAMES in RPC) {
    TOTAL = TOTAL+THROUGHPUT[$2,COUNT,NAMES] - TXNCNTS[$2,TOP,NAMES];
  }

# write output to a string buffer.  We'll output at end of script
# on a per session basis.

  TABLE[$2] = TABLE[$2] sprintf ("%2d %15s %5d %5d ",TOP,substr(TXNNAME[$2,TOP],1,15),LMSGS,LMSGS - TOTAL);

  if (OPTION == "C") {
    for (NAMES in RPC) {
      TABLE[$2] = TABLE[$2] sprintf("%5d ",THROUGHPUT[$2,COUNT,NAMES] - TXNCNTS[$2,TOP,NAMES])
    }
    TABLE[$2] = TABLE[$2] sprintf("\n");
  } else {
    for (NAMES in RPC) {
      TABLE[$2] = TABLE[$2] sprintf("%5.3f ",(THROUGHPUT[$2,DURATION,NAMES] - TXNDURS[$2,TOP,NAMES])/1000000.);
    }
    TABLE[$2] = TABLE[$2] sprintf("\n");
  }
}

EVENT_TYPE == "realtime-counters-name" {

# Remember the realtime_counter display name.

  TABLE[$2] = sprintf("%2s %15s %5s %5s ","","txnname","nmsgs","nacct");
  for (NAMES in RPC) {
    TABLE[$2] = TABLE[$2] sprintf("%5s ",RPC[NAMES]);
  }
  TABLE[$2] = TABLE[$2] sprintf("\n");
  for (N = 4; N <= NF; N++) {
    REALTIME[N] = $N;
  }
}


EVENT_TYPE == "realtime-counters-duration" {
  for (N = 4; N <= NF; N++) {
    if (REALTIME[N] in RPC) {
      THROUGHPUT[$2,DURATION,REALTIME[N]] = $N;
    }
  }
}

EVENT_TYPE == "realtime-counters-count" {
  for (N = 4; N <= NF; N++) {
    if (REALTIME[N] in RPC) {
      THROUGHPUT[$2,COUNT,REALTIME[N]] = $N;
    }
  }
}

END {
  for (N in TABLE) {
    printf "Realtime ";
    if (OPTION == "C") {
      printf "counts of server calls for session [%s]\n",N;
    }  else {
      printf "times of server calls for session [%s]\n",N;
    }
    printf "%s\n",TABLE[N];
  }
}
