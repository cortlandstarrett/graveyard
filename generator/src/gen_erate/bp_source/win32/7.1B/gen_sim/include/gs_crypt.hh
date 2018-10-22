/*========================================================================
 *
 * File:      $RCSfile: gs_crypt.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:16 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 * Purpose:   Defines interface to the archetype encryption routines
 */


#ifndef CRYPT_H_INCLUDED
#define CRYPT_H_INCLUDED

/* Function: Encrypt_Line                                                    */
/* Purpose:  encrypts a null-terminated string into a new null terminated    */
/*           string.  The caller must provide space for the new string. The  */
/*           encrypted string does NOT contain an end-of-line character      */
/*           even if the input string does.                                  */
/*           Length of the output string will be                             */
/*               13 * (15+clear_length div 8)                                */
/*           (not including the zero in either length)                       */
/* Return:   integer: 0 if successful, otherwise returns the required length */
/*           of the output buffer (including the terminating null.)          */
int Encrypt_Line(const char *input_buffer, char *output_buffer, 
                 int output_buffer_length);

/* Function: Decrypt_Line                                                    */
/* Purpose:  Decrypts a null-terminated string into a new null terminated    */
/*           string.  The caller must provide space for the new string. The  */
/*           decrypted string will never be longer the encrypted string.     */
/*           Lines which do not begin .+ are passed through unchanged.       */
/* Return:   void                                                            */

void Decrypt_Line(const char *input_buffer, char *output_buffer);

#endif
