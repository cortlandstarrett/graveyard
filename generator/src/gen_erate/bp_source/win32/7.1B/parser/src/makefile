#==========================================================================
#
# File:      $RCSfile: makefile,v $
# Version:   $Revision: 1.9 $
# Modified:  $Date: 2013/01/10 23:41:20 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#

SOURCE_HOME =	../..

GFILE=al
SCAN = DLGLexer
SOR3FILE=genal
SOR4FILE=sim
PARSERCLASS = P
SOR3CLASS = GEN_SOR
SOR4CLASS = SIM_SOR

SOURCES =	\
		p_check.cc \
		p_ckbase.cc \
		p_ckgendb.cc \
		p_ckosdb.cc \
		p_error.cc \
		p_msgs.cc \
		p_swhere.cc \
		p_symtbl.cc \
		p_tthred.cc \
		sym.cc

CPP_SOURCES = \
		$(GFILE).cpp \
		$(GFILE)_rd.cpp \
		$(PARSERCLASS).cpp \
		$(SCAN).cpp \
		$(SOR3CLASS).cpp \
		$(SOR3FILE).cpp \
		$(SOR3FILE)_rd.cpp \
		$(SOR4FILE).cpp \
		$(SOR4FILE)_rd.cpp \
		$(SOR4FILE)_rd2.cpp \
		$(SOR4FILE)_rd3.cpp \
		$(SOR4FILE)_rd4.cpp \
		$(SOR4FILE)_rd5.cpp \
		AParser.cpp \
		ASTBase.cpp \
		ATokenBuffer.cpp \
		DLexerBase.cpp \
		PCCTSAST.cpp \
		STreeParser.cpp \
		colToken.cpp \
		myAST.cpp \
		myPanic.cpp \
		mySyn.cpp \
		myTokenBuffer.cpp \
		noleakAST.cpp \
		noleakTok.cpp

COMPONENT = PARS

LIBNAME =	lib$(COMPONENT).a

ANTLR_MAKEFILE = mf.pccts
ANTLR_LINKS    = relinkpccts
ANTLR_COMPILE  = bp_build

include		${SOURCE_HOME}/make/leaf.mk
