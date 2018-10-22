/*========================================================================
 *
 * File:      $RCSfile: p_msglst.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:31 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */

// This file in included by p_msgs.hh.  Do NOT put an #ifndef around the
// body of this file.  It is allowed to be included and scanned twice at
// file scope, once to generate declarations, and once to generate definitions.
// In fact, p_msgs.hh does just that if the intention is to define the
// message variables.

// This is a list of messages which use the AL_DEFMSG() macro.  The results
// of including this file differ depending on which version of AL_DEFMSGx()
// is defined.  See p_msgs.hh for usage of the AL_DEFMSGx() macro.

// This is the full list of parser messages:

//---------------------------------------------------------------
// INFO messages:
//---------------------------------------------------------------

//---------------------------------------------------------------
// WARN messages:
//---------------------------------------------------------------

//---------------------------------------------------------------
// ERR messages:
//---------------------------------------------------------------

// CONTROL LOGIC  001-019

AL_DEFMSG1(ERR, 001, 0,
           "END statement found without corresponding beginning.\n")

AL_DEFMSG1(ERR, 002, 0,
           "ELSE statement must be contained in IF block.\n")

AL_DEFMSG1(ERR, 003, 0,
           "END FOR statement must terminate FOR EACH block.\n")

AL_DEFMSG1(ERR, 004, 0,
           "END IF statement must terminate IF block.\n")

AL_DEFMSG1(ERR, 005, 1,
           "Expression within %s statement does not yield boolean result.\n")

AL_DEFMSG1(ERR, 006, 0,
           "Statement block is not properly terminated with END statement.\n")

AL_DEFMSG1(ERR, 007, 0,
           "ELIF statement must be contained in IF block.\n")

AL_DEFMSG1(ERR, 008, 0,
           "END WHILE statement must terminate WHILE block.\n")

AL_DEFMSG1(ERR, 009, 0,
           "Break statement can only be used in WHILE and FOR EACH block.\n")

AL_DEFMSG1(ERR, 010, 0,
           "Continue statement can only be used in WHILE and FOR EACH block.\n")

AL_DEFMSG1(ERR, 011, 0,
           "FOR EACH block not properly terminated with END statement.\n")

AL_DEFMSG1(ERR, 014, 0,
           "Expression within If statement does not yield boolean result.\n")

AL_DEFMSG1(ERR, 015, 0,
           "Expression within Elif statement does not yield boolean result.\n")

AL_DEFMSG1(ERR, 016, 0,
           "Expression within While statement does not yield boolean result.\n")

AL_DEFMSG1(ERR, 017, 0,
           "Expression within Select Where clause does not yield boolean result.\n")

AL_DEFMSG1(ERR, 018, 0,
           "Expression within Where Spec clause does not yield boolean result.\n")

// REDUNDANT  020-039

