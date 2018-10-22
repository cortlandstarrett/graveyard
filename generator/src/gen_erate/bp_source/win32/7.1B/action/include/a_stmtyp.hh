/*========================================================================
 *
 * File:      $RCSfile: a_stmtyp.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:39 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef AL_STMT_TYPE_HH
#define AL_STMT_TYPE_HH


/*************PLEASE MAINTAIN CURRENT ORDER...ADD NEW TYPES TO END**********/

enum t_statement_type
{
	DONT_CARE				=	0,
	GEN_EVT_TO_SELF			=	1,
	GEN_EVT_TO_REF			=	2,
	GEN_EVT_TO_OBJ_ASSIGNER =	3,
	GEN_EVT_TO_EE			=	4,
	TRANSFORM_STMT_TYPE		=	5,
	BRIDGE_STMT_TYPE		=	6,
	GEN_EVT_TO_CREATOR		=	7,
	GEN_EVT_INSTANCE_VAR	=	8
};

#endif
