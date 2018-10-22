#ifndef vportINCLUDED
#include <vport.h> /* for v*HEADER */
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#include "rultag.h"


const vname	 *_rultagPredefs[_rultagCOUNT];
static const char	 *_rultag_predefStrings[] = {
	"EditMenu",
	"Ruler",
	"FileMenu",
	"Dialog",
	"ListView",
	"Menu Bar",
	"appQUIT"
};


void rultagInternNames() 
{
	register int	i;

	for ( i = 0; i < _rultagCOUNT; i++ ) 
		_rultagPredefs[i] = vnameInternGlobalLiteral( _rultag_predefStrings[i] );
}
