/* $Id: vundo.h,v 1.25 1997/04/29 22:28:45 doug Exp $ */

/************************************************************

    vundo.h
    C Interface file for the Undo Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vundoINCLUDED
#define vundoINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbyte */
#include vstdHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
  vundoNEW,
  vundoDONE,
  vundoUNDONE
};

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */


typedef struct vundoAction	 vundoAction;
typedef struct vundoActionClass  vundoActionClass;

typedef struct vundoActionList		vundoActionList;
typedef struct vundoActionListClass	vundoActionListClass;

typedef struct vundoLog			vundoLog;
typedef struct vundoLogClass		vundoLogClass;

typedef struct vundoCommand             vundoCommand;
typedef struct vundoCommandClass        vundoCommandClass;

typedef struct vundoUndoCommand         vundoUndoCommand;
typedef struct vundoUndoCommandClass    vundoUndoCommandClass;

typedef struct vundoRedoCommand         vundoRedoCommand;
typedef struct vundoRedoCommandClass    vundoRedoCommandClass;

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vundoStartup(void);


/*
 * Basic action class:
 */

vundoActionClass *vundoGetDefaultActionClass(
    void
    );

vundoActionClass *vundoGetActionClass(
    vundoAction 		*action
    );

vinstance *vundoGetActionInstance(
    vundoAction 		*action
    );

vundoAction *vundoCreateAction(
    void
    );

vundoAction *vundoCreateActionOfClass(
    void 			*clas
    );

void vundoDestroyAction(
    vundoAction 		*action
    );

void vundoActAction(
    vundoAction 		*action
    );

int vundoGetActionState(
    vundoAction 		*action
    );

const vchar *vundoGetActionName(
    vundoAction 		*action
    );

vscribe *vundoScribeAction(
    vundoAction 		*action
    );


/*
 * Action list class:
 */

vundoActionListClass *vundoGetDefaultActionListClass(
    void
    );

vundoActionListClass *vundoGetActionListClass(
    vundoActionList 		*list
    );

vundoAction *vundoGetActionListAction(
    vundoActionList 		*list
    );

vundoActionList *vundoCreateActionList(
    void
    );

vundoActionList *vundoCreateActionListOfClass(
    void 			*clas
    );

void vundoDestroyActionList(
    vundoActionList 		*list
    );

void vundoActActionList(
    vundoActionList 		*list
    );

int vundoGetActionListState(
    vundoActionList 		*list
    );

const vchar *vundoGetActionListName(
    vundoActionList 		*list
    );

void vundoSetActionListName(
    vundoActionList 		*list,
    const vchar			*name
    );

vscribe *vundoScribeActionList(
    vundoActionList 		*list
    );

void vundoAddActionListAction(
    vundoActionList 		*list, 
    vundoAction 		*action
    );

size_t vundoGetActionListCount(
    vundoActionList		*list
    );

void vundoSetActionListSlots(
    vundoActionList 		*list, 
    size_t 			count
    );

size_t vundoGetActionListSlots(
    vundoActionList		*list
    );


/*
 * Undo log:
 */

vundoLogClass *vundoGetDefaultLogClass(
    void
    );

vundoLogClass *vundoGetLogClass(
    vundoLog 			*log
    );

vinstance *vundoGetLogInstance(
    vundoLog 			*log
    );

vundoLog *vundoCreateLog(
    void
    );

vundoLog *vundoCreateLogOfClass(
    void 			*clas
    );

vundoRedoCommand *vundoCreateLogRedoCommand(
    vundoLog                    *log
    );

vundoUndoCommand *vundoCreateLogUndoCommand(
    vundoLog                    *log
    );

void vundoDestroyLog(
    vundoLog 			*log
    );

void vundoClearLog(
    vundoLog			*log
    );

void vundoSetLogSize(
    vundoLog			*log,
    int				newSize
    );

int vundoGetLogSize(
    vundoLog			*log
    );

void vundoAddLogAction(
    vundoLog			*log,
    vundoAction			*action
    );

void vundoMarkLogSaved(
    vundoLog			*log
    );

int vundoIsLogSaved(
    vundoLog			*log
    );

vundoAction *vundoGetLogUndoAction(
    vundoLog			*log
    );

