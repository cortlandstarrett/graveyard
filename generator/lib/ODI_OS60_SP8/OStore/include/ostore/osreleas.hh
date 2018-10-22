/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_RELEASE_HH_
#define _OS_RELEASE_HH_

/*
 * OS_PRODUCT_NAME is a non-null character string containing the
 * short form of the name of the product.
 *
 * OS_RELEASE_NAME is a non-null character string containing the word
 * "ObjectStore", a release number (e.g. "2.0" or "1.2.4" and possibly,
 * although not necessarily, a qualifier (e.g. "Beta").  The format of
 * this string is undefined and subject to change.  No parsing of this
 * string should be done.  We reserve the right to make this string
 * contain foreign language characters in the future.
 *
 * OS_RELEASE_STRING only contains the version number of the release
 * in string format.
 *
 * OS_MAJOR_RELEASE is an integer and represents the major release number
 * of ObjectStore.
 *
 * OS_MINOR_RELEASE is an integer and represents the minor release number
 * of ObjectStore.
 *
 * OS_MAINTENANCE_RELEASE is an integer and represents the maintenance
 * release number of ObjectStore.
 *
 * OS_PATCH_RELEASE is a string that denotes the consolidated patch name
 * of the release.  If the release is not a  consolidated patch, the string
 * will be "0" (zero).
 *
 * OS_BETA_RELEASE is an integer and represents the beta release
 * number of ObjectStore.  Zero if this is not a beta release.
 *
 * OS_ALPHA_RELEASE is an integer and represents the alpha release
 * number of ObjectStore.  Zero if this is not a alpha release.
 *
 * OS_RELEASE_CANDIDATE is an integer and represents the RC number
 * of ObjectStore.  Zero if this is not an RC.
 */

#define OS_PRODUCT_NAME "ObjectStore"
#define OS_RELEASE_NAME "ObjectStore Release 6.0 Service Pack 8"
#define OS_RELEASE_STRING "6.0"
#define OS_MAJOR_RELEASE 6
#define OS_MINOR_RELEASE 0
#define OS_MAINTENANCE_RELEASE 8
#define OS_PATCH_RELEASE "0"
#define OS_BETA_RELEASE 0
#define OS_ALPHA_RELEASE 0
#define OS_RELEASE_CANDIDATE 0

#endif	/* _OS_RELEASE_HH_ */



