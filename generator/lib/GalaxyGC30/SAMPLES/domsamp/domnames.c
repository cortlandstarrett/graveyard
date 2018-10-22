#include <vport.h>

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#include "domnames.h"

const vname		*_domnamesPredefs[_domnamesCOUNT];
static const char	*_domnames_predefStrings[] = {
  "DomainCoords",
  "selColorSpec",
  "Images"
};

void domnamesInternNames(void)
{
  register int i;

  for (i = 0; i < _domnamesCOUNT; i++)
    _domnamesPredefs[i] = vnameInternGlobalLiteral(_domnames_predefStrings[i]);
}