vundoAction *vundoGetLogRedoAction(
    vundoLog			*log
    );

void vundoUndoLog(
    vundoLog			*log
    );

void vundoRedoLog(
    vundoLog			*log
    );

vscribe *vundoScribeLogUndoAction(
    vundoLog			*log
    );

vscribe *vundoScribeLogRedoAction(
    vundoLog			*log
    );

void vundoSetLogData(
    vundoLog			*log,
    void			*data
    );

void *vundoGetLogData(
    vundoLog			*log
    );

void vundoSetLogUndoCommandName(
    vundoLog			*log,
    const vname			*undoName
    );

const vname *vundoGetLogUndoCommandName(
    vundoLog			*log
    );

void vundoSetLogRedoCommandName(
    vundoLog			*log,
    const vname			*redoName
    );

const vname *vundoGetLogRedoCommandName(
    vundoLog			*log
    );

void vundoSetLogSaveCommandName(
    vundoLog			*log,
    const vname			*saveName
    );

const vname *vundoGetLogSaveCommandName(
    vundoLog			*log
    );

void vundoSetLogDispatchEnabled(
    vundoLog			*log,
    int	/* vbool */		value
    );		

vbool vundoGetLogDispatchEnabled(
    vundoLog			*log
    );		

void vundoInstallLogCommands(
    vundoLog			*log,
    vcommandSpace		*commandSpace
    );

vbool vundoInstallLogCommandsAtObject(
    vundoLog			*log,
    vobjectAttributed		*object
    );

void vundoUninstallLogCommands(
    vundoLog			*log
    );

/*
 * Base Undo Command
 */

vundoCommandClass *vundoGetDefaultCommandClass(
    void
    );

vundoCommandClass *vundoGetCommandClass(
    vundoCommand                *command
    );

vcommand *vundoGetCommandCommand(
    vundoCommand                *command
    );

vundoCommand *vundoCreateCommandOfClass(
    vundoCommandClass           *clas
    );

void vundoInitCommandOfClass(
    vundoCommand                *command,
    vundoCommandClass           *clas
    );

/*
 * Undo Command
 */

vundoUndoCommandClass *vundoGetDefaultUndoCommandClass(
    void
    );

vundoUndoCommandClass *vundoGetUndoCommandClass(
    vundoUndoCommand            *command
    );

vundoCommand *vundoGetUndoCommandCommand(
    vundoUndoCommand            *command
    );

vundoUndoCommand *vundoCreateUndoCommandOfClass(
    vundoUndoCommandClass       *clas
    );

void vundoInitUndoCommandOfClass(
    vundoUndoCommand            *command,
    vundoUndoCommandClass       *clas
    );

/*
 * Redo Command
 */

vundoRedoCommandClass *vundoGetDefaultRedoCommandClass(
    void
    );

vundoRedoCommandClass *vundoGetRedoCommandClass(
    vundoRedoCommand            *command
    );

vundoCommand *vundoGetRedoCommandCommand(
    vundoRedoCommand            *command
    );

vundoRedoCommand *vundoCreateRedoCommandOfClass(
    vundoRedoCommandClass       *clas
    );

void vundoInitRedoCommandOfClass(
    vundoRedoCommand            *command,
    vundoRedoCommandClass       *clas
    );

/*
 * * * * * * * * * PRIVATE TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */


/*
 * Basic action class:
 */

struct vundoAction
{
  vinstance		instance;

  vbyte 		state;
};

#define vundoDESTROY		vinstanceDESTROY

#define vundoActionCLASS(CLASS, ACTION) 				\
    vinstanceCLASS(CLASS, ACTION);					\
    vclassVARIABLE(vundoNAME, const vchar *); 				\
    vclassMETHOD_RET(vundoGET_NAME, const vchar *, (ACTION *action));	\
    vclassMETHOD(vundoACT, (ACTION *action))

struct vundoActionClass
{
  vundoActionCLASS(vundoActionClass, vundoAction);
};


/*
 * Multi-action class:
 */

struct vundoActionList
{
  vundoAction 	action;

  vundoAction 	**subactions;
  short 	subactionCount;
  short 	subactionSlots;
  const vchar 	*name;
};

