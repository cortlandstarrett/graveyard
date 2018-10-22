/* $Id: spcellop.h,v 1.1 1994/11/21 01:06:27 chad Exp $ */
/*
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/* 
 * spcellop.h -- Header file for the spreadsheet cell operations.  
 *
 * See the file spread.c for more information.
 */

#define ADD_SELECTION           1
#define MULTIPLY_SELECTION      2
#define ESCALATE_SELECTION      3

extern long lastEscalationRate;
extern long lastMultiplyValue;
extern long lastAddValue;

