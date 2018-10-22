//
//  simple.g
//
//  Simple project for Dev Studio
//
//    Use every default
//
//       No AST options
//       Default token
//       No column counting
//
//  pccts 1.33MR15
//


/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

<<
#include "AToken.h"
#include "DLGLexer.h"

typedef ANTLRCommonToken ANTLRToken;

int main() {

   fprintf(stdout,"A Simple Dev Studio Project for pccts 1.33mr15 - Version 3-Oct-1998\n"); 
   fprintf(stdout,"For use with Microsoft MSVC 5.0\n");
   fprintf(stdout,"\n");
   fprintf(stdout,"Sample input file in \"test.dat\"\n");
   fprintf(stdout,"\n");

   DLGFileInput		in(stdin);
   DLGLexer			lexer(&in,2000);
   ANTLRTokenBuffer	pipe(&lexer,1);
   ANTLRToken		aToken;
   P				parser(&pipe);

   lexer.setToken(&aToken);
   parser.init();
   parser.statement();
   fclose(stdin);
   fclose(stdout);
   return 0;
}
>>

#token	Eof	"@"

#token  Number		"[0-9]+"
#token  Word		"[a-z A-Z]+"
#token  Whitespace  "[\t \ \f]"		<<skip(); >>
#token  Other	    "~[\ \t \n \r \f]+"
#token  Newline		"\n|\r|\n\r"	<<newline(); skip(); >>

class P {

statement : 
		  (	n:Number	<<fprintf(stdout,"Number: %s\n",$n->getText()); >>
		  | w:Word		<<fprintf(stdout,"Word: %s\n",$w->getText()); >>
		  | o:Other     <<fprintf(stdout,"Other: %s\n",$o->getText()); >>
		  )*
		  Eof
		  ;
}
