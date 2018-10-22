/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef __AF_MISC__
#define __AF_MISC__

/******************************************************************************
Class Name      : Segments_and_Clusters
Description     : Describes a segment & the associated clusters that are
                : managed by an Extended allocator. A persistent allocator
		: contains one such struct to indicate the segment & the
		: clusters in each segment it manages.
Remarks         : 
******************************************************************************/

typedef struct Segments_and_Clusters
{
  os_unsigned_int32               af_segment_number;
  os_Array<os_unsigned_int32 *> * af_clusters;
} SegmentClusterList;


/* Traits currently handled */

#define DB_ALLOC_PATHNAME_TRAIT "Database Path"
#define DB_MAX_CLUSTER_SIZE_TRAIT "Max Cluster Size"
#define DB_MAX_SEGS_PER_DB_TRAIT "Max Segments per DB"
#define DB_MAX_CLUSTERS_PER_SEG_TRAIT "Max Clusters per Segment"

//  Default values for some Traits

#define MAX_SEGMENTS 2
#define MAX_CLUSTERS 1
#define MAX_CLUSTER_SIZE 0x80000000 /* 2Gb */

#endif















