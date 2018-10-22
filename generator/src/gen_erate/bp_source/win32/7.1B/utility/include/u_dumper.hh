/*========================================================================
 *
 * File:      $RCSfile: u_dumper.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
// This header declares the special dump function(s);

// Function for external caller
void dump_special1();

// Used by dump_special1()
void special_dumper();

// For use by external caller and used by dump_special()
void dump_core(void *mem, int size, const char *tag = 0, const char *indent = 0);





