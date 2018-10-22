#ifndef genINCLUDED
#define genINCLUDED

#ifndef vportINCLUDED
#include <vport.h> /* for v*HEADER */
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
	_generated_CALC_ADD_BUTTON,
	_generated_CALC_RESULT_LABEL,
	_generated_CALC_OP1_LABEL,
	_generated_CALC_MULT_BUTTON,
	_generated_CALC_OP1,
	_generated_CALC_OP2,
	_generated_CALC_RESULT,
	_generated_Dialog,
	_generated_CALC_OP2_LABEL,
	_generatedCOUNT
};


#define generated_CALC_ADD_BUTTON		 _generatedPredefs[_generated_CALC_ADD_BUTTON]
#define generated_CALC_RESULT_LABEL		 _generatedPredefs[_generated_CALC_RESULT_LABEL]
#define generated_CALC_OP1_LABEL		 _generatedPredefs[_generated_CALC_OP1_LABEL]
#define generated_CALC_MULT_BUTTON		 _generatedPredefs[_generated_CALC_MULT_BUTTON]
#define generated_CALC_OP1		 _generatedPredefs[_generated_CALC_OP1]
#define generated_CALC_OP2		 _generatedPredefs[_generated_CALC_OP2]
#define generated_CALC_RESULT		 _generatedPredefs[_generated_CALC_RESULT]
#define generated_Dialog		 _generatedPredefs[_generated_Dialog]
#define generated_CALC_OP2_LABEL		 _generatedPredefs[_generated_CALC_OP2_LABEL]

/*
 * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * *
 */

extern const vname	 *_generatedPredefs[];

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void generatedInternNames( void ); 

#endif