#define vundoActionListCLASS(CLASS, ACTION) \
    vundoActionCLASS(CLASS, ACTION)

struct vundoActionListClass
{
  vundoActionListCLASS(struct vundoActionListClass, 
			  struct vundoActionList);
};

/*
 * Undo log:
 */

struct vundoLog
{
  vinstance	super;

  vundoAction	**actions;
  short 	firstAction;	/* index of oldest action */
  short 	lastAction;	/* index of newest action + 1 */
  short		lastDoneAction;	/* index of newest done action + 1 */
  short		savedAtAction;	/* lastDoneAction value at last save or -1*/
  short 	maxActions;	/* max # of actions in log + 1*/
  vbool		dispatchEnabled;
  const vname	*undoName;
  const vname	*redoName;
  const vname 	*saveName;
  vcommandSpace	*commandSpace;
  vdict		*commandDict;
  void 		*userData;
};

#define vundoLogCLASS(CLASS, LOG)	 				\
    vinstanceCLASS(CLASS, LOG);                                         \
    vclassMETHOD_RET(vundoCREATE_LOG_UNDO_COMMAND,                      \
                     vundoUndoCommand *, (LOG *log));                   \
    vclassMETHOD_RET(vundoCREATE_LOG_REDO_COMMAND,                      \
                     vundoRedoCommand *, (LOG *log))

struct vundoLogClass
{
  vundoLogCLASS(vundoLogClass, vundoLog);
};


struct vundoCommand
{
    vcommand    command;
    vundoLog    *log;
    vstr        *lastTitle;
};

#define vundoCOMMAND_CLASS(SUPER, COMMAND)                              \
    vcommandCLASS(SUPER, COMMAND)
    
struct vundoCommandClass {
    vundoCOMMAND_CLASS(vundoCommandClass, vundoCommand);
};


struct vundoUndoCommand
{
    vundoCommand        command;
};

#define vundoUNDO_COMMAND_CLASS(SUPER, COMMAND)                         \
    vundoCOMMAND_CLASS(SUPER, COMMAND)

struct vundoUndoCommandClass {
    vundoUNDO_COMMAND_CLASS(vundoUndoCommandClass, vundoUndoCommand);
};


struct vundoRedoCommand
{
    vundoCommand        command;
};

#define vundoREDO_COMMAND_CLASS(SUPER, COMMAND)                         \
    vundoCOMMAND_CLASS(SUPER, COMMAND)

struct vundoRedoCommandClass {
    vundoREDO_COMMAND_CLASS(vundoRedoCommandClass, vundoRedoCommand);
};

/*
 * * * * * * * * * Functions exported internally  * * * * * * * *
 */

void _vundoPropagateAll(vundoLog *log);
void _vundoPropagateSave(vundoLog *log);

/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define vundoGetActionInstance(a) \
    vportBASE_OBJECT((a), instance)
#define vundoGetActionClass(a) \
    ((vundoActionClass *) vinstanceGetClass(vundoGetActionInstance(a)))

