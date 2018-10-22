#ifndef vportINCLUDED
#include <vport.h> /* for v*HEADER */
#endif

#ifndef rultagINCLUDED
#define rultagINCLUDED

#ifndef vnameINCLUDED
#include vnameHEADER
#endif


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
	_rultag_EditMenu,
	_rultag_Ruler,
	_rultag_FileMenu,
	_rultag_Dialog,
	_rultag_ListView,
	_rultag_Menu_Bar,
	_rultag_appQUIT,
	_rultagCOUNT
};


#define rultag_EditMenu		 _rultagPredefs[_rultag_EditMenu]
#define rultag_Ruler		 _rultagPredefs[_rultag_Ruler]
#define rultag_FileMenu		 _rultagPredefs[_rultag_FileMenu]
#define rultag_Dialog		 _rultagPredefs[_rultag_Dialog]
#define rultag_ListView		 _rultagPredefs[_rultag_ListView]
#define rultag_Menu_Bar		 _rultagPredefs[_rultag_Menu_Bar]
#define rultag_appQUIT		 _rultagPredefs[_rultag_appQUIT]

/*
 * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * *
 */

extern const vname	 *_rultagPredefs[];

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void rultagInternNames( void ); 

#endif
