/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_COMPACT_HH
#define _OS_COMPACT_HH
#include <ostore/hdrstart.hh>

/* the mother of all compaction exceptions */
_OS_DECLARE_EXCEPTION(_OS_SEVOL, err_os_compaction);

class os_pathname_and_segment_number {
public:
  const char *database_pathname;
  os_unsigned_int32 segment_number;

  os_pathname_and_segment_number(
    const char* db,
    os_unsigned_int32 seg_num);
};

class os_pathname_segment_cluster {
public:
  const char *database_pathname;
  os_unsigned_int32 segment_number;
  os_unsigned_int32 cluster_number;

  os_pathname_segment_cluster(
    const char* db,
    os_unsigned_int32 seg_num,
    os_unsigned_int32 clus_num);
};

class os_compact {
public:
  static void compact(
    const char** dbs_to_be_compacted,
    os_pathname_and_segment_number** segments_to_be_compacted = 0,
    os_pathname_segment_cluster**    clusters_to_be_compacted = 0,
    const char** referencing_dbs = 0,
    os_pathname_and_segment_number** referencing_segments = 0,
    os_pathname_segment_cluster**    referencing_clusters = 0);
};

#include <ostore/hdrend.hh>
#endif /* _OS_COMPACT_HH */