AL_DEFMSG2(ERR, 020, 1,
           "More than one event with label ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG2(ERR, 021, 1,
           "More than one external entity with key letters ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG3(ERR, 022, 1,
           "More than one external entity with",
           "name ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG2(ERR, 023, 1,
           "More than one object with key letters ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG2(ERR, 024, 1,
           "More than one relationship with number ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

// SCOPE  040-059

AL_DEFMSG2(ERR, 041, 1,
           "Variable ->%s<- does not exist in",
           "scope as an object instance variable.\n")

AL_DEFMSG2(ERR, 042, 1,
           "Variable ->%s<- must be in current",
           "scope and per instance.\n")

AL_DEFMSG2(ERR, 043, 1,
           "Token ->%s<- must be a variable in",
           "current scope and per instance, or be external entity keyletters.\n")

AL_DEFMSG2(ERR, 044, 1,
           "Variable ->%s<- used in context",
           "where it must already exist.\n")

// EVENTS  060-099

AL_DEFMSG1(ERR, 060, 1,
           "Cannot find event for event label ->%s<-.\n")

AL_DEFMSG2(ERR, 061, 2,
           "Cannot find event for event label ->%s<-",
           "associated with object ->%s<-.\n")

AL_DEFMSG2(ERR, 062, 2,
           "Cannot find event for event label ->%s<-",
           "for external entity ->%s<-.\n")

// This won't be used because keyletters are validated in validate_obj_kl
AL_DEFMSG2(ERR, 063, 1,
           "Cannot find specified object key letters ->%s<-",
           "to send event to assigner.\n")

// This won't be used because keyletters are validated in validate_obj_kl
AL_DEFMSG2(ERR, 064, 1,
           "Cannot find specified object key letters ->%s<-",
           "to send event to creator.\n")

AL_DEFMSG2(ERR, 065, 2,
           "Event ->%s<- does not exist for",
           "assigner state model of object ->%s<-.\n")

AL_DEFMSG2(ERR, 066, 2,
           "Event ->%s<- is not a creation",
           "transition for object ->%s<-.\n")

AL_DEFMSG2(ERR, 067, 1,
           "Event ->%s<- is an external entity",
           "event, not a state model event.\n")

AL_DEFMSG2(ERR, 068, 1,
           "Event ->%s<- is not associated",
           "with this state model.\n")

AL_DEFMSG2(ERR, 069, 2,
           "Event meaning ->%s<- is not",
           "associated with event label ->%s<-.\n")

AL_DEFMSG2(ERR, 070, 1,
           "Event with label ->%s<- exists but",
           "has not been assigned to any state transitions.\n")

AL_DEFMSG2(ERR, 071, 1,
           "External entity event with label ->%s<-",
           "is missing corresponding data items.\n")

AL_DEFMSG2(ERR, 072, 1,
           "State model event with label ->%s<-",
           "has redundant supplemental data items.\n")

AL_DEFMSG2(ERR, 073, 1,
           "State model event with label ->%s<-",
           "is missing some supplemental data items.\n")

AL_DEFMSG2(ERR, 074, 2,
           "Supplemental data item ->%s<- is not associated",
           "with event ->%s<-.\n")

AL_DEFMSG1(ERR, 075, 0,
           "Cannot assign a value to received event data.\n")

AL_DEFMSG1(ERR, 076, 0,
           "Event is a polymorphic event. Event label must contain '*'.\n")

AL_DEFMSG1(ERR, 077, 0,
           "Event is not a polymorphic event. Event label must not contain '*'.\n")

// EXTERNAL ENTITIES  100-119

AL_DEFMSG1(ERR, 100, 1,
           "Cannot find specified external entity with key letters ->%s<-.\n")

AL_DEFMSG2(ERR, 101, 1,
           "External entity ->%s<- does not",
           "exist.\n")

AL_DEFMSG2(ERR, 102, 2,
           "External entity ->%s<- is not",
           "associated with event ->%s<-.\n")

AL_DEFMSG1(ERR, 103, 2,
           "Cannot locate transformer or bridge ->%s:%s<-.\n")

// OBJECTS/INSTANCES/ATTRIBUTES  120-149

AL_DEFMSG2(ERR, 120, 1,
           "Attempting to delete an object with uninitialized",
           "instance variable ->%s<-.\n")

AL_DEFMSG2(ERR, 121, 1,
           "Attribute ->%s<- has not been",
           "data typed yet.\n")

AL_DEFMSG2(ERR, 122, 1,
           "Cannot assign to a referential",
           "attribute ->%s<-.\n")

AL_DEFMSG1(ERR, 123, 1,
           "Cannot find specified object key letters ->%s<-.\n")

AL_DEFMSG2(ERR, 124, 2,
           "Object ->%s<- does not contain",
           "attribute ->%s<-.\n")

AL_DEFMSG2(ERR, 125, 2,
           "Object ->%s<- does not have an instance state model",
           "to be associated with event label ->%s<-.\n")

AL_DEFMSG2(ERR, 126, 1,
           "Object ->%s<- does not have an instance state model",
           "to send creation event to.\n")

AL_DEFMSG2(ERR, 127, 3,
           "Object ->%s<- referenced by variable ->%s<-",
           "does not contain attribute ->%s<-.\n")

AL_DEFMSG2(ERR, 128, 3,
           "Object ->%s<- referenced by variable ->%s<-",
           "does not receive event ->%s<-.\n")

AL_DEFMSG1(ERR, 129, 0,
           "Cannot assign to the current_state attribute")

AL_DEFMSG2(ERR, 130, 1,
           "Cannot assign to a derived",
           "attribute ->%s<-.\n")

// STATES  150-169

AL_DEFMSG1(ERR, 151, 1,
           "Object ->%s<- does not have an assigner state model.\n")

AL_DEFMSG2(ERR, 152, 1,
           "Supplemental data item ->%s<-",
           "is not associated with received event.\n")

AL_DEFMSG1(ERR, 153, 1,
           "Supplemental data item ->%s<- is not received by this state.\n")

AL_DEFMSG1(ERR, 154, 0,
           "Keyword ->Selected<- cannot be used outside a where expression.\n")

AL_DEFMSG1(ERR, 155, 0,
           "Keyword ->Selected<- must be referenced inside a where expression.\n")

AL_DEFMSG1(ERR, 156, 1,
           "Keyword ->Self<- cannot be used in %s AL specifications.\n")

AL_DEFMSG1(ERR, 157, 1,
           "Supplemental data item ->%s<- belongs to a Polymorphic Event that is no longer defined in supertype.\n")

// RELATIONSHIP  170-199

AL_DEFMSG2(ERR, 170, 0,
           "A destination relationship phrase is not allowed for a supertype/subtype",
           "relationship specification within an instance chain.\n")

AL_DEFMSG2(ERR, 171, 0,
           "At least one relationship has a right object with multiplicity of many.",
           "With SELECT ONE, all right objects must have multiplicity of one.\n")

AL_DEFMSG2(ERR, 172, 1,
           "Cannot find specified object key letters ->%s<-",
           "in relationship chain.\n")

AL_DEFMSG1(ERR, 173, 1,
           "Cannot find specified relationship ->R%s<-.\n")

AL_DEFMSG2(ERR, 174, 1,
           "Cannot find specified relationship ->R%s<-",
           "in relationship chain.\n")

AL_DEFMSG2(ERR, 176, 1,
           "Need USING clause when RELATEing associative objects",
           "in relationship ->R%s<-.\n")

AL_DEFMSG2(ERR, 177, 0,
           "No right object has multiplicity of many.",
           "With SELECT ANY, at least one object must have multiplicity of many.\n")

AL_DEFMSG2(ERR, 178, 0,
           "No right object has multiplicity of many.",
           "With SELECT MANY, at least one object must have multiplicity of many.\n")

AL_DEFMSG2(ERR, 179, 4,
           "Object ->%s<- does not exist as the associative object between",
           "objects ->%s<- and ->%s<- in associative relationship ->R%s<-.\n")

AL_DEFMSG1(ERR, 180, 2,
           "Object ->%s<- does not participate in the associative relationship ->R%s<-.\n")

AL_DEFMSG2(ERR, 181, 3,
           "Object ->%s<- in reflexive relationship ->R%d<-",
           "does not contain destination relationship phrase ->%s<-.\n")

AL_DEFMSG2(ERR, 182, 3,
           "Object ->%s<- in relationship ->R%d<-",
           "does not contain destination relationship phrase ->%s<-.\n")

AL_DEFMSG2(ERR, 183, 2,
           "Object ->%s<- is incorrectly specified in associative",
           "relationship ->R%s<-.\n")

AL_DEFMSG1(ERR, 184, 1,
           "Relationship ->R%s<- is not associative.\n")

AL_DEFMSG2(ERR, 185, 3,
           "The destination relationship phrase must be specified for",
           "reflexive relationship ->R%d<- between objects ->%s<- and ->%s<-.\n")

AL_DEFMSG2(ERR, 186, 3,
           "The specified relationship ->R%d<- does not exist between",
           "objects ->%s<- and ->%s<-.\n")

AL_DEFMSG2(ERR, 187, 0,
           "At least one right object has multiplicity of many.",
           "With instance references, no objects may have a multiplicity of many.\n")

AL_DEFMSG2(ERR, 188, 1,
           "Instance reference set variable ->%s<- cannot be",
           "used with SELECT ONE.\n")

AL_DEFMSG2(ERR, 189, 0,
           "SELECT ONE cannot be used with FROM INSTANCES OF.",
           "Use SELECT ANY or SELECT MANY.\n")

AL_DEFMSG2(ERR, 190, 3,
           "The objects ->%s<- and ->%s<- are subtype",
           "objects in the relationship ->R%d<-.\n")

// TRANSFORMERS, SYNCHRONOUS SERVICES, AND BRIDGES   200-259

AL_DEFMSG1(ERR, 200, 2,
           "Parameter ->%s<- is not associated with service ->%s<-.\n")

AL_DEFMSG1(ERR, 201, 1,
           "Service ->%s<- is missing corresponding parameter(s).\n")

AL_DEFMSG1(ERR, 202, 1,
           "Service ->%s<- has redundant parameters.\n")

AL_DEFMSG1(ERR, 203, 2,
           "Parameter ->%s<- is not associated with service ->%s<-.\n")

AL_DEFMSG2(ERR, 220, 2,
           "Bridge ->%s<- for external entity ->%s<-",
           "has not been assigned return type.\n")

AL_DEFMSG2(ERR, 221, 2,
           "Bridge ->%s<- for external entity ->%s<-",
           "is missing corresponding parameters.\n")

AL_DEFMSG1(ERR, 222, 1,
           "Bridge ->%s<- has more actual parameters than specified.\n")

AL_DEFMSG2(ERR, 223, 2,
           "Bridge ->%s::%s<- has no return type (return type is void)",
           "and thus cannot be used in an expression.\n")

AL_DEFMSG1(ERR, 224, 1,
           "Bridge ->%s<- has not been given a return type.\n")

AL_DEFMSG2(ERR, 225, 2,
           "Bridge ->%s::%s<- has a return type which is not",
           "being assigned to a variable.\n")

AL_DEFMSG2(ERR, 226, 2,
           "Cannot find specified bridge ->%s<-",
           "for external entity ->%s<-.\n")

AL_DEFMSG2(ERR, 227, 2,
           "Cannot find specified transformer ->%s<-",
           "for object ->%s<-.\n")

AL_DEFMSG1(ERR, 228, 2,
           "Parameter ->%s<- is not associated with bridge ->%s<-.\n")

AL_DEFMSG1(ERR, 229, 2,
           "Parameter ->%s<- is not associated with transformer ->%s<-.\n")

AL_DEFMSG2(ERR, 230, 2,
           "Transformer ->%s<- for object ->%s<-",
           "has not been assigned return type.\n")

AL_DEFMSG1(ERR, 231, 1,
           "Transformer ->%s<- has more actual parameters than specified.\n")

AL_DEFMSG2(ERR, 232, 2,
           "Transformer ->%s::%s<- has no return value (return type is void)",
           "and thus cannot be used in an expression.\n")

AL_DEFMSG1(ERR, 233, 1,
           "Transformer ->%s<- has not been given a return type.\n")

AL_DEFMSG2(ERR, 234, 2,
           "Transformer ->%s<- for object ->%s<-",
           "is missing corresponding parameter(s).\n")

AL_DEFMSG2(ERR, 235, 2,
           "Transformer ->%s::%s<-has a return value which is not",
           "being assigned to a variable.\n")

AL_DEFMSG1(ERR, 236, 1,
           "Return value required by %s.\n")

AL_DEFMSG1(ERR, 237, 1,
           "Invalid data type returned for %s.\n")

AL_DEFMSG1(ERR, 238, 1,
           "Return value not required by %s.\n")

AL_DEFMSG2(ERR, 239, 2,
           "Bridge ->%s<- for external entity ->%s<-",
           "has redundant parameters.\n")

AL_DEFMSG2(ERR, 240, 2,
           "Transformer ->%s<- for object ->%s<-",
           "has redundant parameters.\n")

AL_DEFMSG2(ERR, 241, 2,
           "Transformer ->%s.%s<- has no return type (return type is void)",
           "and thus cannot be used in an expression.\n")

AL_DEFMSG2(ERR, 242, 2,
           "Transformer ->%s.%s<- has a return value which is not",
           "being assigned to a variable.\n")

AL_DEFMSG2(ERR, 243, 2,
           "Transformer ->%s<- is instance-based and must",
           "be invoked as <var>.%s.\n")

AL_DEFMSG2(ERR, 244, 2,
           "Transformer ->%s<- is not instance-based and",
           "must be invoked as <kl>::%s.\n")

AL_DEFMSG2(ERR, 245, 1,
           "Synchronous service ->%s<- has no return type (return type is void)",
           "and thus cannot be used in an expression.\n")

AL_DEFMSG2(ERR, 246, 1,
           "Synchronous service ->%s<- has a return value which is not",
           "being assigned to a variable.\n")

AL_DEFMSG1(ERR, 247, 1,
           "Cannot find specified service ->%s<-.\n")

AL_DEFMSG2(ERR, 248, 1,
           "More than one synchronous service named ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG1(ERR, 249, 1,
           "You must assign a value to the derived attribute self.%s .\n")

AL_DEFMSG1(ERR, 250, 1,
           "Parameter ->%s<- is not passed by reference and is not assignable.\n")

AL_DEFMSG1(ERR, 251, 1,
           "Cannot pass read-only value to pass-by-reference parameter ->%s<-.\n")

AL_DEFMSG1(ERR, 252, 1,
           "You cannot use the derived attribute self.%s as an r-value in its own action specification.\n")

// VARIABLES  260-269

AL_DEFMSG1(ERR, 260, 1,
           "Variable ->%s<- is not associated with an object instance.\n")

AL_DEFMSG1(ERR, 261, 1,
           "Variable ->%s<- is not associated with an object.\n")

AL_DEFMSG1(ERR, 262, 1,
           "Variable ->%s<- must already exist.\n")

AL_DEFMSG1(ERR, 263, 1,
           "Variable ->%s<- must be initialized and for a set.\n")

AL_DEFMSG1(ERR, 264, 1,
           "Variable ->%s<- must be initialized and per instance.\n")

AL_DEFMSG1(ERR, 265, 1,
           "Token ->%s<- is a keyword and cannot be used in this context.\n")

// TYPE  270-299

AL_DEFMSG1(ERR, 270, 1,
           "Variable ->%s<- already being used as a set variable.\n")

AL_DEFMSG1(ERR, 271, 1,
           "Variable ->%s<- already being used as an instance variable.\n")

AL_DEFMSG1(ERR, 272, 1,
           "Variable ->%s<- already exists as a different type.\n")

AL_DEFMSG2(ERR, 273, 1,
           "Cannot assign to an attribute ->%s<- which is",
           "of type unique_id and also an identifier.\n")

AL_DEFMSG1(ERR, 274, 0,
           "Data types are not assignable or compatible across assignment statement.\n")

AL_DEFMSG2(ERR, 275, 3,
           "Instance reference set variable %s< %s > cannot",
           "be assigned from instance reference set variable of type -> %s <-.\n")

AL_DEFMSG2(ERR, 276, 3,
           "Instance reference variable %s of type %s ",
           "cannot be assigned from instance reference variable of type %s.\n")

AL_DEFMSG1(ERR, 277, 1,
           "Operand(s) of expression are incompatible with operator(s)")

AL_DEFMSG1(ERR, 278, 1,
           "Parameter ->%s<- has been assigned value of different type.\n")

AL_DEFMSG1(ERR, 279, 1,
           "Parameter ->%s<- has not been assigned a core data type.\n")

AL_DEFMSG1(ERR, 280, 1,
           "Supplemental data item ->%s<- has not been data typed yet.\n")

AL_DEFMSG2(ERR, 281, 1,
           "Supplemental data item ->%s<- has been assigned",
           "value of different type.\n")

AL_DEFMSG1(ERR, 282, 1,
           "Variable ->%s<- is of type not allowed on either side of assignment.\n")

AL_DEFMSG1(ERR, 283, 1,
           "Reference variable ->%s<- must be of type inst<Event>.\n")

AL_DEFMSG1(ERR, 284, 0,
           "Cannot assign a value to ->Self<-.\n")

// TYPE 290-299

AL_DEFMSG1(ERR, 290, 1,
           "Cannot find enumeration data type ->%s<-.\n")

AL_DEFMSG2(ERR, 291, 1,
           "More than one enumeration data type named ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG1(ERR, 292, 2,
           "Cannot find enumerator ->%s<- for enumeration data type ->%s<-.\n")

AL_DEFMSG2(ERR, 293, 2,
           "More than one enumerator ->%s<- defined for enumeration data type named ->%s<-.",
           "You will need to eventually run the audit and/or clear this up.\n")

AL_DEFMSG2(ERR, 294, 0,
           "Illegal comparison operator between enumerators.",
		   "Only the == and != operators are allowed.\n")

AL_DEFMSG1(ERR, 298, 1,
           "Cannot define variable ->%s<- with invalid datatype.\n")

AL_DEFMSG1(ERR, 299, 1,
           "Cannot define variable ->%s<- with unknown datatype.\n")


// GENERIC  300-320

AL_DEFMSG1(ERR, 300, 1,
           "Syntax error while parsing ->%s<-.\n")

//   UNUSED - 311

AL_DEFMSG1(ERR, 312, 0,
           "Incompatible operand for signed expression.\n")

AL_DEFMSG1(ERR, 314, 0,
           "Assignment statement not allowed in an expression.\n")

AL_DEFMSG1(ERR, 315, 0,
           "Missing trailing tick mark in phrase.\n")

AL_DEFMSG1(ERR, 316, 0,
           "Missing trailing quote in string.\n")

AL_DEFMSG1(ERR, 317, 0,
           "Incompatible operands for boolean expression.\n")

AL_DEFMSG1(ERR, 318, 0,
           "Incompatible operands for comparison expression.\n")

AL_DEFMSG1(ERR, 319, 0,
           "Incompatible operands for arithmetic expression.\n")

AL_DEFMSG1(ERR, 320, 0,
           "Incompatible operands for string expression.\n")

AL_DEFMSG1(ERR, 321, 0,
           "End of file encountered in a comment.\n")

// Internal errors 350-399

AL_DEFMSG3(ERR, 350, 4,
           "**INTERNAL ERROR**  ",
           "AST token type mismatch at line %d in file %S.",
           "Token type was %d, should be %d.\n") 

AL_DEFMSG3(ERR, 351, 5,
           "**INTERNAL ERROR**  ",
           "AST token type mismatch at line %d in file %S.",
           "Token type was %d, should be %d or %d.\n") 

  // Invoked in a_bush.cc:
AL_DEFMSG3(ERR, 352, 3,
           "**INTERNAL ERROR**  ",
           "Relocatables list is out of order.",
           "text: %s, c_offset: %d, c_last_offset: %d.\n")

  // Used in p_check.hh:
AL_DEFMSG2(ERR, 353, 2,
           "**INTERNAL ERROR**  ",
         "AST objPtr was NULL at line %d in file %S.\n") 

  // This error is actually directly implemented in DLGLexer::errstd()
  // But we'll add this definition here so it's not forgotten
  // Currently the only value for the first parameter is 'invalid token'

AL_DEFMSG1(ERR, 354, 2,
           "%S (skipping text '%S')\n")

  // This error is actually directly implemented in DLGLexer::errstd()
  // But we'll add this definition here so it's not forgotten

AL_DEFMSG1(ERR, 355, 1,
           "Lexical error (skipping text '%S')\n")

  // Errors from Sorcerer

AL_DEFMSG1(ERR, 356, 2,
    "parse error: expected token range %d..%d found NULL tree\n")

AL_DEFMSG1(ERR, 357, 3,
    "parse error: expected token range %d..%d found token %d\n")

AL_DEFMSG1(ERR, 358, 0,
    "parse error: expected any token/tree found found NULL tree\n")

AL_DEFMSG1(ERR, 359, 1,
    "parse error: expected token %d found NULL tree\n")

AL_DEFMSG1(ERR, 360, 2,
    "parse error: expected token %d found token %d\n")

AL_DEFMSG1(ERR, 361, 1,
    "parse error: in rule %S, no viable alternative for NULL tree\n")

AL_DEFMSG1(ERR, 362, 1,
    "parse error: in rule %S, no viable alternative for tree\n")


//---------------------------------------------------------------
// FAIL messages:
//---------------------------------------------------------------