#define vundoCreateActionOfClass(c) \
    ((vundoAction *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vundoCreateAction() \
    (vundoCreateActionOfClass(vundoGetDefaultActionClass()))
#define vundoDestroyAction(a) \
    vinstanceDestroy(vundoGetActionInstance(a))

#define vundoGetActionState(a)		((a)->state)

#define vundoGetActionName(a) \
    (vclassSend(vundoGetActionClass(a), vundoGET_NAME, (a)))
#define vundoActAction(a) \
    (vclassSend(vundoGetActionClass(a), vundoACT, (a)))



#define vundoGetActionListAction(a) \
    vportBASE_OBJECT((a), action)
#define vundoGetActionListClass(a) \
    ((vundoActionListClass *) \
     	vundoGetActionClass(vundoGetActionListAction(a)))

#define vundoCreateActionListOfClass(c) \
    ((vundoActionList *) vundoCreateActionOfClass(c))
#define vundoCreateActionList() \
    (vundoCreateActionListOfClass(vundoGetDefaultActionListClass()))
#define vundoDestroyActionList(a) \
    vundoDestroyAction(vundoGetActionListAction(a))

#define vundoGetActionListName(a) \
    (vclassSend(vundoGetActionListClass(a), vundoGET_NAME, (a)))
#define vundoActActionList(a) \
    (vclassSend(vundoGetActionListClass(a), vundoACT, (a)))
#define vundoGetActionListState(a) \
    (vundoGetActionState(vundoGetActionListAction(a)))
#define vundoScribeActionList(a) \
    (vundoScribeAction(vundoGetActionListAction(a)))

#define vundoSetActionListName(a, s) \
    ((a)->name = (s))

#define vundoGetActionListCount(a) \
    ((a)->subactionCount)
#define vundoGetActionListSlots(a) \
    ((a)->subactionSlots)


#define vundoGetLogInstance(a) \
    vportBASE_OBJECT((a), super)
#define vundoGetLogClass(a) \
    ((vundoLogClass *) vinstanceGetClass(vundoGetLogInstance(a)))

#define vundoCreateLogOfClass(c) \
    ((vundoLog *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vundoCreateLog() \
    (vundoCreateLogOfClass(vundoGetDefaultLogClass()))
#define vundoDestroyLog(a) \
    vinstanceDestroy(vundoGetLogInstance(a))
    
#define vundoCreateLogUndoCommand(u) \
    vclassSend(vundoGetLogClass(u), vundoCREATE_LOG_UNDO_COMMAND, (u))
#define vundoCreateLogRedoCommand(u) \
    vclassSend(vundoGetLogClass(u), vundoCREATE_LOG_REDO_COMMAND, (u))

#define vundoSetLogData(u,d)		((u)->userData = (d))
#define vundoGetLogData(u)		((u)->userData)

#define vundoGetLogSize(u)		((u)->maxActions - 1)

#define vundoSetLogSaveCommandName(u,n)	((u)->saveName = (n))

#define vundoGetLogUndoCommandName(u)	((u)->undoName)
#define vundoGetLogRedoCommandName(u)	((u)->redoName)
#define vundoGetLogSaveCommandName(u)	((u)->saveName)

#define vundoSetLogDispatchEnabled(u,v)	((u)->dispatchEnabled = ((v)!=0))
#define vundoGetLogDispatchEnabled(u)	((u)->dispatchEnabled)

#define vundoGetCommandCommand(c) \
    vportBASE_OBJECT((c), command)
#define vundoGetCommandClass(c) \
    ((vundoCommandClass *) vcommandGetClass(vundoGetCommandCommand(c)))
#define vundoCreateCommandOfClass(c) \
    ((vundoCommand *)vcommandCreateOfClass((vcommandClass*)(c)))
#define vundoInitCommandOfClass(c, cl) \
    vcommandInitOfClass(vundoGetCommandCommand(c), (vcommandClass*)(cl))

#define vundoGetUndoCommandCommand(c) \
    vportBASE_OBJECT((c), command)
#define vundoGetUndoCommandClass(c) \
    ((vundoUndoCommandClass *) \
     vundoGetCommandClass(vundoGetUndoCommandCommand(c)))
#define vundoCreateUndoCommandOfClass(c) \
    ((vundoUndoCommand *)vundoCreateCommandOfClass((vundoCommandClass*)(c)))
#define vundoCreateUndoCommand() \
    (vundoCreateUndoCommandOfClass(vundoGetDefaultUndoCommandClass()))
#define vundoInitUndoCommandOfClass(c, cl) \
    vundoInitCommandOfClass( \
        vundoGetUndoCommandCommand(c), (vundoCommandClass*)(cl))

#define vundoGetRedoCommandCommand(c) \
    vportBASE_OBJECT((c), command)
#define vundoGetRedoCommandClass(c) \
    ((vundoRedoCommandClass *) \
     vundoGetCommandClass(vundoGetRedoCommandCommand(c)))
#define vundoCreateRedoCommandOfClass(c) \
    ((vundoRedoCommand *)vundoCreateCommandOfClass((vundoCommandClass*)(c)))
#define vundoCreateRedoCommand() \
    (vundoCreateRedoCommandOfClass(vundoGetDefaultRedoCommandClass()))
#define vundoInitRedoCommandOfClass(c, cl) \
    vundoInitCommandOfClass( \
        vundoGetRedoCommandCommand(c), (vundoCommandClass*)(cl))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vundoINCLUDED */

