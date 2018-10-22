BEGIN {
  DURATION = 1;
  COUNT = 2;
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

  RELOC["reloc_page_forward"]   = "RPF";
  RELOC["reloc_page_in"]        = "RPI";
  RELOC["reloc_page_out"]       = "RPO";
  RELOC["reloc_page_scan"]      = "RPS";
  RELOC["reloc_page_sp_conditional_decache"] = "RPSCD";
  RELOC["reloc_page_sp_resolve"]= "RPSR";
  RELOC["reloc_page_spm_gc"]    = "RPSG";

# try to guess which counters are non-inclusive.

  OSTORE["reloc_page_sp_conditional_decache"] = 1;
  OSTORE["reloc_page_sp_resolve"]             = 1;
  OSTORE["reloc_page_spm_gc"]                 = 1;
  OSTORE["allocate_huge_object"]              = 1;
  OSTORE["allocate_normal_object"]            = 1;
  OSTORE["delete_huge_object"]                = 1;
  OSTORE["delete_normal_object"]              = 1;
  OSTORE["signal"]                            = 1;
  OSTORE["cluster_size_rpc"]                  = 1;
  OSTORE["create_cluster_rpc"]                = 1;
  OSTORE["create_segment_rpc"]                = 1;
  OSTORE["delete_cluster_rpc"]                = 1;
  OSTORE["delete_segment_rpc"]                = 1;
#  OSTORE["write_lock_cluster"]                = 1;
#  OSTORE["write_lock_db"]                     = 1;
#  OSTORE["write_lock_seg"]                    = 1;
#  OSTORE["read_lock_cluster"]                 = 1;
#  OSTORE["read_lock_db"]                      = 1;
#  OSTORE["read_lock_seg"]                     = 1;

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
}

EVENT_TYPE == "txn-begin" {
  TOP++;
  TOPTXN[$2]++;
  TOP = TOPTXN[$2];
  TXNNAME[$2,TOP] = $NF;
  TIMES[$2,TOP,1] = $5+$6;     #CPU usage at beginning of txn
  TIMES[$2,TOP,2] = $7;        #time txn started
  TIMES[$2,TOP,5] = TIMERS[$2,1]; #time spent at server
  TIMES[$2,TOP,6] = TIMERS[$2,2]; #time spent in reloc
  TIMES[$2,TOP,7] = LLOCK[$2];     #time spent in lock wait at server
  TIMES[$2,TOP,8] = TIMERS[$2,3]; #time spent in ostore?

}


# 4
# 5
# 6
EVENT_TYPE ~ /txn-before-(commit|abort)/ {
  TOP = TOPTXN[$2];
  TIMES[$2,TOP,3] = $5+$6; #CPU usage just before txn end
  TIMES[$2,TOP,4] = $7;    #time just before txn end
}


EVENT_TYPE ~ /txn-after/ {
  TOP = TOPTXN[$2];
  CPU   = ($5+$6 - TIMES[$2,TOP,1])/1000.;      #CPU during txn
  TOTAL = ($7 - TIMES[$2,TOP,2])/1000.;         #time spent in txn
  TIMES[$2,TOP,3] = $5+$6 - TIMES[$2,TOP,3];       #CPU usage during commit
  COMMIT = ($7 - TIMES[$2,TOP,4])/1000.;        #time spent doing commit
  SERVER = (TIMERS[$2,1] - TIMES[$2,TOP,5])/1000.; #time spent at server during txn
  TRELOC = (TIMERS[$2,2] - TIMES[$2,TOP,6])/1000.; #time spent in reloc during txn
  LOCKW = (LLOCK[$2] - TIMES[$2,TOP,7]);      #time spent in lock wait at server
  TOSTORE = (TIMERS[$2,3] - TIMES[$2,TOP,8])/1000. + COMMIT; #time spent in ostore?
  if (TABLE[$2] == 0) {
    TABLE[$2] = sprintf("%2s   %4s    %6s   %15s   %11s   %11s   %11s   %11s\n",
      "#","wall","cpu","ostore","server","commit","reloc","lockw");
  }
  TABLE[$2] = TABLE[$2] sprintf("%2d %5.2f   ",TOP,TOTAL);
  if (TOTAL == 0) TOTAL = 1;
  TABLE[$2] = TABLE[$2] sprintf(" %5.2f [%%%02d]   ",CPU,CPU*100/TOTAL);
  TABLE[$2] = TABLE[$2] sprintf(" %5.2f [%%%02d]   ",TOSTORE,TOSTORE*100/TOTAL);
  TABLE[$2] = TABLE[$2] sprintf(" %5.2f [%%%02d]   ",SERVER,SERVER*100/TOTAL);
  TABLE[$2] = TABLE[$2] sprintf(" %5.2f [%%%02d]   ",COMMIT,COMMIT*100/TOTAL);
#  printf " %5.2f [%%%02d]   ",OTHER,OTHER*100/TOTAL;
#  printf " %5.2f [%%%02d]  ",CLIENT,CLIENT*100/TOTAL;
#  printf " %5.2f [%%%02d]  ",UNACCOUNT,UNACCOUNT*100/TOTAL;
  TABLE[$2] = TABLE[$2] sprintf(" %5.2f [%%%02d]",TRELOC,TRELOC*100/TOTAL);
  TABLE[$2] = TABLE[$2] sprintf(" %5.2f [%%%02d]",LOCKW,LOCKW*100/TOTAL);
  TABLE[$2] = TABLE[$2] sprintf("\n");
  TOPTXN[$2]--;
}

#
# Messages not accounted for in REALTIME counters
#   . ping_proc
#   . hello
#   . open_db (...)
#   . create_db
#   . get_db_path
#   . something else from a nested transaction?

EVENT_TYPE == "server-status" {
  LLOCK[$2] = $NF;
}

EVENT_TYPE == "realtime-counters-name" {

# Remember the realtime_counter display name.

  for (N = 4; N <= NF; N++) {
    REALTIME[N] = $N;
  }
}


EVENT_TYPE == "realtime-counters-duration" {
  TIMERS[$2,1] = 0;
  TIMERS[$2,2] = 0;
  TIMERS[$2,3] = 0;
  for (N = 4; N <= NF; N++) {
    if (REALTIME[N] in RPC) {
      TIMERS[$2,1] += $N/1000;
    }
    if (REALTIME[N] in RELOC) {
      TIMERS[$2,2] += $N/1000;
    }
    if (REALTIME[N] in OSTORE) {
      TIMERS[$2,3] += $N/1000;
    }
  }
}

END {
  for (N in TABLE) {
    printf "%s\n",TABLE[N];
  }
}
