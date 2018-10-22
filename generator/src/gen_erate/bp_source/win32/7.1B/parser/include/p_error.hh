/*========================================================================
 *
 * File:      $RCSfile: p_error.hh,v $
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
#ifndef P_ERROR_HH
#define P_ERROR_HH

#include <vstdarg.h>
#include <vchar.h>

#include "p_types.hh"    // typedef bool
#include "config.h"      // TRUE, FALSE

class P_error
{
public:
  P_error():
    number_errors(0),
    first_error_linenum(0),
    first_error_start(0),
    first_error_end(0),
    error_this_stmt(FALSE),
    lng_error_messages(0),
    status(OK)
    {
      error_messages = new vchar[PRINTBUFSIZE];
      error_messages[0] = '\0';
    }
  ~P_error()
  {
    delete [] error_messages;
  }
  void no_stmt_error() { error_this_stmt = FALSE; }
  bool is_stmt_error() { return error_this_stmt; }
  void severe_error( const char *msg, ... );
  void no_error()
    {
      number_errors = 0;
      no_stmt_error();
    }
  int error_count() { return number_errors; }
  void stmt_error( long int linenum,
                   long int start,
                   long int end,
                   const char *fmtstr, ... );
  void print_string( const char *fmtstr, ... );

  long int get_first_error_linenum()
    { return first_error_linenum; }

  void get_first_error_location( long int &p_bad_line_num,
                                 long int &p_err_start,
                                 long int &p_err_end )
    {
      p_bad_line_num = first_error_linenum;
      p_err_start = first_error_start;
      p_err_end = first_error_end;
    }

  const vchar *get_error_messages()
    { return error_messages; }
private:
  void vprint_string( va_list *ap, const char *fmtstr );
  enum status_e
  { OK,
    PRINTBUFFULL,
    PRINTERROR
  };
  enum
  { PRINTBUFSIZE = 10000,
    PRINTBUFLIMIT = 200
  };
  int number_errors;
  long int first_error_linenum;
  long int first_error_start;
  long int first_error_end;
  bool error_this_stmt;
  int lng_error_messages;
  status_e status;
  vchar *error_messages;
};

#undef AL_error

#define AL_PARSE_ERR0(p_ast, format_str)                         \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn() ); }

#define AL_PARSE_ERR1(p_ast, format_str,                         \
                      p1)                                        \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1 ); }

#define AL_PARSE_ERR2(p_ast, format_str,                         \
                      p1, p2)                                    \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2 ); }

#define AL_PARSE_ERR3(p_ast, format_str,                         \
                      p1, p2, p3)                                \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3 ); }

#define AL_PARSE_ERR4(p_ast, format_str,                         \
                      p1, p2, p3, p4)                            \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3, p4 ); }

#define AL_PARSE_ERR5(p_ast, format_str,                         \
                      p1, p2, p3, p4, p5)                        \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3, p4, p5 ); }

#define AL_PARSE_ERR6(p_ast, format_str,                         \
                      p1, p2, p3, p4, p5, p6)                    \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3, p4, p5, p6 ); }

#define AL_PARSE_ERR7(p_ast, format_str,                         \
                      p1, p2, p3, p4, p5, p6, p7)                \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3, p4, p5, p6, p7 ); }

#define AL_PARSE_ERR8(p_ast, format_str,                         \
                      p1, p2, p3, p4, p5, p6, p7, p8)            \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3, p4, p5, p6, p7, p8 ); }

#define AL_PARSE_ERR9(p_ast, format_str,                         \
                      p1, p2, p3, p4, p5, p6, p7, p8, p9)        \
  {if (p_ast)                                                    \
  er->stmt_error( p_ast->getLine(),                              \
                  p_ast->getOffset(),                            \
                  p_ast->getOffset() + p_ast->getSegLength(),    \
                  format_str,                                    \
                  p_ast->getLine(),                              \
                  p_ast->getColumn(),                            \
                  p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }

#define AL_MSG_STR                                               \
  er->print_string

#endif
