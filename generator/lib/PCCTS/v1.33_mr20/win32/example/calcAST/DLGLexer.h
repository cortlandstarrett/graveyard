#ifndef DLGLexer_h
#define DLGLexer_h
/*
 * D L G L e x e r  C l a s s  D e f i n i t i o n
 *
 * Generated from: parser.dlg
 *
 * 1989-1999 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR21
 */


#include "DLexerBase.h"

class DLGLexer : public DLGLexerBase {
public:
public:
	static const int MAX_MODE;
	static const int DfaStates;
	static const int START;
	typedef unsigned char DfaState;

	DLGLexer(DLGInputStream *in,
		unsigned bufsize=2000)
		: DLGLexerBase(in, bufsize, 0)
	{
	;
	}
	void	  mode(int);
	ANTLRTokenType nextTokenType(void);
	void     advance(void);
protected:
	ANTLRTokenType act1();
	ANTLRTokenType act2();
	ANTLRTokenType act3();
	ANTLRTokenType act4();
	ANTLRTokenType act5();
	ANTLRTokenType act6();
	ANTLRTokenType act7();
	ANTLRTokenType act8();
	ANTLRTokenType act9();
	ANTLRTokenType act10();
	static DfaState st0[13];
	static DfaState st1[13];
	static DfaState st2[13];
	static DfaState st3[13];
	static DfaState st4[13];
	static DfaState st5[13];
	static DfaState st6[13];
	static DfaState st7[13];
	static DfaState st8[13];
	static DfaState st9[13];
	static DfaState st10[13];
	static DfaState st11[13];
	static DfaState st12[13];
	static DfaState st13[13];
	static DfaState st14[13];
	static DfaState *dfa[15];
	static DfaState dfa_base[];
	static unsigned char *b_class_no[];
	static DfaState accepts[16];
	static DLGChar alternatives[16];
	static ANTLRTokenType (DLGLexer::*actions[11])();
	static unsigned char shift0[257];
	int ZZSHIFT(int c) { return b_class_no[automaton][1+c]; }
//
// 133MR1 Deprecated feature to allow inclusion of user-defined code in DLG class header
//
#ifdef DLGLexerIncludeFile
#include DLGLexerIncludeFile
#endif
};
typedef ANTLRTokenType (DLGLexer::*PtrDLGLexerMemberFunc)();
#endif
