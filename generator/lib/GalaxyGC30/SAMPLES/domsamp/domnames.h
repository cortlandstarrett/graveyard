#ifndef domnamesINCLUDED
#define domnamesINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
  _domnames_DomainCoords,
  _domnames_selColorSpec,
  _domnames_Images,
  _domnamesCOUNT
};

#define domnames_DomainCoords	_domnamesPredefs[_domnames_DomainCoords]
#define domnames_selColorSpec	_domnamesPredefs[_domnames_selColorSpec]
#define domnames_Images		_domnamesPredefs[_domnames_Images]

/*
 * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * *
 */

extern const vname	 *_domnamesPredefs[];

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void domnamesInternNames( void ); 

#endif
