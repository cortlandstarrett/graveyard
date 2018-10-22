/*========================================================================
 *
 * File:      $RCSfile: p_msgs.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:30 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef P_MSGS_HH
#define P_MSGS_HH

// AL_DEFMSG() macro
// 
//   The AL_DEFMSG() macro is used to define a parser message. There
//   are four parameters to AL_DEFMSG macro:
//     severity  - one of INFO, WARN, ERR, or FAIL
//     seq_no    - three digit sequence number
//     num_parms - number of parameters in the format string
//     msg       - quoted format_string of the form used by printf()
//                 with trailing newline
//   Examples:
//     AL_DEFMSG(ERR, 001, 0,
//       "Keyword --> Self <-- cannot be used in assigner state model.\n")
//     AL_DEFMSG(ERR, 002, 1,
//       "This is a test msg %s\n")
// 
//   The AL_GETMSG() macro is used to get a pointer to a particular
//   parser message.  There are three parameters to the AL_GETMSG()
//   macro, which match exactly with the first three parameters of
//   corresponding AL_DEFMSG() macro:
//     severity  - one of INFO, WARN, ERR, or FAIL
//     seq_no    - three digit sequence number
//     num_parms - number of parameters in the format string
// 
//   The three parameters, severity, id, and num_parms, taken together
//   constitute a unique identifier for each message.  If fact, only
//   one would be enough.  The first two allow us to classify the
//   messages as to severity and give them a sequence number to
//   identify the message for tool users.  The third parameters,
//   num_parms, is there to provide a level of documentation for the
//   definition of the message and the intended usage of the message.
// 
//   The fourth parameter to the AL_DEFMSG() macro is a format string
//   destined for a printf (sprintf) function.  In a format string,
//   one can use %x (x = s, d, etc.) to tell the xprinf() function to
//   substitute parameters for the %x placeholders.  "num_parms" is
//   the number of substition parameters in the format string.

#define PARSE_ERROR_SEVERITY_INFO "info"
#define PARSE_ERROR_SEVERITY_WARN "warn"
#define PARSE_ERROR_SEVERITY_ERR  "err"
#define PARSE_ERROR_SEVERITY_SEV  "fail"

#ifndef P_MSGS_HH_MSGLIST_FILENAME
#define P_MSGS_HH_MSGLIST_FILENAME "p_msglst.hh"
#endif

#define AL_DEFMSG(_sev, _id, _nparms, _msg)           \
  static const char *                                 \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms;

#define AL_DEFMSG1(_sev, _id, _nparms, _msg)          \
  static const char *                                 \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms;

#define AL_DEFMSG2(_sev, _id, _nparms, _m1, _m2)      \
  static const char *                                 \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms;

#define AL_DEFMSG3(_sev, _id, _nparms, _m1, _m2, _m3) \
  static const char *                                 \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms;

class P_messages
{
public:
#include P_MSGS_HH_MSGLIST_FILENAME
};

#ifdef P_MSGS_HH_DEFINE_MSGS

#undef AL_DEFMSG_SEP
#undef AL_DEFMSG
#undef AL_DEFMSG1
#undef AL_DEFMSG2
#undef AL_DEFMSG3

// #define AL_DEFMSG_SEP P_messages::msg_sep
#define AL_DEFMSG_SEP "\n    "

#define AL_DEFMSG(_sev, _id, _nparms, _msg)        \
  AL_DEFMSG1(_sev, _id, _nparms, _msg)

#define AL_DEFMSG1(_sev, _id, _nparms, _m1)        \
  const char *P_messages::                         \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms = \
    "Near line %d col %d ("                        \
    PARSE_ERROR_SEVERITY_ ## _sev                  \
    #_id                                           \
    "): "                                          \
    _m1;

#define AL_DEFMSG2(_sev, _id, _nparms, _m1, _m2)   \
  const char *P_messages::                         \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms = \
    "Near line %d col %d ("                        \
    PARSE_ERROR_SEVERITY_ ## _sev                  \
    #_id                                           \
    "): "                                          \
    _m1                                            \
    AL_DEFMSG_SEP                                  \
    _m2;

#define AL_DEFMSG3(_sev, _id, _nparms, _m1, _m2, _m3)   \
  const char *P_messages::                         \
  AL_parse_msg_ ## _sev ## _id ## _np ## _nparms = \
    "Near line %d col %d ("                        \
    PARSE_ERROR_SEVERITY_ ## _sev                  \
    #_id                                           \
    "): "                                          \
    _m1                                            \
    AL_DEFMSG_SEP                                  \
    _m2                                            \
    AL_DEFMSG_SEP                                  \
    _m3;

#include P_MSGS_HH_MSGLIST_FILENAME

#endif

#define AL_GETMSG(_sev, _id, _nparms)              \
  P_messages::                                     \
  AL_parse_msg_ ## _sev ## _id ## _np ##  _nparms

#undef PARSE_ERROR_SEVERITY_INFO
#undef PARSE_ERROR_SEVERITY_WARN
#undef PARSE_ERROR_SEVERITY_ERR
#undef PARSE_ERROR_SEVERITY_SEV
#undef P_MSGS_HH_DEFINE_MSGS
#undef AL_DEFMSG
#undef AL_DEFMSG1
#undef AL_DEFMSG2
#undef AL_DEFMSG3
#undef AL_DEFMSG_SEP
#undef P_MSGS_HH_MSGLIST_FILENAME

#endif
