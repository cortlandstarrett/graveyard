--========================================================================
--
--File:      $RCSfile: perf_test3.sql,v $
--Version:   $Revision: 1.9 $
--Modified:  $Date: 2013/01/10 23:41:40 $
--
--(c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
--
--========================================================================
--This document contains information proprietary and confidential to
--Mentor Graphics Corp., and is not for external distribution.
--======================================================================== 
--
--This contains the entire escher_ooa_schema and entire mc3020_meta.sql model.
--
-- ============================================================================
-- File:        escher_ooa_schema.sql
--
-- Description:
--   This file provides an SQL schema file suitable for use with the
-- DesignPoint MC-3020 Model Compiler.
--
-- Model Repository:  mc3020_meta.ooa
--
-- Notice:
--   (C) Copyright Mentor Grapchics Corporation.  1999-2005
--   All rights reserved.
--   Enhancements provided by TOYO Corporation.
--   Enhancements provided by Radix Unlimited.
--
--              !!! THIS IS AN AUTO-GENERATED FILE. !!!
--   Any extensions added via hand editing of this file will need to be
-- manually carried forward across subsequent releases of the Model Compiler.
-- ============================================================================

-- ============================================================================
-- Objects In Subsystem: Domain  
-- ============================================================================

-- Class:  1.  Domain
CREATE TABLE S_DOM (
	Dom_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Full_Der	INTEGER,
	Config_ID	UNIQUE_ID,
	Sys_ID	UNIQUE_ID,
	RegisteredName	STRING,
	RegisteredID	INTEGER,
	TypeCode	INTEGER,
	StateTrace	BOOLEAN,
	StmtTrace	BOOLEAN,
	DetectEmpty	BOOLEAN,
	OptDisabled	BOOLEAN,
	RawComments	BOOLEAN,
	CodeComments	BOOLEAN,
	UseModelNames	BOOLEAN,
	ReflexPhrase	BOOLEAN,
	TextBuffer	STRING,
	CollectionsFlavor	INTEGER,
	TargetMonitorEnabled	BOOLEAN,
	SystemPrefix	STRING,
	SystemMethodPrefix	STRING,
	SystemTypePrefix	STRING,
	SystemDefinePrefix	STRING,
	SystemFilePrefix	STRING,
	IsStaticPopulateOld	BOOLEAN,
	CharacterEncoding	STRING );

-- Class:  2.  Subsystem
CREATE TABLE S_SS (
	SS_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Prefix	STRING,
	Num_Rng	INTEGER,
	Dom_ID	UNIQUE_ID,
	Config_ID	UNIQUE_ID,
	Order	INTEGER,
	Included	BOOLEAN );

-- Class:  3.  External Entity
CREATE TABLE S_EE (
	EE_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Key_Lett	STRING,
	Dom_ID	UNIQUE_ID,
	RegisteredID	INTEGER,
	RegisteredName	STRING,
	TypeCode	INTEGER,
	Included	BOOLEAN,
	Include_File	STRING,
	Bridge_Obj_Kl	STRING,
	ClassName	STRING,
	Used	BOOLEAN,
	C_Style	BOOLEAN );

-- Class:  4.  External Entity in Model
CREATE TABLE S_EEM (
	EEmod_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	Modl_Typ	INTEGER,
	SS_ID	UNIQUE_ID );

-- Class:  5.  External Entity Data Item
CREATE TABLE S_EEDI (
	EEdi_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	DT_ID	UNIQUE_ID );

-- Class:  6.  External Entity Event
CREATE TABLE S_EEEVT (
	EEevt_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	Numb	INTEGER,
	Mning	STRING,
	Is_Lbl_U	INTEGER,
	Unq_Lbl	STRING,
	Drv_Lbl	STRING,
	Descrip	STRING,
	Used	INTEGER,
	UsedCount	INTEGER );

-- Class:  7.  External Entity Event Data Item
CREATE TABLE S_EEEDI (
	EEedi_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	DT_ID	UNIQUE_ID,
	Order	INTEGER,
	ParamBuffer	STRING,
	OALParamBuffer	STRING );

-- Class:  8.  External Entity Event Data
CREATE TABLE S_EEEDT (
	EE_ID	UNIQUE_ID,
	EEevt_ID	UNIQUE_ID,
	EEedi_ID	UNIQUE_ID );

-- Class:  9.  Data Type
CREATE TABLE S_DT (
	DT_ID	UNIQUE_ID,
	Dom_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Included	BOOLEAN,
	ExtName	STRING,
	EventExtName	STRING,
	Include_File	STRING,
	Initial_Value	STRING,
	Is_Enum	BOOLEAN,
	Enum_Class_Name	STRING,
	Owning_Dom_Name	STRING );

-- Class:  10.  Core Data Type
CREATE TABLE S_CDT (
	DT_ID	UNIQUE_ID,
	Core_Typ	INTEGER );

-- Class:  11.  User Data Type
CREATE TABLE S_UDT (
	DT_ID	UNIQUE_ID,
	CDT_ID	UNIQUE_ID,
	Gen_Type	INTEGER );

-- Class:  12.  Bridge
CREATE TABLE S_BRG (
	Brg_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Brg_Typ	INTEGER,
	DT_ID	UNIQUE_ID,
	Action_Semantics	STRING,
	Suc_Pars	INTEGER,
	AutID	INTEGER,
	AbaID	UNIQUE_ID,
	StmtCount	INTEGER,
	XlateSemantics	BOOLEAN,
	NonSelfEventCount	INTEGER,
	SelectManyCount	INTEGER,
	SelectAnyWhereCount	INTEGER,
	TimerStartCount	INTEGER,
	ReturnStmtUsed	BOOLEAN,
	BreakStmtUsed	BOOLEAN,
	ContinueStmtUsed	BOOLEAN );

-- Class:  13.  Bridge Parameter
CREATE TABLE S_BPARM (
	BParm_ID	UNIQUE_ID,
	Brg_ID	UNIQUE_ID,
	Name	STRING,
	DT_ID	UNIQUE_ID,
	By_Ref	INTEGER,
	Order	INTEGER,
	ParamBuffer	STRING,
	OALParamBuffer	STRING );

-- Class:  14.  Enumeration Data Type
CREATE TABLE S_EDT (
	DT_ID	UNIQUE_ID,
	Initial_Value	STRING );

-- Class:  15.  Enumerator
CREATE TABLE S_ENUM (
	Enum_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	EDT_ID	UNIQUE_ID,
	Value	STRING,
	Order	INTEGER );

-- Class:  16.  Function
CREATE TABLE S_SYNC (
	Sync_ID	UNIQUE_ID,
	Dom_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Action_Semantics	STRING,
	DT_ID	UNIQUE_ID,
	Suc_Pars	INTEGER,
	AutID	INTEGER,
	AbaID	UNIQUE_ID,
	Included	BOOLEAN,
	IsInitFunction	BOOLEAN,
	NonSelfEventCount	INTEGER,
	SelectManyCount	INTEGER,
	SelectAnyWhereCount	INTEGER,
	TimerStartCount	INTEGER,
	IsSafeForInterrupts	BOOLEAN,
	ReturnStmtUsed	BOOLEAN,
	BreakStmtUsed	BOOLEAN,
	ContinueStmtUsed	BOOLEAN,
	Order	INTEGER,
	XlateSemantics	BOOLEAN );

-- Class:  17.  Function Parameter
CREATE TABLE S_SPARM (
	SParm_ID	UNIQUE_ID,
	Sync_ID	UNIQUE_ID,
	Name	STRING,
	DT_ID	UNIQUE_ID,
	By_Ref	INTEGER,
	Order	INTEGER,
	ParamBuffer	STRING,
	OALParamBuffer	STRING );

-- Class:  18.  System Model
CREATE TABLE S_SYS (
	Sys_ID	UNIQUE_ID,
	Name	STRING );

-- Class:  19.  Function Package
CREATE TABLE S_FPK (
	FunPack_ID	UNIQUE_ID,
	Name	STRING,
	Dom_ID	UNIQUE_ID,
	Parent_FunPack_ID	UNIQUE_ID );

-- Class:  20.  Function in Package
CREATE TABLE S_FIP (
	FunPack_ID	UNIQUE_ID,
	Sync_ID	UNIQUE_ID );

-- Class:  21.  Function Package in Package
CREATE TABLE S_FPIP (
	FunPack_ID	UNIQUE_ID );

-- Class:  22.  External Entity Package
CREATE TABLE S_EEPK (
	EEPack_ID	UNIQUE_ID,
	Name	STRING,
	Dom_ID	UNIQUE_ID,
	Parent_EEPack_ID	UNIQUE_ID );

-- Class:  23.  External Entity in Package
CREATE TABLE S_EEIP (
	EEPack_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID );

-- Class:  24.  EE Package in Package
CREATE TABLE S_EEPIP (
	EEPack_ID	UNIQUE_ID );

-- Class:  25.  Datatype Package
CREATE TABLE S_DPK (
	DatPack_ID	UNIQUE_ID,
	Name	STRING,
	Dom_ID	UNIQUE_ID,
	Parent_DatPack_ID	UNIQUE_ID );

-- Class:  26.  Datatype in Package
CREATE TABLE S_DIP (
	DatPack_ID	UNIQUE_ID,
	DT_ID	UNIQUE_ID );

-- Class:  27.  Datatype Package in Package
CREATE TABLE S_DPIP (
	DatPack_ID	UNIQUE_ID );

-- Class:  30.  Subsystem in Subsystem
CREATE TABLE S_SIS (
	Parent_SS_ID	UNIQUE_ID,
	Child_SS_ID	UNIQUE_ID );

-- Class:  31.  Subsystem in Domain
CREATE TABLE S_SID (
	Dom_ID	UNIQUE_ID,
	SS_ID	UNIQUE_ID );


-- ============================================================================
-- Objects In Subsystem: Class  
-- ============================================================================

-- Class:  101.  Class
CREATE TABLE O_OBJ (
	Obj_ID	UNIQUE_ID,
	Name	STRING,
	Numb	INTEGER,
	Key_Lett	STRING,
	Descrip	STRING,
	SS_ID	UNIQUE_ID,
	Included	BOOLEAN,
	IsBridgeObject	BOOLEAN,
	IsInitObject	BOOLEAN,
	IsAsyncObject	BOOLEAN,
	PEIsDefinedInData	BOOLEAN,
	IsFixedPopulation	BOOLEAN,
	IsStaticPopulate	BOOLEAN,
	IsReadOnly	BOOLEAN,
	StaticExtentSize	INTEGER,
	ExcludeFromGen	BOOLEAN,
	MaxExtentSize	INTEGER,
	SelfCreated	BOOLEAN,
	NonSelfCreated	BOOLEAN,
	DeleteAccessor	BOOLEAN,
	CreateAccessor	BOOLEAN,
	ExtendedSetOps	BOOLEAN,
	Persistent	BOOLEAN,
	Order	INTEGER,
	IsTrace	BOOLEAN,
	IsSynchronizedSelfEvent	BOOLEAN,
	Include_File	STRING,
	ContainerIndex	INTEGER,
	Task	INTEGER );

-- Class:  102.  Imported Class
CREATE TABLE O_IOBJ (
	IObj_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	Modl_Typ	INTEGER,
	SS_ID	UNIQUE_ID,
	Obj_Name	STRING,
	Obj_KL	STRING );

-- Class:  103.  Attribute
CREATE TABLE O_ATTR (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	PAttr_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	Prefix	STRING,
	Root_Nam	STRING,
	Pfx_Mode	INTEGER,
	DT_ID	UNIQUE_ID,
	Used	BOOLEAN,
	AssignUsed	BOOLEAN,
	Included	BOOLEAN,
	Order	INTEGER,
	ParamBuffer	STRING,
	OALParamBuffer	STRING,
	Persistent	BOOLEAN );

-- Class:  104.  Class Identifier
CREATE TABLE O_ID (
	Oid_ID	INTEGER,
	Obj_ID	UNIQUE_ID,
	WhereKey	BOOLEAN );

-- Class:  105.  Class Identifier Attribute 
CREATE TABLE O_OIDA (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	Oid_ID	INTEGER );

-- Class:  106.  Base Attribute
CREATE TABLE O_BATTR (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID );

-- Class:  107.  Derived Based Attribute
CREATE TABLE O_DBATTR (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	Action_Semantics	STRING,
	Suc_Pars	INTEGER,
	AutID	INTEGER,
	AbaID	UNIQUE_ID,
	Included	BOOLEAN,
	SelfEventCount	INTEGER,
	NonSelfEventCount	INTEGER,
	SelectManyCount	INTEGER,
	SelectAnyWhereCount	INTEGER,
	TimerStartCount	INTEGER,
	ReturnStmtUsed	BOOLEAN,
	BreakStmtUsed	BOOLEAN,
	ContinueStmtUsed	BOOLEAN );

-- Class:  108.  New Base Attribute 
CREATE TABLE O_NBATTR (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID );

-- Class:  109.  Referential Attribute 
CREATE TABLE O_RATTR (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	BAttr_ID	UNIQUE_ID,
	BObj_ID	UNIQUE_ID,
	Ref_Mode	INTEGER );

-- Class:  110.  Attribute Reference in Object 
CREATE TABLE O_REF (
	Obj_ID	UNIQUE_ID,
	RObj_ID	UNIQUE_ID,
	ROid_ID	INTEGER,
	RAttr_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	ROIR_ID	UNIQUE_ID,
	Attr_ID	UNIQUE_ID,
	ARef_ID	UNIQUE_ID,
	PARef_ID	UNIQUE_ID,
	Is_Cstrd	BOOLEAN,
	Descrip	STRING );

-- Class:  111.  Referred To Identifier Attribute 
CREATE TABLE O_RTIDA (
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	Oid_ID	INTEGER,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID );

-- Class:  112.  Transformer
CREATE TABLE O_TFR (
	Tfr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	DT_ID	UNIQUE_ID,
	Instance_Based	INTEGER,
	Action_Semantics	STRING,
	Suc_Pars	INTEGER,
	AutID	INTEGER,
	AbaID	UNIQUE_ID,
	Included	BOOLEAN,
	XlateSemantics	BOOLEAN,
	MaxSelfEvents	INTEGER,
	MaxNonSelfEvents	INTEGER,
	SelfEventCount	INTEGER,
	NonSelfEventCount	INTEGER,
	SelectManyCount	INTEGER,
	SelectAnyWhereCount	INTEGER,
	TimerStartCount	INTEGER,
	ReturnStmtUsed	BOOLEAN,
	BreakStmtUsed	BOOLEAN,
	ContinueStmtUsed	BOOLEAN );

-- Class:  113.  Transformer Parameter
CREATE TABLE O_TPARM (
	TParm_ID	UNIQUE_ID,
	Tfr_ID	UNIQUE_ID,
	Name	STRING,
	DT_ID	UNIQUE_ID,
	By_Ref	INTEGER,
	Order	INTEGER,
	ParamBuffer	STRING,
	OALParamBuffer	STRING );


-- ============================================================================
-- Objects In Subsystem: Association  
-- ============================================================================

-- Class:  201.  Relationship
CREATE TABLE R_REL (
	Rel_ID	UNIQUE_ID,
	Numb	INTEGER,
	Descrip	STRING,
	SS_ID	UNIQUE_ID,
	LinkNeeded	BOOLEAN,
	UnlinkNeeded	BOOLEAN,
	Navigated	BOOLEAN,
	Order	INTEGER,
	storage_needed	BOOLEAN,
	set_storage_needed	BOOLEAN,
	set_storage_key_lett	STRING );

-- Class:  202.  Object In Relationship
CREATE TABLE R_OIR (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	IObj_ID	UNIQUE_ID );

-- Class:  203.  Referred To Object in Rel
CREATE TABLE R_RTO (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Oid_ID	INTEGER,
	NavigatedTo	BOOLEAN );

-- Class:  204.  Referring Object In Rel
CREATE TABLE R_RGO (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	NavigatedTo	BOOLEAN );

-- Class:  205.  Simple Relationship
CREATE TABLE R_SIMP (
	Rel_ID	UNIQUE_ID );

-- Class:  206.  Object As Simple Participant
CREATE TABLE R_PART (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER,
	Cond	INTEGER,
	Txt_Phrs	STRING );

-- Class:  207.  Object As Simple Formalizer
CREATE TABLE R_FORM (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER,
	Cond	INTEGER,
	Txt_Phrs	STRING );

-- Class:  208.  Associative Relationship
CREATE TABLE R_ASSOC (
	Rel_ID	UNIQUE_ID );

-- Class:  209.  Object As Associated One Side
CREATE TABLE R_AONE (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER,
	Cond	INTEGER,
	Txt_Phrs	STRING );

-- Class:  210.  Object As Associated Other Side
CREATE TABLE R_AOTH (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER,
	Cond	INTEGER,
	Txt_Phrs	STRING );

-- Class:  211.  Object As Associator
CREATE TABLE R_ASSR (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER );

-- Class:  212.  Subtype/Supertype Relationship
CREATE TABLE R_SUBSUP (
	Rel_ID	UNIQUE_ID );

-- Class:  213.  Object As Supertype
CREATE TABLE R_SUPER (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID );

-- Class:  214.  Object As Subtype
CREATE TABLE R_SUB (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID );

-- Class:  215.  Composition Relationship
CREATE TABLE R_COMP (
	Rel_ID	UNIQUE_ID,
	Rel_Chn	STRING );

-- Class:  216.  Object As Composition One Side
CREATE TABLE R_CONE (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER,
	Cond	INTEGER,
	Txt_Phrs	STRING );

-- Class:  217.  Object As Composition Other Side
CREATE TABLE R_COTH (
	Obj_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	OIR_ID	UNIQUE_ID,
	Mult	INTEGER,
	Cond	INTEGER,
	Txt_Phrs	STRING );


-- ============================================================================
-- Objects In Subsystem: Communication And Access  
-- ============================================================================

-- Class:  401.  Communication Path
CREATE TABLE CA_COMM (
	CPath_ID	UNIQUE_ID,
	SS_ID	UNIQUE_ID );

-- Class:  402.  EE to SM Comm Path
CREATE TABLE CA_EESMC (
	CPath_ID	UNIQUE_ID,
	EEmod_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID );

-- Class:  403.  SM to SM Comm Path
CREATE TABLE CA_SMSMC (
	CPath_ID	UNIQUE_ID,
	OSM_ID	UNIQUE_ID,
	DSM_ID	UNIQUE_ID,
	OIObj_ID	UNIQUE_ID,
	DIObj_ID	UNIQUE_ID );

-- Class:  404.  SM to EE Comm Path
CREATE TABLE CA_SMEEC (
	CPath_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	EEmod_ID	UNIQUE_ID );

-- Class:  405.  EE to SM Event Comm
CREATE TABLE CA_EESME (
	CPath_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID );

-- Class:  406.  SM to SM Event Comm
CREATE TABLE CA_SMSME (
	CPath_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID );

-- Class:  407.  SM to EE Event Comm
CREATE TABLE CA_SMEEE (
	CPath_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	EEevt_ID	UNIQUE_ID );

-- Class:  408.  Access Path
CREATE TABLE CA_ACC (
	APath_ID	UNIQUE_ID,
	SS_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	IObj_ID	UNIQUE_ID );

-- Class:  409.  SM to OBJ Access Path
CREATE TABLE CA_SMOA (
	APath_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	IObj_ID	UNIQUE_ID );

-- Class:  410.  SM to EE Access Path
CREATE TABLE CA_SMEEA (
	APath_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID,
	EEmod_ID	UNIQUE_ID );

-- Class:  411.  SM to OBJ Attribute Access
CREATE TABLE CA_SMOAA (
	APath_ID	UNIQUE_ID,
	Attr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID );

-- Class:  412.  SM to EE Data Item Access
CREATE TABLE CA_SMEED (
	APath_ID	UNIQUE_ID,
	EEdi_ID	UNIQUE_ID,
	EE_ID	UNIQUE_ID );


-- ============================================================================
-- Objects In Subsystem: State Model  
-- ============================================================================

-- Class:  501.  State Model
CREATE TABLE SM_SM (
	SM_ID	UNIQUE_ID,
	Descrip	STRING,
	Config_ID	INTEGER,
	SelfEventCountValid	BOOLEAN,
	PersistentCurrentState	BOOLEAN );

-- Class:  502.  State Model State
CREATE TABLE SM_STATE (
	SMstt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	Name	STRING,
	Numb	INTEGER,
	Final	INTEGER,
	Order	INTEGER );

-- Class:  503.  State Model Event
CREATE TABLE SM_EVT (
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	Numb	INTEGER,
	Mning	STRING,
	Is_Lbl_U	INTEGER,
	Unq_Lbl	STRING,
	Drv_Lbl	STRING,
	Descrip	STRING,
	Order	INTEGER,
	Used	BOOLEAN,
	AssignUsed	BOOLEAN,
	UsedCount	INTEGER,
	Priority	INTEGER,
	SelfDirectedOnly	BOOLEAN,
	SelfDirected	BOOLEAN,
	IsSynchronizedEvent	BOOLEAN,
	IsEventFunction	BOOLEAN );

-- Class:  504.  State Event Matrix Entry
CREATE TABLE SM_SEME (
	SMstt_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  505.  New State Transition
CREATE TABLE SM_NSTXN (
	Trans_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMstt_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  506.  Event Ignored
CREATE TABLE SM_EIGN (
	SMstt_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	Descrip	STRING );

-- Class:  507.  Cant Happen
CREATE TABLE SM_CH (
	SMstt_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	Descrip	STRING );

-- Class:  508.  Transition
CREATE TABLE SM_TXN (
	Trans_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMstt_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  509.  No Event Transition
CREATE TABLE SM_NETXN (
	Trans_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMstt_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  510.  Creation Transition
CREATE TABLE SM_CRTXN (
	Trans_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  511.  Moore State Model
CREATE TABLE SM_MOORE (
	SM_ID	UNIQUE_ID );

-- Class:  512.  Mealy State Model
CREATE TABLE SM_MEALY (
	SM_ID	UNIQUE_ID );

-- Class:  513.  Moore Action Home
CREATE TABLE SM_MOAH (
	Act_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMstt_ID	UNIQUE_ID );

-- Class:  514.  Mealy Action Home
CREATE TABLE SM_MEAH (
	Act_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	Trans_ID	UNIQUE_ID );

-- Class:  515.  Action Home
CREATE TABLE SM_AH (
	Act_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID );

-- Class:  516.  Action
CREATE TABLE SM_ACT (
	Act_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	Suc_Pars	INTEGER,
	Action_Semantics	STRING,
	Descrip	STRING,
	AutID	INTEGER,
	AbaID	UNIQUE_ID,
	SelfEventCount	INTEGER,
	NonSelfEventCount	INTEGER,
	SelectManyCount	INTEGER,
	SelectAnyWhereCount	INTEGER,
	TimerStartCount	INTEGER,
	IsSafeForInterrupts	BOOLEAN,
	IsAsynchronous	BOOLEAN,
	AsynchronousType	STRING,
	AsynchronousNumber	STRING,
	IsCallback	BOOLEAN,
	CallbackNumber	STRING,
	CallbackInitStatus	BOOLEAN,
	ReturnStmtUsed	BOOLEAN,
	BreakStmtUsed	BOOLEAN,
	ContinueStmtUsed	BOOLEAN );

-- Class:  517.  State Model Event Data Item
CREATE TABLE SM_EVTDI (
	SMedi_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	Name	STRING,
	Descrip	STRING,
	DT_ID	UNIQUE_ID,
	Order	INTEGER,
	ParamBuffer	STRING,
	OALParamBuffer	STRING );

-- Class:  518.  Event Supplemental Data
CREATE TABLE SM_SUPDT (
	SMspd_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	Non_Local	BOOLEAN );

-- Class:  519.  Supplemental Data Items
CREATE TABLE SM_SDI (
	SMedi_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID );

-- Class:  520.  Instance State Model
CREATE TABLE SM_ISM (
	SM_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	MaxSelfEvents	INTEGER,
	MaxNonSelfEvents	INTEGER );

-- Class:  521.  Assigner State Model
CREATE TABLE SM_ASM (
	SM_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	MaxSelfEvents	INTEGER,
	MaxNonSelfEvents	INTEGER );

-- Class:  522.  Polymorhic Event
CREATE TABLE SM_PEVT (
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  525.  SEM Event
CREATE TABLE SM_SEVT (
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  526.  Non Local Event
CREATE TABLE SM_NLEVT (
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	polySMevt_ID	UNIQUE_ID,
	polySM_ID	UNIQUE_ID,
	polySMspd_ID	INTEGER,
	Local_Meaning	STRING );

-- Class:  527.  Local Event
CREATE TABLE SM_LEVT (
	SMevt_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );


-- ============================================================================
-- Objects In Subsystem: Instance  
-- ============================================================================

-- Class:  600.  Instance
CREATE TABLE I_INS (
	Obj_ID	UNIQUE_ID,
	Inst_ID	UNIQUE_ID,
	Array_Index	INTEGER );

-- Class:  601.  Value
CREATE TABLE I_AVL (
	Obj_ID	UNIQUE_ID,
	Inst_ID	UNIQUE_ID,
	Attr_ID	UNIQUE_ID,
	Value	STRING );

-- Class:  602.  Link
CREATE TABLE I_LNK (
	Link_ID	UNIQUE_ID,
	Rel_ID	UNIQUE_ID,
	From_Obj_ID	UNIQUE_ID,
	From_Inst_ID	UNIQUE_ID,
	To_Obj_ID	UNIQUE_ID,
	To_Inst_ID	UNIQUE_ID,
	Assoc_Obj_ID	UNIQUE_ID,
	Assoc_Inst_ID	UNIQUE_ID,
	Txt_Phrs	STRING );

-- Class:  603.  Event Instance
CREATE TABLE I_EVI (
	EvtInst_ID	UNIQUE_ID,
	Inst_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID );

-- Class:  604.  Actual Data Item
CREATE TABLE I_ADI (
	EvtInst_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMevt_ID	UNIQUE_ID,
	SMspd_ID	UNIQUE_ID,
	SMedi_ID	UNIQUE_ID,
	Value	STRING );

-- Class:  605.  Function Invocation
CREATE TABLE I_FIN (
	FuncInv_ID	UNIQUE_ID,
	Sync_ID	UNIQUE_ID );

-- Class:  606.  Actual Function Parameter
CREATE TABLE I_AFP (
	FuncInv_ID	UNIQUE_ID,
	Sync_ID	UNIQUE_ID,
	SParm_ID	UNIQUE_ID,
	Value	STRING );

-- Class:  607.  State Machine
CREATE TABLE I_SMC (
	Obj_ID	UNIQUE_ID,
	Inst_ID	UNIQUE_ID,
	SM_ID	UNIQUE_ID,
	SMstt_ID	UNIQUE_ID );

-- Class:  608.  Transformer Invocation
CREATE TABLE I_TRI (
	TrInv_ID	UNIQUE_ID,
	Tfr_ID	UNIQUE_ID,
	Obj_ID	UNIQUE_ID,
	Inst_ID	UNIQUE_ID );

-- Class:  609.  Actual Transformer Parameter
CREATE TABLE I_ATP (
	TrInv_ID	UNIQUE_ID,
	Tfr_ID	UNIQUE_ID,
	TParm_ID	UNIQUE_ID,
	Value	STRING );

-- Class:  610.  Bridge Invocation
CREATE TABLE I_BRI (
	BrgInv_ID	UNIQUE_ID,
	Brg_ID	UNIQUE_ID );

-- Class:  611.  Actual Bridge Parameter
CREATE TABLE I_ABP (
	BrgInv_ID	UNIQUE_ID,
	Brg_ID	UNIQUE_ID,
	BParm_ID	UNIQUE_ID,
	Value	STRING );


-- ============================================================================
-- Objects In Subsystem: Version Management  
-- ============================================================================

-- Class:  905.  Component Version in Configuration Version
CREATE TABLE V_CIOV (
	Domain_Name	STRING,
	Component_id	UNIQUE_ID,
	Parent_Component_id	UNIQUE_ID,
	Component_type	INTEGER,
	Component_Branch_Name	STRING,
	Component_Version_Num	INTEGER,
	Pinned	BOOLEAN,
	Abstract	STRING );


-- ============================================================================
-- Objects In Subsystem: Translation Extensions  
-- ============================================================================

-- Class:  2000.  Special Where Clause
CREATE TABLE TE_SWC (
	Obj_Kl	STRING,
	Where_Spec	STRING,
	Key	STRING,
	Ret_Val	BOOLEAN,
	Built_In	BOOLEAN,
	Oid_ID	INTEGER );

-- Class:  2001.  Action Scratch Pad
CREATE TABLE TE_ASP (
	AspID	INTEGER,
	Sync_Supp_Data	BOOLEAN,
	SpecialWhereValid	BOOLEAN,
	Indent_Level	INTEGER,
	Indentation	STRING,
	IsBridgeObject	BOOLEAN,
	CurrentBlock	INTEGER,
	CurrentBlockDepth	INTEGER,
	LoopDepth	INTEGER,
	OIV_Counter	INTEGER,
	ReturnStmtUsed	BOOLEAN,
	ObjVarTracking	BOOLEAN,
	RvalReturnTracking	BOOLEAN );

-- Class:  2002.  Static Analysis Information
CREATE TABLE TE_SAIB (
	RegisteredDomName	STRING,
	RegisteredDomID	INTEGER,
	RepositoryName	STRING,
	RepositoryVersion	INTEGER,
	StartTimeStamp	STRING,
	EndTimeStamp	STRING,
	TextBuffer	STRING,
	SpecialWhereBuffer	STRING,
	MaxSelfEvents	INTEGER,
	MaxNonSelfEvents	INTEGER,
	MaxManyDeclared	INTEGER,
	MaxManyTransient	INTEGER,
	TIM_MaxTimers	INTEGER );

-- Class:  2003.  Domain Limits System Populator
CREATE TABLE TE_DLSP (
	RegisteredDomName	STRING,
	RegisteredDomID	INTEGER,
	SystemID	INTEGER,
	RepositoryName	STRING,
	RepositoryVersion	INTEGER,
	MaxObjExtent	INTEGER,
	MaxRelExtent	INTEGER,
	MaxSelectExtent	INTEGER,
	MaxSelfEvents	INTEGER,
	MaxNonSelfEvents	INTEGER,
	MaxPriorityEvents	INTEGER,
	MaxTimers	INTEGER,
	InterleavedBridges	INTEGER,
	CharacterEncoding	STRING,
	PEIClassCount	INTEGER,
	PersistentClassCount	INTEGER );

-- Class:  2004.  System
CREATE TABLE TE_SYS (
	SystemID	INTEGER,
	ModelCompilerName	STRING,
	ModelCompilerVersion	STRING,
	ModelCompilerSerNum	STRING,
	ModelCompilerKey	STRING,
	BridgePointLicenseKey	STRING,
	TextBuffer	STRING,
	ExecutableName	STRING,
	MaxStringLen	INTEGER,
	MaxObjExtent	INTEGER,
	MaxRelExtent	INTEGER,
	MaxSelectExtent	INTEGER,
	TotalContainers	INTEGER,
	MaxSelfEvents	INTEGER,
	MaxNonSelfEvents	INTEGER,
	MaxTimers	INTEGER,
	MaxInterleavedBridges	INTEGER,
	MaxInterleavedBridgeDataSize	INTEGER,
	CollectionsFlavor	INTEGER,
	TargetMonitorEnabled	BOOLEAN,
	ForcePriorityEvents	BOOLEAN,
	SystemPrefix	STRING,
	SystemMethodPrefix	STRING,
	SystemTypePrefix	STRING,
	SystemDefinePrefix	STRING,
	SystemFilePrefix	STRING,
	PEIClassCount	INTEGER,
	PersistentClassCount	INTEGER,
	PersistInstanceCacheDepth	INTEGER,
	PersistLinkCacheDepth	INTEGER,
	TaskingFlavor	STRING,
	NumberOfTasks	INTEGER,
	SerializeProcessing	BOOLEAN );

-- Class:  2005.  Dispatcher
CREATE TABLE TE_DISP (
	Dispatcher_ID	INTEGER,
	SystemID	INTEGER,
	Name	STRING,
	Descrip	STRING );

-- Class:  2006.  Message Queue
CREATE TABLE TE_QUEUE (
	Queue_ID	INTEGER,
	Dispatcher_ID	INTEGER,
	Type	INTEGER,
	Descrip	STRING,
	RenderCode	BOOLEAN,
	MaxDepth	INTEGER,
	Blocking	BOOLEAN,
	PriorityLevel	INTEGER,
	InstEnabled	BOOLEAN );

-- Class:  2007.  Action Under Translation
CREATE TABLE TE_AUT (
	AutID	INTEGER,
	AspID	INTEGER,
	SemanticsType	INTEGER,
	AbaID	UNIQUE_ID );

-- Class:  2008.  Action Block Anchor
CREATE TABLE TE_ABA (
	AbaID	UNIQUE_ID );

-- Class:  2009.  Action Block
CREATE TABLE TE_BLOCK (
	AbaID	UNIQUE_ID,
	Number	INTEGER,
	PreviousNumber	INTEGER,
	Depth	INTEGER,
	Type	INTEGER,
	Closing	BOOLEAN,
	Active	BOOLEAN );

-- Class:  2010.  Object Instance Variable
CREATE TABLE TE_OIV (
	OivID	INTEGER,
	Name	STRING,
	VarName	STRING,
	TypeCode	INTEGER,
	DeclareBlock	INTEGER,
	Obj_ID	UNIQUE_ID );

-- Class:  2011.  Object Instance Reference
CREATE TABLE TE_OIR (
	AbaID	UNIQUE_ID,
	Number	INTEGER,
	OivID	INTEGER );

-- Class:  2012.  Domain Under Translation
CREATE TABLE TE_DUT (
	Dom_ID	UNIQUE_ID );


-- ============================================================================
-- Relationships In Subsystem: Domain  
-- ============================================================================
  
CREATE ROP REF_ID R1	FROM MC S_SS	(Dom_ID)
			  TO 1  S_DOM	(Dom_ID);

CREATE ROP REF_ID R2	FROM MC O_OBJ	(SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R3	FROM MC O_IOBJ	(SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R4	FROM MC R_REL	(SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R5	FROM MC CA_COMM	(SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R6	FROM MC CA_ACC	(SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R7	FROM MC S_EEM	(SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R8	FROM MC S_EE	(Dom_ID)
			  TO 1  S_DOM	(Dom_ID);

CREATE ROP REF_ID R9	FROM MC S_EEM	(EE_ID)
			  TO 1  S_EE	(EE_ID);

CREATE ROP REF_ID R10	FROM MC S_EEEVT	(EE_ID)
			  TO 1  S_EE	(EE_ID);

CREATE ROP REF_ID R11	FROM MC S_EEDI	(EE_ID)
			  TO 1  S_EE	(EE_ID);

CREATE ROP REF_ID R12	FROM MC S_EEEDI	(EE_ID)
			  TO 1  S_EE	(EE_ID);

CREATE ROP REF_ID R13	FROM MC S_EEEDT	(EEedi_ID, EE_ID)
			  TO 1  S_EEEDI	(EEedi_ID, EE_ID);

CREATE ROP REF_ID R13	FROM MC S_EEEDT	(EEevt_ID, EE_ID)
			  TO 1  S_EEEVT	(EEevt_ID, EE_ID);

CREATE ROP REF_ID R14	FROM MC S_DT	(Dom_ID)
			  TO 1  S_DOM	(Dom_ID);

CREATE ROP REF_ID R15	FROM MC S_EEDI	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R16	FROM MC S_EEEDI	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R17	FROM 1C S_CDT	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R17	FROM 1C S_UDT	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R17	FROM 1C S_EDT	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R18	FROM MC S_UDT	(CDT_ID)
			  TO 1  S_CDT	(DT_ID);

CREATE ROP REF_ID R19	FROM MC S_BRG	(EE_ID)
			  TO 1  S_EE	(EE_ID);

CREATE ROP REF_ID R20	FROM MC S_BRG	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R21	FROM MC S_BPARM	(Brg_ID)
			  TO 1  S_BRG	(Brg_ID);

CREATE ROP REF_ID R22	FROM MC S_BPARM	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R23	FROM MC S_SYNC	(Dom_ID)
			  TO 1  S_DOM	(Dom_ID);

CREATE ROP REF_ID R24	FROM MC S_SPARM	(Sync_ID)
			  TO 1  S_SYNC	(Sync_ID);

CREATE ROP REF_ID R25	FROM MC S_SYNC	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R26	FROM MC S_SPARM	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R27	FROM MC S_ENUM	(EDT_ID)
			  TO 1  S_EDT	(DT_ID);

CREATE ROP REF_ID R28	FROM MC S_DOM	(Sys_ID)
			  TO 1  S_SYS	(Sys_ID);

CREATE ROP REF_ID R29	FROM MC S_FPK	(Dom_ID)
			  TO 1C S_DOM	(Dom_ID);

CREATE ROP REF_ID R30	FROM 1C S_FPIP	(FunPack_ID)
			  TO 1  S_FPK	(FunPack_ID);

CREATE ROP REF_ID R31	FROM MC S_FIP	(FunPack_ID)
			  TO 1  S_FPK	(FunPack_ID);

CREATE ROP REF_ID R31	FROM 1  S_FIP	(Sync_ID)
			  TO 1  S_SYNC	(Sync_ID);

CREATE ROP REF_ID R32	FROM MC S_FPK	(Parent_FunPack_ID)
			  TO 1C S_FPIP	(FunPack_ID);

CREATE ROP REF_ID R33	FROM MC S_EEIP	(EEPack_ID)
			  TO 1  S_EEPK	(EEPack_ID);

CREATE ROP REF_ID R33	FROM 1  S_EEIP	(EE_ID)
			  TO 1  S_EE	(EE_ID);

CREATE ROP REF_ID R34	FROM 1C S_EEPIP	(EEPack_ID)
			  TO 1  S_EEPK	(EEPack_ID);

CREATE ROP REF_ID R35	FROM MC S_EEPK	(Parent_EEPack_ID)
			  TO 1C S_EEPIP	(EEPack_ID);

CREATE ROP REF_ID R36	FROM MC S_EEPK	(Dom_ID)
			  TO 1C S_DOM	(Dom_ID);

CREATE ROP REF_ID R37	FROM 1C S_DPIP	(DatPack_ID)
			  TO 1  S_DPK	(DatPack_ID);

CREATE ROP REF_ID R38	FROM MC S_DPK	(Parent_DatPack_ID)
			  TO 1C S_DPIP	(DatPack_ID);

CREATE ROP REF_ID R39	FROM MC S_DIP	(DatPack_ID)
			  TO 1  S_DPK	(DatPack_ID);

CREATE ROP REF_ID R39	FROM 1  S_DIP	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R40	FROM MC S_DPK	(Dom_ID)
			  TO 1C S_DOM	(Dom_ID);

CREATE ROP REF_ID R41	FROM MC S_SIS	(Parent_SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R42	FROM 1C S_SIS	(Child_SS_ID)
			  TO 1  S_SS	(SS_ID);

CREATE ROP REF_ID R43	FROM MC S_SID	(Dom_ID)
			  TO 1  S_DOM	(Dom_ID);

CREATE ROP REF_ID R43	FROM 1C S_SID	(SS_ID)
			  TO 1  S_SS	(SS_ID);


-- ============================================================================
-- Relationships In Subsystem: Class  
-- ============================================================================
  
CREATE ROP REF_ID R101	FROM MC O_IOBJ	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R102	FROM MC O_ATTR	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R103	FROM 1C O_ATTR	(Obj_ID, PAttr_ID) PHRASE 'succeeds'
			  TO 1C O_ATTR	(Obj_ID, Attr_ID) PHRASE 'precedes';

CREATE ROP REF_ID R104	FROM MC O_ID	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R105	FROM MC O_OIDA	(Obj_ID, Oid_ID)
			  TO 1  O_ID	(Obj_ID, Oid_ID);

CREATE ROP REF_ID R105	FROM MC O_OIDA	(Obj_ID, Attr_ID)
			  TO 1  O_ATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R106	FROM 1C O_BATTR	(Obj_ID, Attr_ID)
			  TO 1  O_ATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R106	FROM 1C O_RATTR	(Obj_ID, Attr_ID)
			  TO 1  O_ATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R107	FROM 1C O_DBATTR	(Obj_ID, Attr_ID)
			  TO 1  O_BATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R107	FROM 1C O_NBATTR	(Obj_ID, Attr_ID)
			  TO 1  O_BATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R108	FROM M  O_REF	(Obj_ID, Attr_ID)
			  TO 1  O_RATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R109	FROM MC R_RTO	(Obj_ID, Oid_ID)
			  TO 1C O_ID	(Obj_ID, Oid_ID);

CREATE ROP REF_ID R110	FROM M  O_RTIDA	(Obj_ID, Rel_ID, Oid_ID, OIR_ID)
			  TO 1  R_RTO	(Obj_ID, Rel_ID, Oid_ID, OIR_ID);

CREATE ROP REF_ID R110	FROM MC O_RTIDA	(Oid_ID, Attr_ID, Obj_ID)
			  TO 1  O_OIDA	(Oid_ID, Attr_ID, Obj_ID);

CREATE ROP REF_ID R111	FROM M  O_REF	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RGO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R111	FROM M  O_REF	(ROid_ID, RAttr_ID, RObj_ID, ROIR_ID, Rel_ID)
			  TO 1  O_RTIDA	(Oid_ID, Attr_ID, Obj_ID, OIR_ID, Rel_ID);

CREATE ROP REF_ID R112	FROM 1C O_REF	(PARef_ID) PHRASE 'succeeds'
			  TO 1C O_REF	(ARef_ID) PHRASE 'precedes';

CREATE ROP REF_ID R113	FROM MC O_RATTR	(BObj_ID, BAttr_ID)
			  TO 1  O_BATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R114	FROM MC O_ATTR	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R115	FROM MC O_TFR	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R116	FROM MC O_TFR	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R117	FROM MC O_TPARM	(Tfr_ID)
			  TO 1  O_TFR	(Tfr_ID);

CREATE ROP REF_ID R118	FROM MC O_TPARM	(DT_ID)
			  TO 1  S_DT	(DT_ID);


-- ============================================================================
-- Relationships In Subsystem: Association  
-- ============================================================================
  
CREATE ROP REF_ID R201	FROM M  R_OIR	(Rel_ID)
			  TO 1  R_REL	(Rel_ID);

CREATE ROP REF_ID R201	FROM MC R_OIR	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R202	FROM MC R_OIR	(IObj_ID)
			  TO 1C O_IOBJ	(IObj_ID);

CREATE ROP REF_ID R203	FROM 1C R_RTO	(Obj_ID, OIR_ID, Rel_ID)
			  TO 1  R_OIR	(Obj_ID, OIR_ID, Rel_ID);

CREATE ROP REF_ID R203	FROM 1C R_RGO	(Obj_ID, OIR_ID, Rel_ID)
			  TO 1  R_OIR	(Obj_ID, OIR_ID, Rel_ID);

CREATE ROP REF_ID R203	FROM 1C R_CONE	(Obj_ID, OIR_ID, Rel_ID)
			  TO 1  R_OIR	(Obj_ID, OIR_ID, Rel_ID);

CREATE ROP REF_ID R203	FROM 1C R_COTH	(Obj_ID, OIR_ID, Rel_ID)
			  TO 1  R_OIR	(Obj_ID, OIR_ID, Rel_ID);

CREATE ROP REF_ID R204	FROM 1C R_SUPER	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RTO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R204	FROM 1C R_PART	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RTO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R204	FROM 1C R_AONE	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RTO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R204	FROM 1C R_AOTH	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RTO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R205	FROM 1C R_SUB	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RGO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R205	FROM 1C R_FORM	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RGO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R205	FROM 1C R_ASSR	(OIR_ID, Obj_ID, Rel_ID)
			  TO 1  R_RGO	(OIR_ID, Obj_ID, Rel_ID);

CREATE ROP REF_ID R206	FROM 1C R_SIMP	(Rel_ID)
			  TO 1  R_REL	(Rel_ID);

CREATE ROP REF_ID R206	FROM 1C R_COMP	(Rel_ID)
			  TO 1  R_REL	(Rel_ID);

CREATE ROP REF_ID R206	FROM 1C R_ASSOC	(Rel_ID)
			  TO 1  R_REL	(Rel_ID);

CREATE ROP REF_ID R206	FROM 1C R_SUBSUP	(Rel_ID)
			  TO 1  R_REL	(Rel_ID);

CREATE ROP REF_ID R207	FROM 1  R_PART	(Rel_ID)
			  TO 1  R_SIMP	(Rel_ID);

CREATE ROP REF_ID R208	FROM 1C R_FORM	(Rel_ID)
			  TO 1  R_SIMP	(Rel_ID);

CREATE ROP REF_ID R209	FROM 1  R_AONE	(Rel_ID)
			  TO 1  R_ASSOC	(Rel_ID);

CREATE ROP REF_ID R210	FROM 1  R_AOTH	(Rel_ID)
			  TO 1  R_ASSOC	(Rel_ID);

CREATE ROP REF_ID R211	FROM 1  R_ASSR	(Rel_ID)
			  TO 1  R_ASSOC	(Rel_ID);

CREATE ROP REF_ID R212	FROM 1  R_SUPER	(Rel_ID)
			  TO 1  R_SUBSUP	(Rel_ID);

CREATE ROP REF_ID R213	FROM MC R_SUB	(Rel_ID)
			  TO 1  R_SUBSUP	(Rel_ID);

CREATE ROP REF_ID R214	FROM 1  R_CONE	(Rel_ID)
			  TO 1  R_COMP	(Rel_ID);

CREATE ROP REF_ID R215	FROM 1  R_COTH	(Rel_ID)
			  TO 1  R_COMP	(Rel_ID);


-- ============================================================================
-- Relationships In Subsystem: Communication And Access  
-- ============================================================================
  
CREATE ROP REF_ID R401	FROM 1C CA_EESMC	(CPath_ID)
			  TO 1  CA_COMM	(CPath_ID);

CREATE ROP REF_ID R401	FROM 1C CA_SMEEC	(CPath_ID)
			  TO 1  CA_COMM	(CPath_ID);

CREATE ROP REF_ID R401	FROM 1C CA_SMSMC	(CPath_ID)
			  TO 1  CA_COMM	(CPath_ID);

CREATE ROP REF_ID R402	FROM MC CA_EESMC	(EE_ID, EEmod_ID)
			  TO 1  S_EEM	(EE_ID, EEmod_ID);

CREATE ROP REF_ID R403	FROM MC CA_EESMC	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R404	FROM MC CA_EESME	(CPath_ID)
			  TO 1  CA_EESMC	(CPath_ID);

CREATE ROP REF_ID R405	FROM MC CA_EESME	(SMevt_ID, SM_ID)
			  TO 1  SM_EVT	(SMevt_ID, SM_ID);

CREATE ROP REF_ID R406	FROM MC CA_SMSMC	(OSM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R407	FROM MC CA_SMSMC	(DSM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R408	FROM MC CA_SMSME	(CPath_ID)
			  TO 1  CA_SMSMC	(CPath_ID);

CREATE ROP REF_ID R409	FROM MC CA_SMSME	(SMevt_ID, SM_ID)
			  TO 1  SM_EVT	(SMevt_ID, SM_ID);

CREATE ROP REF_ID R410	FROM MC CA_SMEEC	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R411	FROM MC CA_SMEEC	(EE_ID, EEmod_ID)
			  TO 1  S_EEM	(EE_ID, EEmod_ID);

CREATE ROP REF_ID R412	FROM MC CA_SMEEE	(CPath_ID)
			  TO 1  CA_SMEEC	(CPath_ID);

CREATE ROP REF_ID R413	FROM MC CA_SMEEE	(EEevt_ID, EE_ID)
			  TO 1  S_EEEVT	(EEevt_ID, EE_ID);

CREATE ROP REF_ID R414	FROM MC CA_SMSMC	(DIObj_ID)
			  TO 1C O_IOBJ	(IObj_ID);

CREATE ROP REF_ID R415	FROM 1C CA_SMOA	(APath_ID)
			  TO 1  CA_ACC	(APath_ID);

CREATE ROP REF_ID R415	FROM 1C CA_SMEEA	(APath_ID)
			  TO 1  CA_ACC	(APath_ID);

CREATE ROP REF_ID R416	FROM MC CA_ACC	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R417	FROM MC CA_SMOA	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R418	FROM MC CA_SMOAA	(Obj_ID, APath_ID)
			  TO 1  CA_SMOA	(Obj_ID, APath_ID);

CREATE ROP REF_ID R419	FROM MC CA_SMOAA	(Obj_ID, Attr_ID)
			  TO 1  O_ATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R420	FROM MC CA_SMOA	(IObj_ID)
			  TO 1C O_IOBJ	(IObj_ID);

CREATE ROP REF_ID R421	FROM MC CA_SMEEA	(EE_ID, EEmod_ID)
			  TO 1  S_EEM	(EE_ID, EEmod_ID);

CREATE ROP REF_ID R422	FROM MC CA_SMEED	(EE_ID, APath_ID)
			  TO 1  CA_SMEEA	(EE_ID, APath_ID);

CREATE ROP REF_ID R423	FROM MC CA_SMEED	(EEdi_ID, EE_ID)
			  TO 1  S_EEDI	(EEdi_ID, EE_ID);

CREATE ROP REF_ID R424	FROM MC CA_SMSMC	(OIObj_ID)
			  TO 1C O_IOBJ	(IObj_ID);

CREATE ROP REF_ID R425	FROM MC CA_ACC	(IObj_ID)
			  TO 1C O_IOBJ	(IObj_ID);


-- ============================================================================
-- Relationships In Subsystem: State Model  
-- ============================================================================
  
CREATE ROP REF_ID R501	FROM MC SM_STATE	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R502	FROM MC SM_EVT	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R503	FROM MC SM_SEME	(SM_ID, SMstt_ID)
			  TO 1  SM_STATE	(SM_ID, SMstt_ID);

CREATE ROP REF_ID R503	FROM MC SM_SEME	(SM_ID, SMevt_ID, SMspd_ID)
			  TO 1  SM_SEVT	(SM_ID, SMevt_ID, SMspd_ID);

CREATE ROP REF_ID R504	FROM 1C SM_NSTXN	(SM_ID, SMspd_ID, SMevt_ID, SMstt_ID)
			  TO 1  SM_SEME	(SM_ID, SMspd_ID, SMevt_ID, SMstt_ID);

CREATE ROP REF_ID R504	FROM 1C SM_EIGN	(SM_ID, SMspd_ID, SMevt_ID, SMstt_ID)
			  TO 1  SM_SEME	(SM_ID, SMspd_ID, SMevt_ID, SMstt_ID);

CREATE ROP REF_ID R504	FROM 1C SM_CH	(SM_ID, SMspd_ID, SMevt_ID, SMstt_ID)
			  TO 1  SM_SEME	(SM_ID, SMspd_ID, SMevt_ID, SMstt_ID);

CREATE ROP REF_ID R505	FROM MC SM_TXN	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R506	FROM MC SM_TXN	(SM_ID, SMstt_ID, SMspd_ID)
			  TO 1  SM_STATE	(SM_ID, SMstt_ID, SMspd_ID);

CREATE ROP REF_ID R507	FROM 1C SM_NETXN	(SM_ID, Trans_ID)
			  TO 1  SM_TXN	(SM_ID, Trans_ID);

CREATE ROP REF_ID R507	FROM 1C SM_NSTXN	(SM_ID, Trans_ID)
			  TO 1  SM_TXN	(SM_ID, Trans_ID);

CREATE ROP REF_ID R507	FROM 1C SM_CRTXN	(SM_ID, Trans_ID)
			  TO 1  SM_TXN	(SM_ID, Trans_ID);

CREATE ROP REF_ID R508	FROM MC SM_NETXN	(SM_ID, SMstt_ID)
			  TO 1  SM_STATE	(SM_ID, SMstt_ID);

CREATE ROP REF_ID R509	FROM 1C SM_CRTXN	(SMevt_ID, SM_ID)
			  TO 1C SM_LEVT	(SMevt_ID, SM_ID);

CREATE ROP REF_ID R510	FROM 1C SM_MOORE	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R510	FROM 1C SM_MEALY	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R511	FROM MC SM_MOAH	(SM_ID)
			  TO 1  SM_MOORE	(SM_ID);

CREATE ROP REF_ID R511	FROM 1C SM_MOAH	(SM_ID, SMstt_ID)
			  TO 1  SM_STATE	(SM_ID, SMstt_ID);

CREATE ROP REF_ID R512	FROM MC SM_MEAH	(SM_ID)
			  TO 1  SM_MEALY	(SM_ID);

CREATE ROP REF_ID R512	FROM 1C SM_MEAH	(SM_ID, Trans_ID)
			  TO 1  SM_TXN	(SM_ID, Trans_ID);

CREATE ROP REF_ID R513	FROM 1C SM_MOAH	(SM_ID, Act_ID)
			  TO 1  SM_AH	(SM_ID, Act_ID);

CREATE ROP REF_ID R513	FROM 1C SM_MEAH	(SM_ID, Act_ID)
			  TO 1  SM_AH	(SM_ID, Act_ID);

CREATE ROP REF_ID R514	FROM 1  SM_AH	(SM_ID, Act_ID)
			  TO 1  SM_ACT	(SM_ID, Act_ID);

CREATE ROP REF_ID R515	FROM MC SM_ACT	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R516	FROM MC SM_EVTDI	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R517	FROM 1C SM_ASM	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R517	FROM 1C SM_ISM	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R518	FROM 1C SM_ISM	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R519	FROM 1C SM_ASM	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R520	FROM M  SM_EVT	(SM_ID, SMspd_ID)
			  TO 1  SM_SUPDT	(SM_ID, SMspd_ID);

CREATE ROP REF_ID R521	FROM MC SM_STATE	(SM_ID, SMspd_ID)
			  TO 1C SM_SUPDT	(SM_ID, SMspd_ID);

CREATE ROP REF_ID R522	FROM MC SM_SDI	(SMedi_ID, SM_ID)
			  TO 1  SM_EVTDI	(SMedi_ID, SM_ID);

CREATE ROP REF_ID R522	FROM MC SM_SDI	(SM_ID, SMspd_ID)
			  TO 1  SM_SUPDT	(SM_ID, SMspd_ID);

CREATE ROP REF_ID R523	FROM MC SM_SUPDT	(SM_ID)
			  TO 1  SM_SM	(SM_ID);

CREATE ROP REF_ID R524	FROM MC SM_EVTDI	(DT_ID)
			  TO 1  S_DT	(DT_ID);

CREATE ROP REF_ID R525	FROM 1C SM_PEVT	(SMspd_ID, SMevt_ID, SM_ID)
			  TO 1  SM_EVT	(SMspd_ID, SMevt_ID, SM_ID);

CREATE ROP REF_ID R525	FROM 1C SM_SEVT	(SMspd_ID, SMevt_ID, SM_ID)
			  TO 1  SM_EVT	(SMspd_ID, SMevt_ID, SM_ID);

CREATE ROP REF_ID R526	FROM 1C SM_LEVT	(SM_ID, SMevt_ID, SMspd_ID)
			  TO 1  SM_SEVT	(SM_ID, SMevt_ID, SMspd_ID);

CREATE ROP REF_ID R526	FROM 1C SM_NLEVT	(SM_ID, SMevt_ID, SMspd_ID)
			  TO 1  SM_SEVT	(SM_ID, SMevt_ID, SMspd_ID);

CREATE ROP REF_ID R527	FROM MC SM_NLEVT	(polySM_ID, polySMevt_ID)
			  TO 1  SM_PEVT	(SM_ID, SMevt_ID);


-- ============================================================================
-- Relationships In Subsystem: Instance  
-- ============================================================================
  
CREATE ROP REF_ID R600	FROM MC I_INS	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

CREATE ROP REF_ID R601	FROM MC I_AVL	(Obj_ID, Attr_ID)
			  TO 1  O_ATTR	(Obj_ID, Attr_ID);

CREATE ROP REF_ID R602	FROM MC I_AVL	(Inst_ID, Obj_ID)
			  TO 1  I_INS	(Inst_ID, Obj_ID);

CREATE ROP REF_ID R603	FROM MC I_LNK	(Rel_ID)
			  TO 1  R_REL	(Rel_ID);

CREATE ROP REF_ID R604	FROM MC I_LNK	(From_Inst_ID, From_Obj_ID)
			  TO 1  I_INS	(Inst_ID, Obj_ID);

CREATE ROP REF_ID R605	FROM M  I_LNK	(To_Inst_ID, To_Obj_ID)
			  TO 1  I_INS	(Inst_ID, Obj_ID);

CREATE ROP REF_ID R606	FROM MC I_LNK	(Assoc_Inst_ID, Assoc_Obj_ID)
			  TO 1C I_INS	(Inst_ID, Obj_ID);

CREATE ROP REF_ID R607	FROM MC I_EVI	(SMspd_ID, SMevt_ID, SM_ID)
			  TO 1  SM_EVT	(SMspd_ID, SMevt_ID, SM_ID);

CREATE ROP REF_ID R608	FROM MC I_ADI	(EvtInst_ID, SMevt_ID, SMspd_ID, SM_ID)
			  TO 1  I_EVI	(EvtInst_ID, SMevt_ID, SMspd_ID, SM_ID);

CREATE ROP REF_ID R609	FROM MC I_ADI	(SMedi_ID, SMspd_ID, SM_ID)
			  TO 1  SM_SDI	(SMedi_ID, SMspd_ID, SM_ID);

CREATE ROP REF_ID R610	FROM MC I_FIN	(Sync_ID)
			  TO 1  S_SYNC	(Sync_ID);

CREATE ROP REF_ID R611	FROM MC I_AFP	(FuncInv_ID, Sync_ID)
			  TO 1  I_FIN	(FuncInv_ID, Sync_ID);

CREATE ROP REF_ID R612	FROM MC I_AFP	(Sync_ID, SParm_ID)
			  TO 1  S_SPARM	(Sync_ID, SParm_ID);

CREATE ROP REF_ID R613	FROM MC I_EVI	(SM_ID, Inst_ID)
			  TO 1  I_SMC	(SM_ID, Inst_ID);

CREATE ROP REF_ID R614	FROM MC I_SMC	(SM_ID)
			  TO 1C SM_ISM	(SM_ID);

CREATE ROP REF_ID R615	FROM 1  I_SMC	(SM_ID)
			  TO 1C SM_ASM	(SM_ID);

CREATE ROP REF_ID R616	FROM 1C I_SMC	(Inst_ID, Obj_ID)
			  TO 1C I_INS	(Inst_ID, Obj_ID);

CREATE ROP REF_ID R617	FROM MC I_TRI	(Tfr_ID)
			  TO 1  O_TFR	(Tfr_ID);

CREATE ROP REF_ID R618	FROM MC I_ATP	(Tfr_ID, TrInv_ID)
			  TO 1  I_TRI	(Tfr_ID, TrInv_ID);

CREATE ROP REF_ID R619	FROM MC I_ATP	(TParm_ID)
			  TO 1  O_TPARM	(TParm_ID);

CREATE ROP REF_ID R620	FROM MC I_BRI	(Brg_ID)
			  TO 1  S_BRG	(Brg_ID);

CREATE ROP REF_ID R621	FROM MC I_ABP	(BrgInv_ID, Brg_ID)
			  TO 1  I_BRI	(BrgInv_ID, Brg_ID);

CREATE ROP REF_ID R622	FROM MC I_ABP	(BParm_ID)
			  TO 1  S_BPARM	(BParm_ID);

CREATE ROP REF_ID R623	FROM MC I_TRI	(Inst_ID, Obj_ID)
			  TO 1C I_INS	(Inst_ID, Obj_ID);


-- ============================================================================
-- Relationships In Subsystem: Version Management  
-- ============================================================================
  

-- ============================================================================
-- Relationships In Subsystem: Translation Extensions  
-- ============================================================================
  
CREATE ROP REF_ID R2000	FROM 1C TE_AUT	(AspID)
			  TO 1C TE_ASP	(AspID);

CREATE ROP REF_ID R2001	FROM MC TE_SWC	(Obj_Kl)
			  TO 1C O_OBJ	(Key_Lett);

CREATE ROP REF_ID R2002	FROM MC TE_DLSP	(SystemID)
			  TO 1C TE_SYS	(SystemID);

CREATE ROP REF_ID R2003	FROM MC TE_DISP	(SystemID)
			  TO 1C TE_SYS	(SystemID);

CREATE ROP REF_ID R2004	FROM MC TE_QUEUE	(Dispatcher_ID)
			  TO 1C TE_DISP	(Dispatcher_ID);

CREATE ROP REF_ID R2009	FROM 1C O_TFR	(AutID)
			  TO 1C TE_AUT	(AutID);

CREATE ROP REF_ID R2009	FROM 1C S_SYNC	(AutID)
			  TO 1C TE_AUT	(AutID);

CREATE ROP REF_ID R2009	FROM 1C SM_ACT	(AutID)
			  TO 1C TE_AUT	(AutID);

CREATE ROP REF_ID R2009	FROM 1C S_BRG	(AutID)
			  TO 1C TE_AUT	(AutID);

CREATE ROP REF_ID R2009	FROM 1C O_DBATTR	(AutID)
			  TO 1C TE_AUT	(AutID);

CREATE ROP REF_ID R2010	FROM 1C O_TFR	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2010	FROM 1C S_BRG	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2010	FROM 1C O_DBATTR	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2010	FROM 1C S_SYNC	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2010	FROM 1C SM_ACT	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2011	FROM MC TE_BLOCK	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2012	FROM 1C TE_BLOCK	(AbaID, PreviousNumber) PHRASE 'succeeds'
			  TO 1C TE_BLOCK	(AbaID, Number) PHRASE 'preceeds';

CREATE ROP REF_ID R2014	FROM MC TE_OIR	(OivID)
			  TO 1  TE_OIV	(OivID);

CREATE ROP REF_ID R2014	FROM MC TE_OIR	(AbaID, Number)
			  TO 1  TE_BLOCK	(AbaID, Number);

CREATE ROP REF_ID R2015	FROM 1C TE_OIV	(Obj_ID)
			  TO 1C O_OBJ	(Obj_ID);

CREATE ROP REF_ID R2016	FROM 1C TE_AUT	(AbaID)
			  TO 1C TE_ABA	(AbaID);

CREATE ROP REF_ID R2017	FROM 1C TE_DUT	(Dom_ID)
			  TO 1  S_DOM	(Dom_ID);


-- ============================================================================
-- Pre-instantiated table inserts
-- ============================================================================

INSERT INTO TE_ASP VALUES (
	0,
	FALSE,
	FALSE,
	0,
	'',
	FALSE,
	0,
	0,
	0,
	0,
	FALSE,
	FALSE,
	FALSE );

INSERT INTO TE_SAIB VALUES (
	'',
	0,
	'',
	0,
	'',
	'',
	'',
	'',
	0,
	0,
	0,
	0,
	0 );


-- Exercise C - CPP Data Types
CREATE TABLE S_CPPTYPE (
	DT_ID	UNIQUE_ID,
	CppType	STRING
);

-- BP 6.1D content: domain syschar: 3

INSERT INTO S_DOM
	VALUES (94514,
	'mc3020_meta',
	'

Notes:
',
	1,
	1);
INSERT INTO S_CDT
	VALUES (524289,
	0);
INSERT INTO S_DT
	VALUES (524289,
	94514,
	'void',
	'');
INSERT INTO S_CDT
	VALUES (524290,
	1);
INSERT INTO S_DT
	VALUES (524290,
	94514,
	'boolean',
	'');
INSERT INTO S_CDT
	VALUES (524291,
	2);
INSERT INTO S_DT
	VALUES (524291,
	94514,
	'integer',
	'');
INSERT INTO S_CDT
	VALUES (524292,
	3);
INSERT INTO S_DT
	VALUES (524292,
	94514,
	'real',
	'');
INSERT INTO S_CDT
	VALUES (524293,
	4);
INSERT INTO S_DT
	VALUES (524293,
	94514,
	'string',
	'');
INSERT INTO S_CDT
	VALUES (524294,
	5);
INSERT INTO S_DT
	VALUES (524294,
	94514,
	'unique_id',
	'');
INSERT INTO S_CDT
	VALUES (524295,
	6);
INSERT INTO S_DT
	VALUES (524295,
	94514,
	'state<State_Model>',
	'');
INSERT INTO S_CDT
	VALUES (524296,
	7);
INSERT INTO S_DT
	VALUES (524296,
	94514,
	'same_as<Base_Attribute>',
	'');
INSERT INTO S_CDT
	VALUES (524297,
	8);
INSERT INTO S_DT
	VALUES (524297,
	94514,
	'inst_ref<Object>',
	'');
INSERT INTO S_CDT
	VALUES (524298,
	9);
INSERT INTO S_DT
	VALUES (524298,
	94514,
	'inst_ref_set<Object>',
	'');
INSERT INTO S_CDT
	VALUES (524299,
	10);
INSERT INTO S_DT
	VALUES (524299,
	94514,
	'inst<Event>',
	'');
INSERT INTO S_CDT
	VALUES (524300,
	11);
INSERT INTO S_DT
	VALUES (524300,
	94514,
	'inst<Mapping>',
	'');
INSERT INTO S_CDT
	VALUES (524301,
	12);
INSERT INTO S_DT
	VALUES (524301,
	94514,
	'inst_ref<Mapping>',
	'');
INSERT INTO S_UDT
	VALUES (524302,
	524300,
	1);
INSERT INTO S_DT
	VALUES (524302,
	94514,
	'date',
	'');
INSERT INTO S_UDT
	VALUES (524303,
	524300,
	2);
INSERT INTO S_DT
	VALUES (524303,
	94514,
	'timestamp',
	'');
INSERT INTO S_UDT
	VALUES (524304,
	524301,
	3);
INSERT INTO S_DT
	VALUES (524304,
	94514,
	'inst_ref<Timer>',
	'');
INSERT INTO S_UDT
	VALUES (524305,
	524294,
	0);
INSERT INTO S_DT
	VALUES (524305,
	94514,
	'arbitrary_id',
	'Arbitrary ID with core data type of unique_id.');
INSERT INTO S_SYNC
	VALUES (1,
	94514,
	'setup',
	'',
	'// We don''t have any PEI, and don''t want to do anything here.',
	524289,
	1);
INSERT INTO S_SYNC
	VALUES (2,
	94514,
	'test',
	'',
	'// We don''t have any PEIs to check or tests to run, just trigger xit.
::xit();',
	524289,
	1);
INSERT INTO S_SYNC
	VALUES (3,
	94514,
	'xit',
	'',
	'// No instances to delete, just call arch::shutdown
ARCH::shutdown();',
	524289,
	1);
INSERT INTO S_EE
	VALUES (1,
	'Logging',
	'',
	'LOG',
	94514);
INSERT INTO S_BRG
	VALUES (1,
	1,
	'LogFailure',
	'',
	0,
	524289,
	'',
	1);
INSERT INTO S_BPARM
	VALUES (1,
	1,
	'message',
	524293,
	0);
INSERT INTO S_BRG
	VALUES (2,
	1,
	'LogSuccess',
	'',
	0,
	524289,
	'',
	1);
INSERT INTO S_BPARM
	VALUES (2,
	2,
	'message',
	524293,
	0);
INSERT INTO S_EE
	VALUES (2,
	'Architecture',
	'',
	'ARCH',
	94514);
INSERT INTO S_BRG
	VALUES (3,
	2,
	'shutdown',
	'',
	0,
	524289,
	'',
	1);
INSERT INTO S_EE
	VALUES (3,
	'Non-volatile storage',
	'',
	'',
	94514);
INSERT INTO S_BRG
	VALUES (5,
	3,
	'format',
	'',
	0,
	524291,
	'',
	1);
INSERT INTO S_BRG
	VALUES (6,
	3,
	'checksum',
	'',
	0,
	524291,
	'',
	1);
INSERT INTO S_BPARM
	VALUES (3,
	6,
	'first',
	524291,
	0);
INSERT INTO S_BPARM
	VALUES (4,
	6,
	'second',
	524291,
	0);
INSERT INTO S_BRG
	VALUES (7,
	3,
	'version',
	'',
	0,
	524291,
	'',
	1);
INSERT INTO S_BPARM
	VALUES (5,
	7,
	'first',
	524291,
	0);
INSERT INTO S_BPARM
	VALUES (6,
	7,
	'second',
	524291,
	0);
INSERT INTO S_EE
	VALUES (4,
	'Persistence Services',
	'',
	'PERSIST',
	94514);
INSERT INTO S_BRG
	VALUES (4,
	4,
	'commit',
	'',
	0,
	524291,
	'',
	1);
INSERT INTO S_SS
	VALUES (1048578,
	'Domain',
	'

Notes:

',
	'S',
	1,
	94514,
	1048578);
INSERT INTO O_OBJ
	VALUES (1048577,
	'Domain',
	1,
	'S_DOM',
	'A typical software system generally consists of distinct and independent subject matters. A Shlaer/Mellor analysis partition is based within each of these subject matters - each subject matter is called a Domain. A Domain is inhabited by its  own conceptual entities (call objects). A domain may be partitioned into subsystems depending upon its complexity. Each Domain is given a mission statement which provides a charter for the construction of the OOA models.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048577,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048577,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048577,
	1048577,
	0,
	'Dom_ID',
	'Full Name: Domain Identifier',
	'',
	'Dom_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1048578,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048578,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048578,
	1048577,
	1048577,
	'Name',
	'Full Name: Domain Name',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048579,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048579,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048579,
	1048577,
	1048578,
	'Descrip',
	'Full Name: Domain Description',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048580,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048580,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048580,
	1048577,
	1048579,
	'Full_Der',
	'Full Name: Fully Derived Flag

A flag indicating whether the Object Communication Model and Object Access Model are fully derived from the information contained in the Object Information Model and Action Specifications.

Value 0 indicates OCM and OAM are not fully derived.
Value 1 indicates OCM and OAM are fully derived.
',
	'',
	'Full_Der',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048581,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048581,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048581,
	1048577,
	1048580,
	'Config_ID',
	'Full Name: Configuration Identifier

The Configuration Identifier of the version management configuration which the domain is part of (refer to Version Management Subsystem). This ID can be used to access the V_CONFIG record corresponding to the Domain/Subsystem Configuration.',
	'',
	'Config_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1048582,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048582,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048582,
	1048577,
	4718692,
	'RegisteredName',
	'The  assigned (e.g., registered) domain name to be used for this domain. This name will be used as a prefix in the generated code to assure namespace uniqueness for systems which contain multiple domains.
',
	'',
	'RegisteredName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048583,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048583,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048583,
	1048577,
	1048582,
	'RegisteredID',
	'An admistratively assigned (via coloring data) identification number for the domain. This number must be unique for each domain which is part of a multiple domain system.

Note that the value zero (0) is reserved as the domain identification number of the Software Architecture.',
	'',
	'RegisteredID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048584,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048584,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048584,
	1048577,
	1048583,
	'TypeCode',
	'A numeric value which provides domain specialization information to the translation engine.

Data Domain:
0 => OOA domain
1 => Realized domain.',
	'',
	'TypeCode',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048585,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048585,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048585,
	1048577,
	1048584,
	'StateTrace',
	'Full Name: Trace State Tranisitions Enabled

A flag used by the translation engine to indicate that state transition tracing capabilities should be generated for the state machines in this domain.',
	'',
	'StateTrace',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048586,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048586,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048586,
	1048577,
	1048585,
	'StmtTrace',
	'Full Name: Trace Action Language Statements

A flag used by the translation engine to indicate that statement level tracing capabilities should be generated for the state machines in this domain.',
	'',
	'StmtTrace',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048587,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048587,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048587,
	1048577,
	1048586,
	'DetectEmpty',
	'',
	'',
	'DetectEmpty',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048588,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048588,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048588,
	1048577,
	1048587,
	'OptDisabled',
	'Full Name: Generated Code Optimizations Disabled

A flag used by the translation engine to indicated (via coloring) that first pass optimizations should not be applied to the generated code.',
	'',
	'OptDisabled',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048589,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048589,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048589,
	1048577,
	1048588,
	'RawComments',
	'A flag used by the translation engine to control whether or not each state action should be included the ''raw'' BPAL action semantics as a comment block. If TRUE, each state action will contain the raw BPAL as a comment prelude to the generated code. If FALSE, the raw BPAL will not be included as a comment in the generated code.',
	'',
	'RawComments',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048590,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048590,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048590,
	1048577,
	1048589,
	'CodeComments',
	'A flag used by the translation engine to control whether or not BPAL statements should be rendered at the implementation statement level immediately before the coorosponding code fragment. If TRUE, each generated code statement block in an action will be preluded with the  associated BPAL statement. If FALSE, no BPAL comments will be emitted at the statement level in the generated state action code. ',
	'',
	'CodeComments',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048591,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048591,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048591,
	1048577,
	1048590,
	'UseModelNames',
	'',
	'',
	'UseModelNames',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048592,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048592,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048592,
	1048577,
	1048591,
	'ReflexPhrase',
	'A flag used by the translation engine to control the method naming of relationship code for simple reflexive and associative reflexive relationships. If TRUE, the relationship phrase will be used in a textual formulation of reflexive method names (for debug/educational purposes). If FALSE, reflexive method names will be at the complete discression of the translation engine, generally rendered for code brevity. ',
	'',
	'ReflexPhrase',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048593,
	1048577);
INSERT INTO O_BATTR
	VALUES (1048593,
	1048577);
INSERT INTO O_ATTR
	VALUES (1048593,
	1048577,
	1048592,
	'TextBuffer',
	'A general purpose text/string buffer for use by the translation engine.',
	'',
	'TextBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718642,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718642,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718642,
	1048577,
	1048593,
	'CollectionsFlavor',
	'',
	'',
	'CollectionsFlavor',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718643,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718643,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718643,
	1048577,
	4718642,
	'TargetMonitorEnabled',
	'',
	'',
	'TargetMonitorEnabled',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718644,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718644,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718644,
	1048577,
	4718643,
	'SystemPrefix',
	'',
	'',
	'SystemPrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718645,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718645,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718645,
	1048577,
	4718644,
	'SystemMethodPrefix',
	'',
	'',
	'SystemMethodPrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718646,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718646,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718646,
	1048577,
	4718645,
	'SystemTypePrefix',
	'',
	'',
	'SystemTypePrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718647,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718647,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718647,
	1048577,
	4718646,
	'SystemDefinePrefix',
	'',
	'',
	'SystemDefinePrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718648,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718648,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718648,
	1048577,
	4718647,
	'SystemFilePrefix',
	'',
	'',
	'SystemFilePrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718649,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718649,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718649,
	1048577,
	4718648,
	'IsStaticPopulateOld',
	'',
	'',
	'IsStaticPopulateOld',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718650,
	1048577);
INSERT INTO O_BATTR
	VALUES (4718650,
	1048577);
INSERT INTO O_ATTR
	VALUES (4718650,
	1048577,
	4718649,
	'CharacterEncoding',
	'',
	'',
	'CharacterEncoding',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048577,
	4718605,
	0,
	4718690,
	4718617,
	4718642,
	4718641,
	4718692,
	4718636,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718692,
	1048577,
	4718690,
	4718605,
	1);
INSERT INTO O_ATTR
	VALUES (4718692,
	1048577,
	1048581,
	'Sys_ID',
	'',
	'',
	'Sys_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	1048577);
INSERT INTO O_OIDA
	VALUES (1048577,
	1048577,
	0);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	1048584,
	1048591);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	1048601,
	1048628);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	1048582,
	1048587);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	1048577,
	1048577);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	4718618,
	4718644);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	4718626,
	4718662);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	4718630,
	4718671);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	4718636,
	4718684);
INSERT INTO O_RTIDA
	VALUES (1048577,
	1048577,
	0,
	4718638,
	4718691);
INSERT INTO O_OBJ
	VALUES (1048578,
	'Subsystem',
	2,
	'S_SS',
	'A Subsystem is based on the partitioning of an entire
Domain. The number of Subsystems in a Domain is dependent
upon the Domain subject matter and complexity.

A Subsystem is composed of objects which tend to cluster, i.e.,
objects which have many relationships with one another but few
relationships with objects in different clusters.

Inter-Subsystem relationships, asynchronous communications,
and synchronous accesses are captured in the Subsystem
Relationship Model, Subsystem Communication Model and 
Subsystem Access Model, respectively.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048594,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048594,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048594,
	1048578,
	0,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1048595,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048595,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048595,
	1048578,
	1048594,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048596,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048596,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048596,
	1048578,
	1048595,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048597,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048597,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048597,
	1048578,
	1048596,
	'Prefix',
	'The subsystem keyletter prefix is used when objects are
created in the subsystem - the subsystem keyletter prefix is used
as the default prefix in the object keyletters.
',
	'',
	'Prefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048598,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048598,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048598,
	1048578,
	1048597,
	'Num_Rng',
	'The subsystem number range start is used when objects
and relationships are created in the subsystem - the subsystem
number range start is used as the default auto-numbering start
value in for the newly created Object''s number and newly
created Relationship''s number. 
',
	'',
	'Num_Rng',
	0,
	524291);
INSERT INTO O_REF
	VALUES (1048578,
	1048577,
	0,
	1048577,
	1048577,
	1048578,
	1048577,
	1048599,
	1048583,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048599,
	1048578,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (1048599,
	1048578,
	1048598,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048600,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048600,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048600,
	1048578,
	1048599,
	'Config_ID',
	'',
	'',
	'Config_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1048601,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048601,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048601,
	1048578,
	1048600,
	'Order',
	'A utlity attribute for the archetypes to specify a particular order of the subsystems in the domain. 
This attribute is a "work around" until the archetype language supports an "ORDERED BY" clause.',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048602,
	1048578);
INSERT INTO O_BATTR
	VALUES (1048602,
	1048578);
INSERT INTO O_ATTR
	VALUES (1048602,
	1048578,
	1048601,
	'Included',
	'A general purpose flag available for use by the archetype language.
Note: Attribute added to the original BP OIM (PT).',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	1048578);
INSERT INTO O_OIDA
	VALUES (1048594,
	1048578,
	0);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	1048578,
	1048579);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	1048595,
	1048616);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	1048594,
	1048614);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	1048596,
	1048618);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	1048598,
	1048622);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	1048597,
	1048620);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	4718630,
	4718672);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	4718632,
	4718677);
INSERT INTO O_RTIDA
	VALUES (1048594,
	1048578,
	0,
	4718631,
	4718675);
INSERT INTO O_OBJ
	VALUES (1048579,
	'External Entity',
	3,
	'S_EE',
	'An External Entity represents something outside of the
Domain being modeled that interacts with objects within the
Domain being modeled. The interactions are showed by Event 
Communications in the Object Communication Models and Data
Accesses in the Object Access Models. Each External Entity is
given a unique name and keyletters within a Domain.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048603,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048603,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048603,
	1048579,
	0,
	'EE_ID',
	'Full Name: External Entity Identifier',
	'',
	'EE_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1048604,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048604,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048604,
	1048579,
	1048603,
	'Name',
	'Full Name: External Entity Name',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048605,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048605,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048605,
	1048579,
	1048604,
	'Descrip',
	'Full Name: External Entity Description
A textual description of the external entity which appears in a domains Subsystem Partition Model (SPM).',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048606,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048606,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048606,
	1048579,
	1048605,
	'Key_Lett',
	'Full Name: External Entity Key Letters
The key letters assigned to an external entity on a domains SPM.',
	'',
	'Key_Lett',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048579,
	1048577,
	0,
	1048577,
	1048584,
	1048592,
	1048591,
	1048607,
	1048584,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048607,
	1048579,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (1048607,
	1048579,
	1048606,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048608,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048608,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048608,
	1048579,
	1048607,
	'RegisteredID',
	'An admistratively assigned (via coloring data) identification number for the domain represented by the External Entity. This number must be unique for each domain which is part of a multiple domain system.

Note that the value zero (0) is reserved as the domain identification number of the Software Architecture.',
	'',
	'RegisteredID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048609,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048609,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048609,
	1048579,
	1048608,
	'RegisteredName',
	'The adminstratively assigned name for the External Entity. This attribute is analogous to the ''Domain.SubstDomName'' attribute.',
	'',
	'RegisteredName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048610,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048610,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048610,
	1048579,
	1048609,
	'TypeCode',
	'',
	'',
	'TypeCode',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048611,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048611,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048611,
	1048579,
	1048610,
	'Included',
	'A general purpose flag used by the archetypes to mark waypoints in generation processes associated with an instance of External Entity.
Note: Attribute added to original BP OIM.',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048612,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048612,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048612,
	1048579,
	1048611,
	'Include_File',
	'Note: Attribute added to original BP OIM.',
	'',
	'Include_File',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048613,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048613,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048613,
	1048579,
	1048612,
	'Bridge_Obj_Kl',
	'',
	'',
	'Bridge_Obj_Kl',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048614,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048614,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048614,
	1048579,
	1048613,
	'ClassName',
	'',
	'',
	'ClassName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048615,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048615,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048615,
	1048579,
	1048614,
	'Used',
	'A flag to indicate to the translation engine that the external entity is accessed by at least one state action in the domain.',
	'',
	'Used',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048616,
	1048579);
INSERT INTO O_BATTR
	VALUES (1048616,
	1048579);
INSERT INTO O_ATTR
	VALUES (1048616,
	1048579,
	1048615,
	'C_Style',
	'',
	'',
	'C_Style',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	1048579);
INSERT INTO O_OIDA
	VALUES (1048603,
	1048579,
	0);
INSERT INTO O_RTIDA
	VALUES (1048603,
	1048579,
	0,
	1048580,
	1048583);
INSERT INTO O_RTIDA
	VALUES (1048603,
	1048579,
	0,
	1048589,
	1048604);
INSERT INTO O_RTIDA
	VALUES (1048603,
	1048579,
	0,
	1048581,
	1048585);
INSERT INTO O_RTIDA
	VALUES (1048603,
	1048579,
	0,
	1048592,
	1048610);
INSERT INTO O_RTIDA
	VALUES (1048603,
	1048579,
	0,
	1048579,
	1048581);
INSERT INTO O_RTIDA
	VALUES (1048603,
	1048579,
	0,
	4718633,
	4718679);
INSERT INTO O_OBJ
	VALUES (1048580,
	'External Entity in Model',
	4,
	'S_EEM',
	'The External Entity in Model is the presence of an
External Entity in a model such as the Object Communication
Model or Object Access Model. The same External Entity can be 
represented by more than one External Entity in Model in the
same model to enhance model layout.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048617,
	1048580);
INSERT INTO O_BATTR
	VALUES (1048617,
	1048580);
INSERT INTO O_ATTR
	VALUES (1048617,
	1048580,
	0,
	'EEmod_ID',
	'',
	'',
	'EEmod_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048580,
	1048579,
	0,
	1048603,
	1048579,
	1048582,
	1048581,
	1048618,
	1048585,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048618,
	1048580,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (1048618,
	1048580,
	1048617,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048619,
	1048580);
INSERT INTO O_BATTR
	VALUES (1048619,
	1048580);
INSERT INTO O_ATTR
	VALUES (1048619,
	1048580,
	1048618,
	'Modl_Typ',
	'Value indicates what type of model the External Entity is in:

value 6 indicates Object Communication Model
Value 7 indicates Object Access Model',
	'',
	'Modl_Typ',
	0,
	524291);
INSERT INTO O_REF
	VALUES (1048580,
	1048578,
	0,
	1048594,
	1048578,
	1048580,
	1048579,
	1048620,
	1048586,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048620,
	1048580,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (1048620,
	1048580,
	1048619,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1048580);
INSERT INTO O_OIDA
	VALUES (1048618,
	1048580,
	0);
INSERT INTO O_RTIDA
	VALUES (1048618,
	1048580,
	0,
	2097173,
	2097197);
INSERT INTO O_RTIDA
	VALUES (1048618,
	1048580,
	0,
	2097163,
	2097176);
INSERT INTO O_RTIDA
	VALUES (1048618,
	1048580,
	0,
	2097154,
	2097158);
INSERT INTO O_OIDA
	VALUES (1048617,
	1048580,
	0);
INSERT INTO O_RTIDA
	VALUES (1048617,
	1048580,
	0,
	2097173,
	2097197);
INSERT INTO O_RTIDA
	VALUES (1048617,
	1048580,
	0,
	2097163,
	2097176);
INSERT INTO O_RTIDA
	VALUES (1048617,
	1048580,
	0,
	2097154,
	2097158);
INSERT INTO O_OBJ
	VALUES (1048581,
	'External Entity Data Item',
	5,
	'S_EEDI',
	'Interactions between Objects and External Entities
shown in the Object Acess Models involve the access of data. An
External Entity Data Item is a characteristic of an External Entity
that an Object may read.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048621,
	1048581);
INSERT INTO O_BATTR
	VALUES (1048621,
	1048581);
INSERT INTO O_ATTR
	VALUES (1048621,
	1048581,
	0,
	'EEdi_ID',
	'',
	'',
	'EEdi_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048581,
	1048579,
	0,
	1048603,
	1048592,
	1048609,
	1048610,
	1048622,
	1048577,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048622,
	1048581,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (1048622,
	1048581,
	1048621,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048623,
	1048581);
INSERT INTO O_BATTR
	VALUES (1048623,
	1048581);
INSERT INTO O_ATTR
	VALUES (1048623,
	1048581,
	1048622,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048624,
	1048581);
INSERT INTO O_BATTR
	VALUES (1048624,
	1048581);
INSERT INTO O_ATTR
	VALUES (1048624,
	1048581,
	1048623,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048581,
	1048584,
	0,
	1048643,
	1048590,
	1048606,
	1048605,
	1048625,
	1048587,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048625,
	1048581,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048625,
	1048581,
	1048624,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1048581);
INSERT INTO O_OIDA
	VALUES (1048621,
	1048581,
	0);
INSERT INTO O_RTIDA
	VALUES (1048621,
	1048581,
	0,
	2097175,
	2097201);
INSERT INTO O_OIDA
	VALUES (1048622,
	1048581,
	0);
INSERT INTO O_RTIDA
	VALUES (1048622,
	1048581,
	0,
	2097175,
	2097201);
INSERT INTO O_OBJ
	VALUES (1048582,
	'External Entity Event',
	6,
	'S_EEEVT',
	'An External Entity identifies an interaction
between an Object and an External Entity and is captured on an
Object Communcaiton Model. Each External Entity Event is
given a unique label.

',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048626,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048626,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048626,
	1048582,
	0,
	'EEevt_ID',
	'',
	'',
	'EEevt_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048582,
	1048579,
	0,
	1048603,
	1048580,
	1048584,
	1048583,
	1048627,
	1048588,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048627,
	1048582,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (1048627,
	1048582,
	1048626,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048628,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048628,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048628,
	1048582,
	1048627,
	'Numb',
	'',
	'',
	'Numb',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048629,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048629,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048629,
	1048582,
	1048628,
	'Mning',
	'',
	'',
	'Mning',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048630,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048630,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048630,
	1048582,
	1048629,
	'Is_Lbl_U',
	'This is a flag that indicates whether custom label keyletters are used for the External Entity Event.

Value 0 indicates custom label keyletters are used.
Value 1 indicates External Entity keyletters are used.',
	'',
	'Is_Lbl_U',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048631,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048631,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048631,
	1048582,
	1048630,
	'Unq_Lbl',
	'',
	'',
	'Unq_Lbl',
	0,
	524293);
INSERT INTO O_DBATTR
	VALUES (1048632,
	1048582,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (1048632,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048632,
	1048582,
	1048631,
	'Drv_Lbl',
	'Hold the event label - derived by concatenating the
keyletters and the event number.

If the Is_Lbl_U attribute is 0, then the value of the External
Entity.Name attribute is concatenated with the External 
Entity.Numb attribute.

If the Is_Lbl_U attribute is 1, then the value of the External
Entity.Cust.KL attribute is concatenated with the
External Entity.Numb attribute.
',
	'',
	'Drv_Lbl',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048633,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048633,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048633,
	1048582,
	1048632,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048634,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048634,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048634,
	1048582,
	1048633,
	'Used',
	'',
	'',
	'Used',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048635,
	1048582);
INSERT INTO O_BATTR
	VALUES (1048635,
	1048582);
INSERT INTO O_ATTR
	VALUES (1048635,
	1048582,
	1048634,
	'UsedCount',
	'',
	'',
	'UsedCount',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	1048582);
INSERT INTO O_OIDA
	VALUES (1048626,
	1048582,
	0);
INSERT INTO O_RTIDA
	VALUES (1048626,
	1048582,
	0,
	2097165,
	2097180);
INSERT INTO O_RTIDA
	VALUES (1048626,
	1048582,
	0,
	1048593,
	1048612);
INSERT INTO O_OIDA
	VALUES (1048627,
	1048582,
	0);
INSERT INTO O_RTIDA
	VALUES (1048627,
	1048582,
	0,
	2097165,
	2097180);
INSERT INTO O_RTIDA
	VALUES (1048627,
	1048582,
	0,
	1048593,
	1048612);
INSERT INTO O_OBJ
	VALUES (1048583,
	'External Entity Event Data Item',
	7,
	'S_EEEDI',
	'Synchronous interactions from Objects to External
Entities modeled by allowing an Object to synchronously access
the data items of the External Entity - the interaction is captured
on the Object Communication Model. En External Entity Data
Item is a characteristic of an External Entity.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048636,
	1048583);
INSERT INTO O_BATTR
	VALUES (1048636,
	1048583);
INSERT INTO O_ATTR
	VALUES (1048636,
	1048583,
	0,
	'EEedi_ID',
	'',
	'',
	'EEedi_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048583,
	1048579,
	0,
	1048603,
	1048581,
	1048586,
	1048585,
	1048637,
	1048589,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048637,
	1048583,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (1048637,
	1048583,
	1048636,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048638,
	1048583);
INSERT INTO O_BATTR
	VALUES (1048638,
	1048583);
INSERT INTO O_ATTR
	VALUES (1048638,
	1048583,
	1048637,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048639,
	1048583);
INSERT INTO O_BATTR
	VALUES (1048639,
	1048583);
INSERT INTO O_ATTR
	VALUES (1048639,
	1048583,
	1048638,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048583,
	1048584,
	0,
	1048643,
	1048583,
	1048590,
	1048589,
	1048640,
	1048590,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048640,
	1048583,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048640,
	1048583,
	1048639,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048641,
	1048583);
INSERT INTO O_BATTR
	VALUES (1048641,
	1048583);
INSERT INTO O_ATTR
	VALUES (1048641,
	1048583,
	1048640,
	'Order',
	'Attribute provided for the translation engine to specify a relative order in which instances of External Entity Event Data Item need to be processed. ',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048642,
	1048583);
INSERT INTO O_BATTR
	VALUES (1048642,
	1048583);
INSERT INTO O_ATTR
	VALUES (1048642,
	1048583,
	1048641,
	'ParamBuffer',
	'A string buffer provided for the translation engine to hold intermediate code fragments when processing a parameter list (e.g., fragment generation ''param_*'' functions.',
	'',
	'ParamBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718651,
	1048583);
INSERT INTO O_BATTR
	VALUES (4718651,
	1048583);
INSERT INTO O_ATTR
	VALUES (4718651,
	1048583,
	1048642,
	'OALParamBuffer',
	'',
	'',
	'OALParamBuffer',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1048583);
INSERT INTO O_OIDA
	VALUES (1048636,
	1048583,
	0);
INSERT INTO O_RTIDA
	VALUES (1048636,
	1048583,
	0,
	1048593,
	1048611);
INSERT INTO O_OIDA
	VALUES (1048637,
	1048583,
	0);
INSERT INTO O_RTIDA
	VALUES (1048637,
	1048583,
	0,
	1048593,
	1048611);
INSERT INTO O_OBJ
	VALUES (1048584,
	'Data Type',
	9,
	'S_DT',
	'An analyst can assign a data type to the various data
items in the OOA, e.g., object attribute, state model event data
item, transformer/bridge parameter/return value.

This data type does not capture the representation of the data
items, but rather, the characteristics of the data items including:

1. Value Definition, e.g., whole numbers
2. Value Range, e.g., values between 0 and 10
3. Operations, e.g., +, -, *, /
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048643,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048643,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048643,
	1048584,
	0,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048584,
	1048577,
	0,
	1048577,
	1048582,
	1048588,
	1048587,
	1048644,
	1048591,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048644,
	1048584,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (1048644,
	1048584,
	1048643,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048645,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048645,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048645,
	1048584,
	1048644,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048646,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048646,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048646,
	1048584,
	1048645,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048647,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048647,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048647,
	1048584,
	1048646,
	'Included',
	'',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048648,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048648,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048648,
	1048584,
	1048647,
	'ExtName',
	'',
	'',
	'ExtName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048649,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048649,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048649,
	1048584,
	1048648,
	'EventExtName',
	'',
	'',
	'EventExtName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048650,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048650,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048650,
	1048584,
	1048649,
	'Include_File',
	'',
	'',
	'Include_File',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048651,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048651,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048651,
	1048584,
	1048650,
	'Initial_Value',
	'',
	'',
	'Initial_Value',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048652,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048652,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048652,
	1048584,
	1048651,
	'Is_Enum',
	'',
	'',
	'Is_Enum',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048653,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048653,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048653,
	1048584,
	1048652,
	'Enum_Class_Name',
	'',
	'',
	'Enum_Class_Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048654,
	1048584);
INSERT INTO O_BATTR
	VALUES (1048654,
	1048584);
INSERT INTO O_ATTR
	VALUES (1048654,
	1048584,
	1048653,
	'Owning_Dom_Name',
	'',
	'',
	'Owning_Dom_Name',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1048584);
INSERT INTO O_OIDA
	VALUES (1048643,
	1048584,
	0);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048583,
	1048589);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048587,
	1048599);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048590,
	1048605);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	3145730,
	3145731);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048600,
	1048626);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	3145735,
	3145741);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	3145731,
	3145733);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048585,
	1048593);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	2621461,
	2621490);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048591,
	1048607);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	1048602,
	1048630);
INSERT INTO O_RTIDA
	VALUES (1048643,
	1048584,
	0,
	4718627,
	4718665);
INSERT INTO O_ID
	VALUES (1,
	1048584);
INSERT INTO O_OIDA
	VALUES (1048643,
	1048584,
	1);
INSERT INTO O_OIDA
	VALUES (1048644,
	1048584,
	1);
INSERT INTO O_OBJ
	VALUES (1048585,
	'Core Data Type',
	10,
	'S_CDT',
	'Core Data Types are those data types which are
fundamental, or core, to all data types.
',
	1048578);
INSERT INTO O_REF
	VALUES (1048585,
	1048584,
	0,
	1048643,
	1048585,
	1048594,
	1048593,
	1048655,
	1048578,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048655,
	1048585,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048655,
	1048585,
	0,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048656,
	1048585);
INSERT INTO O_BATTR
	VALUES (1048656,
	1048585);
INSERT INTO O_ATTR
	VALUES (1048656,
	1048585,
	1048655,
	'Core_Typ',
	'Data Domain:

0 = void
1 = boolean
2 = integer
3 = real
4 = string
5 = integer
6 = current_state
7 = same_as_base
8 = inst_ref<Object>
9 = inst_ref_set<Object>
10= inst<Event>
11= inst<Mapping>
12= inst_ref<Mapping>
',
	'',
	'Core_Typ',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	1048585);
INSERT INTO O_OIDA
	VALUES (1048655,
	1048585,
	0);
INSERT INTO O_RTIDA
	VALUES (1048655,
	1048585,
	0,
	1048586,
	1048597);
INSERT INTO O_OBJ
	VALUES (1048586,
	'User Data Type',
	11,
	'S_UDT',
	'User Data Types are those data types which have been
derived from the core data types - they typically are derived
because more assumptions can be made about the range of
values which can be stored or they are derived to serve as a
common funneling oint for several data items which share some
common data type.
',
	1048578);
INSERT INTO O_REF
	VALUES (1048586,
	1048584,
	0,
	1048643,
	1048585,
	1048595,
	1048593,
	1048657,
	1048579,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048657,
	1048586,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048657,
	1048586,
	0,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1048586,
	1048585,
	0,
	1048655,
	1048586,
	1048598,
	1048597,
	1048658,
	1048592,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048658,
	1048586,
	1048643,
	1048584,
	0);
INSERT INTO O_ATTR
	VALUES (1048658,
	1048586,
	1048657,
	'CDT_ID',
	'',
	'C',
	'DT_ID',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048659,
	1048586);
INSERT INTO O_BATTR
	VALUES (1048659,
	1048586);
INSERT INTO O_ATTR
	VALUES (1048659,
	1048586,
	1048658,
	'Gen_Type',
	'Data Domain:
0 = user defined
1 = date
2 = timestamp
3 = inst_ref<Timer>
4 = inst_ref<Prompt>
',
	'',
	'Gen_Type',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	1048586);
INSERT INTO O_OIDA
	VALUES (1048657,
	1048586,
	0);
INSERT INTO O_OBJ
	VALUES (1048587,
	'Bridge',
	12,
	'S_BRG',
	'A Bridge is a method associated with an External Entity
 - bridges can be synchronously called from Action Specifications.
',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048660,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048660,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048660,
	1048587,
	0,
	'Brg_ID',
	'',
	'',
	'Brg_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048587,
	1048579,
	0,
	1048603,
	1048589,
	1048603,
	1048604,
	1048661,
	1048580,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048661,
	1048587,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (1048661,
	1048587,
	1048660,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048662,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048662,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048662,
	1048587,
	1048661,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048663,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048663,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048663,
	1048587,
	1048662,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048664,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048664,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048664,
	1048587,
	1048663,
	'Brg_Typ',
	'',
	'',
	'Brg_Typ',
	0,
	524291);
INSERT INTO O_REF
	VALUES (1048587,
	1048584,
	0,
	1048643,
	1048587,
	1048600,
	1048599,
	1048665,
	1048593,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048665,
	1048587,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048665,
	1048587,
	1048664,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048666,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048666,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048666,
	1048587,
	1048665,
	'Action_Semantics',
	'',
	'',
	'Action_Semantics',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048667,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048667,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048667,
	1048587,
	1048666,
	'Suc_Pars',
	'Full Name: Successfully Parsed

Indicates if the semantics contained in attribute ''Action_Semantics'' has been successfully parsed by ModeBuilder.

Data Domain:
0 == ''Action_Semantics'' has not been successfully parsed, and thus can not be translated. 
1 == ''Action_Semantics'' has been successfully parsed.',
	'',
	'Suc_Pars',
	0,
	524291);
INSERT INTO O_REF
	VALUES (1048587,
	4194312,
	0,
	4194380,
	4194310,
	4194319,
	4194315,
	1048668,
	1048594,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048668,
	1048587,
	4194380,
	4194312,
	1);
INSERT INTO O_ATTR
	VALUES (1048668,
	1048587,
	1048667,
	'AutID',
	'',
	'',
	'AutID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1048587,
	4194313,
	0,
	4194384,
	4194311,
	4194323,
	4194321,
	1048669,
	1048595,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048669,
	1048587,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (1048669,
	1048587,
	1048668,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048670,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048670,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048670,
	1048587,
	1048669,
	'StmtCount',
	'The total number of times this bridge process is invoked (at the statement level) by the action language of the application analysis.',
	'',
	'StmtCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048671,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048671,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048671,
	1048587,
	1048670,
	'XlateSemantics',
	'A flag used by the translation engine to indicate that the action semantics of this bridge should be translated.',
	'',
	'XlateSemantics',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048672,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048672,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048672,
	1048587,
	1048671,
	'NonSelfEventCount',
	'',
	'',
	'NonSelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048673,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048673,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048673,
	1048587,
	1048672,
	'SelectManyCount',
	'',
	'',
	'SelectManyCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048674,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048674,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048674,
	1048587,
	1048673,
	'SelectAnyWhereCount',
	'',
	'',
	'SelectAnyWhereCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048675,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048675,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048675,
	1048587,
	1048674,
	'TimerStartCount',
	'',
	'',
	'TimerStartCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048676,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048676,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048676,
	1048587,
	1048675,
	'ReturnStmtUsed',
	'',
	'',
	'ReturnStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048677,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048677,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048677,
	1048587,
	1048676,
	'BreakStmtUsed',
	'',
	'',
	'BreakStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048678,
	1048587);
INSERT INTO O_BATTR
	VALUES (1048678,
	1048587);
INSERT INTO O_ATTR
	VALUES (1048678,
	1048587,
	1048677,
	'ContinueStmtUsed',
	'',
	'',
	'ContinueStmtUsed',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	1048587);
INSERT INTO O_OIDA
	VALUES (1048660,
	1048587,
	0);
INSERT INTO O_RTIDA
	VALUES (1048660,
	1048587,
	0,
	1048588,
	1048601);
INSERT INTO O_RTIDA
	VALUES (1048660,
	1048587,
	0,
	4718613,
	4718634);
INSERT INTO O_OBJ
	VALUES (1048588,
	'Bridge Parameter',
	13,
	'S_BPARM',
	'A paramter to a bridge.',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048679,
	1048588);
INSERT INTO O_BATTR
	VALUES (1048679,
	1048588);
INSERT INTO O_ATTR
	VALUES (1048679,
	1048588,
	0,
	'BParm_ID',
	'Full Name: Bridge Parameter Identifier',
	'',
	'BParm_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048588,
	1048587,
	0,
	1048660,
	1048588,
	1048602,
	1048601,
	1048680,
	1048596,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048680,
	1048588,
	1048660,
	1048587,
	1);
INSERT INTO O_ATTR
	VALUES (1048680,
	1048588,
	1048679,
	'Brg_ID',
	'',
	'',
	'Brg_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048681,
	1048588);
INSERT INTO O_BATTR
	VALUES (1048681,
	1048588);
INSERT INTO O_ATTR
	VALUES (1048681,
	1048588,
	1048680,
	'Name',
	'Full Name: Bridge Parameter Name
The name of a parameter used to identify a supplemental data item being provided in a Bridge statement.',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048588,
	1048584,
	0,
	1048643,
	1048591,
	1048608,
	1048607,
	1048682,
	1048597,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048682,
	1048588,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048682,
	1048588,
	1048681,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048683,
	1048588);
INSERT INTO O_BATTR
	VALUES (1048683,
	1048588);
INSERT INTO O_ATTR
	VALUES (1048683,
	1048588,
	1048682,
	'By_Ref',
	'Full Name: Pass Parameter By Reference

When a parameter is defined as pass by reference, the parameter may be written to in the application BPAL (BP V5.0 or greater).

Data Domain:
0 == Pass by "value" (or const &)
1 == Pass by "reference"
',
	'',
	'By_Ref',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048684,
	1048588);
INSERT INTO O_BATTR
	VALUES (1048684,
	1048588);
INSERT INTO O_ATTR
	VALUES (1048684,
	1048588,
	1048683,
	'Order',
	'Attribute provided for the translation engine to specify a relative order in which instances of Bridge Parameter need to be processed. ',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048685,
	1048588);
INSERT INTO O_BATTR
	VALUES (1048685,
	1048588);
INSERT INTO O_ATTR
	VALUES (1048685,
	1048588,
	1048684,
	'ParamBuffer',
	'A string buffer provided for the translation engine to hold intermediate code fragments when processing a parameter list (e.g., fragment generation ''param_*'' functions.',
	'',
	'ParamBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718652,
	1048588);
INSERT INTO O_BATTR
	VALUES (4718652,
	1048588);
INSERT INTO O_ATTR
	VALUES (4718652,
	1048588,
	1048685,
	'OALParamBuffer',
	'',
	'',
	'OALParamBuffer',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1048588);
INSERT INTO O_OIDA
	VALUES (1048679,
	1048588,
	0);
INSERT INTO O_RTIDA
	VALUES (1048679,
	1048588,
	0,
	4718616,
	4718640);
INSERT INTO O_OBJ
	VALUES (1048589,
	'External Entity Event Data',
	8,
	'S_EEEDT',
	'This object serves as a correlation table.
',
	1048578);
INSERT INTO O_REF
	VALUES (1048589,
	1048583,
	0,
	1048637,
	1048593,
	1048613,
	1048611,
	1048686,
	1048598,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1048589,
	1048582,
	0,
	1048627,
	1048593,
	1048613,
	1048612,
	1048686,
	1048599,
	1048598,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048686,
	1048589,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (1048686,
	1048589,
	0,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1048589,
	1048582,
	0,
	1048626,
	1048593,
	1048613,
	1048612,
	1048687,
	1048600,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048687,
	1048589,
	1048626,
	1048582,
	1);
INSERT INTO O_ATTR
	VALUES (1048687,
	1048589,
	1048686,
	'EEevt_ID',
	'',
	'',
	'EEevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1048589,
	1048583,
	0,
	1048636,
	1048593,
	1048613,
	1048611,
	1048688,
	1048601,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048688,
	1048589,
	1048636,
	1048583,
	1);
INSERT INTO O_ATTR
	VALUES (1048688,
	1048589,
	1048687,
	'EEedi_ID',
	'',
	'',
	'EEedi_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1048589);
INSERT INTO O_OIDA
	VALUES (1048686,
	1048589,
	0);
INSERT INTO O_OIDA
	VALUES (1048688,
	1048589,
	0);
INSERT INTO O_OIDA
	VALUES (1048687,
	1048589,
	0);
INSERT INTO O_OBJ
	VALUES (1048590,
	'Function',
	16,
	'S_SYNC',
	'',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048689,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048689,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048689,
	1048590,
	0,
	'Sync_ID',
	'',
	'',
	'Sync_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048590,
	1048577,
	0,
	1048577,
	1048601,
	1048629,
	1048628,
	1048690,
	1048602,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048690,
	1048590,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (1048690,
	1048590,
	1048689,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048691,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048691,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048691,
	1048590,
	1048690,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048692,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048692,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048692,
	1048590,
	1048691,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048693,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048693,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048693,
	1048590,
	1048692,
	'Action_Semantics',
	'',
	'',
	'Action_Semantics',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048590,
	1048584,
	0,
	1048643,
	1048600,
	1048627,
	1048626,
	1048694,
	1048603,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048694,
	1048590,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048694,
	1048590,
	1048693,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048695,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048695,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048695,
	1048590,
	1048694,
	'Suc_Pars',
	'Full Name: Successfully Parsed

Indicates if the semantics contained in attribute ''Action_Semantics'' has been successfully parsed by ModeBuilder.

Data Domain:
0 == ''Action_Semantics'' has not been successfully parsed, and thus can not be translated. 
1 == ''Action_Semantics'' has been successfully parsed.',
	'',
	'Suc_Pars',
	0,
	524291);
INSERT INTO O_REF
	VALUES (1048590,
	4194312,
	0,
	4194380,
	4194310,
	4194317,
	4194315,
	1048696,
	1048604,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048696,
	1048590,
	4194380,
	4194312,
	1);
INSERT INTO O_ATTR
	VALUES (1048696,
	1048590,
	1048695,
	'AutID',
	'',
	'',
	'AutID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1048590,
	4194313,
	0,
	4194384,
	4194311,
	4194325,
	4194321,
	1048697,
	1048605,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048697,
	1048590,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (1048697,
	1048590,
	1048696,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048698,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048698,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048698,
	1048590,
	1048697,
	'Included',
	'A flag used by the translation engine to indicate this instance is being used in current processing.',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048699,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048699,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048699,
	1048590,
	4718669,
	'NonSelfEventCount',
	'',
	'',
	'NonSelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048700,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048700,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048700,
	1048590,
	1048699,
	'SelectManyCount',
	'',
	'',
	'SelectManyCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048701,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048701,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048701,
	1048590,
	1048700,
	'SelectAnyWhereCount',
	'',
	'',
	'SelectAnyWhereCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048702,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048702,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048702,
	1048590,
	1048701,
	'TimerStartCount',
	'',
	'',
	'TimerStartCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048703,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048703,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048703,
	1048590,
	1048702,
	'IsSafeForInterrupts',
	'Now that funky bridge objects are obsoleted, we have
synchronous service action homes.  This action home
can server as a bridge that can be marked safe for
invocation from within an interrupt handler (or other
context/process/thread).  True means that the synchronous
server (domain function) is protected.',
	'',
	'IsSafeForInterrupts',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048704,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048704,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048704,
	1048590,
	1048703,
	'ReturnStmtUsed',
	'',
	'',
	'ReturnStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048705,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048705,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048705,
	1048590,
	1048704,
	'BreakStmtUsed',
	'',
	'',
	'BreakStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1048706,
	1048590);
INSERT INTO O_BATTR
	VALUES (1048706,
	1048590);
INSERT INTO O_ATTR
	VALUES (1048706,
	1048590,
	1048705,
	'ContinueStmtUsed',
	'',
	'',
	'ContinueStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718656,
	1048590);
INSERT INTO O_BATTR
	VALUES (4718656,
	1048590);
INSERT INTO O_ATTR
	VALUES (4718656,
	1048590,
	1048706,
	'Order',
	'',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718657,
	1048590);
INSERT INTO O_BATTR
	VALUES (4718657,
	1048590);
INSERT INTO O_ATTR
	VALUES (4718657,
	1048590,
	4718656,
	'XlateSemantics',
	'',
	'',
	'XlateSemantics',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718669,
	1048590);
INSERT INTO O_BATTR
	VALUES (4718669,
	1048590);
INSERT INTO O_ATTR
	VALUES (4718669,
	1048590,
	1048698,
	'IsInitFunction',
	'',
	'',
	'IsInitFunction',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	1048590);
INSERT INTO O_OIDA
	VALUES (1048689,
	1048590,
	0);
INSERT INTO O_RTIDA
	VALUES (1048689,
	1048590,
	0,
	4718614,
	4718635);
INSERT INTO O_RTIDA
	VALUES (1048689,
	1048590,
	0,
	1048599,
	1048624);
INSERT INTO O_RTIDA
	VALUES (1048689,
	1048590,
	0,
	4718620,
	4718648);
INSERT INTO O_OBJ
	VALUES (1048591,
	'Function Parameter',
	17,
	'S_SPARM',
	'',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048707,
	1048591);
INSERT INTO O_BATTR
	VALUES (1048707,
	1048591);
INSERT INTO O_ATTR
	VALUES (1048707,
	1048591,
	0,
	'SParm_ID',
	'',
	'',
	'SParm_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1048591,
	1048590,
	0,
	1048689,
	1048599,
	1048625,
	1048624,
	1048708,
	1048606,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048708,
	1048591,
	1048689,
	1048590,
	1);
INSERT INTO O_ATTR
	VALUES (1048708,
	1048591,
	1048707,
	'Sync_ID',
	'',
	'',
	'Sync_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048709,
	1048591);
INSERT INTO O_BATTR
	VALUES (1048709,
	1048591);
INSERT INTO O_ATTR
	VALUES (1048709,
	1048591,
	1048708,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048591,
	1048584,
	0,
	1048643,
	1048602,
	1048631,
	1048630,
	1048710,
	1048607,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048710,
	1048591,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048710,
	1048591,
	1048709,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1048711,
	1048591);
INSERT INTO O_BATTR
	VALUES (1048711,
	1048591);
INSERT INTO O_ATTR
	VALUES (1048711,
	1048591,
	1048710,
	'By_Ref',
	'Full Name: Pass Parameter By Reference

When a parameter is defined as pass by reference, the parameter may be written to in the application BPAL (BP V5.0 or greater).

Data Domain:
0 == Pass by "value" (or const &)
1 == Pass by "reference"',
	'',
	'By_Ref',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048712,
	1048591);
INSERT INTO O_BATTR
	VALUES (1048712,
	1048591);
INSERT INTO O_ATTR
	VALUES (1048712,
	1048591,
	1048711,
	'Order',
	'Attribute provided for the translation engine to specify a relative order in which instances of Synchronous Service Parameter need to be processed. ',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1048713,
	1048591);
INSERT INTO O_BATTR
	VALUES (1048713,
	1048591);
INSERT INTO O_ATTR
	VALUES (1048713,
	1048591,
	1048712,
	'ParamBuffer',
	'A string buffer provided for the translation engine to hold intermediate code fragments when processing a parameter list (e.g., fragment generation ''param_*'' functions.',
	'',
	'ParamBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718658,
	1048591);
INSERT INTO O_BATTR
	VALUES (4718658,
	1048591);
INSERT INTO O_ATTR
	VALUES (4718658,
	1048591,
	1048713,
	'OALParamBuffer',
	'',
	'',
	'OALParamBuffer',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1048591);
INSERT INTO O_OIDA
	VALUES (1048707,
	1048591,
	0);
INSERT INTO O_ID
	VALUES (1,
	1048591);
INSERT INTO O_OIDA
	VALUES (1048708,
	1048591,
	1);
INSERT INTO O_RTIDA
	VALUES (1048708,
	1048591,
	1,
	4718615,
	4718638);
INSERT INTO O_OIDA
	VALUES (1048707,
	1048591,
	1);
INSERT INTO O_RTIDA
	VALUES (1048707,
	1048591,
	1,
	4718615,
	4718638);
INSERT INTO O_OBJ
	VALUES (1048592,
	'Enumeration Data Type',
	14,
	'S_EDT',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (1048592,
	1048584,
	0,
	1048643,
	1048585,
	1048596,
	1048593,
	1048714,
	1048581,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048714,
	1048592,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048714,
	1048592,
	0,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718653,
	1048592);
INSERT INTO O_BATTR
	VALUES (4718653,
	1048592);
INSERT INTO O_ATTR
	VALUES (4718653,
	1048592,
	1048714,
	'Initial_Value',
	'',
	'',
	'Initial_Value',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1048592);
INSERT INTO O_OIDA
	VALUES (1048714,
	1048592,
	0);
INSERT INTO O_RTIDA
	VALUES (1048714,
	1048592,
	0,
	1048603,
	1048633);
INSERT INTO O_OBJ
	VALUES (1048593,
	'Enumerator',
	15,
	'S_ENUM',
	'',
	1048578);
INSERT INTO O_NBATTR
	VALUES (1048715,
	1048593);
INSERT INTO O_BATTR
	VALUES (1048715,
	1048593);
INSERT INTO O_ATTR
	VALUES (1048715,
	1048593,
	0,
	'Enum_ID',
	'',
	'',
	'Enum_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1048716,
	1048593);
INSERT INTO O_BATTR
	VALUES (1048716,
	1048593);
INSERT INTO O_ATTR
	VALUES (1048716,
	1048593,
	1048715,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (1048717,
	1048593);
INSERT INTO O_BATTR
	VALUES (1048717,
	1048593);
INSERT INTO O_ATTR
	VALUES (1048717,
	1048593,
	1048716,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1048593,
	1048592,
	0,
	1048714,
	1048603,
	1048632,
	1048633,
	1048718,
	1048582,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1048718,
	1048593,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (1048718,
	1048593,
	1048717,
	'EDT_ID',
	'',
	'E',
	'DT_ID',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718654,
	1048593);
INSERT INTO O_BATTR
	VALUES (4718654,
	1048593);
INSERT INTO O_ATTR
	VALUES (4718654,
	1048593,
	1048718,
	'Value',
	'',
	'',
	'Value',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718655,
	1048593);
INSERT INTO O_BATTR
	VALUES (4718655,
	1048593);
INSERT INTO O_ATTR
	VALUES (4718655,
	1048593,
	4718654,
	'Order',
	'',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	1048593);
INSERT INTO O_OIDA
	VALUES (1048715,
	1048593,
	0);
INSERT INTO O_OBJ
	VALUES (4718605,
	'System Model',
	18,
	'S_SYS',
	'',
	1048578);
INSERT INTO O_NBATTR
	VALUES (4718690,
	4718605);
INSERT INTO O_BATTR
	VALUES (4718690,
	4718605);
INSERT INTO O_ATTR
	VALUES (4718690,
	4718605,
	0,
	'Sys_ID',
	'',
	'',
	'Sys_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (4718691,
	4718605);
INSERT INTO O_BATTR
	VALUES (4718691,
	4718605);
INSERT INTO O_ATTR
	VALUES (4718691,
	4718605,
	4718690,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718605);
INSERT INTO O_OIDA
	VALUES (4718690,
	4718605,
	0);
INSERT INTO O_RTIDA
	VALUES (4718690,
	4718605,
	0,
	4718617,
	4718641);
INSERT INTO O_OBJ
	VALUES (4718606,
	'Function Package',
	19,
	'S_FPK',
	'',
	1048578);
INSERT INTO O_NBATTR
	VALUES (4718693,
	4718606);
INSERT INTO O_BATTR
	VALUES (4718693,
	4718606);
INSERT INTO O_ATTR
	VALUES (4718693,
	4718606,
	0,
	'FunPack_ID',
	'',
	'',
	'FunPack_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (4718694,
	4718606);
INSERT INTO O_BATTR
	VALUES (4718694,
	4718606);
INSERT INTO O_ATTR
	VALUES (4718694,
	4718606,
	4718693,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_REF
	VALUES (4718606,
	1048577,
	0,
	1048577,
	4718618,
	4718643,
	4718644,
	4718696,
	4718637,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718696,
	4718606,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (4718696,
	4718606,
	4718694,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718606,
	4718608,
	0,
	4718699,
	4718622,
	4718653,
	4718652,
	4718708,
	4718647,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718708,
	4718606,
	4718693,
	4718606,
	1);
INSERT INTO O_ATTR
	VALUES (4718708,
	4718606,
	4718696,
	'Parent_FunPack_ID',
	'',
	'Parent_',
	'FunPack_ID',
	1,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718606);
INSERT INTO O_OIDA
	VALUES (4718693,
	4718606,
	0);
INSERT INTO O_RTIDA
	VALUES (4718693,
	4718606,
	0,
	4718620,
	4718647);
INSERT INTO O_RTIDA
	VALUES (4718693,
	4718606,
	0,
	4718621,
	4718651);
INSERT INTO O_OBJ
	VALUES (4718607,
	'Function in Package',
	20,
	'S_FIP',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718607,
	4718606,
	0,
	4718693,
	4718620,
	4718649,
	4718647,
	4718697,
	4718638,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718697,
	4718607,
	4718693,
	4718606,
	1);
INSERT INTO O_ATTR
	VALUES (4718697,
	4718607,
	0,
	'FunPack_ID',
	'',
	'',
	'FunPack_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718607,
	1048590,
	0,
	1048689,
	4718620,
	4718649,
	4718648,
	4718698,
	4718639,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718698,
	4718607,
	1048689,
	1048590,
	1);
INSERT INTO O_ATTR
	VALUES (4718698,
	4718607,
	4718697,
	'Sync_ID',
	'',
	'',
	'Sync_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718607);
INSERT INTO O_OIDA
	VALUES (4718697,
	4718607,
	0);
INSERT INTO O_OIDA
	VALUES (4718698,
	4718607,
	0);
INSERT INTO O_OBJ
	VALUES (4718608,
	'Function Package in Package',
	21,
	'S_FPIP',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718608,
	4718606,
	0,
	4718693,
	4718621,
	4718650,
	4718651,
	4718699,
	4718640,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718699,
	4718608,
	4718693,
	4718606,
	1);
INSERT INTO O_ATTR
	VALUES (4718699,
	4718608,
	0,
	'FunPack_ID',
	'',
	'',
	'FunPack_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718608);
INSERT INTO O_OIDA
	VALUES (4718699,
	4718608,
	0);
INSERT INTO O_RTIDA
	VALUES (4718699,
	4718608,
	0,
	4718622,
	4718652);
INSERT INTO O_OBJ
	VALUES (4718609,
	'External Entity Package',
	22,
	'S_EEPK',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718609,
	1048577,
	0,
	1048577,
	4718636,
	4718685,
	4718684,
	4718713,
	4718652,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718713,
	4718609,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (4718713,
	4718609,
	4718715,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (4718714,
	4718609);
INSERT INTO O_BATTR
	VALUES (4718714,
	4718609);
INSERT INTO O_ATTR
	VALUES (4718714,
	4718609,
	0,
	'EEPack_ID',
	'',
	'',
	'EEPack_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (4718715,
	4718609);
INSERT INTO O_BATTR
	VALUES (4718715,
	4718609);
INSERT INTO O_ATTR
	VALUES (4718715,
	4718609,
	4718714,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_REF
	VALUES (4718609,
	4718610,
	0,
	4718716,
	4718634,
	4718680,
	4718681,
	4718719,
	4718656,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718719,
	4718609,
	4718714,
	4718609,
	1);
INSERT INTO O_ATTR
	VALUES (4718719,
	4718609,
	4718713,
	'Parent_EEPack_ID',
	'',
	'Parent_',
	'EEPack_ID',
	1,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718609);
INSERT INTO O_OIDA
	VALUES (4718714,
	4718609,
	0);
INSERT INTO O_RTIDA
	VALUES (4718714,
	4718609,
	0,
	4718635,
	4718683);
INSERT INTO O_RTIDA
	VALUES (4718714,
	4718609,
	0,
	4718633,
	4718678);
INSERT INTO O_OBJ
	VALUES (4718610,
	'EE Package in Package',
	24,
	'S_EEPIP',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718610,
	4718609,
	0,
	4718714,
	4718635,
	4718682,
	4718683,
	4718716,
	4718653,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718716,
	4718610,
	4718714,
	4718609,
	1);
INSERT INTO O_ATTR
	VALUES (4718716,
	4718610,
	0,
	'EEPack_ID',
	'',
	'',
	'EEPack_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718610);
INSERT INTO O_OIDA
	VALUES (4718716,
	4718610,
	0);
INSERT INTO O_RTIDA
	VALUES (4718716,
	4718610,
	0,
	4718634,
	4718681);
INSERT INTO O_OBJ
	VALUES (4718611,
	'External Entity in Package',
	23,
	'S_EEIP',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718611,
	4718609,
	0,
	4718714,
	4718633,
	4718686,
	4718678,
	4718717,
	4718654,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718717,
	4718611,
	4718714,
	4718609,
	1);
INSERT INTO O_ATTR
	VALUES (4718717,
	4718611,
	0,
	'EEPack_ID',
	'',
	'',
	'EEPack_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718611,
	1048579,
	0,
	1048603,
	4718633,
	4718686,
	4718679,
	4718718,
	4718655,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718718,
	4718611,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (4718718,
	4718611,
	4718717,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718611);
INSERT INTO O_OIDA
	VALUES (4718717,
	4718611,
	0);
INSERT INTO O_OIDA
	VALUES (4718718,
	4718611,
	0);
INSERT INTO O_OBJ
	VALUES (4718612,
	'Datatype Package',
	25,
	'S_DPK',
	'',
	1048578);
INSERT INTO O_NBATTR
	VALUES (4718701,
	4718612);
INSERT INTO O_BATTR
	VALUES (4718701,
	4718612);
INSERT INTO O_ATTR
	VALUES (4718701,
	4718612,
	0,
	'DatPack_ID',
	'',
	'',
	'DatPack_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718612,
	4718614,
	0,
	4718704,
	4718629,
	4718669,
	4718670,
	4718705,
	4718645,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718705,
	4718612,
	4718701,
	4718612,
	1);
INSERT INTO O_ATTR
	VALUES (4718705,
	4718612,
	4718706,
	'Parent_DatPack_ID',
	'',
	'Parent_',
	'DatPack_ID',
	1,
	524294);
INSERT INTO O_REF
	VALUES (4718612,
	1048577,
	0,
	1048577,
	4718626,
	4718663,
	4718662,
	4718706,
	4718646,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718706,
	4718612,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (4718706,
	4718612,
	4718707,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (4718707,
	4718612);
INSERT INTO O_BATTR
	VALUES (4718707,
	4718612);
INSERT INTO O_ATTR
	VALUES (4718707,
	4718612,
	4718701,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718612);
INSERT INTO O_OIDA
	VALUES (4718701,
	4718612,
	0);
INSERT INTO O_RTIDA
	VALUES (4718701,
	4718612,
	0,
	4718627,
	4718664);
INSERT INTO O_RTIDA
	VALUES (4718701,
	4718612,
	0,
	4718628,
	4718668);
INSERT INTO O_OBJ
	VALUES (4718613,
	'Datatype in Package',
	26,
	'S_DIP',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718613,
	4718612,
	0,
	4718701,
	4718627,
	4718666,
	4718664,
	4718702,
	4718642,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718702,
	4718613,
	4718701,
	4718612,
	1);
INSERT INTO O_ATTR
	VALUES (4718702,
	4718613,
	0,
	'DatPack_ID',
	'',
	'',
	'DatPack_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718613,
	1048584,
	0,
	1048643,
	4718627,
	4718666,
	4718665,
	4718703,
	4718643,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718703,
	4718613,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (4718703,
	4718613,
	4718702,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718613);
INSERT INTO O_OIDA
	VALUES (4718702,
	4718613,
	0);
INSERT INTO O_OIDA
	VALUES (4718703,
	4718613,
	0);
INSERT INTO O_OBJ
	VALUES (4718614,
	'Datatype Package in Package',
	27,
	'S_DPIP',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718614,
	4718612,
	0,
	4718701,
	4718628,
	4718667,
	4718668,
	4718704,
	4718644,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718704,
	4718614,
	4718701,
	4718612,
	1);
INSERT INTO O_ATTR
	VALUES (4718704,
	4718614,
	0,
	'DatPack_ID',
	'',
	'',
	'DatPack_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718614);
INSERT INTO O_OIDA
	VALUES (4718704,
	4718614,
	0);
INSERT INTO O_RTIDA
	VALUES (4718704,
	4718614,
	0,
	4718629,
	4718670);
INSERT INTO O_OBJ
	VALUES (4718615,
	'Subsystem in Subsystem',
	30,
	'S_SIS',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718615,
	1048578,
	0,
	1048594,
	4718632,
	4718676,
	4718677,
	4718711,
	4718650,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718711,
	4718615,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (4718711,
	4718615,
	4718712,
	'Child_SS_ID',
	'',
	'Child_',
	'SS_ID',
	1,
	524294);
INSERT INTO O_REF
	VALUES (4718615,
	1048578,
	0,
	1048594,
	4718631,
	4718674,
	4718675,
	4718712,
	4718651,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718712,
	4718615,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (4718712,
	4718615,
	0,
	'Parent_SS_ID',
	'',
	'Parent_',
	'SS_ID',
	1,
	524294);
INSERT INTO O_OBJ
	VALUES (4718618,
	'Subsystem in Domain',
	31,
	'S_SID',
	'',
	1048578);
INSERT INTO O_REF
	VALUES (4718618,
	1048577,
	0,
	1048577,
	4718630,
	4718673,
	4718671,
	4718709,
	4718648,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718709,
	4718618,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (4718709,
	4718618,
	0,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718618,
	1048578,
	0,
	1048594,
	4718630,
	4718673,
	4718672,
	4718710,
	4718649,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718710,
	4718618,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (4718710,
	4718618,
	4718709,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718618);
INSERT INTO O_OIDA
	VALUES (4718709,
	4718618,
	0);
INSERT INTO O_OIDA
	VALUES (4718710,
	4718618,
	0);
INSERT INTO O_IOBJ
	VALUES (1048577,
	1572865,
	5,
	1048578,
	'Relationship',
	'R_REL');
INSERT INTO O_IOBJ
	VALUES (1048578,
	2097153,
	5,
	1048578,
	'Communication Path',
	'CA_COMM');
INSERT INTO O_IOBJ
	VALUES (1048579,
	2097160,
	5,
	1048578,
	'Access Path',
	'CA_ACC');
INSERT INTO O_IOBJ
	VALUES (1048580,
	3145732,
	5,
	1048578,
	'Class',
	'O_OBJ');
INSERT INTO O_IOBJ
	VALUES (1048581,
	3145740,
	5,
	1048578,
	'Imported Class',
	'O_IOBJ');
INSERT INTO R_SIMP
	VALUES (1048577);
INSERT INTO R_REL
	VALUES (1048577,
	1,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048577,
	1048577,
	1048577,
	0,
	0,
	'is first level of partitioning for');
INSERT INTO R_RTO
	VALUES (1048577,
	1048577,
	1048577,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	1048577,
	1048577,
	0);
INSERT INTO R_FORM
	VALUES (1048578,
	1048577,
	1048578,
	1,
	1,
	'is partitioned into');
INSERT INTO R_RGO
	VALUES (1048578,
	1048577,
	1048578);
INSERT INTO R_OIR
	VALUES (1048578,
	1048577,
	1048578,
	0);
INSERT INTO R_SIMP
	VALUES (1048578);
INSERT INTO R_REL
	VALUES (1048578,
	7,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048578,
	1048578,
	1048579,
	0,
	0,
	'is a presence of an an external entity in');
INSERT INTO R_RTO
	VALUES (1048578,
	1048578,
	1048579,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	1048578,
	1048579,
	0);
INSERT INTO R_FORM
	VALUES (1048580,
	1048578,
	1048580,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (1048580,
	1048578,
	1048580);
INSERT INTO R_OIR
	VALUES (1048580,
	1048578,
	1048580,
	0);
INSERT INTO R_SIMP
	VALUES (1048579);
INSERT INTO R_REL
	VALUES (1048579,
	9,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048579,
	1048579,
	1048581,
	0,
	0,
	'is a presence in subsystem model of');
INSERT INTO R_RTO
	VALUES (1048579,
	1048579,
	1048581,
	0);
INSERT INTO R_OIR
	VALUES (1048579,
	1048579,
	1048581,
	0);
INSERT INTO R_FORM
	VALUES (1048580,
	1048579,
	1048582,
	1,
	1,
	'is represented by');
INSERT INTO R_RGO
	VALUES (1048580,
	1048579,
	1048582);
INSERT INTO R_OIR
	VALUES (1048580,
	1048579,
	1048582,
	0);
INSERT INTO R_SIMP
	VALUES (1048580);
INSERT INTO R_REL
	VALUES (1048580,
	10,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048579,
	1048580,
	1048583,
	0,
	0,
	'is vehicle of communication for');
INSERT INTO R_RTO
	VALUES (1048579,
	1048580,
	1048583,
	0);
INSERT INTO R_OIR
	VALUES (1048579,
	1048580,
	1048583,
	0);
INSERT INTO R_FORM
	VALUES (1048582,
	1048580,
	1048584,
	1,
	1,
	'can receive asynchronous communication via');
INSERT INTO R_RGO
	VALUES (1048582,
	1048580,
	1048584);
INSERT INTO R_OIR
	VALUES (1048582,
	1048580,
	1048584,
	0);
INSERT INTO R_SIMP
	VALUES (1048581);
INSERT INTO R_REL
	VALUES (1048581,
	12,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048579,
	1048581,
	1048585,
	0,
	0,
	'is data for events of');
INSERT INTO R_RTO
	VALUES (1048579,
	1048581,
	1048585,
	0);
INSERT INTO R_OIR
	VALUES (1048579,
	1048581,
	1048585,
	0);
INSERT INTO R_FORM
	VALUES (1048583,
	1048581,
	1048586,
	1,
	1,
	'can asynchronously communicate via');
INSERT INTO R_RGO
	VALUES (1048583,
	1048581,
	1048586);
INSERT INTO R_OIR
	VALUES (1048583,
	1048581,
	1048586,
	0);
INSERT INTO R_SIMP
	VALUES (1048582);
INSERT INTO R_REL
	VALUES (1048582,
	14,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048577,
	1048582,
	1048587,
	0,
	0,
	'defines types within');
INSERT INTO R_RTO
	VALUES (1048577,
	1048582,
	1048587,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	1048582,
	1048587,
	0);
INSERT INTO R_FORM
	VALUES (1048584,
	1048582,
	1048588,
	1,
	1,
	'contains defined');
INSERT INTO R_RGO
	VALUES (1048584,
	1048582,
	1048588);
INSERT INTO R_OIR
	VALUES (1048584,
	1048582,
	1048588,
	0);
INSERT INTO R_SIMP
	VALUES (1048583);
INSERT INTO R_REL
	VALUES (1048583,
	16,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048584,
	1048583,
	1048589,
	0,
	0,
	'is defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	1048583,
	1048589,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048583,
	1048589,
	0);
INSERT INTO R_FORM
	VALUES (1048583,
	1048583,
	1048590,
	1,
	1,
	'defines the type of');
INSERT INTO R_RGO
	VALUES (1048583,
	1048583,
	1048590);
INSERT INTO R_OIR
	VALUES (1048583,
	1048583,
	1048590,
	0);
INSERT INTO R_SIMP
	VALUES (1048584);
INSERT INTO R_REL
	VALUES (1048584,
	8,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048577,
	1048584,
	1048591,
	0,
	0,
	'interacts with');
INSERT INTO R_RTO
	VALUES (1048577,
	1048584,
	1048591,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	1048584,
	1048591,
	0);
INSERT INTO R_FORM
	VALUES (1048579,
	1048584,
	1048592,
	1,
	1,
	'interacts with');
INSERT INTO R_RGO
	VALUES (1048579,
	1048584,
	1048592);
INSERT INTO R_OIR
	VALUES (1048579,
	1048584,
	1048592,
	0);
INSERT INTO R_SUBSUP
	VALUES (1048585);
INSERT INTO R_REL
	VALUES (1048585,
	17,
	'',
	1048578);
INSERT INTO R_SUPER
	VALUES (1048584,
	1048585,
	1048593);
INSERT INTO R_RTO
	VALUES (1048584,
	1048585,
	1048593,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048585,
	1048593,
	0);
INSERT INTO R_SUB
	VALUES (1048585,
	1048585,
	1048594);
INSERT INTO R_RGO
	VALUES (1048585,
	1048585,
	1048594);
INSERT INTO R_OIR
	VALUES (1048585,
	1048585,
	1048594,
	0);
INSERT INTO R_SUB
	VALUES (1048586,
	1048585,
	1048595);
INSERT INTO R_RGO
	VALUES (1048586,
	1048585,
	1048595);
INSERT INTO R_OIR
	VALUES (1048586,
	1048585,
	1048595,
	0);
INSERT INTO R_SUB
	VALUES (1048592,
	1048585,
	1048596);
INSERT INTO R_RGO
	VALUES (1048592,
	1048585,
	1048596);
INSERT INTO R_OIR
	VALUES (1048592,
	1048585,
	1048596,
	0);
INSERT INTO R_SIMP
	VALUES (1048586);
INSERT INTO R_REL
	VALUES (1048586,
	18,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048585,
	1048586,
	1048597,
	0,
	0,
	'are defined within');
INSERT INTO R_RTO
	VALUES (1048585,
	1048586,
	1048597,
	0);
INSERT INTO R_OIR
	VALUES (1048585,
	1048586,
	1048597,
	0);
INSERT INTO R_FORM
	VALUES (1048586,
	1048586,
	1048598,
	1,
	1,
	'defines domain of');
INSERT INTO R_RGO
	VALUES (1048586,
	1048586,
	1048598);
INSERT INTO R_OIR
	VALUES (1048586,
	1048586,
	1048598,
	0);
INSERT INTO R_SIMP
	VALUES (1048587);
INSERT INTO R_REL
	VALUES (1048587,
	20,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048584,
	1048587,
	1048599,
	0,
	0,
	'return value defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	1048587,
	1048599,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048587,
	1048599,
	0);
INSERT INTO R_FORM
	VALUES (1048587,
	1048587,
	1048600,
	1,
	1,
	'defines the return value');
INSERT INTO R_RGO
	VALUES (1048587,
	1048587,
	1048600);
INSERT INTO R_OIR
	VALUES (1048587,
	1048587,
	1048600,
	0);
INSERT INTO R_SIMP
	VALUES (1048588);
INSERT INTO R_REL
	VALUES (1048588,
	21,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048587,
	1048588,
	1048601,
	0,
	0,
	'contains');
INSERT INTO R_RTO
	VALUES (1048587,
	1048588,
	1048601,
	0);
INSERT INTO R_OIR
	VALUES (1048587,
	1048588,
	1048601,
	0);
INSERT INTO R_FORM
	VALUES (1048588,
	1048588,
	1048602,
	1,
	1,
	'is part of');
INSERT INTO R_RGO
	VALUES (1048588,
	1048588,
	1048602);
INSERT INTO R_OIR
	VALUES (1048588,
	1048588,
	1048602,
	0);
INSERT INTO R_SIMP
	VALUES (1048589);
INSERT INTO R_REL
	VALUES (1048589,
	19,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (1048587,
	1048589,
	1048603,
	1,
	1,
	'uses');
INSERT INTO R_RGO
	VALUES (1048587,
	1048589,
	1048603);
INSERT INTO R_OIR
	VALUES (1048587,
	1048589,
	1048603,
	0);
INSERT INTO R_PART
	VALUES (1048579,
	1048589,
	1048604,
	0,
	0,
	'provides access to');
INSERT INTO R_RTO
	VALUES (1048579,
	1048589,
	1048604,
	0);
INSERT INTO R_OIR
	VALUES (1048579,
	1048589,
	1048604,
	0);
INSERT INTO R_SIMP
	VALUES (1048590);
INSERT INTO R_REL
	VALUES (1048590,
	15,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048584,
	1048590,
	1048605,
	0,
	0,
	'is defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	1048590,
	1048605,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048590,
	1048605,
	0);
INSERT INTO R_FORM
	VALUES (1048581,
	1048590,
	1048606,
	1,
	1,
	'defines the type of');
INSERT INTO R_RGO
	VALUES (1048581,
	1048590,
	1048606);
INSERT INTO R_OIR
	VALUES (1048581,
	1048590,
	1048606,
	0);
INSERT INTO R_SIMP
	VALUES (1048591);
INSERT INTO R_REL
	VALUES (1048591,
	22,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048584,
	1048591,
	1048607,
	0,
	0,
	'is defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	1048591,
	1048607,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048591,
	1048607,
	0);
INSERT INTO R_FORM
	VALUES (1048588,
	1048591,
	1048608,
	1,
	1,
	'defines the type of');
INSERT INTO R_RGO
	VALUES (1048588,
	1048591,
	1048608);
INSERT INTO R_OIR
	VALUES (1048588,
	1048591,
	1048608,
	0);
INSERT INTO R_SIMP
	VALUES (1048592);
INSERT INTO R_REL
	VALUES (1048592,
	11,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (1048581,
	1048592,
	1048609,
	1,
	1,
	'can be accessed synchronously via');
INSERT INTO R_RGO
	VALUES (1048581,
	1048592,
	1048609);
INSERT INTO R_OIR
	VALUES (1048581,
	1048592,
	1048609,
	0);
INSERT INTO R_PART
	VALUES (1048579,
	1048592,
	1048610,
	0,
	0,
	'is data for');
INSERT INTO R_RTO
	VALUES (1048579,
	1048592,
	1048610,
	0);
INSERT INTO R_OIR
	VALUES (1048579,
	1048592,
	1048610,
	0);
INSERT INTO R_ASSOC
	VALUES (1048593);
INSERT INTO R_REL
	VALUES (1048593,
	13,
	'',
	1048578);
INSERT INTO R_AONE
	VALUES (1048583,
	1048593,
	1048611,
	1,
	1,
	'may carry');
INSERT INTO R_RTO
	VALUES (1048583,
	1048593,
	1048611,
	0);
INSERT INTO R_OIR
	VALUES (1048583,
	1048593,
	1048611,
	0);
INSERT INTO R_AOTH
	VALUES (1048582,
	1048593,
	1048612,
	1,
	1,
	'is carried via');
INSERT INTO R_RTO
	VALUES (1048582,
	1048593,
	1048612,
	0);
INSERT INTO R_OIR
	VALUES (1048582,
	1048593,
	1048612,
	0);
INSERT INTO R_ASSR
	VALUES (1048589,
	1048593,
	1048613,
	0);
INSERT INTO R_RGO
	VALUES (1048589,
	1048593,
	1048613);
INSERT INTO R_OIR
	VALUES (1048589,
	1048593,
	1048613,
	0);
INSERT INTO R_SIMP
	VALUES (1048594);
INSERT INTO R_REL
	VALUES (1048594,
	2,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048578,
	1048594,
	1048614,
	0,
	0,
	'is contained in');
INSERT INTO R_RTO
	VALUES (1048578,
	1048594,
	1048614,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	1048594,
	1048614,
	0);
INSERT INTO R_FORM
	VALUES (3145732,
	1048594,
	1048615,
	1,
	1,
	'is decomposed into');
INSERT INTO R_RGO
	VALUES (3145732,
	1048594,
	1048615);
INSERT INTO R_OIR
	VALUES (3145732,
	1048594,
	1048615,
	1048580);
INSERT INTO R_SIMP
	VALUES (1048595);
INSERT INTO R_REL
	VALUES (1048595,
	4,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048578,
	1048595,
	1048616,
	0,
	0,
	'abstracts associations between objects in');
INSERT INTO R_RTO
	VALUES (1048578,
	1048595,
	1048616,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	1048595,
	1048616,
	0);
INSERT INTO R_FORM
	VALUES (1572865,
	1048595,
	1048617,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (1572865,
	1048595,
	1048617);
INSERT INTO R_OIR
	VALUES (1572865,
	1048595,
	1048617,
	1048577);
INSERT INTO R_SIMP
	VALUES (1048596);
INSERT INTO R_REL
	VALUES (1048596,
	5,
	'

Notes:

',
	1048578);
INSERT INTO R_PART
	VALUES (1048578,
	1048596,
	1048618,
	0,
	0,
	'abstracts asynchronous communication between objects in');
INSERT INTO R_RTO
	VALUES (1048578,
	1048596,
	1048618,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	1048596,
	1048618,
	0);
INSERT INTO R_FORM
	VALUES (2097153,
	1048596,
	1048619,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (2097153,
	1048596,
	1048619);
INSERT INTO R_OIR
	VALUES (2097153,
	1048596,
	1048619,
	1048578);
INSERT INTO R_SIMP
	VALUES (1048597);
INSERT INTO R_REL
	VALUES (1048597,
	6,
	'

Notes:

',
	1048578);
INSERT INTO R_PART
	VALUES (1048578,
	1048597,
	1048620,
	0,
	0,
	'abstracts synchronous data access between objects in');
INSERT INTO R_RTO
	VALUES (1048578,
	1048597,
	1048620,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	1048597,
	1048620,
	0);
INSERT INTO R_FORM
	VALUES (2097160,
	1048597,
	1048621,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (2097160,
	1048597,
	1048621);
INSERT INTO R_OIR
	VALUES (2097160,
	1048597,
	1048621,
	1048579);
INSERT INTO R_SIMP
	VALUES (1048598);
INSERT INTO R_REL
	VALUES (1048598,
	3,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048578,
	1048598,
	1048622,
	0,
	0,
	'represents an object from another subsystem in');
INSERT INTO R_RTO
	VALUES (1048578,
	1048598,
	1048622,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	1048598,
	1048622,
	0);
INSERT INTO R_FORM
	VALUES (3145740,
	1048598,
	1048623,
	1,
	1,
	'can contain objects from other subsystems via');
INSERT INTO R_RGO
	VALUES (3145740,
	1048598,
	1048623);
INSERT INTO R_OIR
	VALUES (3145740,
	1048598,
	1048623,
	1048581);
INSERT INTO R_SIMP
	VALUES (1048599);
INSERT INTO R_REL
	VALUES (1048599,
	24,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048590,
	1048599,
	1048624,
	0,
	0,
	'is defined for');
INSERT INTO R_RTO
	VALUES (1048590,
	1048599,
	1048624,
	0);
INSERT INTO R_OIR
	VALUES (1048590,
	1048599,
	1048624,
	0);
INSERT INTO R_FORM
	VALUES (1048591,
	1048599,
	1048625,
	1,
	1,
	'defines');
INSERT INTO R_RGO
	VALUES (1048591,
	1048599,
	1048625);
INSERT INTO R_OIR
	VALUES (1048591,
	1048599,
	1048625,
	0);
INSERT INTO R_SIMP
	VALUES (1048600);
INSERT INTO R_REL
	VALUES (1048600,
	25,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048584,
	1048600,
	1048626,
	0,
	0,
	'has return type of');
INSERT INTO R_RTO
	VALUES (1048584,
	1048600,
	1048626,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048600,
	1048626,
	0);
INSERT INTO R_FORM
	VALUES (1048590,
	1048600,
	1048627,
	1,
	1,
	'defines return type of');
INSERT INTO R_RGO
	VALUES (1048590,
	1048600,
	1048627);
INSERT INTO R_OIR
	VALUES (1048590,
	1048600,
	1048627,
	0);
INSERT INTO R_SIMP
	VALUES (1048601);
INSERT INTO R_REL
	VALUES (1048601,
	23,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048577,
	1048601,
	1048628,
	0,
	0,
	'is defined in');
INSERT INTO R_RTO
	VALUES (1048577,
	1048601,
	1048628,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	1048601,
	1048628,
	0);
INSERT INTO R_FORM
	VALUES (1048590,
	1048601,
	1048629,
	1,
	1,
	'defines');
INSERT INTO R_RGO
	VALUES (1048590,
	1048601,
	1048629);
INSERT INTO R_OIR
	VALUES (1048590,
	1048601,
	1048629,
	0);
INSERT INTO R_SIMP
	VALUES (1048602);
INSERT INTO R_REL
	VALUES (1048602,
	26,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048584,
	1048602,
	1048630,
	0,
	0,
	'');
INSERT INTO R_RTO
	VALUES (1048584,
	1048602,
	1048630,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	1048602,
	1048630,
	0);
INSERT INTO R_FORM
	VALUES (1048591,
	1048602,
	1048631,
	1,
	1,
	'defines type of');
INSERT INTO R_RGO
	VALUES (1048591,
	1048602,
	1048631);
INSERT INTO R_OIR
	VALUES (1048591,
	1048602,
	1048631,
	0);
INSERT INTO R_SIMP
	VALUES (1048603);
INSERT INTO R_REL
	VALUES (1048603,
	27,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (1048593,
	1048603,
	1048632,
	1,
	1,
	'is defined by');
INSERT INTO R_RGO
	VALUES (1048593,
	1048603,
	1048632);
INSERT INTO R_OIR
	VALUES (1048593,
	1048603,
	1048632,
	0);
INSERT INTO R_PART
	VALUES (1048592,
	1048603,
	1048633,
	0,
	0,
	'defines');
INSERT INTO R_RTO
	VALUES (1048592,
	1048603,
	1048633,
	0);
INSERT INTO R_OIR
	VALUES (1048592,
	1048603,
	1048633,
	0);
INSERT INTO R_SIMP
	VALUES (4718617);
INSERT INTO R_REL
	VALUES (4718617,
	28,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (4718605,
	4718617,
	4718641,
	0,
	0,
	'');
INSERT INTO R_RTO
	VALUES (4718605,
	4718617,
	4718641,
	0);
INSERT INTO R_OIR
	VALUES (4718605,
	4718617,
	4718641,
	0);
INSERT INTO R_FORM
	VALUES (1048577,
	4718617,
	4718642,
	1,
	1,
	'');
INSERT INTO R_RGO
	VALUES (1048577,
	4718617,
	4718642);
INSERT INTO R_OIR
	VALUES (1048577,
	4718617,
	4718642,
	0);
INSERT INTO R_SIMP
	VALUES (4718618);
INSERT INTO R_REL
	VALUES (4718618,
	29,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718606,
	4718618,
	4718643,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (4718606,
	4718618,
	4718643);
INSERT INTO R_OIR
	VALUES (4718606,
	4718618,
	4718643,
	0);
INSERT INTO R_PART
	VALUES (1048577,
	4718618,
	4718644,
	0,
	1,
	'');
INSERT INTO R_RTO
	VALUES (1048577,
	4718618,
	4718644,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	4718618,
	4718644,
	0);
INSERT INTO R_ASSOC
	VALUES (4718620);
INSERT INTO R_REL
	VALUES (4718620,
	31,
	'',
	1048578);
INSERT INTO R_AONE
	VALUES (4718606,
	4718620,
	4718647,
	0,
	0,
	'');
INSERT INTO R_RTO
	VALUES (4718606,
	4718620,
	4718647,
	0);
INSERT INTO R_OIR
	VALUES (4718606,
	4718620,
	4718647,
	0);
INSERT INTO R_AOTH
	VALUES (1048590,
	4718620,
	4718648,
	1,
	1,
	'contains');
INSERT INTO R_RTO
	VALUES (1048590,
	4718620,
	4718648,
	0);
INSERT INTO R_OIR
	VALUES (1048590,
	4718620,
	4718648,
	0);
INSERT INTO R_ASSR
	VALUES (4718607,
	4718620,
	4718649,
	0);
INSERT INTO R_RGO
	VALUES (4718607,
	4718620,
	4718649);
INSERT INTO R_OIR
	VALUES (4718607,
	4718620,
	4718649,
	0);
INSERT INTO R_SIMP
	VALUES (4718621);
INSERT INTO R_REL
	VALUES (4718621,
	30,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718608,
	4718621,
	4718650,
	0,
	1,
	'is parent to other packages via');
INSERT INTO R_RGO
	VALUES (4718608,
	4718621,
	4718650);
INSERT INTO R_OIR
	VALUES (4718608,
	4718621,
	4718650,
	0);
INSERT INTO R_PART
	VALUES (4718606,
	4718621,
	4718651,
	0,
	0,
	'contains children of');
INSERT INTO R_RTO
	VALUES (4718606,
	4718621,
	4718651,
	0);
INSERT INTO R_OIR
	VALUES (4718606,
	4718621,
	4718651,
	0);
INSERT INTO R_SIMP
	VALUES (4718622);
INSERT INTO R_REL
	VALUES (4718622,
	32,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (4718608,
	4718622,
	4718652,
	0,
	1,
	'is child via');
INSERT INTO R_RTO
	VALUES (4718608,
	4718622,
	4718652,
	0);
INSERT INTO R_OIR
	VALUES (4718608,
	4718622,
	4718652,
	0);
INSERT INTO R_FORM
	VALUES (4718606,
	4718622,
	4718653,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (4718606,
	4718622,
	4718653);
INSERT INTO R_OIR
	VALUES (4718606,
	4718622,
	4718653,
	0);
INSERT INTO R_SIMP
	VALUES (4718626);
INSERT INTO R_REL
	VALUES (4718626,
	40,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048577,
	4718626,
	4718662,
	0,
	1,
	'');
INSERT INTO R_RTO
	VALUES (1048577,
	4718626,
	4718662,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	4718626,
	4718662,
	0);
INSERT INTO R_FORM
	VALUES (4718612,
	4718626,
	4718663,
	1,
	1,
	'');
INSERT INTO R_RGO
	VALUES (4718612,
	4718626,
	4718663);
INSERT INTO R_OIR
	VALUES (4718612,
	4718626,
	4718663,
	0);
INSERT INTO R_ASSOC
	VALUES (4718627);
INSERT INTO R_REL
	VALUES (4718627,
	39,
	'',
	1048578);
INSERT INTO R_AONE
	VALUES (4718612,
	4718627,
	4718664,
	0,
	0,
	'is contained in');
INSERT INTO R_RTO
	VALUES (4718612,
	4718627,
	4718664,
	0);
INSERT INTO R_OIR
	VALUES (4718612,
	4718627,
	4718664,
	0);
INSERT INTO R_AOTH
	VALUES (1048584,
	4718627,
	4718665,
	1,
	1,
	'contains');
INSERT INTO R_RTO
	VALUES (1048584,
	4718627,
	4718665,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	4718627,
	4718665,
	0);
INSERT INTO R_ASSR
	VALUES (4718613,
	4718627,
	4718666,
	0);
INSERT INTO R_RGO
	VALUES (4718613,
	4718627,
	4718666);
INSERT INTO R_OIR
	VALUES (4718613,
	4718627,
	4718666,
	0);
INSERT INTO R_SIMP
	VALUES (4718628);
INSERT INTO R_REL
	VALUES (4718628,
	37,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718614,
	4718628,
	4718667,
	0,
	1,
	'is parent to other packages via');
INSERT INTO R_RGO
	VALUES (4718614,
	4718628,
	4718667);
INSERT INTO R_OIR
	VALUES (4718614,
	4718628,
	4718667,
	0);
INSERT INTO R_PART
	VALUES (4718612,
	4718628,
	4718668,
	0,
	0,
	'contains children of');
INSERT INTO R_RTO
	VALUES (4718612,
	4718628,
	4718668,
	0);
INSERT INTO R_OIR
	VALUES (4718612,
	4718628,
	4718668,
	0);
INSERT INTO R_SIMP
	VALUES (4718629);
INSERT INTO R_REL
	VALUES (4718629,
	38,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718612,
	4718629,
	4718669,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (4718612,
	4718629,
	4718669);
INSERT INTO R_OIR
	VALUES (4718612,
	4718629,
	4718669,
	0);
INSERT INTO R_PART
	VALUES (4718614,
	4718629,
	4718670,
	0,
	1,
	'is child via');
INSERT INTO R_RTO
	VALUES (4718614,
	4718629,
	4718670,
	0);
INSERT INTO R_OIR
	VALUES (4718614,
	4718629,
	4718670,
	0);
INSERT INTO R_ASSOC
	VALUES (4718630);
INSERT INTO R_REL
	VALUES (4718630,
	43,
	'',
	1048578);
INSERT INTO R_AONE
	VALUES (1048577,
	4718630,
	4718671,
	0,
	1,
	'is first level of partitioning for');
INSERT INTO R_RTO
	VALUES (1048577,
	4718630,
	4718671,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	4718630,
	4718671,
	0);
INSERT INTO R_AOTH
	VALUES (1048578,
	4718630,
	4718672,
	1,
	1,
	'has top level subsystems');
INSERT INTO R_RTO
	VALUES (1048578,
	4718630,
	4718672,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	4718630,
	4718672,
	0);
INSERT INTO R_ASSR
	VALUES (4718618,
	4718630,
	4718673,
	0);
INSERT INTO R_RGO
	VALUES (4718618,
	4718630,
	4718673);
INSERT INTO R_OIR
	VALUES (4718618,
	4718630,
	4718673,
	0);
INSERT INTO R_SIMP
	VALUES (4718631);
INSERT INTO R_REL
	VALUES (4718631,
	41,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718615,
	4718631,
	4718674,
	1,
	1,
	'is parent to other packages via');
INSERT INTO R_RGO
	VALUES (4718615,
	4718631,
	4718674);
INSERT INTO R_OIR
	VALUES (4718615,
	4718631,
	4718674,
	0);
INSERT INTO R_PART
	VALUES (1048578,
	4718631,
	4718675,
	0,
	0,
	'contains children of');
INSERT INTO R_RTO
	VALUES (1048578,
	4718631,
	4718675,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	4718631,
	4718675,
	0);
INSERT INTO R_SIMP
	VALUES (4718632);
INSERT INTO R_REL
	VALUES (4718632,
	42,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718615,
	4718632,
	4718676,
	0,
	1,
	'is child via');
INSERT INTO R_RGO
	VALUES (4718615,
	4718632,
	4718676);
INSERT INTO R_OIR
	VALUES (4718615,
	4718632,
	4718676,
	0);
INSERT INTO R_PART
	VALUES (1048578,
	4718632,
	4718677,
	0,
	0,
	'contains');
INSERT INTO R_RTO
	VALUES (1048578,
	4718632,
	4718677,
	0);
INSERT INTO R_OIR
	VALUES (1048578,
	4718632,
	4718677,
	0);
INSERT INTO R_ASSOC
	VALUES (4718633);
INSERT INTO R_REL
	VALUES (4718633,
	33,
	'',
	1048578);
INSERT INTO R_AONE
	VALUES (4718609,
	4718633,
	4718678,
	0,
	0,
	'is contained in');
INSERT INTO R_RTO
	VALUES (4718609,
	4718633,
	4718678,
	0);
INSERT INTO R_OIR
	VALUES (4718609,
	4718633,
	4718678,
	0);
INSERT INTO R_AOTH
	VALUES (1048579,
	4718633,
	4718679,
	1,
	1,
	'contains');
INSERT INTO R_RTO
	VALUES (1048579,
	4718633,
	4718679,
	0);
INSERT INTO R_OIR
	VALUES (1048579,
	4718633,
	4718679,
	0);
INSERT INTO R_ASSR
	VALUES (4718611,
	4718633,
	4718686,
	0);
INSERT INTO R_RGO
	VALUES (4718611,
	4718633,
	4718686);
INSERT INTO R_OIR
	VALUES (4718611,
	4718633,
	4718686,
	0);
INSERT INTO R_SIMP
	VALUES (4718634);
INSERT INTO R_REL
	VALUES (4718634,
	35,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718609,
	4718634,
	4718680,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (4718609,
	4718634,
	4718680);
INSERT INTO R_OIR
	VALUES (4718609,
	4718634,
	4718680,
	0);
INSERT INTO R_PART
	VALUES (4718610,
	4718634,
	4718681,
	0,
	1,
	'is child via');
INSERT INTO R_RTO
	VALUES (4718610,
	4718634,
	4718681,
	0);
INSERT INTO R_OIR
	VALUES (4718610,
	4718634,
	4718681,
	0);
INSERT INTO R_SIMP
	VALUES (4718635);
INSERT INTO R_REL
	VALUES (4718635,
	34,
	'',
	1048578);
INSERT INTO R_FORM
	VALUES (4718610,
	4718635,
	4718682,
	0,
	1,
	'is parent to other packages via');
INSERT INTO R_RGO
	VALUES (4718610,
	4718635,
	4718682);
INSERT INTO R_OIR
	VALUES (4718610,
	4718635,
	4718682,
	0);
INSERT INTO R_PART
	VALUES (4718609,
	4718635,
	4718683,
	0,
	0,
	'contains children of');
INSERT INTO R_RTO
	VALUES (4718609,
	4718635,
	4718683,
	0);
INSERT INTO R_OIR
	VALUES (4718609,
	4718635,
	4718683,
	0);
INSERT INTO R_SIMP
	VALUES (4718636);
INSERT INTO R_REL
	VALUES (4718636,
	36,
	'',
	1048578);
INSERT INTO R_PART
	VALUES (1048577,
	4718636,
	4718684,
	0,
	1,
	'is contained in');
INSERT INTO R_RTO
	VALUES (1048577,
	4718636,
	4718684,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	4718636,
	4718684,
	0);
INSERT INTO R_FORM
	VALUES (4718609,
	4718636,
	4718685,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (4718609,
	4718636,
	4718685);
INSERT INTO R_OIR
	VALUES (4718609,
	4718636,
	4718685,
	0);
INSERT INTO S_SS
	VALUES (1572867,
	'Association',
	'

Notes:

',
	'R',
	201,
	94514,
	1572867);
INSERT INTO O_OBJ
	VALUES (1572865,
	'Relationship',
	201,
	'R_REL',
	'A Relationship captures an association that exists between things in the real world. A Relationship is stated in terms of the formal Objects that participate in the association.',
	1572867);
INSERT INTO O_NBATTR
	VALUES (1572865,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572865,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572865,
	1572865,
	0,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (1572866,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572866,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572866,
	1572865,
	1572865,
	'Numb',
	'',
	'',
	'Numb',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572867,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572867,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572867,
	1572865,
	1572866,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (1572865,
	1048578,
	0,
	1048594,
	1048595,
	1048617,
	1048616,
	1572868,
	1572865,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572868,
	1572865,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (1572868,
	1572865,
	1572867,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572869,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572869,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572869,
	1572865,
	1572868,
	'LinkNeeded',
	'A flag used by the translation engine to indicate that relationship instantiation implementation code needs to be generated. This flag is set to TRUE by the first pass translation process if a RELATE statement involving this relationship is used in the action language.',
	'',
	'LinkNeeded',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1572870,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572870,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572870,
	1572865,
	1572869,
	'UnlinkNeeded',
	'A flag used by the translation engine to indicate that relationship deletion implementation code needs to be generated. This flag is set to TRUE by the first pass translation process if an UNRELATE statement involving this relationship is used in the action language.',
	'',
	'UnlinkNeeded',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1572871,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572871,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572871,
	1572865,
	1572870,
	'Navigated',
	'A flag used by the translation engine to indicate that this relationship is navigated in the action language of the application analysis domain.',
	'',
	'Navigated',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1572872,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572872,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572872,
	1572865,
	1572871,
	'Order',
	'This attribute is provided to allow the archetypes to sort a collection of Relationship instance in a particular order. For example, sorting an objects relationships in ascending order relative to the Relationship.Numb attribute (relationship number).',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572873,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572873,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572873,
	1572865,
	1572872,
	'storage_needed',
	'',
	'',
	'storage_needed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1572874,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572874,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572874,
	1572865,
	1572873,
	'set_storage_needed',
	'',
	'',
	'set_storage_needed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (1572875,
	1572865);
INSERT INTO O_BATTR
	VALUES (1572875,
	1572865);
INSERT INTO O_ATTR
	VALUES (1572875,
	1572865,
	1572874,
	'set_storage_key_lett',
	'',
	'',
	'set_storage_key_lett',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572865);
INSERT INTO O_OIDA
	VALUES (1572865,
	1572865,
	0);
INSERT INTO O_RTIDA
	VALUES (1572865,
	1572865,
	0,
	1572866,
	1572868);
INSERT INTO O_RTIDA
	VALUES (1572865,
	1572865,
	0,
	1572865,
	1572865);
INSERT INTO O_RTIDA
	VALUES (1572865,
	1572865,
	0,
	4718606,
	4718620);
INSERT INTO O_OBJ
	VALUES (1572866,
	'Simple Relationship',
	205,
	'R_SIMP',
	'A Simple Relationship is a relationship between two objects which is formalized with referential attributes.',
	1572867);
INSERT INTO O_REF
	VALUES (1572866,
	1572865,
	0,
	1572865,
	1572866,
	1572869,
	1572868,
	1572876,
	1572866,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572876,
	1572866,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572876,
	1572866,
	0,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1572866);
INSERT INTO O_OIDA
	VALUES (1572876,
	1572866,
	0);
INSERT INTO O_RTIDA
	VALUES (1572876,
	1572866,
	0,
	1572868,
	1572876);
INSERT INTO O_RTIDA
	VALUES (1572876,
	1572866,
	0,
	1572867,
	1572874);
INSERT INTO O_OBJ
	VALUES (1572867,
	'Associative Relationship',
	208,
	'R_ASSOC',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572867,
	1572865,
	0,
	1572865,
	1572866,
	1572871,
	1572868,
	1572877,
	1572867,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572877,
	1572867,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572877,
	1572867,
	0,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1572867);
INSERT INTO O_OIDA
	VALUES (1572877,
	1572867,
	0);
INSERT INTO O_RTIDA
	VALUES (1572877,
	1572867,
	0,
	1572870,
	1572880);
INSERT INTO O_RTIDA
	VALUES (1572877,
	1572867,
	0,
	1572871,
	1572882);
INSERT INTO O_RTIDA
	VALUES (1572877,
	1572867,
	0,
	1572869,
	1572878);
INSERT INTO O_OBJ
	VALUES (1572868,
	'Subtype-Supertype Relationship',
	212,
	'R_SUBSUP',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572868,
	1572865,
	0,
	1572865,
	1572866,
	1572872,
	1572868,
	1572878,
	1572868,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572878,
	1572868,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572878,
	1572868,
	0,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1572868);
INSERT INTO O_OIDA
	VALUES (1572878,
	1572868,
	0);
INSERT INTO O_RTIDA
	VALUES (1572878,
	1572868,
	0,
	1572873,
	1572886);
INSERT INTO O_RTIDA
	VALUES (1572878,
	1572868,
	0,
	1572872,
	1572884);
INSERT INTO O_OBJ
	VALUES (1572869,
	'Composition Relationship',
	215,
	'R_COMP',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572869,
	1572865,
	0,
	1572865,
	1572866,
	1572870,
	1572868,
	1572879,
	1572869,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572879,
	1572869,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572879,
	1572869,
	0,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572880,
	1572869);
INSERT INTO O_BATTR
	VALUES (1572880,
	1572869);
INSERT INTO O_ATTR
	VALUES (1572880,
	1572869,
	1572879,
	'Rel_Chn',
	'Relationship Chain.',
	'',
	'Rel_Chn',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572869);
INSERT INTO O_OIDA
	VALUES (1572879,
	1572869,
	0);
INSERT INTO O_RTIDA
	VALUES (1572879,
	1572869,
	0,
	1572874,
	1572888);
INSERT INTO O_RTIDA
	VALUES (1572879,
	1572869,
	0,
	1572875,
	1572890);
INSERT INTO O_OBJ
	VALUES (1572870,
	'Object As Simple Participant',
	206,
	'R_PART',
	'An Object As Simple Participant is the referred to object in a simple relationship.',
	1572867);
INSERT INTO O_REF
	VALUES (1572870,
	1572880,
	0,
	1572931,
	1572878,
	1572902,
	1572900,
	1572881,
	1572885,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572881,
	1572870,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572881,
	1572870,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572870,
	1572866,
	0,
	1572876,
	1572867,
	1572873,
	1572874,
	1572882,
	1572870,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572870,
	1572880,
	0,
	1572932,
	1572878,
	1572902,
	1572900,
	1572882,
	1572886,
	1572870,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572882,
	1572870,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572882,
	1572870,
	1572881,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572870,
	1572880,
	0,
	1572933,
	1572878,
	1572902,
	1572900,
	1572883,
	1572887,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572883,
	1572870,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572883,
	1572870,
	1572882,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572884,
	1572870);
INSERT INTO O_BATTR
	VALUES (1572884,
	1572870);
INSERT INTO O_ATTR
	VALUES (1572884,
	1572870,
	1572883,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572885,
	1572870);
INSERT INTO O_BATTR
	VALUES (1572885,
	1572870);
INSERT INTO O_ATTR
	VALUES (1572885,
	1572870,
	1572884,
	'Cond',
	'',
	'',
	'Cond',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572886,
	1572870);
INSERT INTO O_BATTR
	VALUES (1572886,
	1572870);
INSERT INTO O_ATTR
	VALUES (1572886,
	1572870,
	1572885,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572870);
INSERT INTO O_OIDA
	VALUES (1572882,
	1572870,
	0);
INSERT INTO O_OIDA
	VALUES (1572881,
	1572870,
	0);
INSERT INTO O_OIDA
	VALUES (1572883,
	1572870,
	0);
INSERT INTO O_OBJ
	VALUES (1572871,
	'Object As Simple Formalizer',
	207,
	'R_FORM',
	'An Object As Simple Formalizer is the referring object in a simple relationsip.',
	1572867);
INSERT INTO O_REF
	VALUES (1572871,
	1572881,
	0,
	1572936,
	1572877,
	1572898,
	1572896,
	1572887,
	1572888,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572887,
	1572871,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572887,
	1572871,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572871,
	1572866,
	0,
	1572876,
	1572868,
	1572875,
	1572876,
	1572888,
	1572871,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572871,
	1572881,
	0,
	1572937,
	1572877,
	1572898,
	1572896,
	1572888,
	1572889,
	1572871,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572888,
	1572871,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572888,
	1572871,
	1572887,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572871,
	1572881,
	0,
	1572938,
	1572877,
	1572898,
	1572896,
	1572889,
	1572890,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572889,
	1572871,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572889,
	1572871,
	1572888,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572890,
	1572871);
INSERT INTO O_BATTR
	VALUES (1572890,
	1572871);
INSERT INTO O_ATTR
	VALUES (1572890,
	1572871,
	1572889,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572891,
	1572871);
INSERT INTO O_BATTR
	VALUES (1572891,
	1572871);
INSERT INTO O_ATTR
	VALUES (1572891,
	1572871,
	1572890,
	'Cond',
	'',
	'',
	'Cond',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572892,
	1572871);
INSERT INTO O_BATTR
	VALUES (1572892,
	1572871);
INSERT INTO O_ATTR
	VALUES (1572892,
	1572871,
	1572891,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572871);
INSERT INTO O_OIDA
	VALUES (1572888,
	1572871,
	0);
INSERT INTO O_OIDA
	VALUES (1572889,
	1572871,
	0);
INSERT INTO O_OIDA
	VALUES (1572887,
	1572871,
	0);
INSERT INTO O_OBJ
	VALUES (1572872,
	'Object As Associated One Side',
	209,
	'R_AONE',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572872,
	1572880,
	0,
	1572931,
	1572878,
	1572903,
	1572900,
	1572893,
	1572891,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572893,
	1572872,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572893,
	1572872,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572872,
	1572867,
	0,
	1572877,
	1572869,
	1572877,
	1572878,
	1572894,
	1572872,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572872,
	1572880,
	0,
	1572932,
	1572878,
	1572903,
	1572900,
	1572894,
	1572892,
	1572872,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572894,
	1572872,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572894,
	1572872,
	1572893,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572872,
	1572880,
	0,
	1572933,
	1572878,
	1572903,
	1572900,
	1572895,
	1572893,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572895,
	1572872,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572895,
	1572872,
	1572894,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572896,
	1572872);
INSERT INTO O_BATTR
	VALUES (1572896,
	1572872);
INSERT INTO O_ATTR
	VALUES (1572896,
	1572872,
	1572895,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572897,
	1572872);
INSERT INTO O_BATTR
	VALUES (1572897,
	1572872);
INSERT INTO O_ATTR
	VALUES (1572897,
	1572872,
	1572896,
	'Cond',
	'',
	'',
	'Cond',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572898,
	1572872);
INSERT INTO O_BATTR
	VALUES (1572898,
	1572872);
INSERT INTO O_ATTR
	VALUES (1572898,
	1572872,
	1572897,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572872);
INSERT INTO O_OIDA
	VALUES (1572895,
	1572872,
	0);
INSERT INTO O_OIDA
	VALUES (1572893,
	1572872,
	0);
INSERT INTO O_OIDA
	VALUES (1572894,
	1572872,
	0);
INSERT INTO O_OBJ
	VALUES (1572873,
	'Object As Associated Other Side',
	210,
	'R_AOTH',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572873,
	1572880,
	0,
	1572931,
	1572878,
	1572904,
	1572900,
	1572899,
	1572894,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572899,
	1572873,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572899,
	1572873,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572873,
	1572867,
	0,
	1572877,
	1572870,
	1572879,
	1572880,
	1572900,
	1572873,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572873,
	1572880,
	0,
	1572932,
	1572878,
	1572904,
	1572900,
	1572900,
	1572895,
	1572873,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572900,
	1572873,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572900,
	1572873,
	1572899,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572873,
	1572880,
	0,
	1572933,
	1572878,
	1572904,
	1572900,
	1572901,
	1572896,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572901,
	1572873,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572901,
	1572873,
	1572900,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572902,
	1572873);
INSERT INTO O_BATTR
	VALUES (1572902,
	1572873);
INSERT INTO O_ATTR
	VALUES (1572902,
	1572873,
	1572901,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572903,
	1572873);
INSERT INTO O_BATTR
	VALUES (1572903,
	1572873);
INSERT INTO O_ATTR
	VALUES (1572903,
	1572873,
	1572902,
	'Cond',
	'',
	'',
	'Cond',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572904,
	1572873);
INSERT INTO O_BATTR
	VALUES (1572904,
	1572873);
INSERT INTO O_ATTR
	VALUES (1572904,
	1572873,
	1572903,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572873);
INSERT INTO O_OIDA
	VALUES (1572901,
	1572873,
	0);
INSERT INTO O_OIDA
	VALUES (1572900,
	1572873,
	0);
INSERT INTO O_OIDA
	VALUES (1572899,
	1572873,
	0);
INSERT INTO O_OBJ
	VALUES (1572874,
	'Object As Associator',
	211,
	'R_ASSR',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572874,
	1572881,
	0,
	1572936,
	1572877,
	1572899,
	1572896,
	1572905,
	1572897,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572905,
	1572874,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572905,
	1572874,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572874,
	1572867,
	0,
	1572877,
	1572871,
	1572881,
	1572882,
	1572906,
	1572874,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572874,
	1572881,
	0,
	1572937,
	1572877,
	1572899,
	1572896,
	1572906,
	1572898,
	1572874,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572906,
	1572874,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572906,
	1572874,
	1572905,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572874,
	1572881,
	0,
	1572938,
	1572877,
	1572899,
	1572896,
	1572907,
	1572899,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572907,
	1572874,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572907,
	1572874,
	1572906,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572908,
	1572874);
INSERT INTO O_BATTR
	VALUES (1572908,
	1572874);
INSERT INTO O_ATTR
	VALUES (1572908,
	1572874,
	1572907,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	1572874);
INSERT INTO O_OIDA
	VALUES (1572907,
	1572874,
	0);
INSERT INTO O_OIDA
	VALUES (1572905,
	1572874,
	0);
INSERT INTO O_OIDA
	VALUES (1572906,
	1572874,
	0);
INSERT INTO O_OBJ
	VALUES (1572875,
	'Object As Supertype',
	213,
	'R_SUPER',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572875,
	1572880,
	0,
	1572931,
	1572878,
	1572901,
	1572900,
	1572909,
	1572900,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572909,
	1572875,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572909,
	1572875,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572875,
	1572868,
	0,
	1572878,
	1572872,
	1572883,
	1572884,
	1572910,
	1572875,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572875,
	1572880,
	0,
	1572932,
	1572878,
	1572901,
	1572900,
	1572910,
	1572901,
	1572875,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572910,
	1572875,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572910,
	1572875,
	1572909,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572875,
	1572880,
	0,
	1572933,
	1572878,
	1572901,
	1572900,
	1572911,
	1572902,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572911,
	1572875,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572911,
	1572875,
	1572910,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1572875);
INSERT INTO O_OIDA
	VALUES (1572910,
	1572875,
	0);
INSERT INTO O_OIDA
	VALUES (1572909,
	1572875,
	0);
INSERT INTO O_OIDA
	VALUES (1572911,
	1572875,
	0);
INSERT INTO O_OBJ
	VALUES (1572876,
	'Object As Subtype',
	214,
	'R_SUB',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572876,
	1572881,
	0,
	1572936,
	1572877,
	1572897,
	1572896,
	1572912,
	1572903,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572912,
	1572876,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572912,
	1572876,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572876,
	1572868,
	0,
	1572878,
	1572873,
	1572885,
	1572886,
	1572913,
	1572876,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572876,
	1572881,
	0,
	1572937,
	1572877,
	1572897,
	1572896,
	1572913,
	1572904,
	1572876,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572913,
	1572876,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572913,
	1572876,
	1572912,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572876,
	1572881,
	0,
	1572938,
	1572877,
	1572897,
	1572896,
	1572914,
	1572905,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572914,
	1572876,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572914,
	1572876,
	1572913,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1572876);
INSERT INTO O_OIDA
	VALUES (1572914,
	1572876,
	0);
INSERT INTO O_OIDA
	VALUES (1572912,
	1572876,
	0);
INSERT INTO O_OIDA
	VALUES (1572913,
	1572876,
	0);
INSERT INTO O_OBJ
	VALUES (1572877,
	'Object As Composition One Side',
	216,
	'R_CONE',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572877,
	1572879,
	0,
	1572927,
	1572876,
	1572894,
	1572891,
	1572915,
	1572906,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572915,
	1572877,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572915,
	1572877,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572877,
	1572869,
	0,
	1572879,
	1572874,
	1572887,
	1572888,
	1572916,
	1572877,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572877,
	1572879,
	0,
	1572928,
	1572876,
	1572894,
	1572891,
	1572916,
	1572907,
	1572877,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572916,
	1572877,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572916,
	1572877,
	1572915,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572877,
	1572879,
	0,
	1572929,
	1572876,
	1572894,
	1572891,
	1572917,
	1572908,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572917,
	1572877,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572917,
	1572877,
	1572916,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_DBATTR
	VALUES (1572918,
	1572877,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (1572918,
	1572877);
INSERT INTO O_ATTR
	VALUES (1572918,
	1572877,
	1572917,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_DBATTR
	VALUES (1572919,
	1572877,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (1572919,
	1572877);
INSERT INTO O_ATTR
	VALUES (1572919,
	1572877,
	1572918,
	'Cond',
	'',
	'',
	'Cond',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572920,
	1572877);
INSERT INTO O_BATTR
	VALUES (1572920,
	1572877);
INSERT INTO O_ATTR
	VALUES (1572920,
	1572877,
	1572919,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572877);
INSERT INTO O_OIDA
	VALUES (1572917,
	1572877,
	0);
INSERT INTO O_OIDA
	VALUES (1572915,
	1572877,
	0);
INSERT INTO O_OIDA
	VALUES (1572916,
	1572877,
	0);
INSERT INTO O_OBJ
	VALUES (1572878,
	'Object As Composition Other Side',
	217,
	'R_COTH',
	'',
	1572867);
INSERT INTO O_REF
	VALUES (1572878,
	1572879,
	0,
	1572927,
	1572876,
	1572895,
	1572891,
	1572921,
	1572909,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572921,
	1572878,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572921,
	1572878,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572878,
	1572869,
	0,
	1572879,
	1572875,
	1572889,
	1572890,
	1572922,
	1572878,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572878,
	1572879,
	0,
	1572928,
	1572876,
	1572895,
	1572891,
	1572922,
	1572910,
	1572878,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572922,
	1572878,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572922,
	1572878,
	1572921,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572878,
	1572879,
	0,
	1572929,
	1572876,
	1572895,
	1572891,
	1572923,
	1572911,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572923,
	1572878,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572923,
	1572878,
	1572922,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_DBATTR
	VALUES (1572924,
	1572878,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (1572924,
	1572878);
INSERT INTO O_ATTR
	VALUES (1572924,
	1572878,
	1572923,
	'Mult',
	'',
	'',
	'Mult',
	0,
	524291);
INSERT INTO O_DBATTR
	VALUES (1572925,
	1572878,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (1572925,
	1572878);
INSERT INTO O_ATTR
	VALUES (1572925,
	1572878,
	1572924,
	'Cond',
	'',
	'',
	'Cond',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (1572926,
	1572878);
INSERT INTO O_BATTR
	VALUES (1572926,
	1572878);
INSERT INTO O_ATTR
	VALUES (1572926,
	1572878,
	1572925,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	1572878);
INSERT INTO O_OIDA
	VALUES (1572923,
	1572878,
	0);
INSERT INTO O_OIDA
	VALUES (1572921,
	1572878,
	0);
INSERT INTO O_OIDA
	VALUES (1572922,
	1572878,
	0);
INSERT INTO O_OBJ
	VALUES (1572879,
	'Object In Relationship',
	202,
	'R_OIR',
	'An Object In Relationship captures the role which an object plays in participating in a relationship.',
	1572867);
INSERT INTO O_REF
	VALUES (1572879,
	3145732,
	0,
	3145773,
	1572865,
	1572867,
	1572866,
	1572927,
	1572912,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572927,
	1572879,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572927,
	1572879,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572879,
	1572865,
	0,
	1572865,
	1572865,
	1572867,
	1572865,
	1572928,
	1572913,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572928,
	1572879,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572928,
	1572879,
	1572927,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572929,
	1572879);
INSERT INTO O_BATTR
	VALUES (1572929,
	1572879);
INSERT INTO O_ATTR
	VALUES (1572929,
	1572879,
	1572928,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (1572879,
	3145740,
	0,
	3145838,
	1572879,
	1572906,
	1572905,
	1572930,
	1572914,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572930,
	1572879,
	3145838,
	3145740,
	1);
INSERT INTO O_ATTR
	VALUES (1572930,
	1572879,
	1572929,
	'IObj_ID',
	'',
	'',
	'IObj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	1572879);
INSERT INTO O_OIDA
	VALUES (1572927,
	1572879,
	0);
INSERT INTO O_RTIDA
	VALUES (1572927,
	1572879,
	0,
	1572876,
	1572891);
INSERT INTO O_OIDA
	VALUES (1572929,
	1572879,
	0);
INSERT INTO O_RTIDA
	VALUES (1572929,
	1572879,
	0,
	1572876,
	1572891);
INSERT INTO O_OIDA
	VALUES (1572928,
	1572879,
	0);
INSERT INTO O_RTIDA
	VALUES (1572928,
	1572879,
	0,
	1572876,
	1572891);
INSERT INTO O_OBJ
	VALUES (1572880,
	'Referred To Object in Rel',
	203,
	'R_RTO',
	'A Referred To Object In Relationship is an object which contains identifying attributes which are referred to across the relationship.',
	1572867);
INSERT INTO O_REF
	VALUES (1572880,
	1572879,
	0,
	1572927,
	1572876,
	1572892,
	1572891,
	1572931,
	1572879,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (1572880,
	3145738,
	0,
	3145833,
	3145745,
	3145766,
	3145765,
	1572931,
	1572915,
	1572879,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572931,
	1572880,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572931,
	1572880,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572880,
	1572879,
	0,
	1572928,
	1572876,
	1572892,
	1572891,
	1572932,
	1572880,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572932,
	1572880,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572932,
	1572880,
	1572931,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572880,
	1572879,
	0,
	1572929,
	1572876,
	1572892,
	1572891,
	1572933,
	1572881,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572933,
	1572880,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572933,
	1572880,
	1572932,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572880,
	3145738,
	0,
	3145832,
	3145745,
	3145766,
	3145765,
	1572934,
	1572916,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572934,
	1572880,
	3145832,
	3145738,
	1);
INSERT INTO O_ATTR
	VALUES (1572934,
	1572880,
	1572933,
	'Oid_ID',
	'',
	'',
	'Oid_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572935,
	1572880);
INSERT INTO O_BATTR
	VALUES (1572935,
	1572880);
INSERT INTO O_ATTR
	VALUES (1572935,
	1572880,
	1572934,
	'NavigatedTo',
	'A flag used by the translation engine to indicate that the application analysis action language contains a relationship navigation in which the object corrosponding to R_RTO is a component of the ''right hand side'' link expression of the selection statement.

For architectures which optimize relationships, a value of TRUE indicates that storage is necessary in the R_RGO implementation (e.g., ''left hand side'').',
	'',
	'NavigatedTo',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	1572880);
INSERT INTO O_OIDA
	VALUES (1572933,
	1572880,
	0);
INSERT INTO O_RTIDA
	VALUES (1572933,
	1572880,
	0,
	1572878,
	1572900);
INSERT INTO O_OIDA
	VALUES (1572931,
	1572880,
	0);
INSERT INTO O_RTIDA
	VALUES (1572931,
	1572880,
	0,
	1572878,
	1572900);
INSERT INTO O_OIDA
	VALUES (1572932,
	1572880,
	0);
INSERT INTO O_RTIDA
	VALUES (1572932,
	1572880,
	0,
	1572878,
	1572900);
INSERT INTO O_ID
	VALUES (1,
	1572880);
INSERT INTO O_OIDA
	VALUES (1572931,
	1572880,
	1);
INSERT INTO O_RTIDA
	VALUES (1572931,
	1572880,
	1,
	3145744,
	3145762);
INSERT INTO O_OIDA
	VALUES (1572932,
	1572880,
	1);
INSERT INTO O_RTIDA
	VALUES (1572932,
	1572880,
	1,
	3145744,
	3145762);
INSERT INTO O_OIDA
	VALUES (1572934,
	1572880,
	1);
INSERT INTO O_RTIDA
	VALUES (1572934,
	1572880,
	1,
	3145744,
	3145762);
INSERT INTO O_OIDA
	VALUES (1572933,
	1572880,
	1);
INSERT INTO O_RTIDA
	VALUES (1572933,
	1572880,
	1,
	3145744,
	3145762);
INSERT INTO O_OBJ
	VALUES (1572881,
	'Referring Object In Rel',
	204,
	'R_RGO',
	'A referring Object In Relationship is an object which contains referential attributes which refer to identifying attributes across the relationship.',
	1572867);
INSERT INTO O_REF
	VALUES (1572881,
	1572879,
	0,
	1572927,
	1572876,
	1572893,
	1572891,
	1572936,
	1572882,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572936,
	1572881,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (1572936,
	1572881,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572881,
	1572879,
	0,
	1572928,
	1572876,
	1572893,
	1572891,
	1572937,
	1572883,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572937,
	1572881,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (1572937,
	1572881,
	1572936,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (1572881,
	1572879,
	0,
	1572929,
	1572876,
	1572893,
	1572891,
	1572938,
	1572884,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (1572938,
	1572881,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (1572938,
	1572881,
	1572937,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (1572939,
	1572881);
INSERT INTO O_BATTR
	VALUES (1572939,
	1572881);
INSERT INTO O_ATTR
	VALUES (1572939,
	1572881,
	1572938,
	'NavigatedTo',
	'A flag used by the translation engine to indicate that the application analysis action language contains a relationship navigation in which the object corrosponding to R_RGO is a component of the ''right hand side'' link expression of the selection statement.

For architectures which optimize relationships, a value of TRUE indicates that storage is necessary in the R_RTO implementation (e.g., ''left hand side'').',
	'',
	'NavigatedTo',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	1572881);
INSERT INTO O_OIDA
	VALUES (1572938,
	1572881,
	0);
INSERT INTO O_RTIDA
	VALUES (1572938,
	1572881,
	0,
	3145746,
	3145767);
INSERT INTO O_RTIDA
	VALUES (1572938,
	1572881,
	0,
	1572877,
	1572896);
INSERT INTO O_OIDA
	VALUES (1572936,
	1572881,
	0);
INSERT INTO O_RTIDA
	VALUES (1572936,
	1572881,
	0,
	1572877,
	1572896);
INSERT INTO O_RTIDA
	VALUES (1572936,
	1572881,
	0,
	3145746,
	3145767);
INSERT INTO O_OIDA
	VALUES (1572937,
	1572881,
	0);
INSERT INTO O_RTIDA
	VALUES (1572937,
	1572881,
	0,
	1572877,
	1572896);
INSERT INTO O_RTIDA
	VALUES (1572937,
	1572881,
	0,
	3145746,
	3145767);
INSERT INTO O_IOBJ
	VALUES (1572865,
	3145732,
	5,
	1572867,
	'Class',
	'O_OBJ');
INSERT INTO O_IOBJ
	VALUES (1572866,
	3145740,
	5,
	1572867,
	'Imported Class',
	'O_IOBJ');
INSERT INTO R_ASSOC
	VALUES (1572865);
INSERT INTO R_REL
	VALUES (1572865,
	201,
	'',
	1572867);
INSERT INTO R_AONE
	VALUES (1572865,
	1572865,
	1572865,
	1,
	1,
	'has instance associations abstracted');
INSERT INTO R_RTO
	VALUES (1572865,
	1572865,
	1572865,
	0);
INSERT INTO R_OIR
	VALUES (1572865,
	1572865,
	1572865,
	0);
INSERT INTO R_AOTH
	VALUES (3145732,
	1572865,
	1572866,
	1,
	0,
	'abstracts association between instances of');
INSERT INTO R_RTO
	VALUES (3145732,
	1572865,
	1572866,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	1572865,
	1572866,
	1572865);
INSERT INTO R_ASSR
	VALUES (1572879,
	1572865,
	1572867,
	1);
INSERT INTO R_RGO
	VALUES (1572879,
	1572865,
	1572867);
INSERT INTO R_OIR
	VALUES (1572879,
	1572865,
	1572867,
	0);
INSERT INTO R_SUBSUP
	VALUES (1572866);
INSERT INTO R_REL
	VALUES (1572866,
	206,
	'',
	1572867);
INSERT INTO R_SUPER
	VALUES (1572865,
	1572866,
	1572868);
INSERT INTO R_RTO
	VALUES (1572865,
	1572866,
	1572868,
	0);
INSERT INTO R_OIR
	VALUES (1572865,
	1572866,
	1572868,
	0);
INSERT INTO R_SUB
	VALUES (1572866,
	1572866,
	1572869);
INSERT INTO R_RGO
	VALUES (1572866,
	1572866,
	1572869);
INSERT INTO R_OIR
	VALUES (1572866,
	1572866,
	1572869,
	0);
INSERT INTO R_SUB
	VALUES (1572869,
	1572866,
	1572870);
INSERT INTO R_RGO
	VALUES (1572869,
	1572866,
	1572870);
INSERT INTO R_OIR
	VALUES (1572869,
	1572866,
	1572870,
	0);
INSERT INTO R_SUB
	VALUES (1572867,
	1572866,
	1572871);
INSERT INTO R_RGO
	VALUES (1572867,
	1572866,
	1572871);
INSERT INTO R_OIR
	VALUES (1572867,
	1572866,
	1572871,
	0);
INSERT INTO R_SUB
	VALUES (1572868,
	1572866,
	1572872);
INSERT INTO R_RGO
	VALUES (1572868,
	1572866,
	1572872);
INSERT INTO R_OIR
	VALUES (1572868,
	1572866,
	1572872,
	0);
INSERT INTO R_SIMP
	VALUES (1572867);
INSERT INTO R_REL
	VALUES (1572867,
	207,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572870,
	1572867,
	1572873,
	0,
	0,
	'relates');
INSERT INTO R_RGO
	VALUES (1572870,
	1572867,
	1572873);
INSERT INTO R_OIR
	VALUES (1572870,
	1572867,
	1572873,
	0);
INSERT INTO R_PART
	VALUES (1572866,
	1572867,
	1572874,
	0,
	0,
	'is related to formalizer via');
INSERT INTO R_RTO
	VALUES (1572866,
	1572867,
	1572874,
	0);
INSERT INTO R_OIR
	VALUES (1572866,
	1572867,
	1572874,
	0);
INSERT INTO R_SIMP
	VALUES (1572868);
INSERT INTO R_REL
	VALUES (1572868,
	208,
	'The conditionality towards R_FORM accounts for unformalized simple relationships in the analysis models. In BridgePoint V3.x, and unformalized simple relationship results in two instances of the Object As Simple Participant (R_PART), and zero instances of Object As Simple Formalizer. Archetypes should check the cardinality of R_FORM (verifying it is one) before navigating to R_PART.',
	1572867);
INSERT INTO R_FORM
	VALUES (1572871,
	1572868,
	1572875,
	0,
	1,
	'relates');
INSERT INTO R_RGO
	VALUES (1572871,
	1572868,
	1572875);
INSERT INTO R_OIR
	VALUES (1572871,
	1572868,
	1572875,
	0);
INSERT INTO R_PART
	VALUES (1572866,
	1572868,
	1572876,
	0,
	0,
	'is related to participant via');
INSERT INTO R_RTO
	VALUES (1572866,
	1572868,
	1572876,
	0);
INSERT INTO R_OIR
	VALUES (1572866,
	1572868,
	1572876,
	0);
INSERT INTO R_SIMP
	VALUES (1572869);
INSERT INTO R_REL
	VALUES (1572869,
	209,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572872,
	1572869,
	1572877,
	0,
	0,
	'relates');
INSERT INTO R_RGO
	VALUES (1572872,
	1572869,
	1572877);
INSERT INTO R_OIR
	VALUES (1572872,
	1572869,
	1572877,
	0);
INSERT INTO R_PART
	VALUES (1572867,
	1572869,
	1572878,
	0,
	0,
	'is related to other side via');
INSERT INTO R_RTO
	VALUES (1572867,
	1572869,
	1572878,
	0);
INSERT INTO R_OIR
	VALUES (1572867,
	1572869,
	1572878,
	0);
INSERT INTO R_SIMP
	VALUES (1572870);
INSERT INTO R_REL
	VALUES (1572870,
	210,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572873,
	1572870,
	1572879,
	0,
	0,
	'relates');
INSERT INTO R_RGO
	VALUES (1572873,
	1572870,
	1572879);
INSERT INTO R_OIR
	VALUES (1572873,
	1572870,
	1572879,
	0);
INSERT INTO R_PART
	VALUES (1572867,
	1572870,
	1572880,
	0,
	0,
	'is related to one side via');
INSERT INTO R_RTO
	VALUES (1572867,
	1572870,
	1572880,
	0);
INSERT INTO R_OIR
	VALUES (1572867,
	1572870,
	1572880,
	0);
INSERT INTO R_SIMP
	VALUES (1572871);
INSERT INTO R_REL
	VALUES (1572871,
	211,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572874,
	1572871,
	1572881,
	0,
	0,
	'uses a formalizer');
INSERT INTO R_RGO
	VALUES (1572874,
	1572871,
	1572881);
INSERT INTO R_OIR
	VALUES (1572874,
	1572871,
	1572881,
	0);
INSERT INTO R_PART
	VALUES (1572867,
	1572871,
	1572882,
	0,
	0,
	'formalizes relationship between associated objects');
INSERT INTO R_RTO
	VALUES (1572867,
	1572871,
	1572882,
	0);
INSERT INTO R_OIR
	VALUES (1572867,
	1572871,
	1572882,
	0);
INSERT INTO R_SIMP
	VALUES (1572872);
INSERT INTO R_REL
	VALUES (1572872,
	212,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572875,
	1572872,
	1572883,
	0,
	0,
	'relates');
INSERT INTO R_RGO
	VALUES (1572875,
	1572872,
	1572883);
INSERT INTO R_OIR
	VALUES (1572875,
	1572872,
	1572883,
	0);
INSERT INTO R_PART
	VALUES (1572868,
	1572872,
	1572884,
	0,
	0,
	'is related to subtypes via');
INSERT INTO R_RTO
	VALUES (1572868,
	1572872,
	1572884,
	0);
INSERT INTO R_OIR
	VALUES (1572868,
	1572872,
	1572884,
	0);
INSERT INTO R_SIMP
	VALUES (1572873);
INSERT INTO R_REL
	VALUES (1572873,
	213,
	'The conditionality towards Object As Subtype (R_SUB) represents that an analysis model may contain a supertype object that does not yet have any subtype objects entered on the OIM.',
	1572867);
INSERT INTO R_FORM
	VALUES (1572876,
	1572873,
	1572885,
	1,
	1,
	'relates');
INSERT INTO R_RGO
	VALUES (1572876,
	1572873,
	1572885);
INSERT INTO R_OIR
	VALUES (1572876,
	1572873,
	1572885,
	0);
INSERT INTO R_PART
	VALUES (1572868,
	1572873,
	1572886,
	0,
	0,
	'is related to supertype via');
INSERT INTO R_RTO
	VALUES (1572868,
	1572873,
	1572886,
	0);
INSERT INTO R_OIR
	VALUES (1572868,
	1572873,
	1572886,
	0);
INSERT INTO R_SIMP
	VALUES (1572874);
INSERT INTO R_REL
	VALUES (1572874,
	214,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572877,
	1572874,
	1572887,
	0,
	0,
	'relates');
INSERT INTO R_RGO
	VALUES (1572877,
	1572874,
	1572887);
INSERT INTO R_OIR
	VALUES (1572877,
	1572874,
	1572887,
	0);
INSERT INTO R_PART
	VALUES (1572869,
	1572874,
	1572888,
	0,
	0,
	'is related to other type via');
INSERT INTO R_RTO
	VALUES (1572869,
	1572874,
	1572888,
	0);
INSERT INTO R_OIR
	VALUES (1572869,
	1572874,
	1572888,
	0);
INSERT INTO R_SIMP
	VALUES (1572875);
INSERT INTO R_REL
	VALUES (1572875,
	215,
	'',
	1572867);
INSERT INTO R_FORM
	VALUES (1572878,
	1572875,
	1572889,
	0,
	0,
	'relates');
INSERT INTO R_RGO
	VALUES (1572878,
	1572875,
	1572889);
INSERT INTO R_OIR
	VALUES (1572878,
	1572875,
	1572889,
	0);
INSERT INTO R_PART
	VALUES (1572869,
	1572875,
	1572890,
	0,
	0,
	'is related to one side via');
INSERT INTO R_RTO
	VALUES (1572869,
	1572875,
	1572890,
	0);
INSERT INTO R_OIR
	VALUES (1572869,
	1572875,
	1572890,
	0);
INSERT INTO R_SUBSUP
	VALUES (1572876);
INSERT INTO R_REL
	VALUES (1572876,
	203,
	'',
	1572867);
INSERT INTO R_SUPER
	VALUES (1572879,
	1572876,
	1572891);
INSERT INTO R_RTO
	VALUES (1572879,
	1572876,
	1572891,
	0);
INSERT INTO R_OIR
	VALUES (1572879,
	1572876,
	1572891,
	0);
INSERT INTO R_SUB
	VALUES (1572880,
	1572876,
	1572892);
INSERT INTO R_RGO
	VALUES (1572880,
	1572876,
	1572892);
INSERT INTO R_OIR
	VALUES (1572880,
	1572876,
	1572892,
	0);
INSERT INTO R_SUB
	VALUES (1572881,
	1572876,
	1572893);
INSERT INTO R_RGO
	VALUES (1572881,
	1572876,
	1572893);
INSERT INTO R_OIR
	VALUES (1572881,
	1572876,
	1572893,
	0);
INSERT INTO R_SUB
	VALUES (1572877,
	1572876,
	1572894);
INSERT INTO R_RGO
	VALUES (1572877,
	1572876,
	1572894);
INSERT INTO R_OIR
	VALUES (1572877,
	1572876,
	1572894,
	0);
INSERT INTO R_SUB
	VALUES (1572878,
	1572876,
	1572895);
INSERT INTO R_RGO
	VALUES (1572878,
	1572876,
	1572895);
INSERT INTO R_OIR
	VALUES (1572878,
	1572876,
	1572895,
	0);
INSERT INTO R_SUBSUP
	VALUES (1572877);
INSERT INTO R_REL
	VALUES (1572877,
	205,
	'',
	1572867);
INSERT INTO R_SUPER
	VALUES (1572881,
	1572877,
	1572896);
INSERT INTO R_RTO
	VALUES (1572881,
	1572877,
	1572896,
	0);
INSERT INTO R_OIR
	VALUES (1572881,
	1572877,
	1572896,
	0);
INSERT INTO R_SUB
	VALUES (1572876,
	1572877,
	1572897);
INSERT INTO R_RGO
	VALUES (1572876,
	1572877,
	1572897);
INSERT INTO R_OIR
	VALUES (1572876,
	1572877,
	1572897,
	0);
INSERT INTO R_SUB
	VALUES (1572871,
	1572877,
	1572898);
INSERT INTO R_RGO
	VALUES (1572871,
	1572877,
	1572898);
INSERT INTO R_OIR
	VALUES (1572871,
	1572877,
	1572898,
	0);
INSERT INTO R_SUB
	VALUES (1572874,
	1572877,
	1572899);
INSERT INTO R_RGO
	VALUES (1572874,
	1572877,
	1572899);
INSERT INTO R_OIR
	VALUES (1572874,
	1572877,
	1572899,
	0);
INSERT INTO R_SUBSUP
	VALUES (1572878);
INSERT INTO R_REL
	VALUES (1572878,
	204,
	'',
	1572867);
INSERT INTO R_SUPER
	VALUES (1572880,
	1572878,
	1572900);
INSERT INTO R_RTO
	VALUES (1572880,
	1572878,
	1572900,
	0);
INSERT INTO R_OIR
	VALUES (1572880,
	1572878,
	1572900,
	0);
INSERT INTO R_SUB
	VALUES (1572875,
	1572878,
	1572901);
INSERT INTO R_RGO
	VALUES (1572875,
	1572878,
	1572901);
INSERT INTO R_OIR
	VALUES (1572875,
	1572878,
	1572901,
	0);
INSERT INTO R_SUB
	VALUES (1572870,
	1572878,
	1572902);
INSERT INTO R_RGO
	VALUES (1572870,
	1572878,
	1572902);
INSERT INTO R_OIR
	VALUES (1572870,
	1572878,
	1572902,
	0);
INSERT INTO R_SUB
	VALUES (1572872,
	1572878,
	1572903);
INSERT INTO R_RGO
	VALUES (1572872,
	1572878,
	1572903);
INSERT INTO R_OIR
	VALUES (1572872,
	1572878,
	1572903,
	0);
INSERT INTO R_SUB
	VALUES (1572873,
	1572878,
	1572904);
INSERT INTO R_RGO
	VALUES (1572873,
	1572878,
	1572904);
INSERT INTO R_OIR
	VALUES (1572873,
	1572878,
	1572904,
	0);
INSERT INTO R_SIMP
	VALUES (1572879);
INSERT INTO R_REL
	VALUES (1572879,
	202,
	'',
	1572867);
INSERT INTO R_PART
	VALUES (3145740,
	1572879,
	1572905,
	0,
	1,
	'may be represented by');
INSERT INTO R_RTO
	VALUES (3145740,
	1572879,
	1572905,
	0);
INSERT INTO R_OIR
	VALUES (3145740,
	1572879,
	1572905,
	1572866);
INSERT INTO R_FORM
	VALUES (1572879,
	1572879,
	1572906,
	1,
	1,
	'is used for spanning relationships as');
INSERT INTO R_RGO
	VALUES (1572879,
	1572879,
	1572906);
INSERT INTO R_OIR
	VALUES (1572879,
	1572879,
	1572906,
	0);
INSERT INTO S_SS
	VALUES (2097156,
	'Communication And Access',
	'

Notes:

',
	'CA',
	401,
	94514,
	2097156);
INSERT INTO O_OBJ
	VALUES (2097153,
	'Communication Path',
	401,
	'CA_COMM',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_NBATTR
	VALUES (2097153,
	2097153);
INSERT INTO O_BATTR
	VALUES (2097153,
	2097153);
INSERT INTO O_ATTR
	VALUES (2097153,
	2097153,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2097153,
	1048578,
	0,
	1048594,
	1048596,
	1048619,
	1048618,
	2097154,
	2097153,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097154,
	2097153,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (2097154,
	2097153,
	2097153,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097153);
INSERT INTO O_OIDA
	VALUES (2097153,
	2097153,
	0);
INSERT INTO O_RTIDA
	VALUES (2097153,
	2097153,
	0,
	2097153,
	2097153);
INSERT INTO O_OBJ
	VALUES (2097154,
	'EE to SM Comm Path',
	402,
	'CA_EESMC',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097154,
	2097153,
	0,
	2097153,
	2097153,
	2097154,
	2097153,
	2097155,
	2097154,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097155,
	2097154,
	2097153,
	2097153,
	1);
INSERT INTO O_ATTR
	VALUES (2097155,
	2097154,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097154,
	1048580,
	0,
	1048617,
	2097154,
	2097157,
	2097158,
	2097156,
	2097155,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097156,
	2097154,
	1048617,
	1048580,
	1);
INSERT INTO O_ATTR
	VALUES (2097156,
	2097154,
	2097155,
	'EEmod_ID',
	'',
	'',
	'EEmod_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097154,
	1048580,
	0,
	1048618,
	2097154,
	2097157,
	2097158,
	2097157,
	2097156,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097157,
	2097154,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (2097157,
	2097154,
	2097156,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097154,
	2621441,
	0,
	2621441,
	2097155,
	2097159,
	2097160,
	2097158,
	2097157,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097158,
	2097154,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097158,
	2097154,
	2097157,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097154);
INSERT INTO O_OIDA
	VALUES (2097155,
	2097154,
	0);
INSERT INTO O_RTIDA
	VALUES (2097155,
	2097154,
	0,
	2097156,
	2097161);
INSERT INTO O_ID
	VALUES (1,
	2097154);
INSERT INTO O_OIDA
	VALUES (2097158,
	2097154,
	1);
INSERT INTO O_OIDA
	VALUES (2097157,
	2097154,
	1);
INSERT INTO O_OBJ
	VALUES (2097155,
	'SM to SM Comm Path',
	403,
	'CA_SMSMC',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097155,
	2097153,
	0,
	2097153,
	2097153,
	2097156,
	2097153,
	2097159,
	2097158,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097159,
	2097155,
	2097153,
	2097153,
	1);
INSERT INTO O_ATTR
	VALUES (2097159,
	2097155,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097155,
	2621441,
	0,
	2621441,
	2097158,
	2097165,
	2097166,
	2097160,
	2097159,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097160,
	2097155,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097160,
	2097155,
	2097159,
	'OSM_ID',
	'',
	'O',
	'SM_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (2097155,
	2621441,
	0,
	2621441,
	2097159,
	2097167,
	2097168,
	2097161,
	2097160,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097161,
	2097155,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097161,
	2097155,
	2097160,
	'DSM_ID',
	'',
	'D',
	'SM_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (2097155,
	3145740,
	0,
	3145838,
	2097176,
	2097202,
	2097203,
	2097162,
	2097161,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2097162,
	2097155,
	3145838,
	3145740,
	1);
INSERT INTO O_ATTR
	VALUES (2097162,
	2097155,
	2097161,
	'OIObj_ID',
	'',
	'O',
	'IObj_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (2097155,
	3145740,
	0,
	3145838,
	2097166,
	2097182,
	2097181,
	2097163,
	2097183,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097163,
	2097155,
	3145838,
	3145740,
	1);
INSERT INTO O_ATTR
	VALUES (2097163,
	2097155,
	2097162,
	'DIObj_ID',
	'',
	'D',
	'IObj_ID',
	1,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097155);
INSERT INTO O_OIDA
	VALUES (2097159,
	2097155,
	0);
INSERT INTO O_RTIDA
	VALUES (2097159,
	2097155,
	0,
	2097160,
	2097169);
INSERT INTO O_ID
	VALUES (1,
	2097155);
INSERT INTO O_OIDA
	VALUES (2097161,
	2097155,
	1);
INSERT INTO O_OIDA
	VALUES (2097160,
	2097155,
	1);
INSERT INTO O_OBJ
	VALUES (2097156,
	'SM to EE Comm Path',
	404,
	'CA_SMEEC',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097156,
	2097153,
	0,
	2097153,
	2097153,
	2097155,
	2097153,
	2097164,
	2097162,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097164,
	2097156,
	2097153,
	2097153,
	1);
INSERT INTO O_ATTR
	VALUES (2097164,
	2097156,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097156,
	2621441,
	0,
	2621441,
	2097162,
	2097173,
	2097174,
	2097165,
	2097163,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097165,
	2097156,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097165,
	2097156,
	2097164,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097156,
	1048580,
	0,
	1048618,
	2097163,
	2097175,
	2097176,
	2097166,
	2097164,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097166,
	2097156,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (2097166,
	2097156,
	2097165,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097156,
	1048580,
	0,
	1048617,
	2097163,
	2097175,
	2097176,
	2097167,
	2097165,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097167,
	2097156,
	1048617,
	1048580,
	1);
INSERT INTO O_ATTR
	VALUES (2097167,
	2097156,
	2097166,
	'EEmod_ID',
	'',
	'',
	'EEmod_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097156);
INSERT INTO O_OIDA
	VALUES (2097164,
	2097156,
	0);
INSERT INTO O_RTIDA
	VALUES (2097164,
	2097156,
	0,
	2097164,
	2097177);
INSERT INTO O_ID
	VALUES (1,
	2097156);
INSERT INTO O_OIDA
	VALUES (2097165,
	2097156,
	1);
INSERT INTO O_OIDA
	VALUES (2097166,
	2097156,
	1);
INSERT INTO O_OBJ
	VALUES (2097157,
	'EE to SM Event Comm',
	405,
	'CA_EESME',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097157,
	2097154,
	0,
	2097155,
	2097156,
	2097162,
	2097161,
	2097168,
	2097184,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097168,
	2097157,
	2097153,
	2097153,
	1);
INSERT INTO O_ATTR
	VALUES (2097168,
	2097157,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097157,
	2621443,
	0,
	2621454,
	2097157,
	2097163,
	2097164,
	2097169,
	2097166,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097169,
	2097157,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097169,
	2097157,
	2097168,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097157,
	2621443,
	0,
	2621453,
	2097157,
	2097163,
	2097164,
	2097170,
	2097167,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097170,
	2097157,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2097170,
	2097157,
	2097169,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097157);
INSERT INTO O_OIDA
	VALUES (2097168,
	2097157,
	0);
INSERT INTO O_OIDA
	VALUES (2097170,
	2097157,
	0);
INSERT INTO O_OIDA
	VALUES (2097169,
	2097157,
	0);
INSERT INTO O_OBJ
	VALUES (2097158,
	'SM to SM Event Comm',
	406,
	'CA_SMSME',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097158,
	2097155,
	0,
	2097159,
	2097160,
	2097170,
	2097169,
	2097171,
	2097185,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097171,
	2097158,
	2097153,
	2097153,
	1);
INSERT INTO O_ATTR
	VALUES (2097171,
	2097158,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097158,
	2621443,
	0,
	2621454,
	2097161,
	2097171,
	2097172,
	2097172,
	2097168,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097172,
	2097158,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097172,
	2097158,
	2097171,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097158,
	2621443,
	0,
	2621453,
	2097161,
	2097171,
	2097172,
	2097173,
	2097169,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097173,
	2097158,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2097173,
	2097158,
	2097172,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097158);
INSERT INTO O_OIDA
	VALUES (2097171,
	2097158,
	0);
INSERT INTO O_OIDA
	VALUES (2097172,
	2097158,
	0);
INSERT INTO O_OIDA
	VALUES (2097173,
	2097158,
	0);
INSERT INTO O_OBJ
	VALUES (2097159,
	'SM to EE Event Comm',
	407,
	'CA_SMEEE',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097159,
	2097156,
	0,
	2097164,
	2097164,
	2097178,
	2097177,
	2097174,
	2097186,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097174,
	2097159,
	2097153,
	2097153,
	1);
INSERT INTO O_ATTR
	VALUES (2097174,
	2097159,
	0,
	'CPath_ID',
	'',
	'',
	'CPath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097159,
	1048582,
	0,
	1048627,
	2097165,
	2097179,
	2097180,
	2097175,
	2097170,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097175,
	2097159,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (2097175,
	2097159,
	2097174,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097159,
	1048582,
	0,
	1048626,
	2097165,
	2097179,
	2097180,
	2097176,
	2097171,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097176,
	2097159,
	1048626,
	1048582,
	1);
INSERT INTO O_ATTR
	VALUES (2097176,
	2097159,
	2097175,
	'EEevt_ID',
	'',
	'',
	'EEevt_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097159);
INSERT INTO O_OIDA
	VALUES (2097174,
	2097159,
	0);
INSERT INTO O_OIDA
	VALUES (2097176,
	2097159,
	0);
INSERT INTO O_OIDA
	VALUES (2097175,
	2097159,
	0);
INSERT INTO O_OBJ
	VALUES (2097160,
	'Access Path',
	408,
	'CA_ACC',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_NBATTR
	VALUES (2097177,
	2097160);
INSERT INTO O_BATTR
	VALUES (2097177,
	2097160);
INSERT INTO O_ATTR
	VALUES (2097177,
	2097160,
	0,
	'APath_ID',
	'Full Name: Access Path Identifier',
	'',
	'APath_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2097160,
	1048578,
	0,
	1048594,
	1048597,
	1048621,
	1048620,
	2097178,
	2097172,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097178,
	2097160,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (2097178,
	2097160,
	2097177,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097160,
	2621441,
	0,
	2621441,
	2097168,
	2097186,
	2097187,
	2097179,
	2097173,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097179,
	2097160,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2097179,
	2097160,
	2097178,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097160,
	3145740,
	0,
	3145838,
	2097177,
	2097205,
	2097204,
	2097180,
	2097187,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2097180,
	2097160,
	3145838,
	3145740,
	1);
INSERT INTO O_ATTR
	VALUES (2097180,
	2097160,
	2097179,
	'IObj_ID',
	'',
	'',
	'IObj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097160);
INSERT INTO O_OIDA
	VALUES (2097177,
	2097160,
	0);
INSERT INTO O_RTIDA
	VALUES (2097177,
	2097160,
	0,
	2097167,
	2097183);
INSERT INTO O_OBJ
	VALUES (2097161,
	'SM to OBJ Access Path',
	409,
	'CA_SMOA',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097161,
	2097160,
	0,
	2097177,
	2097167,
	2097184,
	2097183,
	2097181,
	2097174,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097181,
	2097161,
	2097177,
	2097160,
	1);
INSERT INTO O_ATTR
	VALUES (2097181,
	2097161,
	0,
	'APath_ID',
	'',
	'',
	'APath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097161,
	3145732,
	0,
	3145773,
	2097169,
	2097188,
	2097189,
	2097182,
	2097175,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097182,
	2097161,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (2097182,
	2097161,
	2097181,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097161,
	3145740,
	0,
	3145838,
	2097172,
	2097195,
	2097194,
	2097183,
	2097188,
	0,
	1,
	'SM to OBJ Access Path (CA_SMOA).IObj_ID must be constrained such that Imported Object (O_IOBJ).Obj_ID is the same as (CA_SMOA).IObj_ID. That is, the Imported Object instance that the SM to OBJ Access Path instance is related to by R420 , if any, must be the one representing the Object (O_OBJ) instance it is related to by R417.');
INSERT INTO O_RATTR
	VALUES (2097183,
	2097161,
	3145838,
	3145740,
	1);
INSERT INTO O_ATTR
	VALUES (2097183,
	2097161,
	2097182,
	'IObj_ID',
	'',
	'',
	'IObj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097161);
INSERT INTO O_OIDA
	VALUES (2097181,
	2097161,
	0);
INSERT INTO O_ID
	VALUES (1,
	2097161);
INSERT INTO O_OIDA
	VALUES (2097182,
	2097161,
	1);
INSERT INTO O_RTIDA
	VALUES (2097182,
	2097161,
	1,
	2097170,
	2097190);
INSERT INTO O_OIDA
	VALUES (2097181,
	2097161,
	1);
INSERT INTO O_RTIDA
	VALUES (2097181,
	2097161,
	1,
	2097170,
	2097190);
INSERT INTO O_OBJ
	VALUES (2097162,
	'SM to EE Access Path',
	410,
	'CA_SMEEA',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097162,
	2097160,
	0,
	2097177,
	2097167,
	2097185,
	2097183,
	2097184,
	2097176,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097184,
	2097162,
	2097177,
	2097160,
	1);
INSERT INTO O_ATTR
	VALUES (2097184,
	2097162,
	0,
	'APath_ID',
	'

Domain:


Notes:

',
	'',
	'APath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097162,
	1048580,
	0,
	1048618,
	2097173,
	2097196,
	2097197,
	2097185,
	2097177,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097185,
	2097162,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (2097185,
	2097162,
	2097184,
	'EE_ID',
	'

Domain:


Notes:

',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097162,
	1048580,
	0,
	1048617,
	2097173,
	2097196,
	2097197,
	2097186,
	2097178,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097186,
	2097162,
	1048617,
	1048580,
	1);
INSERT INTO O_ATTR
	VALUES (2097186,
	2097162,
	2097185,
	'EEmod_ID',
	'

Domain:


Notes:

',
	'',
	'EEmod_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097162);
INSERT INTO O_OIDA
	VALUES (2097184,
	2097162,
	0);
INSERT INTO O_ID
	VALUES (1,
	2097162);
INSERT INTO O_OIDA
	VALUES (2097185,
	2097162,
	1);
INSERT INTO O_RTIDA
	VALUES (2097185,
	2097162,
	1,
	2097174,
	2097198);
INSERT INTO O_OIDA
	VALUES (2097184,
	2097162,
	1);
INSERT INTO O_RTIDA
	VALUES (2097184,
	2097162,
	1,
	2097174,
	2097198);
INSERT INTO O_OBJ
	VALUES (2097163,
	'SM to OBJ Attribute Access',
	411,
	'CA_SMOAA',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097163,
	2097161,
	1,
	2097181,
	2097170,
	2097191,
	2097190,
	2097187,
	2097189,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2097187,
	2097163,
	2097177,
	2097160,
	1);
INSERT INTO O_ATTR
	VALUES (2097187,
	2097163,
	0,
	'APath_ID',
	'',
	'',
	'APath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097163,
	3145731,
	0,
	3145758,
	2097171,
	2097192,
	2097193,
	2097188,
	2097179,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097188,
	2097163,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (2097188,
	2097163,
	2097187,
	'Attr_ID',
	'

Domain:


Notes:

',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097163,
	3145731,
	0,
	3145759,
	2097171,
	2097192,
	2097193,
	2097189,
	2097180,
	0,
	0,
	'

Notes:

');
INSERT INTO O_REF
	VALUES (2097163,
	2097161,
	1,
	2097182,
	2097170,
	2097191,
	2097190,
	2097189,
	2097190,
	2097180,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2097189,
	2097163,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (2097189,
	2097163,
	2097188,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097163);
INSERT INTO O_OIDA
	VALUES (2097189,
	2097163,
	0);
INSERT INTO O_OIDA
	VALUES (2097187,
	2097163,
	0);
INSERT INTO O_OIDA
	VALUES (2097188,
	2097163,
	0);
INSERT INTO O_OBJ
	VALUES (2097164,
	'SM to EE Data Item Access',
	412,
	'CA_SMEED',
	'

Restrictions applied to Object:

Notes:
',
	2097156);
INSERT INTO O_REF
	VALUES (2097164,
	2097162,
	1,
	2097184,
	2097174,
	2097199,
	2097198,
	2097190,
	2097191,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2097190,
	2097164,
	2097177,
	2097160,
	1);
INSERT INTO O_ATTR
	VALUES (2097190,
	2097164,
	0,
	'APath_ID',
	'',
	'',
	'APath_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097164,
	1048581,
	0,
	1048621,
	2097175,
	2097200,
	2097201,
	2097191,
	2097181,
	0,
	0,
	'

Notes:

');
INSERT INTO O_RATTR
	VALUES (2097191,
	2097164,
	1048621,
	1048581,
	1);
INSERT INTO O_ATTR
	VALUES (2097191,
	2097164,
	2097190,
	'EEdi_ID',
	'

Domain:


Notes:

',
	'',
	'EEdi_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2097164,
	1048581,
	0,
	1048622,
	2097175,
	2097200,
	2097201,
	2097192,
	2097182,
	0,
	0,
	'

Notes:

');
INSERT INTO O_REF
	VALUES (2097164,
	2097162,
	1,
	2097185,
	2097174,
	2097199,
	2097198,
	2097192,
	2097192,
	2097182,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2097192,
	2097164,
	1048603,
	1048579,
	1);
INSERT INTO O_ATTR
	VALUES (2097192,
	2097164,
	2097191,
	'EE_ID',
	'',
	'',
	'EE_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2097164);
INSERT INTO O_OIDA
	VALUES (2097190,
	2097164,
	0);
INSERT INTO O_OIDA
	VALUES (2097192,
	2097164,
	0);
INSERT INTO O_OIDA
	VALUES (2097191,
	2097164,
	0);
INSERT INTO O_IOBJ
	VALUES (2097153,
	1048580,
	5,
	2097156,
	'External Entity in Model',
	'S_EEM');
INSERT INTO O_IOBJ
	VALUES (2097154,
	1048580,
	5,
	2097156,
	'External Entity in Model',
	'S_EEM');
INSERT INTO O_IOBJ
	VALUES (2097155,
	1048581,
	5,
	2097156,
	'External Entity Data Item',
	'S_EEDI');
INSERT INTO O_IOBJ
	VALUES (2097156,
	1048582,
	5,
	2097156,
	'External Entity Event',
	'S_EEEVT');
INSERT INTO O_IOBJ
	VALUES (2097157,
	2621441,
	5,
	2097156,
	'State Model',
	'SM_SM');
INSERT INTO O_IOBJ
	VALUES (2097158,
	2621443,
	5,
	2097156,
	'State Model Event',
	'SM_EVT');
INSERT INTO O_IOBJ
	VALUES (2097159,
	3145731,
	5,
	2097156,
	'Attribute',
	'O_ATTR');
INSERT INTO O_IOBJ
	VALUES (2097160,
	3145732,
	5,
	2097156,
	'Class',
	'O_OBJ');
INSERT INTO O_IOBJ
	VALUES (2097161,
	3145740,
	5,
	2097156,
	'Imported Class',
	'O_IOBJ');
INSERT INTO R_SUBSUP
	VALUES (2097153);
INSERT INTO R_REL
	VALUES (2097153,
	401,
	'

Notes:

',
	2097156);
INSERT INTO R_SUPER
	VALUES (2097153,
	2097153,
	2097153);
INSERT INTO R_RTO
	VALUES (2097153,
	2097153,
	2097153,
	0);
INSERT INTO R_OIR
	VALUES (2097153,
	2097153,
	2097153,
	0);
INSERT INTO R_SUB
	VALUES (2097154,
	2097153,
	2097154);
INSERT INTO R_RGO
	VALUES (2097154,
	2097153,
	2097154);
INSERT INTO R_OIR
	VALUES (2097154,
	2097153,
	2097154,
	0);
INSERT INTO R_SUB
	VALUES (2097156,
	2097153,
	2097155);
INSERT INTO R_RGO
	VALUES (2097156,
	2097153,
	2097155);
INSERT INTO R_OIR
	VALUES (2097156,
	2097153,
	2097155,
	0);
INSERT INTO R_SUB
	VALUES (2097155,
	2097153,
	2097156);
INSERT INTO R_RGO
	VALUES (2097155,
	2097153,
	2097156);
INSERT INTO R_OIR
	VALUES (2097155,
	2097153,
	2097156,
	0);
INSERT INTO R_SIMP
	VALUES (2097154);
INSERT INTO R_REL
	VALUES (2097154,
	402,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097154,
	2097154,
	2097157,
	1,
	1,
	'originates');
INSERT INTO R_RGO
	VALUES (2097154,
	2097154,
	2097157);
INSERT INTO R_OIR
	VALUES (2097154,
	2097154,
	2097157,
	0);
INSERT INTO R_PART
	VALUES (1048580,
	2097154,
	2097158,
	0,
	0,
	'originates from');
INSERT INTO R_RTO
	VALUES (1048580,
	2097154,
	2097158,
	0);
INSERT INTO R_OIR
	VALUES (1048580,
	2097154,
	2097158,
	2097153);
INSERT INTO R_SIMP
	VALUES (2097155);
INSERT INTO R_REL
	VALUES (2097155,
	403,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097154,
	2097155,
	2097159,
	1,
	1,
	'has received event communication represented by');
INSERT INTO R_RGO
	VALUES (2097154,
	2097155,
	2097159);
INSERT INTO R_OIR
	VALUES (2097154,
	2097155,
	2097159,
	0);
INSERT INTO R_PART
	VALUES (2621441,
	2097155,
	2097160,
	0,
	0,
	'shows event communication to');
INSERT INTO R_RTO
	VALUES (2621441,
	2097155,
	2097160,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2097155,
	2097160,
	2097157);
INSERT INTO R_SIMP
	VALUES (2097156);
INSERT INTO R_REL
	VALUES (2097156,
	404,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (2097154,
	2097156,
	2097161,
	0,
	0,
	'is carried by');
INSERT INTO R_RTO
	VALUES (2097154,
	2097156,
	2097161,
	0);
INSERT INTO R_OIR
	VALUES (2097154,
	2097156,
	2097161,
	0);
INSERT INTO R_FORM
	VALUES (2097157,
	2097156,
	2097162,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (2097157,
	2097156,
	2097162);
INSERT INTO R_OIR
	VALUES (2097157,
	2097156,
	2097162,
	0);
INSERT INTO R_SIMP
	VALUES (2097157);
INSERT INTO R_REL
	VALUES (2097157,
	405,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097157,
	2097157,
	2097163,
	1,
	1,
	'is carried in other SMs via');
INSERT INTO R_RGO
	VALUES (2097157,
	2097157,
	2097163);
INSERT INTO R_OIR
	VALUES (2097157,
	2097157,
	2097163,
	0);
INSERT INTO R_PART
	VALUES (2621443,
	2097157,
	2097164,
	0,
	0,
	'represents communication of');
INSERT INTO R_RTO
	VALUES (2621443,
	2097157,
	2097164,
	0);
INSERT INTO R_OIR
	VALUES (2621443,
	2097157,
	2097164,
	2097158);
INSERT INTO R_SIMP
	VALUES (2097158);
INSERT INTO R_REL
	VALUES (2097158,
	406,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097155,
	2097158,
	2097165,
	1,
	1,
	'originates');
INSERT INTO R_RGO
	VALUES (2097155,
	2097158,
	2097165);
INSERT INTO R_OIR
	VALUES (2097155,
	2097158,
	2097165,
	0);
INSERT INTO R_PART
	VALUES (2621441,
	2097158,
	2097166,
	0,
	0,
	'originates from');
INSERT INTO R_RTO
	VALUES (2621441,
	2097158,
	2097166,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2097158,
	2097166,
	2097157);
INSERT INTO R_SIMP
	VALUES (2097159);
INSERT INTO R_REL
	VALUES (2097159,
	407,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097155,
	2097159,
	2097167,
	1,
	1,
	'has received event communication represented by');
INSERT INTO R_RGO
	VALUES (2097155,
	2097159,
	2097167);
INSERT INTO R_OIR
	VALUES (2097155,
	2097159,
	2097167,
	0);
INSERT INTO R_PART
	VALUES (2621441,
	2097159,
	2097168,
	0,
	0,
	'shows event communication to');
INSERT INTO R_RTO
	VALUES (2621441,
	2097159,
	2097168,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2097159,
	2097168,
	2097157);
INSERT INTO R_SIMP
	VALUES (2097160);
INSERT INTO R_REL
	VALUES (2097160,
	408,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (2097155,
	2097160,
	2097169,
	0,
	0,
	'is carried by');
INSERT INTO R_RTO
	VALUES (2097155,
	2097160,
	2097169,
	0);
INSERT INTO R_OIR
	VALUES (2097155,
	2097160,
	2097169,
	0);
INSERT INTO R_FORM
	VALUES (2097158,
	2097160,
	2097170,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (2097158,
	2097160,
	2097170);
INSERT INTO R_OIR
	VALUES (2097158,
	2097160,
	2097170,
	0);
INSERT INTO R_SIMP
	VALUES (2097161);
INSERT INTO R_REL
	VALUES (2097161,
	409,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097158,
	2097161,
	2097171,
	1,
	1,
	'is carried to other SMs via');
INSERT INTO R_RGO
	VALUES (2097158,
	2097161,
	2097171);
INSERT INTO R_OIR
	VALUES (2097158,
	2097161,
	2097171,
	0);
INSERT INTO R_PART
	VALUES (2621443,
	2097161,
	2097172,
	0,
	0,
	'represents communication of');
INSERT INTO R_RTO
	VALUES (2621443,
	2097161,
	2097172,
	0);
INSERT INTO R_OIR
	VALUES (2621443,
	2097161,
	2097172,
	2097158);
INSERT INTO R_SIMP
	VALUES (2097162);
INSERT INTO R_REL
	VALUES (2097162,
	410,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097156,
	2097162,
	2097173,
	1,
	1,
	'originates');
INSERT INTO R_RGO
	VALUES (2097156,
	2097162,
	2097173);
INSERT INTO R_OIR
	VALUES (2097156,
	2097162,
	2097173,
	0);
INSERT INTO R_PART
	VALUES (2621441,
	2097162,
	2097174,
	0,
	0,
	'originates from');
INSERT INTO R_RTO
	VALUES (2621441,
	2097162,
	2097174,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2097162,
	2097174,
	2097157);
INSERT INTO R_SIMP
	VALUES (2097163);
INSERT INTO R_REL
	VALUES (2097163,
	411,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097156,
	2097163,
	2097175,
	1,
	1,
	'has receive event communications represented by');
INSERT INTO R_RGO
	VALUES (2097156,
	2097163,
	2097175);
INSERT INTO R_OIR
	VALUES (2097156,
	2097163,
	2097175,
	0);
INSERT INTO R_PART
	VALUES (1048580,
	2097163,
	2097176,
	0,
	0,
	'shows event communication to');
INSERT INTO R_RTO
	VALUES (1048580,
	2097163,
	2097176,
	0);
INSERT INTO R_OIR
	VALUES (1048580,
	2097163,
	2097176,
	2097153);
INSERT INTO R_SIMP
	VALUES (2097164);
INSERT INTO R_REL
	VALUES (2097164,
	412,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (2097156,
	2097164,
	2097177,
	0,
	0,
	'is carried by');
INSERT INTO R_RTO
	VALUES (2097156,
	2097164,
	2097177,
	0);
INSERT INTO R_OIR
	VALUES (2097156,
	2097164,
	2097177,
	0);
INSERT INTO R_FORM
	VALUES (2097159,
	2097164,
	2097178,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (2097159,
	2097164,
	2097178);
INSERT INTO R_OIR
	VALUES (2097159,
	2097164,
	2097178,
	0);
INSERT INTO R_SIMP
	VALUES (2097165);
INSERT INTO R_REL
	VALUES (2097165,
	413,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097159,
	2097165,
	2097179,
	1,
	1,
	'is carried to EE via');
INSERT INTO R_RGO
	VALUES (2097159,
	2097165,
	2097179);
INSERT INTO R_OIR
	VALUES (2097159,
	2097165,
	2097179,
	0);
INSERT INTO R_PART
	VALUES (1048582,
	2097165,
	2097180,
	0,
	0,
	'represents communication of');
INSERT INTO R_RTO
	VALUES (1048582,
	2097165,
	2097180,
	0);
INSERT INTO R_OIR
	VALUES (1048582,
	2097165,
	2097180,
	2097156);
INSERT INTO R_SIMP
	VALUES (2097166);
INSERT INTO R_REL
	VALUES (2097166,
	414,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (3145740,
	2097166,
	2097181,
	0,
	1,
	'destination SM can be represented by');
INSERT INTO R_RTO
	VALUES (3145740,
	2097166,
	2097181,
	0);
INSERT INTO R_OIR
	VALUES (3145740,
	2097166,
	2097181,
	2097161);
INSERT INTO R_FORM
	VALUES (2097155,
	2097166,
	2097182,
	1,
	1,
	'represents the destination SM for');
INSERT INTO R_RGO
	VALUES (2097155,
	2097166,
	2097182);
INSERT INTO R_OIR
	VALUES (2097155,
	2097166,
	2097182,
	0);
INSERT INTO R_SUBSUP
	VALUES (2097167);
INSERT INTO R_REL
	VALUES (2097167,
	415,
	'

Notes:

',
	2097156);
INSERT INTO R_SUPER
	VALUES (2097160,
	2097167,
	2097183);
INSERT INTO R_RTO
	VALUES (2097160,
	2097167,
	2097183,
	0);
INSERT INTO R_OIR
	VALUES (2097160,
	2097167,
	2097183,
	0);
INSERT INTO R_SUB
	VALUES (2097161,
	2097167,
	2097184);
INSERT INTO R_RGO
	VALUES (2097161,
	2097167,
	2097184);
INSERT INTO R_OIR
	VALUES (2097161,
	2097167,
	2097184,
	0);
INSERT INTO R_SUB
	VALUES (2097162,
	2097167,
	2097185);
INSERT INTO R_RGO
	VALUES (2097162,
	2097167,
	2097185);
INSERT INTO R_OIR
	VALUES (2097162,
	2097167,
	2097185,
	0);
INSERT INTO R_SIMP
	VALUES (2097168);
INSERT INTO R_REL
	VALUES (2097168,
	416,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097160,
	2097168,
	2097186,
	1,
	1,
	'originates');
INSERT INTO R_RGO
	VALUES (2097160,
	2097168,
	2097186);
INSERT INTO R_OIR
	VALUES (2097160,
	2097168,
	2097186,
	0);
INSERT INTO R_PART
	VALUES (2621441,
	2097168,
	2097187,
	0,
	0,
	'originates from');
INSERT INTO R_RTO
	VALUES (2621441,
	2097168,
	2097187,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2097168,
	2097187,
	2097157);
INSERT INTO R_SIMP
	VALUES (2097169);
INSERT INTO R_REL
	VALUES (2097169,
	417,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097161,
	2097169,
	2097188,
	1,
	1,
	'has data access represented by');
INSERT INTO R_RGO
	VALUES (2097161,
	2097169,
	2097188);
INSERT INTO R_OIR
	VALUES (2097161,
	2097169,
	2097188,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	2097169,
	2097189,
	0,
	0,
	'shows accesses of data from');
INSERT INTO R_RTO
	VALUES (3145732,
	2097169,
	2097189,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	2097169,
	2097189,
	2097160);
INSERT INTO R_SIMP
	VALUES (2097170);
INSERT INTO R_REL
	VALUES (2097170,
	418,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (2097161,
	2097170,
	2097190,
	0,
	0,
	'is carried by ');
INSERT INTO R_RTO
	VALUES (2097161,
	2097170,
	2097190,
	1);
INSERT INTO R_OIR
	VALUES (2097161,
	2097170,
	2097190,
	0);
INSERT INTO R_FORM
	VALUES (2097163,
	2097170,
	2097191,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (2097163,
	2097170,
	2097191);
INSERT INTO R_OIR
	VALUES (2097163,
	2097170,
	2097191,
	0);
INSERT INTO R_SIMP
	VALUES (2097171);
INSERT INTO R_REL
	VALUES (2097171,
	419,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097163,
	2097171,
	2097192,
	1,
	1,
	'is accessed by');
INSERT INTO R_RGO
	VALUES (2097163,
	2097171,
	2097192);
INSERT INTO R_OIR
	VALUES (2097163,
	2097171,
	2097192,
	0);
INSERT INTO R_PART
	VALUES (3145731,
	2097171,
	2097193,
	0,
	0,
	'represents access of');
INSERT INTO R_RTO
	VALUES (3145731,
	2097171,
	2097193,
	0);
INSERT INTO R_OIR
	VALUES (3145731,
	2097171,
	2097193,
	2097159);
INSERT INTO R_SIMP
	VALUES (2097172);
INSERT INTO R_REL
	VALUES (2097172,
	420,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (3145740,
	2097172,
	2097194,
	0,
	1,
	'destination OBJ can be represented by');
INSERT INTO R_RTO
	VALUES (3145740,
	2097172,
	2097194,
	0);
INSERT INTO R_OIR
	VALUES (3145740,
	2097172,
	2097194,
	2097161);
INSERT INTO R_FORM
	VALUES (2097161,
	2097172,
	2097195,
	1,
	1,
	'represents the destination OBJ for');
INSERT INTO R_RGO
	VALUES (2097161,
	2097172,
	2097195);
INSERT INTO R_OIR
	VALUES (2097161,
	2097172,
	2097195,
	0);
INSERT INTO R_SIMP
	VALUES (2097173);
INSERT INTO R_REL
	VALUES (2097173,
	421,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097162,
	2097173,
	2097196,
	1,
	1,
	'has data access represented by');
INSERT INTO R_RGO
	VALUES (2097162,
	2097173,
	2097196);
INSERT INTO R_OIR
	VALUES (2097162,
	2097173,
	2097196,
	0);
INSERT INTO R_PART
	VALUES (1048580,
	2097173,
	2097197,
	0,
	0,
	'accesses data of');
INSERT INTO R_RTO
	VALUES (1048580,
	2097173,
	2097197,
	0);
INSERT INTO R_OIR
	VALUES (1048580,
	2097173,
	2097197,
	2097154);
INSERT INTO R_SIMP
	VALUES (2097174);
INSERT INTO R_REL
	VALUES (2097174,
	422,
	'

Notes:

',
	2097156);
INSERT INTO R_PART
	VALUES (2097162,
	2097174,
	2097198,
	0,
	0,
	'is carried by');
INSERT INTO R_RTO
	VALUES (2097162,
	2097174,
	2097198,
	1);
INSERT INTO R_OIR
	VALUES (2097162,
	2097174,
	2097198,
	0);
INSERT INTO R_FORM
	VALUES (2097164,
	2097174,
	2097199,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (2097164,
	2097174,
	2097199);
INSERT INTO R_OIR
	VALUES (2097164,
	2097174,
	2097199,
	0);
INSERT INTO R_SIMP
	VALUES (2097175);
INSERT INTO R_REL
	VALUES (2097175,
	423,
	'

Notes:

',
	2097156);
INSERT INTO R_FORM
	VALUES (2097164,
	2097175,
	2097200,
	1,
	1,
	'is accessed by');
INSERT INTO R_RGO
	VALUES (2097164,
	2097175,
	2097200);
INSERT INTO R_OIR
	VALUES (2097164,
	2097175,
	2097200,
	0);
INSERT INTO R_PART
	VALUES (1048581,
	2097175,
	2097201,
	0,
	0,
	'represents access of');
INSERT INTO R_RTO
	VALUES (1048581,
	2097175,
	2097201,
	0);
INSERT INTO R_OIR
	VALUES (1048581,
	2097175,
	2097201,
	2097155);
INSERT INTO R_SIMP
	VALUES (2097176);
INSERT INTO R_REL
	VALUES (2097176,
	424,
	'',
	2097156);
INSERT INTO R_FORM
	VALUES (2097155,
	2097176,
	2097202,
	1,
	1,
	'represents the origination SM for');
INSERT INTO R_RGO
	VALUES (2097155,
	2097176,
	2097202);
INSERT INTO R_OIR
	VALUES (2097155,
	2097176,
	2097202,
	0);
INSERT INTO R_PART
	VALUES (3145740,
	2097176,
	2097203,
	0,
	1,
	'origination SM can be represented by');
INSERT INTO R_RTO
	VALUES (3145740,
	2097176,
	2097203,
	0);
INSERT INTO R_OIR
	VALUES (3145740,
	2097176,
	2097203,
	2097161);
INSERT INTO R_SIMP
	VALUES (2097177);
INSERT INTO R_REL
	VALUES (2097177,
	425,
	'',
	2097156);
INSERT INTO R_PART
	VALUES (3145740,
	2097177,
	2097204,
	0,
	1,
	'origination OBJ can be represented by');
INSERT INTO R_RTO
	VALUES (3145740,
	2097177,
	2097204,
	0);
INSERT INTO R_OIR
	VALUES (3145740,
	2097177,
	2097204,
	2097161);
INSERT INTO R_FORM
	VALUES (2097160,
	2097177,
	2097205,
	1,
	1,
	'represents origination OBJ for');
INSERT INTO R_RGO
	VALUES (2097160,
	2097177,
	2097205);
INSERT INTO R_OIR
	VALUES (2097160,
	2097177,
	2097205,
	0);
INSERT INTO S_SS
	VALUES (2621445,
	'State Model',
	'

Notes:

',
	'SM',
	501,
	94514,
	2621445);
INSERT INTO O_OBJ
	VALUES (2621441,
	'State Model',
	501,
	'SM_SM',
	'',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621441,
	2621441);
INSERT INTO O_BATTR
	VALUES (2621441,
	2621441);
INSERT INTO O_ATTR
	VALUES (2621441,
	2621441,
	0,
	'SM_ID',
	'Full Name: State Model Identifier',
	'',
	'SM_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (2621442,
	2621441);
INSERT INTO O_BATTR
	VALUES (2621442,
	2621441);
INSERT INTO O_ATTR
	VALUES (2621442,
	2621441,
	2621441,
	'Descrip',
	'Full Name: State Model Description',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621443,
	2621441);
INSERT INTO O_BATTR
	VALUES (2621443,
	2621441);
INSERT INTO O_ATTR
	VALUES (2621443,
	2621441,
	2621442,
	'Config_ID',
	'Full Name: Configuration Identifier

The Configuration ID of the version management configuration which this state model is part of (refer to Version Management subsystem). This ID can be used to access the V_CONFIG record corresponding to the State Model/Action Configuration.',
	'',
	'Config_ID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621444,
	2621441);
INSERT INTO O_BATTR
	VALUES (2621444,
	2621441);
INSERT INTO O_ATTR
	VALUES (2621444,
	2621441,
	2621443,
	'SelfEventCountValid',
	'A flag to indicate if pre-processing to determine if the maximum number of self directed events in this state model have been calculated. If TRUE, pre-processing has been done, and the ''MaxSelfEvents'' attribute of the state model subtype is valid. If FALSE, pre-processing of self directed events has not been done.',
	'',
	'SelfEventCountValid',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621445,
	2621441);
INSERT INTO O_BATTR
	VALUES (2621445,
	2621441);
INSERT INTO O_ATTR
	VALUES (2621445,
	2621441,
	2621444,
	'PersistentCurrentState',
	'A flag to indicate to the translation engine that the State Models current state should be preserved across system invocations.',
	'',
	'PersistentCurrentState',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	2621441);
INSERT INTO O_OIDA
	VALUES (2621441,
	2621441,
	0);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2097155,
	2097160);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621452,
	2621469);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621460,
	2621488);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621454,
	2621473);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621453,
	2621471);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2097168,
	2097187);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621441,
	2621441);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2097162,
	2097174);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621442,
	2621443);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621443,
	2621445);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2097158,
	2097166);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2621447,
	2621455);
INSERT INTO O_RTIDA
	VALUES (2621441,
	2621441,
	0,
	2097159,
	2097168);
INSERT INTO O_OBJ
	VALUES (2621442,
	'State Model State',
	502,
	'SM_STATE',
	'A State Model State abstracts a state of a state model.',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621446,
	2621442);
INSERT INTO O_BATTR
	VALUES (2621446,
	2621442);
INSERT INTO O_ATTR
	VALUES (2621446,
	2621442,
	0,
	'SMstt_ID',
	'Full Name: State Model State Identifier',
	'',
	'SMstt_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2621442,
	2621441,
	0,
	2621441,
	2621441,
	2621442,
	2621441,
	2621447,
	2621465,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621442,
	2621457,
	0,
	2621538,
	2621458,
	2621482,
	2621483,
	2621447,
	2621466,
	2621465,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621447,
	2621442,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621447,
	2621442,
	2621446,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621442,
	2621457,
	0,
	2621537,
	2621458,
	2621482,
	2621483,
	2621448,
	2621467,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621448,
	2621442,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621448,
	2621442,
	2621447,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621449,
	2621442);
INSERT INTO O_BATTR
	VALUES (2621449,
	2621442);
INSERT INTO O_ATTR
	VALUES (2621449,
	2621442,
	2621448,
	'Name',
	'Full Name: State Name',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621450,
	2621442);
INSERT INTO O_BATTR
	VALUES (2621450,
	2621442);
INSERT INTO O_ATTR
	VALUES (2621450,
	2621442,
	2621449,
	'Numb',
	'Full Name: State Number',
	'',
	'Numb',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621451,
	2621442);
INSERT INTO O_BATTR
	VALUES (2621451,
	2621442);
INSERT INTO O_ATTR
	VALUES (2621451,
	2621442,
	2621450,
	'Final',
	'Full Name: Is Deletion Final State

Indicates if this state is a deletion inal state.
0 = Not Deletion Final State
1 = Deletion Final State',
	'',
	'Final',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621452,
	2621442);
INSERT INTO O_BATTR
	VALUES (2621452,
	2621442);
INSERT INTO O_ATTR
	VALUES (2621452,
	2621442,
	2621451,
	'Order',
	'A utlity attribute for the archetypes to specify a particular order of the State Model States.
This attribute is a "work around" until the archetype language supports an "ORDERED BY" clause.',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	2621442);
INSERT INTO O_OIDA
	VALUES (2621447,
	2621442,
	0);
INSERT INTO O_RTIDA
	VALUES (2621447,
	2621442,
	0,
	2621467,
	2621505);
INSERT INTO O_RTIDA
	VALUES (2621447,
	2621442,
	0,
	2621446,
	2621453);
INSERT INTO O_RTIDA
	VALUES (2621447,
	2621442,
	0,
	2621448,
	2621459);
INSERT INTO O_OIDA
	VALUES (2621446,
	2621442,
	0);
INSERT INTO O_RTIDA
	VALUES (2621446,
	2621442,
	0,
	2621467,
	2621505);
INSERT INTO O_RTIDA
	VALUES (2621446,
	2621442,
	0,
	2621448,
	2621459);
INSERT INTO O_RTIDA
	VALUES (2621446,
	2621442,
	0,
	2621446,
	2621453);
INSERT INTO O_ID
	VALUES (1,
	2621442);
INSERT INTO O_OIDA
	VALUES (2621447,
	2621442,
	1);
INSERT INTO O_RTIDA
	VALUES (2621447,
	2621442,
	1,
	2621444,
	2621447);
INSERT INTO O_OIDA
	VALUES (2621446,
	2621442,
	1);
INSERT INTO O_RTIDA
	VALUES (2621446,
	2621442,
	1,
	2621444,
	2621447);
INSERT INTO O_OIDA
	VALUES (2621448,
	2621442,
	1);
INSERT INTO O_RTIDA
	VALUES (2621448,
	2621442,
	1,
	2621444,
	2621447);
INSERT INTO O_OBJ
	VALUES (2621443,
	'State Model Event',
	503,
	'SM_EVT',
	'',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621453,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621453,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621453,
	2621443,
	0,
	'SMevt_ID',
	'Full Name: State Model Event Identifier',
	'',
	'SMevt_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2621443,
	2621441,
	0,
	2621441,
	2621442,
	2621444,
	2621443,
	2621454,
	2621468,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621443,
	2621457,
	0,
	2621538,
	2621457,
	2621481,
	2621480,
	2621454,
	2621469,
	2621468,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621454,
	2621443,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621454,
	2621443,
	2621453,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621443,
	2621457,
	0,
	2621537,
	2621457,
	2621481,
	2621480,
	2621455,
	2621470,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621455,
	2621443,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621455,
	2621443,
	2621454,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621456,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621456,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621456,
	2621443,
	2621455,
	'Numb',
	'Full Name: Event Number',
	'',
	'Numb',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621457,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621457,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621457,
	2621443,
	2621456,
	'Mning',
	'Full Name: Event Meaning',
	'',
	'Mning',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621458,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621458,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621458,
	2621443,
	2621457,
	'Is_Lbl_U',
	'
This is a flag that indicates whether custom label keyletters are used fro the External Entity Event.
Value 0 indicates custom label keyletters are used.
Value 1 indiactes External Entity keyletters are used.',
	'',
	'Is_Lbl_U',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621459,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621459,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621459,
	2621443,
	2621458,
	'Unq_Lbl',
	'Holds the event label - derived by concatenating the keyletters  and event number.

If the "Is_Lbl_U" attribute is 0, then the value of the Object.Keyletter attribute is concatenated with the State Model Event.Numb attribute.
If the "Is_Lbl_U" attribute is 1, then the value of the State Model Event.Cust_KL attribue is concatenated with the State Model Event.Numb attribute.',
	'',
	'Unq_Lbl',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621460,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621460,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621460,
	2621443,
	2621459,
	'Drv_Lbl',
	'Full Name: Derived Label',
	'',
	'Drv_Lbl',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621461,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621461,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621461,
	2621443,
	2621460,
	'Descrip',
	'Full Name: Event Description',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621462,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621462,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621462,
	2621443,
	2621461,
	'Order',
	'A utlity attribute for the archetypes to specify a particular order of the State Model Events.
This attribute is a "work around" until the archetype language supports an "ORDERED BY" clause.',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621463,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621463,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621463,
	2621443,
	2621462,
	'Used',
	'A flag used by the translation engine to marked if the event is ever actually used in the application analysis model. If TRUE, the event is used (either generated or ore-created). If FALSE, the event is not used.',
	'',
	'Used',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621464,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621464,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621464,
	2621443,
	2621463,
	'AssignUsed',
	'',
	'',
	'AssignUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621465,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621465,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621465,
	2621443,
	2621464,
	'UsedCount',
	'The total number of times this event is used in the action language of the application analysis domain.',
	'',
	'UsedCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621466,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621466,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621466,
	2621443,
	2621465,
	'Priority',
	'For architectures which support the notion of "prioritized events", this attibute may be used to capture the priority of the event as supplied by coloring information.',
	'',
	'Priority',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621467,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621467,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621467,
	2621443,
	2621466,
	'SelfDirectedOnly',
	'A flag to indicate to the translation engine if this event is only used as a self directed event.',
	'',
	'SelfDirectedOnly',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621468,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621468,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621468,
	2621443,
	2621467,
	'SelfDirected',
	'',
	'',
	'SelfDirected',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621469,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621469,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621469,
	2621443,
	2621468,
	'IsSynchronizedEvent',
	'',
	'',
	'IsSynchronizedEvent',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621470,
	2621443);
INSERT INTO O_BATTR
	VALUES (2621470,
	2621443);
INSERT INTO O_ATTR
	VALUES (2621470,
	2621443,
	2621469,
	'IsEventFunction',
	'',
	'',
	'IsEventFunction',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	2621443);
INSERT INTO O_OIDA
	VALUES (2621453,
	2621443,
	0);
INSERT INTO O_RTIDA
	VALUES (2621453,
	2621443,
	0,
	2097161,
	2097172);
INSERT INTO O_RTIDA
	VALUES (2621453,
	2621443,
	0,
	2097157,
	2097164);
INSERT INTO O_OIDA
	VALUES (2621454,
	2621443,
	0);
INSERT INTO O_RTIDA
	VALUES (2621454,
	2621443,
	0,
	2097161,
	2097172);
INSERT INTO O_RTIDA
	VALUES (2621454,
	2621443,
	0,
	2097157,
	2097164);
INSERT INTO O_ID
	VALUES (1,
	2621443);
INSERT INTO O_OIDA
	VALUES (2621455,
	2621443,
	1);
INSERT INTO O_RTIDA
	VALUES (2621455,
	2621443,
	1,
	2621463,
	2621495);
INSERT INTO O_RTIDA
	VALUES (2621455,
	2621443,
	1,
	4718611,
	4718629);
INSERT INTO O_OIDA
	VALUES (2621453,
	2621443,
	1);
INSERT INTO O_RTIDA
	VALUES (2621453,
	2621443,
	1,
	2621463,
	2621495);
INSERT INTO O_RTIDA
	VALUES (2621453,
	2621443,
	1,
	4718611,
	4718629);
INSERT INTO O_OIDA
	VALUES (2621454,
	2621443,
	1);
INSERT INTO O_RTIDA
	VALUES (2621454,
	2621443,
	1,
	2621463,
	2621495);
INSERT INTO O_RTIDA
	VALUES (2621454,
	2621443,
	1,
	4718611,
	4718629);
INSERT INTO O_OBJ
	VALUES (2621444,
	'New State Transition',
	505,
	'SM_NSTXN',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621444,
	2621447,
	0,
	2621486,
	2621445,
	2621451,
	2621449,
	2621471,
	2621471,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621471,
	2621444,
	2621486,
	2621447,
	1);
INSERT INTO O_ATTR
	VALUES (2621471,
	2621444,
	0,
	'Trans_ID',
	'',
	'',
	'Trans_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621444,
	2621461,
	0,
	2621553,
	2621462,
	2621492,
	2621491,
	2621472,
	2621472,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621444,
	2621447,
	0,
	2621487,
	2621445,
	2621451,
	2621449,
	2621472,
	2621473,
	2621472,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621472,
	2621444,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621472,
	2621444,
	2621471,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621444,
	2621461,
	0,
	2621551,
	2621462,
	2621492,
	2621491,
	2621473,
	2621474,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621473,
	2621444,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621473,
	2621444,
	2621472,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621444,
	2621461,
	0,
	2621552,
	2621462,
	2621492,
	2621491,
	2621474,
	2621475,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621474,
	2621444,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621474,
	2621444,
	2621473,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621444,
	2621461,
	0,
	2621554,
	2621462,
	2621492,
	2621491,
	2621475,
	2621476,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621475,
	2621444,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621475,
	2621444,
	2621474,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621444);
INSERT INTO O_OIDA
	VALUES (2621474,
	2621444,
	0);
INSERT INTO O_OIDA
	VALUES (2621473,
	2621444,
	0);
INSERT INTO O_OIDA
	VALUES (2621472,
	2621444,
	0);
INSERT INTO O_OIDA
	VALUES (2621475,
	2621444,
	0);
INSERT INTO O_ID
	VALUES (1,
	2621444);
INSERT INTO O_OIDA
	VALUES (2621472,
	2621444,
	1);
INSERT INTO O_OIDA
	VALUES (2621471,
	2621444,
	1);
INSERT INTO O_OBJ
	VALUES (2621445,
	'Event Ignored',
	506,
	'SM_EIGN',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621445,
	2621461,
	0,
	2621551,
	2621462,
	2621493,
	2621491,
	2621476,
	2621477,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621476,
	2621445,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621476,
	2621445,
	0,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621445,
	2621461,
	0,
	2621552,
	2621462,
	2621493,
	2621491,
	2621477,
	2621478,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621477,
	2621445,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621477,
	2621445,
	2621476,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621445,
	2621461,
	0,
	2621553,
	2621462,
	2621493,
	2621491,
	2621478,
	2621479,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621478,
	2621445,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621478,
	2621445,
	2621477,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621445,
	2621461,
	0,
	2621554,
	2621462,
	2621493,
	2621491,
	2621479,
	2621480,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621479,
	2621445,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621479,
	2621445,
	2621478,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621480,
	2621445);
INSERT INTO O_BATTR
	VALUES (2621480,
	2621445);
INSERT INTO O_ATTR
	VALUES (2621480,
	2621445,
	2621479,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	2621445);
INSERT INTO O_OIDA
	VALUES (2621478,
	2621445,
	0);
INSERT INTO O_OIDA
	VALUES (2621477,
	2621445,
	0);
INSERT INTO O_OIDA
	VALUES (2621476,
	2621445,
	0);
INSERT INTO O_OIDA
	VALUES (2621479,
	2621445,
	0);
INSERT INTO O_OBJ
	VALUES (2621446,
	'Cant Happen',
	507,
	'SM_CH',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621446,
	2621461,
	0,
	2621551,
	2621462,
	2621494,
	2621491,
	2621481,
	2621481,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621481,
	2621446,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621481,
	2621446,
	0,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621446,
	2621461,
	0,
	2621552,
	2621462,
	2621494,
	2621491,
	2621482,
	2621482,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621482,
	2621446,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621482,
	2621446,
	2621481,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621446,
	2621461,
	0,
	2621553,
	2621462,
	2621494,
	2621491,
	2621483,
	2621483,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621483,
	2621446,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621483,
	2621446,
	2621482,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621446,
	2621461,
	0,
	2621554,
	2621462,
	2621494,
	2621491,
	2621484,
	2621484,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621484,
	2621446,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621484,
	2621446,
	2621483,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621485,
	2621446);
INSERT INTO O_BATTR
	VALUES (2621485,
	2621446);
INSERT INTO O_ATTR
	VALUES (2621485,
	2621446,
	2621484,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	2621446);
INSERT INTO O_OIDA
	VALUES (2621483,
	2621446,
	0);
INSERT INTO O_OIDA
	VALUES (2621482,
	2621446,
	0);
INSERT INTO O_OIDA
	VALUES (2621484,
	2621446,
	0);
INSERT INTO O_OIDA
	VALUES (2621481,
	2621446,
	0);
INSERT INTO O_OBJ
	VALUES (2621447,
	'Transition',
	508,
	'SM_TXN',
	'',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621486,
	2621447);
INSERT INTO O_BATTR
	VALUES (2621486,
	2621447);
INSERT INTO O_ATTR
	VALUES (2621486,
	2621447,
	0,
	'Trans_ID',
	'',
	'',
	'Trans_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2621447,
	2621441,
	0,
	2621441,
	2621443,
	2621446,
	2621445,
	2621487,
	2621485,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621447,
	2621442,
	1,
	2621447,
	2621444,
	2621448,
	2621447,
	2621487,
	2621486,
	2621485,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621487,
	2621447,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621487,
	2621447,
	2621486,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621447,
	2621442,
	1,
	2621446,
	2621444,
	2621448,
	2621447,
	2621488,
	2621487,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621488,
	2621447,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621488,
	2621447,
	2621487,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621447,
	2621442,
	1,
	2621448,
	2621444,
	2621448,
	2621447,
	2621489,
	2621488,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621489,
	2621447,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621489,
	2621447,
	2621488,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621447);
INSERT INTO O_OIDA
	VALUES (2621487,
	2621447,
	0);
INSERT INTO O_RTIDA
	VALUES (2621487,
	2621447,
	0,
	2621449,
	2621462);
INSERT INTO O_RTIDA
	VALUES (2621487,
	2621447,
	0,
	2621445,
	2621449);
INSERT INTO O_OIDA
	VALUES (2621486,
	2621447,
	0);
INSERT INTO O_RTIDA
	VALUES (2621486,
	2621447,
	0,
	2621445,
	2621449);
INSERT INTO O_RTIDA
	VALUES (2621486,
	2621447,
	0,
	2621449,
	2621462);
INSERT INTO O_OBJ
	VALUES (2621448,
	'No Event Transition',
	509,
	'SM_NETXN',
	'For backwards compatibility with pre-5.1 model databases',
	2621445);
INSERT INTO O_REF
	VALUES (2621448,
	2621447,
	0,
	2621486,
	2621445,
	2621450,
	2621449,
	2621490,
	2621441,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621490,
	2621448,
	2621486,
	2621447,
	1);
INSERT INTO O_ATTR
	VALUES (2621490,
	2621448,
	0,
	'Trans_ID',
	'',
	'',
	'Trans_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621448,
	2621447,
	0,
	2621487,
	2621445,
	2621450,
	2621449,
	2621491,
	2621442,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621448,
	2621442,
	0,
	2621447,
	2621446,
	2621454,
	2621453,
	2621491,
	2621489,
	2621442,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621491,
	2621448,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621491,
	2621448,
	2621490,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621448,
	2621442,
	0,
	2621446,
	2621446,
	2621454,
	2621453,
	2621492,
	2621490,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621492,
	2621448,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621492,
	2621448,
	2621491,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621493,
	2621448);
INSERT INTO O_BATTR
	VALUES (2621493,
	2621448);
INSERT INTO O_ATTR
	VALUES (2621493,
	2621448,
	2621492,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (1,
	2621448);
INSERT INTO O_OIDA
	VALUES (2621491,
	2621448,
	1);
INSERT INTO O_OIDA
	VALUES (2621490,
	2621448,
	1);
INSERT INTO O_OBJ
	VALUES (2621449,
	'Creation Transition',
	510,
	'SM_CRTXN',
	'For backwards compatibility with pre-5.1 model databases',
	2621445);
INSERT INTO O_REF
	VALUES (2621449,
	2621447,
	0,
	2621486,
	2621445,
	2621452,
	2621449,
	2621494,
	2621443,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621494,
	2621449,
	2621486,
	2621447,
	1);
INSERT INTO O_ATTR
	VALUES (2621494,
	2621449,
	0,
	'Trans_ID',
	'',
	'',
	'Trans_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621449,
	2621447,
	0,
	2621487,
	2621445,
	2621452,
	2621449,
	2621495,
	2621444,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621449,
	2621465,
	0,
	2621569,
	2621466,
	2621503,
	2621504,
	2621495,
	2621491,
	2621444,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621495,
	2621449,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621495,
	2621449,
	2621494,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621449,
	2621465,
	0,
	2621568,
	2621466,
	2621503,
	2621504,
	2621496,
	2621492,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621496,
	2621449,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621496,
	2621449,
	2621495,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621497,
	2621449);
INSERT INTO O_BATTR
	VALUES (2621497,
	2621449);
INSERT INTO O_ATTR
	VALUES (2621497,
	2621449,
	2621496,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (1,
	2621449);
INSERT INTO O_OIDA
	VALUES (2621494,
	2621449,
	1);
INSERT INTO O_OIDA
	VALUES (2621495,
	2621449,
	1);
INSERT INTO O_OBJ
	VALUES (2621450,
	'Moore State Model',
	511,
	'SM_MOORE',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621450,
	2621441,
	0,
	2621441,
	2621447,
	2621456,
	2621455,
	2621498,
	2621445,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621498,
	2621450,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621498,
	2621450,
	0,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621450);
INSERT INTO O_OIDA
	VALUES (2621498,
	2621450,
	0);
INSERT INTO O_RTIDA
	VALUES (2621498,
	2621450,
	0,
	2621448,
	2621458);
INSERT INTO O_OBJ
	VALUES (2621451,
	'Mealy State Model',
	512,
	'SM_MEALY',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621451,
	2621441,
	0,
	2621441,
	2621447,
	2621457,
	2621455,
	2621499,
	2621446,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621499,
	2621451,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621499,
	2621451,
	0,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621451);
INSERT INTO O_OIDA
	VALUES (2621499,
	2621451,
	0);
INSERT INTO O_RTIDA
	VALUES (2621499,
	2621451,
	0,
	2621449,
	2621461);
INSERT INTO O_OBJ
	VALUES (2621452,
	'Moore Action Home',
	513,
	'SM_MOAH',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621452,
	2621454,
	0,
	2621506,
	2621450,
	2621465,
	2621464,
	2621500,
	2621493,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621500,
	2621452,
	2621508,
	2621455,
	1);
INSERT INTO O_ATTR
	VALUES (2621500,
	2621452,
	0,
	'Act_ID',
	'',
	'',
	'Act_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621452,
	2621442,
	0,
	2621447,
	2621448,
	2621460,
	2621459,
	2621501,
	2621494,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621452,
	2621450,
	0,
	2621498,
	2621448,
	2621460,
	2621458,
	2621501,
	2621495,
	2621494,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621452,
	2621454,
	0,
	2621507,
	2621450,
	2621465,
	2621464,
	2621501,
	2621496,
	2621495,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621501,
	2621452,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621501,
	2621452,
	2621500,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621452,
	2621442,
	0,
	2621446,
	2621448,
	2621460,
	2621459,
	2621502,
	2621497,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621502,
	2621452,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621502,
	2621452,
	2621501,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621452);
INSERT INTO O_OIDA
	VALUES (2621502,
	2621452,
	0);
INSERT INTO O_OIDA
	VALUES (2621501,
	2621452,
	0);
INSERT INTO O_ID
	VALUES (1,
	2621452);
INSERT INTO O_OIDA
	VALUES (2621501,
	2621452,
	1);
INSERT INTO O_OIDA
	VALUES (2621500,
	2621452,
	1);
INSERT INTO O_OBJ
	VALUES (2621453,
	'Mealy Action Home',
	514,
	'SM_MEAH',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621453,
	2621454,
	0,
	2621506,
	2621450,
	2621466,
	2621464,
	2621503,
	2621498,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621503,
	2621453,
	2621508,
	2621455,
	1);
INSERT INTO O_ATTR
	VALUES (2621503,
	2621453,
	0,
	'Act_ID',
	'',
	'',
	'Act_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621453,
	2621447,
	0,
	2621487,
	2621449,
	2621463,
	2621462,
	2621504,
	2621499,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621453,
	2621451,
	0,
	2621499,
	2621449,
	2621463,
	2621461,
	2621504,
	2621500,
	2621499,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621453,
	2621454,
	0,
	2621507,
	2621450,
	2621466,
	2621464,
	2621504,
	2621501,
	2621500,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621504,
	2621453,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621504,
	2621453,
	2621503,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621453,
	2621447,
	0,
	2621486,
	2621449,
	2621463,
	2621462,
	2621505,
	2621502,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621505,
	2621453,
	2621486,
	2621447,
	1);
INSERT INTO O_ATTR
	VALUES (2621505,
	2621453,
	2621504,
	'Trans_ID',
	'',
	'',
	'Trans_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621453);
INSERT INTO O_OIDA
	VALUES (2621504,
	2621453,
	0);
INSERT INTO O_OIDA
	VALUES (2621505,
	2621453,
	0);
INSERT INTO O_ID
	VALUES (1,
	2621453);
INSERT INTO O_OIDA
	VALUES (2621503,
	2621453,
	1);
INSERT INTO O_OIDA
	VALUES (2621504,
	2621453,
	1);
INSERT INTO O_OBJ
	VALUES (2621454,
	'Action Home',
	515,
	'SM_AH',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621454,
	2621455,
	0,
	2621508,
	2621451,
	2621468,
	2621467,
	2621506,
	2621503,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621506,
	2621454,
	2621508,
	2621455,
	1);
INSERT INTO O_ATTR
	VALUES (2621506,
	2621454,
	0,
	'Act_ID',
	'',
	'',
	'Act_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621454,
	2621455,
	0,
	2621509,
	2621451,
	2621468,
	2621467,
	2621507,
	2621504,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621507,
	2621454,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621507,
	2621454,
	2621506,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621454);
INSERT INTO O_OIDA
	VALUES (2621507,
	2621454,
	0);
INSERT INTO O_RTIDA
	VALUES (2621507,
	2621454,
	0,
	2621450,
	2621464);
INSERT INTO O_OIDA
	VALUES (2621506,
	2621454,
	0);
INSERT INTO O_RTIDA
	VALUES (2621506,
	2621454,
	0,
	2621450,
	2621464);
INSERT INTO O_OBJ
	VALUES (2621455,
	'Action',
	516,
	'SM_ACT',
	'',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621508,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621508,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621508,
	2621455,
	0,
	'Act_ID',
	'',
	'',
	'Act_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2621455,
	2621441,
	0,
	2621441,
	2621452,
	2621470,
	2621469,
	2621509,
	2621505,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621509,
	2621455,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621509,
	2621455,
	2621508,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621510,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621510,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621510,
	2621455,
	2621509,
	'Suc_Pars',
	'Full Name: Successfully Parsed.
Indicates if the state action contained in Action.Descrip has been successfully parsed by ModeBuilder.
A value of zero (0) indicates the state action has not been successfully parsed, and thus can not be translated. A value of one (1) indicates the state action has been successfully parsed.',
	'',
	'Suc_Pars',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621511,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621511,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621511,
	2621455,
	2621510,
	'Action_Semantics',
	'',
	'',
	'Action_Semantics',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621512,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621512,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621512,
	2621455,
	2621511,
	'Descrip',
	'Full Name: Description
Contains the BridgePoint Action Language (BPAL) for this state action instance.',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (2621455,
	4194312,
	0,
	4194380,
	4194310,
	4194318,
	4194315,
	2621513,
	2621506,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621513,
	2621455,
	4194380,
	4194312,
	1);
INSERT INTO O_ATTR
	VALUES (2621513,
	2621455,
	2621512,
	'AutID',
	'',
	'',
	'AutID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621455,
	4194313,
	0,
	4194384,
	4194311,
	4194326,
	4194321,
	2621514,
	2621507,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621514,
	2621455,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (2621514,
	2621455,
	2621513,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621515,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621515,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621515,
	2621455,
	2621514,
	'SelfEventCount',
	'Full Name: Maximum Number of Self Directed Events.

The maximum number of self directed events generated in this state action. A value of zero (0) indicates this state action does not generate any self directed events.',
	'',
	'SelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621516,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621516,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621516,
	2621455,
	2621515,
	'NonSelfEventCount',
	'Full Name: Maximum Number of Non-Self Directed Events.

The maximum number of non-self directed events generated (or pre-created) in this state action. ',
	'',
	'NonSelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621517,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621517,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621517,
	2621455,
	2621516,
	'SelectManyCount',
	'',
	'',
	'SelectManyCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621518,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621518,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621518,
	2621455,
	2621517,
	'SelectAnyWhereCount',
	'',
	'',
	'SelectAnyWhereCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621519,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621519,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621519,
	2621455,
	2621518,
	'TimerStartCount',
	'',
	'',
	'TimerStartCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621520,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621520,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621520,
	2621455,
	2621519,
	'IsSafeForInterrupts',
	'',
	'',
	'IsSafeForInterrupts',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621521,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621521,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621521,
	2621455,
	2621520,
	'IsAsynchronous',
	'',
	'',
	'IsAsynchronous',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621522,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621522,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621522,
	2621455,
	2621521,
	'AsynchronousType',
	'',
	'',
	'AsynchronousType',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621523,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621523,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621523,
	2621455,
	2621522,
	'AsynchronousNumber',
	'',
	'',
	'AsynchronousNumber',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621524,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621524,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621524,
	2621455,
	2621523,
	'IsCallback',
	'',
	'',
	'IsCallback',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621525,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621525,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621525,
	2621455,
	2621524,
	'CallbackNumber',
	'',
	'',
	'CallbackNumber',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621526,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621526,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621526,
	2621455,
	2621525,
	'CallbackInitStatus',
	'',
	'',
	'CallbackInitStatus',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621527,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621527,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621527,
	2621455,
	2621526,
	'ReturnStmtUsed',
	'',
	'',
	'ReturnStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621528,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621528,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621528,
	2621455,
	2621527,
	'BreakStmtUsed',
	'',
	'',
	'BreakStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (2621529,
	2621455);
INSERT INTO O_BATTR
	VALUES (2621529,
	2621455);
INSERT INTO O_ATTR
	VALUES (2621529,
	2621455,
	2621528,
	'ContinueStmtUsed',
	'',
	'',
	'ContinueStmtUsed',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	2621455);
INSERT INTO O_OIDA
	VALUES (2621509,
	2621455,
	0);
INSERT INTO O_RTIDA
	VALUES (2621509,
	2621455,
	0,
	2621451,
	2621467);
INSERT INTO O_OIDA
	VALUES (2621508,
	2621455,
	0);
INSERT INTO O_RTIDA
	VALUES (2621508,
	2621455,
	0,
	2621451,
	2621467);
INSERT INTO O_OBJ
	VALUES (2621456,
	'State Model Event Data Item',
	517,
	'SM_EVTDI',
	'',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621530,
	2621456);
INSERT INTO O_BATTR
	VALUES (2621530,
	2621456);
INSERT INTO O_ATTR
	VALUES (2621530,
	2621456,
	0,
	'SMedi_ID',
	'Full Name: State Model Event Data Item',
	'',
	'SMedi_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2621456,
	2621441,
	0,
	2621441,
	2621453,
	2621472,
	2621471,
	2621531,
	2621508,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621531,
	2621456,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621531,
	2621456,
	2621530,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621532,
	2621456);
INSERT INTO O_BATTR
	VALUES (2621532,
	2621456);
INSERT INTO O_ATTR
	VALUES (2621532,
	2621456,
	2621531,
	'Name',
	'Full Name: Event Data Item Name',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (2621533,
	2621456);
INSERT INTO O_BATTR
	VALUES (2621533,
	2621456);
INSERT INTO O_ATTR
	VALUES (2621533,
	2621456,
	2621532,
	'Descrip',
	'Full Name: Description',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (2621456,
	1048584,
	0,
	1048643,
	2621461,
	2621489,
	2621490,
	2621534,
	2621447,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621534,
	2621456,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (2621534,
	2621456,
	2621533,
	'DT_ID',
	'Notes:
This is the last attribute defined by the BridgePoint internal OOA schema. Any user defined attributes added to this object must come after DT_IS.',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621535,
	2621456);
INSERT INTO O_BATTR
	VALUES (2621535,
	2621456);
INSERT INTO O_ATTR
	VALUES (2621535,
	2621456,
	2621534,
	'Order',
	'Attribute provided for the translation engine to specify a relative order in which instances of State Model Event Data Item need to be processed. ',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621536,
	2621456);
INSERT INTO O_BATTR
	VALUES (2621536,
	2621456);
INSERT INTO O_ATTR
	VALUES (2621536,
	2621456,
	2621535,
	'ParamBuffer',
	'A string buffer provided for the translation engine to hold intermediate code fragments when processing a parameter list (e.g., fragment generation ''param_*'' functions.',
	'',
	'ParamBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718667,
	2621456);
INSERT INTO O_BATTR
	VALUES (4718667,
	2621456);
INSERT INTO O_ATTR
	VALUES (4718667,
	2621456,
	2621536,
	'OALParamBuffer',
	'',
	'',
	'OALParamBuffer',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	2621456);
INSERT INTO O_OIDA
	VALUES (2621530,
	2621456,
	0);
INSERT INTO O_RTIDA
	VALUES (2621530,
	2621456,
	0,
	2621459,
	2621484);
INSERT INTO O_OIDA
	VALUES (2621531,
	2621456,
	0);
INSERT INTO O_RTIDA
	VALUES (2621531,
	2621456,
	0,
	2621459,
	2621484);
INSERT INTO O_OBJ
	VALUES (2621457,
	'Event Supplemental Data',
	518,
	'SM_SUPDT',
	'',
	2621445);
INSERT INTO O_NBATTR
	VALUES (2621537,
	2621457);
INSERT INTO O_BATTR
	VALUES (2621537,
	2621457);
INSERT INTO O_ATTR
	VALUES (2621537,
	2621457,
	0,
	'SMspd_ID',
	'Full Name: Event Supplemental Data Identifier',
	'',
	'SMspd_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (2621457,
	2621441,
	0,
	2621441,
	2621460,
	2621487,
	2621488,
	2621538,
	2621448,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621538,
	2621457,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621538,
	2621457,
	2621537,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_DBATTR
	VALUES (2621539,
	2621457,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (2621539,
	2621457);
INSERT INTO O_ATTR
	VALUES (2621539,
	2621457,
	2621538,
	'Non_Local',
	'',
	'',
	'Non_Local',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	2621457);
INSERT INTO O_OIDA
	VALUES (2621538,
	2621457,
	0);
INSERT INTO O_RTIDA
	VALUES (2621538,
	2621457,
	0,
	2621459,
	2621485);
INSERT INTO O_RTIDA
	VALUES (2621538,
	2621457,
	0,
	2621458,
	2621483);
INSERT INTO O_RTIDA
	VALUES (2621538,
	2621457,
	0,
	2621457,
	2621480);
INSERT INTO O_OIDA
	VALUES (2621537,
	2621457,
	0);
INSERT INTO O_RTIDA
	VALUES (2621537,
	2621457,
	0,
	2621459,
	2621485);
INSERT INTO O_RTIDA
	VALUES (2621537,
	2621457,
	0,
	2621458,
	2621483);
INSERT INTO O_RTIDA
	VALUES (2621537,
	2621457,
	0,
	2621457,
	2621480);
INSERT INTO O_OBJ
	VALUES (2621458,
	'Supplemental Data Items',
	519,
	'SM_SDI',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621458,
	2621456,
	0,
	2621530,
	2621459,
	2621486,
	2621484,
	2621540,
	2621509,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621540,
	2621458,
	2621530,
	2621456,
	1);
INSERT INTO O_ATTR
	VALUES (2621540,
	2621458,
	0,
	'SMedi_ID',
	'',
	'',
	'SMedi_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621458,
	2621457,
	0,
	2621537,
	2621459,
	2621486,
	2621485,
	2621541,
	2621510,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621541,
	2621458,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621541,
	2621458,
	2621540,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621458,
	2621456,
	0,
	2621531,
	2621459,
	2621486,
	2621484,
	2621542,
	2621511,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621458,
	2621457,
	0,
	2621538,
	2621459,
	2621486,
	2621485,
	2621542,
	2621512,
	2621511,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621542,
	2621458,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621542,
	2621458,
	2621541,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621458);
INSERT INTO O_OIDA
	VALUES (2621540,
	2621458,
	0);
INSERT INTO O_RTIDA
	VALUES (2621540,
	2621458,
	0,
	4718612,
	4718631);
INSERT INTO O_OIDA
	VALUES (2621541,
	2621458,
	0);
INSERT INTO O_RTIDA
	VALUES (2621541,
	2621458,
	0,
	4718612,
	4718631);
INSERT INTO O_OIDA
	VALUES (2621542,
	2621458,
	0);
INSERT INTO O_RTIDA
	VALUES (2621542,
	2621458,
	0,
	4718612,
	4718631);
INSERT INTO O_OBJ
	VALUES (2621459,
	'Instance State Model',
	520,
	'SM_ISM',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621459,
	2621441,
	0,
	2621441,
	2621454,
	2621475,
	2621473,
	2621543,
	2621449,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621543,
	2621459,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621543,
	2621459,
	0,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621459,
	3145732,
	0,
	3145773,
	2621455,
	2621476,
	2621477,
	2621544,
	2621450,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621544,
	2621459,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (2621544,
	2621459,
	2621543,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621545,
	2621459);
INSERT INTO O_BATTR
	VALUES (2621545,
	2621459);
INSERT INTO O_ATTR
	VALUES (2621545,
	2621459,
	2621544,
	'MaxSelfEvents',
	'Full Name: Maximum Number of Self Directed Events.
The maximum number of self directed events generated in any state action of this state model. The default value is zero (0), and should only be changed by a pre-code fragment generation processes (multi-pass fragment generator translation engine).
A value of zero (0) indicates this state model does not generate any self directed events.
In a multi-pass translation engine, the code fragment generators can use this value in making decisions regarding optimization of self directed events.',
	'',
	'MaxSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621546,
	2621459);
INSERT INTO O_BATTR
	VALUES (2621546,
	2621459);
INSERT INTO O_ATTR
	VALUES (2621546,
	2621459,
	2621545,
	'MaxNonSelfEvents',
	'',
	'',
	'MaxNonSelfEvents',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	2621459);
INSERT INTO O_OIDA
	VALUES (2621544,
	2621459,
	0);
INSERT INTO O_OIDA
	VALUES (2621543,
	2621459,
	0);
INSERT INTO O_ID
	VALUES (1,
	2621459);
INSERT INTO O_OIDA
	VALUES (2621543,
	2621459,
	1);
INSERT INTO O_RTIDA
	VALUES (2621543,
	2621459,
	1,
	4718609,
	4718625);
INSERT INTO O_OBJ
	VALUES (2621460,
	'Assigner State Model',
	521,
	'SM_ASM',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621460,
	2621441,
	0,
	2621441,
	2621454,
	2621474,
	2621473,
	2621547,
	2621451,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621547,
	2621460,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621547,
	2621460,
	0,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621460,
	3145732,
	0,
	3145773,
	2621456,
	2621478,
	2621479,
	2621548,
	2621452,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621548,
	2621460,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (2621548,
	2621460,
	2621547,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621549,
	2621460);
INSERT INTO O_BATTR
	VALUES (2621549,
	2621460);
INSERT INTO O_ATTR
	VALUES (2621549,
	2621460,
	2621548,
	'MaxSelfEvents',
	'Full Name: Maximum Number of Self Directed Events.
The maximum number of self directed events generated in any state action of this state model. The default value is zero (0), and should only be changed by a pre-code fragment generation processes (multi-pass fragment generator translation engine).
A value of zero (0) indicates this state model does not generate any self directed events.
In a multi-pass translation engine, the code fragment generators can use this value in making decisions regarding optimization of self directed events.',
	'',
	'MaxSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621550,
	2621460);
INSERT INTO O_BATTR
	VALUES (2621550,
	2621460);
INSERT INTO O_ATTR
	VALUES (2621550,
	2621460,
	2621549,
	'MaxNonSelfEvents',
	'',
	'',
	'MaxNonSelfEvents',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	2621460);
INSERT INTO O_OIDA
	VALUES (2621547,
	2621460,
	0);
INSERT INTO O_OIDA
	VALUES (2621548,
	2621460,
	0);
INSERT INTO O_ID
	VALUES (1,
	2621460);
INSERT INTO O_OIDA
	VALUES (2621547,
	2621460,
	1);
INSERT INTO O_RTIDA
	VALUES (2621547,
	2621460,
	1,
	4718610,
	4718627);
INSERT INTO O_OBJ
	VALUES (2621461,
	'State Event Matrix Entry',
	504,
	'SM_SEME',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621461,
	2621442,
	0,
	2621446,
	2621467,
	2621507,
	2621505,
	2621551,
	2621513,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621551,
	2621461,
	2621446,
	2621442,
	1);
INSERT INTO O_ATTR
	VALUES (2621551,
	2621461,
	0,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621461,
	2621463,
	0,
	2621558,
	2621467,
	2621507,
	2621506,
	2621552,
	2621514,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621552,
	2621461,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621552,
	2621461,
	2621551,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621461,
	2621442,
	0,
	2621447,
	2621467,
	2621507,
	2621505,
	2621553,
	2621515,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (2621461,
	2621463,
	0,
	2621559,
	2621467,
	2621507,
	2621506,
	2621553,
	2621516,
	2621515,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621553,
	2621461,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621553,
	2621461,
	2621552,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621461,
	2621463,
	0,
	2621560,
	2621467,
	2621507,
	2621506,
	2621554,
	2621517,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621554,
	2621461,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621554,
	2621461,
	2621553,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621461);
INSERT INTO O_OIDA
	VALUES (2621553,
	2621461,
	0);
INSERT INTO O_RTIDA
	VALUES (2621553,
	2621461,
	0,
	2621462,
	2621491);
INSERT INTO O_OIDA
	VALUES (2621554,
	2621461,
	0);
INSERT INTO O_RTIDA
	VALUES (2621554,
	2621461,
	0,
	2621462,
	2621491);
INSERT INTO O_OIDA
	VALUES (2621552,
	2621461,
	0);
INSERT INTO O_RTIDA
	VALUES (2621552,
	2621461,
	0,
	2621462,
	2621491);
INSERT INTO O_OIDA
	VALUES (2621551,
	2621461,
	0);
INSERT INTO O_RTIDA
	VALUES (2621551,
	2621461,
	0,
	2621462,
	2621491);
INSERT INTO O_OBJ
	VALUES (2621462,
	'Polymorhic Event',
	522,
	'SM_PEVT',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621462,
	2621443,
	1,
	2621453,
	2621463,
	2621496,
	2621495,
	2621555,
	2621453,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621555,
	2621462,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621555,
	2621462,
	0,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621462,
	2621443,
	1,
	2621454,
	2621463,
	2621496,
	2621495,
	2621556,
	2621454,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621556,
	2621462,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621556,
	2621462,
	2621555,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621462,
	2621443,
	1,
	2621455,
	2621463,
	2621496,
	2621495,
	2621557,
	2621455,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621557,
	2621462,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621557,
	2621462,
	2621556,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621462);
INSERT INTO O_OIDA
	VALUES (2621557,
	2621462,
	0);
INSERT INTO O_OIDA
	VALUES (2621556,
	2621462,
	0);
INSERT INTO O_OIDA
	VALUES (2621555,
	2621462,
	0);
INSERT INTO O_ID
	VALUES (1,
	2621462);
INSERT INTO O_OIDA
	VALUES (2621556,
	2621462,
	1);
INSERT INTO O_RTIDA
	VALUES (2621556,
	2621462,
	1,
	2621465,
	2621501);
INSERT INTO O_OIDA
	VALUES (2621555,
	2621462,
	1);
INSERT INTO O_RTIDA
	VALUES (2621555,
	2621462,
	1,
	2621465,
	2621501);
INSERT INTO O_OBJ
	VALUES (2621463,
	'SEM Event',
	525,
	'SM_SEVT',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621463,
	2621443,
	1,
	2621453,
	2621463,
	2621497,
	2621495,
	2621558,
	2621456,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621558,
	2621463,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621558,
	2621463,
	0,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621463,
	2621443,
	1,
	2621454,
	2621463,
	2621497,
	2621495,
	2621559,
	2621457,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621559,
	2621463,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621559,
	2621463,
	2621558,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621463,
	2621443,
	1,
	2621455,
	2621463,
	2621497,
	2621495,
	2621560,
	2621458,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621560,
	2621463,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621560,
	2621463,
	2621559,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621463);
INSERT INTO O_OIDA
	VALUES (2621559,
	2621463,
	0);
INSERT INTO O_RTIDA
	VALUES (2621559,
	2621463,
	0,
	2621467,
	2621506);
INSERT INTO O_RTIDA
	VALUES (2621559,
	2621463,
	0,
	2621464,
	2621498);
INSERT INTO O_OIDA
	VALUES (2621558,
	2621463,
	0);
INSERT INTO O_RTIDA
	VALUES (2621558,
	2621463,
	0,
	2621467,
	2621506);
INSERT INTO O_RTIDA
	VALUES (2621558,
	2621463,
	0,
	2621464,
	2621498);
INSERT INTO O_OIDA
	VALUES (2621560,
	2621463,
	0);
INSERT INTO O_RTIDA
	VALUES (2621560,
	2621463,
	0,
	2621467,
	2621506);
INSERT INTO O_RTIDA
	VALUES (2621560,
	2621463,
	0,
	2621464,
	2621498);
INSERT INTO O_OBJ
	VALUES (2621464,
	'Non Local Event',
	526,
	'SM_NLEVT',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621464,
	2621463,
	0,
	2621558,
	2621464,
	2621500,
	2621498,
	2621561,
	2621459,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621561,
	2621464,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621561,
	2621464,
	0,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621464,
	2621463,
	0,
	2621559,
	2621464,
	2621500,
	2621498,
	2621562,
	2621460,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621562,
	2621464,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621562,
	2621464,
	2621561,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621464,
	2621463,
	0,
	2621560,
	2621464,
	2621500,
	2621498,
	2621563,
	2621461,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621563,
	2621464,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621563,
	2621464,
	2621562,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621464,
	2621462,
	1,
	2621555,
	2621465,
	2621502,
	2621501,
	2621564,
	2621518,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621564,
	2621464,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621564,
	2621464,
	2621563,
	'polySMevt_ID',
	'',
	'poly',
	'SMevt_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (2621464,
	2621462,
	1,
	2621556,
	2621465,
	2621502,
	2621501,
	2621565,
	2621519,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621565,
	2621464,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621565,
	2621464,
	2621564,
	'polySM_ID',
	'',
	'poly',
	'SM_ID',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (2621566,
	2621464);
INSERT INTO O_BATTR
	VALUES (2621566,
	2621464);
INSERT INTO O_ATTR
	VALUES (2621566,
	2621464,
	2621565,
	'polySMspd_ID',
	'',
	'',
	'polySMspd_ID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (2621567,
	2621464);
INSERT INTO O_BATTR
	VALUES (2621567,
	2621464);
INSERT INTO O_ATTR
	VALUES (2621567,
	2621464,
	2621566,
	'Local_Meaning',
	'',
	'',
	'Local_Meaning',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	2621464);
INSERT INTO O_OIDA
	VALUES (2621562,
	2621464,
	0);
INSERT INTO O_OIDA
	VALUES (2621563,
	2621464,
	0);
INSERT INTO O_OBJ
	VALUES (2621465,
	'Local Event',
	527,
	'SM_LEVT',
	'',
	2621445);
INSERT INTO O_REF
	VALUES (2621465,
	2621463,
	0,
	2621558,
	2621464,
	2621499,
	2621498,
	2621568,
	2621462,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621568,
	2621465,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (2621568,
	2621465,
	0,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621465,
	2621463,
	0,
	2621559,
	2621464,
	2621499,
	2621498,
	2621569,
	2621463,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621569,
	2621465,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (2621569,
	2621465,
	2621568,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (2621465,
	2621463,
	0,
	2621560,
	2621464,
	2621499,
	2621498,
	2621570,
	2621464,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (2621570,
	2621465,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (2621570,
	2621465,
	2621569,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	2621465);
INSERT INTO O_OIDA
	VALUES (2621568,
	2621465,
	0);
INSERT INTO O_RTIDA
	VALUES (2621568,
	2621465,
	0,
	2621466,
	2621504);
INSERT INTO O_OIDA
	VALUES (2621569,
	2621465,
	0);
INSERT INTO O_RTIDA
	VALUES (2621569,
	2621465,
	0,
	2621466,
	2621504);
INSERT INTO O_IOBJ
	VALUES (2621441,
	1048584,
	5,
	2621445,
	'Data Type',
	'S_DT');
INSERT INTO O_IOBJ
	VALUES (2621442,
	3145732,
	5,
	2621445,
	'Class',
	'O_OBJ');
INSERT INTO R_SIMP
	VALUES (2621441);
INSERT INTO R_REL
	VALUES (2621441,
	501,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621441,
	2621441,
	2621441,
	0,
	0,
	'');
INSERT INTO R_RTO
	VALUES (2621441,
	2621441,
	2621441,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621441,
	2621441,
	0);
INSERT INTO R_FORM
	VALUES (2621442,
	2621441,
	2621442,
	1,
	1,
	'Is decomposed into');
INSERT INTO R_RGO
	VALUES (2621442,
	2621441,
	2621442);
INSERT INTO R_OIR
	VALUES (2621442,
	2621441,
	2621442,
	0);
INSERT INTO R_SIMP
	VALUES (2621442);
INSERT INTO R_REL
	VALUES (2621442,
	502,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621441,
	2621442,
	2621443,
	0,
	0,
	'stimulates');
INSERT INTO R_RTO
	VALUES (2621441,
	2621442,
	2621443,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621442,
	2621443,
	0);
INSERT INTO R_FORM
	VALUES (2621443,
	2621442,
	2621444,
	1,
	1,
	'can be comunicated to via');
INSERT INTO R_RGO
	VALUES (2621443,
	2621442,
	2621444);
INSERT INTO R_OIR
	VALUES (2621443,
	2621442,
	2621444,
	0);
INSERT INTO R_SIMP
	VALUES (2621443);
INSERT INTO R_REL
	VALUES (2621443,
	505,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621441,
	2621443,
	2621445,
	0,
	0,
	'');
INSERT INTO R_RTO
	VALUES (2621441,
	2621443,
	2621445,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621443,
	2621445,
	0);
INSERT INTO R_FORM
	VALUES (2621447,
	2621443,
	2621446,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (2621447,
	2621443,
	2621446);
INSERT INTO R_OIR
	VALUES (2621447,
	2621443,
	2621446,
	0);
INSERT INTO R_SIMP
	VALUES (2621444);
INSERT INTO R_REL
	VALUES (2621444,
	506,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621442,
	2621444,
	2621447,
	0,
	0,
	'is destination to');
INSERT INTO R_RTO
	VALUES (2621442,
	2621444,
	2621447,
	1);
INSERT INTO R_OIR
	VALUES (2621442,
	2621444,
	2621447,
	0);
INSERT INTO R_FORM
	VALUES (2621447,
	2621444,
	2621448,
	1,
	1,
	'is destination of');
INSERT INTO R_RGO
	VALUES (2621447,
	2621444,
	2621448);
INSERT INTO R_OIR
	VALUES (2621447,
	2621444,
	2621448,
	0);
INSERT INTO R_SUBSUP
	VALUES (2621445);
INSERT INTO R_REL
	VALUES (2621445,
	507,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621447,
	2621445,
	2621449);
INSERT INTO R_RTO
	VALUES (2621447,
	2621445,
	2621449,
	0);
INSERT INTO R_OIR
	VALUES (2621447,
	2621445,
	2621449,
	0);
INSERT INTO R_SUB
	VALUES (2621448,
	2621445,
	2621450);
INSERT INTO R_RGO
	VALUES (2621448,
	2621445,
	2621450);
INSERT INTO R_OIR
	VALUES (2621448,
	2621445,
	2621450,
	0);
INSERT INTO R_SUB
	VALUES (2621444,
	2621445,
	2621451);
INSERT INTO R_RGO
	VALUES (2621444,
	2621445,
	2621451);
INSERT INTO R_OIR
	VALUES (2621444,
	2621445,
	2621451,
	0);
INSERT INTO R_SUB
	VALUES (2621449,
	2621445,
	2621452);
INSERT INTO R_RGO
	VALUES (2621449,
	2621445,
	2621452);
INSERT INTO R_OIR
	VALUES (2621449,
	2621445,
	2621452,
	0);
INSERT INTO R_SIMP
	VALUES (2621446);
INSERT INTO R_REL
	VALUES (2621446,
	508,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621442,
	2621446,
	2621453,
	0,
	0,
	'originates from');
INSERT INTO R_RTO
	VALUES (2621442,
	2621446,
	2621453,
	0);
INSERT INTO R_OIR
	VALUES (2621442,
	2621446,
	2621453,
	0);
INSERT INTO R_FORM
	VALUES (2621448,
	2621446,
	2621454,
	1,
	1,
	'is origination of');
INSERT INTO R_RGO
	VALUES (2621448,
	2621446,
	2621454);
INSERT INTO R_OIR
	VALUES (2621448,
	2621446,
	2621454,
	0);
INSERT INTO R_SUBSUP
	VALUES (2621447);
INSERT INTO R_REL
	VALUES (2621447,
	510,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621441,
	2621447,
	2621455);
INSERT INTO R_RTO
	VALUES (2621441,
	2621447,
	2621455,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621447,
	2621455,
	0);
INSERT INTO R_SUB
	VALUES (2621450,
	2621447,
	2621456);
INSERT INTO R_RGO
	VALUES (2621450,
	2621447,
	2621456);
INSERT INTO R_OIR
	VALUES (2621450,
	2621447,
	2621456,
	0);
INSERT INTO R_SUB
	VALUES (2621451,
	2621447,
	2621457);
INSERT INTO R_RGO
	VALUES (2621451,
	2621447,
	2621457);
INSERT INTO R_OIR
	VALUES (2621451,
	2621447,
	2621457,
	0);
INSERT INTO R_ASSOC
	VALUES (2621448);
INSERT INTO R_REL
	VALUES (2621448,
	511,
	'',
	2621445);
INSERT INTO R_AONE
	VALUES (2621450,
	2621448,
	2621458,
	0,
	1,
	'');
INSERT INTO R_RTO
	VALUES (2621450,
	2621448,
	2621458,
	0);
INSERT INTO R_OIR
	VALUES (2621450,
	2621448,
	2621458,
	0);
INSERT INTO R_AOTH
	VALUES (2621442,
	2621448,
	2621459,
	1,
	1,
	'');
INSERT INTO R_RTO
	VALUES (2621442,
	2621448,
	2621459,
	0);
INSERT INTO R_OIR
	VALUES (2621442,
	2621448,
	2621459,
	0);
INSERT INTO R_ASSR
	VALUES (2621452,
	2621448,
	2621460,
	0);
INSERT INTO R_RGO
	VALUES (2621452,
	2621448,
	2621460);
INSERT INTO R_OIR
	VALUES (2621452,
	2621448,
	2621460,
	0);
INSERT INTO R_ASSOC
	VALUES (2621449);
INSERT INTO R_REL
	VALUES (2621449,
	512,
	'',
	2621445);
INSERT INTO R_AONE
	VALUES (2621451,
	2621449,
	2621461,
	0,
	1,
	'');
INSERT INTO R_RTO
	VALUES (2621451,
	2621449,
	2621461,
	0);
INSERT INTO R_OIR
	VALUES (2621451,
	2621449,
	2621461,
	0);
INSERT INTO R_AOTH
	VALUES (2621447,
	2621449,
	2621462,
	1,
	1,
	'');
INSERT INTO R_RTO
	VALUES (2621447,
	2621449,
	2621462,
	0);
INSERT INTO R_OIR
	VALUES (2621447,
	2621449,
	2621462,
	0);
INSERT INTO R_ASSR
	VALUES (2621453,
	2621449,
	2621463,
	0);
INSERT INTO R_RGO
	VALUES (2621453,
	2621449,
	2621463);
INSERT INTO R_OIR
	VALUES (2621453,
	2621449,
	2621463,
	0);
INSERT INTO R_SUBSUP
	VALUES (2621450);
INSERT INTO R_REL
	VALUES (2621450,
	513,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621454,
	2621450,
	2621464);
INSERT INTO R_RTO
	VALUES (2621454,
	2621450,
	2621464,
	0);
INSERT INTO R_OIR
	VALUES (2621454,
	2621450,
	2621464,
	0);
INSERT INTO R_SUB
	VALUES (2621452,
	2621450,
	2621465);
INSERT INTO R_RGO
	VALUES (2621452,
	2621450,
	2621465);
INSERT INTO R_OIR
	VALUES (2621452,
	2621450,
	2621465,
	0);
INSERT INTO R_SUB
	VALUES (2621453,
	2621450,
	2621466);
INSERT INTO R_RGO
	VALUES (2621453,
	2621450,
	2621466);
INSERT INTO R_OIR
	VALUES (2621453,
	2621450,
	2621466,
	0);
INSERT INTO R_SIMP
	VALUES (2621451);
INSERT INTO R_REL
	VALUES (2621451,
	514,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621455,
	2621451,
	2621467,
	0,
	0,
	'houses');
INSERT INTO R_RTO
	VALUES (2621455,
	2621451,
	2621467,
	0);
INSERT INTO R_OIR
	VALUES (2621455,
	2621451,
	2621467,
	0);
INSERT INTO R_FORM
	VALUES (2621454,
	2621451,
	2621468,
	0,
	0,
	'resides in');
INSERT INTO R_RGO
	VALUES (2621454,
	2621451,
	2621468);
INSERT INTO R_OIR
	VALUES (2621454,
	2621451,
	2621468,
	0);
INSERT INTO R_SIMP
	VALUES (2621452);
INSERT INTO R_REL
	VALUES (2621452,
	515,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621441,
	2621452,
	2621469,
	0,
	0,
	'is contained in');
INSERT INTO R_RTO
	VALUES (2621441,
	2621452,
	2621469,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621452,
	2621469,
	0);
INSERT INTO R_FORM
	VALUES (2621455,
	2621452,
	2621470,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (2621455,
	2621452,
	2621470);
INSERT INTO R_OIR
	VALUES (2621455,
	2621452,
	2621470,
	0);
INSERT INTO R_SIMP
	VALUES (2621453);
INSERT INTO R_REL
	VALUES (2621453,
	516,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621441,
	2621453,
	2621471,
	0,
	0,
	'is carried on events into');
INSERT INTO R_RTO
	VALUES (2621441,
	2621453,
	2621471,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621453,
	2621471,
	0);
INSERT INTO R_FORM
	VALUES (2621456,
	2621453,
	2621472,
	1,
	1,
	'can asynchronously communicate via');
INSERT INTO R_RGO
	VALUES (2621456,
	2621453,
	2621472);
INSERT INTO R_OIR
	VALUES (2621456,
	2621453,
	2621472,
	0);
INSERT INTO R_SUBSUP
	VALUES (2621454);
INSERT INTO R_REL
	VALUES (2621454,
	517,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621441,
	2621454,
	2621473);
INSERT INTO R_RTO
	VALUES (2621441,
	2621454,
	2621473,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621454,
	2621473,
	0);
INSERT INTO R_SUB
	VALUES (2621460,
	2621454,
	2621474);
INSERT INTO R_RGO
	VALUES (2621460,
	2621454,
	2621474);
INSERT INTO R_OIR
	VALUES (2621460,
	2621454,
	2621474,
	0);
INSERT INTO R_SUB
	VALUES (2621459,
	2621454,
	2621475);
INSERT INTO R_RGO
	VALUES (2621459,
	2621454,
	2621475);
INSERT INTO R_OIR
	VALUES (2621459,
	2621454,
	2621475,
	0);
INSERT INTO R_SIMP
	VALUES (2621455);
INSERT INTO R_REL
	VALUES (2621455,
	518,
	'',
	2621445);
INSERT INTO R_FORM
	VALUES (2621459,
	2621455,
	2621476,
	0,
	1,
	'has behavior of');
INSERT INTO R_RGO
	VALUES (2621459,
	2621455,
	2621476);
INSERT INTO R_OIR
	VALUES (2621459,
	2621455,
	2621476,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	2621455,
	2621477,
	0,
	0,
	'captures dynamics of');
INSERT INTO R_RTO
	VALUES (3145732,
	2621455,
	2621477,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	2621455,
	2621477,
	2621442);
INSERT INTO R_SIMP
	VALUES (2621456);
INSERT INTO R_REL
	VALUES (2621456,
	519,
	'',
	2621445);
INSERT INTO R_FORM
	VALUES (2621460,
	2621456,
	2621478,
	0,
	1,
	'has behavior of');
INSERT INTO R_RGO
	VALUES (2621460,
	2621456,
	2621478);
INSERT INTO R_OIR
	VALUES (2621460,
	2621456,
	2621478,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	2621456,
	2621479,
	0,
	0,
	'captures dynamics of');
INSERT INTO R_RTO
	VALUES (3145732,
	2621456,
	2621479,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	2621456,
	2621479,
	2621442);
INSERT INTO R_SIMP
	VALUES (2621457);
INSERT INTO R_REL
	VALUES (2621457,
	520,
	'The first State Model Event (SM_EVT) instance created with a particular supplemental data signature (including NULL) causes creation of an instance of Event Supplemental Data (SM_SUPDT). All subsequent events with the same supplemental data signature point to that same instance of Event Supplemental Data (SM_SUPDT).',
	2621445);
INSERT INTO R_PART
	VALUES (2621457,
	2621457,
	2621480,
	0,
	0,
	'carries');
INSERT INTO R_RTO
	VALUES (2621457,
	2621457,
	2621480,
	0);
INSERT INTO R_OIR
	VALUES (2621457,
	2621457,
	2621480,
	0);
INSERT INTO R_FORM
	VALUES (2621443,
	2621457,
	2621481,
	1,
	0,
	'defines signiture of');
INSERT INTO R_RGO
	VALUES (2621443,
	2621457,
	2621481);
INSERT INTO R_OIR
	VALUES (2621443,
	2621457,
	2621481,
	0);
INSERT INTO R_SIMP
	VALUES (2621458);
INSERT INTO R_REL
	VALUES (2621458,
	521,
	'',
	2621445);
INSERT INTO R_FORM
	VALUES (2621442,
	2621458,
	2621482,
	1,
	1,
	'is delivered by received event to');
INSERT INTO R_RGO
	VALUES (2621442,
	2621458,
	2621482);
INSERT INTO R_OIR
	VALUES (2621442,
	2621458,
	2621482,
	0);
INSERT INTO R_PART
	VALUES (2621457,
	2621458,
	2621483,
	0,
	1,
	'receives asynchronous data via');
INSERT INTO R_RTO
	VALUES (2621457,
	2621458,
	2621483,
	0);
INSERT INTO R_OIR
	VALUES (2621457,
	2621458,
	2621483,
	0);
INSERT INTO R_ASSOC
	VALUES (2621459);
INSERT INTO R_REL
	VALUES (2621459,
	522,
	'',
	2621445);
INSERT INTO R_AONE
	VALUES (2621456,
	2621459,
	2621484,
	1,
	1,
	'is made up of');
INSERT INTO R_RTO
	VALUES (2621456,
	2621459,
	2621484,
	0);
INSERT INTO R_OIR
	VALUES (2621456,
	2621459,
	2621484,
	0);
INSERT INTO R_AOTH
	VALUES (2621457,
	2621459,
	2621485,
	1,
	1,
	'makes up');
INSERT INTO R_RTO
	VALUES (2621457,
	2621459,
	2621485,
	0);
INSERT INTO R_OIR
	VALUES (2621457,
	2621459,
	2621485,
	0);
INSERT INTO R_ASSR
	VALUES (2621458,
	2621459,
	2621486,
	0);
INSERT INTO R_RGO
	VALUES (2621458,
	2621459,
	2621486);
INSERT INTO R_OIR
	VALUES (2621458,
	2621459,
	2621486,
	0);
INSERT INTO R_SIMP
	VALUES (2621460);
INSERT INTO R_REL
	VALUES (2621460,
	523,
	'',
	2621445);
INSERT INTO R_FORM
	VALUES (2621457,
	2621460,
	2621487,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (2621457,
	2621460,
	2621487);
INSERT INTO R_OIR
	VALUES (2621457,
	2621460,
	2621487,
	0);
INSERT INTO R_PART
	VALUES (2621441,
	2621460,
	2621488,
	0,
	0,
	'is assigned to');
INSERT INTO R_RTO
	VALUES (2621441,
	2621460,
	2621488,
	0);
INSERT INTO R_OIR
	VALUES (2621441,
	2621460,
	2621488,
	0);
INSERT INTO R_SIMP
	VALUES (2621461);
INSERT INTO R_REL
	VALUES (2621461,
	524,
	'',
	2621445);
INSERT INTO R_FORM
	VALUES (2621456,
	2621461,
	2621489,
	1,
	1,
	'defines the type of');
INSERT INTO R_RGO
	VALUES (2621456,
	2621461,
	2621489);
INSERT INTO R_OIR
	VALUES (2621456,
	2621461,
	2621489,
	0);
INSERT INTO R_PART
	VALUES (1048584,
	2621461,
	2621490,
	0,
	0,
	'is defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	2621461,
	2621490,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	2621461,
	2621490,
	2621441);
INSERT INTO R_SUBSUP
	VALUES (2621462);
INSERT INTO R_REL
	VALUES (2621462,
	504,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621461,
	2621462,
	2621491);
INSERT INTO R_RTO
	VALUES (2621461,
	2621462,
	2621491,
	0);
INSERT INTO R_OIR
	VALUES (2621461,
	2621462,
	2621491,
	0);
INSERT INTO R_SUB
	VALUES (2621444,
	2621462,
	2621492);
INSERT INTO R_RGO
	VALUES (2621444,
	2621462,
	2621492);
INSERT INTO R_OIR
	VALUES (2621444,
	2621462,
	2621492,
	0);
INSERT INTO R_SUB
	VALUES (2621445,
	2621462,
	2621493);
INSERT INTO R_RGO
	VALUES (2621445,
	2621462,
	2621493);
INSERT INTO R_OIR
	VALUES (2621445,
	2621462,
	2621493,
	0);
INSERT INTO R_SUB
	VALUES (2621446,
	2621462,
	2621494);
INSERT INTO R_RGO
	VALUES (2621446,
	2621462,
	2621494);
INSERT INTO R_OIR
	VALUES (2621446,
	2621462,
	2621494,
	0);
INSERT INTO R_SUBSUP
	VALUES (2621463);
INSERT INTO R_REL
	VALUES (2621463,
	525,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621443,
	2621463,
	2621495);
INSERT INTO R_RTO
	VALUES (2621443,
	2621463,
	2621495,
	1);
INSERT INTO R_OIR
	VALUES (2621443,
	2621463,
	2621495,
	0);
INSERT INTO R_SUB
	VALUES (2621462,
	2621463,
	2621496);
INSERT INTO R_RGO
	VALUES (2621462,
	2621463,
	2621496);
INSERT INTO R_OIR
	VALUES (2621462,
	2621463,
	2621496,
	0);
INSERT INTO R_SUB
	VALUES (2621463,
	2621463,
	2621497);
INSERT INTO R_RGO
	VALUES (2621463,
	2621463,
	2621497);
INSERT INTO R_OIR
	VALUES (2621463,
	2621463,
	2621497,
	0);
INSERT INTO R_SUBSUP
	VALUES (2621464);
INSERT INTO R_REL
	VALUES (2621464,
	526,
	'',
	2621445);
INSERT INTO R_SUPER
	VALUES (2621463,
	2621464,
	2621498);
INSERT INTO R_RTO
	VALUES (2621463,
	2621464,
	2621498,
	0);
INSERT INTO R_OIR
	VALUES (2621463,
	2621464,
	2621498,
	0);
INSERT INTO R_SUB
	VALUES (2621465,
	2621464,
	2621499);
INSERT INTO R_RGO
	VALUES (2621465,
	2621464,
	2621499);
INSERT INTO R_OIR
	VALUES (2621465,
	2621464,
	2621499,
	0);
INSERT INTO R_SUB
	VALUES (2621464,
	2621464,
	2621500);
INSERT INTO R_RGO
	VALUES (2621464,
	2621464,
	2621500);
INSERT INTO R_OIR
	VALUES (2621464,
	2621464,
	2621500,
	0);
INSERT INTO R_SIMP
	VALUES (2621465);
INSERT INTO R_REL
	VALUES (2621465,
	527,
	'',
	2621445);
INSERT INTO R_PART
	VALUES (2621462,
	2621465,
	2621501,
	0,
	0,
	'is defined by');
INSERT INTO R_RTO
	VALUES (2621462,
	2621465,
	2621501,
	1);
INSERT INTO R_OIR
	VALUES (2621462,
	2621465,
	2621501,
	0);
INSERT INTO R_FORM
	VALUES (2621464,
	2621465,
	2621502,
	1,
	1,
	'is aliased by');
INSERT INTO R_RGO
	VALUES (2621464,
	2621465,
	2621502);
INSERT INTO R_OIR
	VALUES (2621464,
	2621465,
	2621502,
	0);
INSERT INTO R_SIMP
	VALUES (2621466);
INSERT INTO R_REL
	VALUES (2621466,
	509,
	'',
	2621445);
INSERT INTO R_FORM
	VALUES (2621449,
	2621466,
	2621503,
	0,
	1,
	'has assigned to it');
INSERT INTO R_RGO
	VALUES (2621449,
	2621466,
	2621503);
INSERT INTO R_OIR
	VALUES (2621449,
	2621466,
	2621503,
	0);
INSERT INTO R_PART
	VALUES (2621465,
	2621466,
	2621504,
	0,
	1,
	'is assigned to');
INSERT INTO R_RTO
	VALUES (2621465,
	2621466,
	2621504,
	0);
INSERT INTO R_OIR
	VALUES (2621465,
	2621466,
	2621504,
	0);
INSERT INTO R_ASSOC
	VALUES (2621467);
INSERT INTO R_REL
	VALUES (2621467,
	503,
	'',
	2621445);
INSERT INTO R_AONE
	VALUES (2621442,
	2621467,
	2621505,
	1,
	1,
	'may be received in');
INSERT INTO R_RTO
	VALUES (2621442,
	2621467,
	2621505,
	0);
INSERT INTO R_OIR
	VALUES (2621442,
	2621467,
	2621505,
	0);
INSERT INTO R_AOTH
	VALUES (2621463,
	2621467,
	2621506,
	1,
	1,
	'receives');
INSERT INTO R_RTO
	VALUES (2621463,
	2621467,
	2621506,
	0);
INSERT INTO R_OIR
	VALUES (2621463,
	2621467,
	2621506,
	0);
INSERT INTO R_ASSR
	VALUES (2621461,
	2621467,
	2621507,
	0);
INSERT INTO R_RGO
	VALUES (2621461,
	2621467,
	2621507);
INSERT INTO R_OIR
	VALUES (2621461,
	2621467,
	2621507,
	0);
INSERT INTO S_SS
	VALUES (3145734,
	'Class',
	'

Notes:

',
	'O',
	101,
	94514,
	3145734);
INSERT INTO O_OBJ
	VALUES (3145729,
	'Transformer',
	112,
	'O_TFR',
	'A Transformer is a method associated with an Object - transformers can be synchronously called from Action Specifications.',
	3145734);
INSERT INTO O_NBATTR
	VALUES (3145729,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145729,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145729,
	3145729,
	0,
	'Tfr_ID',
	'Full Name: Transformer Identifier',
	'',
	'Tfr_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (3145729,
	3145732,
	0,
	3145773,
	3145732,
	3145735,
	3145736,
	3145730,
	3145742,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145730,
	3145729,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145730,
	3145729,
	3145729,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145731,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145731,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145731,
	3145729,
	3145730,
	'Name',
	'The name of this Transformer operation.',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145732,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145732,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145732,
	3145729,
	3145731,
	'Descrip',
	'Full Name: Transformer Description
A textual description of this Transformer operation.',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (3145729,
	1048584,
	0,
	1048643,
	3145731,
	3145734,
	3145733,
	3145733,
	3145743,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145733,
	3145729,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (3145733,
	3145729,
	3145732,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145734,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145734,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145734,
	3145729,
	3145733,
	'Instance_Based',
	'Data Domain:
0 = Class based.
1 = Instance based.',
	'',
	'Instance_Based',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145735,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145735,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145735,
	3145729,
	3145734,
	'Action_Semantics',
	'',
	'',
	'Action_Semantics',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145736,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145736,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145736,
	3145729,
	3145735,
	'Suc_Pars',
	'Full Name: Successfully Parsed

Indicates if the semantics contained in attribute ''Action_Semantics'' has been successfully parsed by ModeBuilder.

Data Domain:
0 == ''Action_Semantics'' has not been successfully parsed, and thus can not be translated. 
1 == ''Action_Semantics'' has been successfully parsed.',
	'',
	'Suc_Pars',
	0,
	524291);
INSERT INTO O_REF
	VALUES (3145729,
	4194312,
	0,
	4194380,
	4194310,
	4194316,
	4194315,
	3145737,
	3145744,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145737,
	3145729,
	4194380,
	4194312,
	1);
INSERT INTO O_ATTR
	VALUES (3145737,
	3145729,
	3145736,
	'AutID',
	'',
	'',
	'AutID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145729,
	4194313,
	0,
	4194384,
	4194311,
	4194322,
	4194321,
	3145738,
	3145745,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145738,
	3145729,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (3145738,
	3145729,
	3145737,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145739,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145739,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145739,
	3145729,
	3145738,
	'Included',
	'A flag to be used by the translation engine to indicate that this Transformer needs to be "Included" by the generated code for a state model. ',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145740,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145740,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145740,
	3145729,
	3145739,
	'XlateSemantics',
	'A flag used by the translation engine to indicate that the action semantics of this operation should be translated.',
	'',
	'XlateSemantics',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145741,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145741,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145741,
	3145729,
	3145740,
	'MaxSelfEvents',
	'',
	'',
	'MaxSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145742,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145742,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145742,
	3145729,
	3145741,
	'MaxNonSelfEvents',
	'',
	'',
	'MaxNonSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145743,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145743,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145743,
	3145729,
	3145742,
	'SelfEventCount',
	'',
	'',
	'SelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145744,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145744,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145744,
	3145729,
	3145743,
	'NonSelfEventCount',
	'',
	'',
	'NonSelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145745,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145745,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145745,
	3145729,
	3145744,
	'SelectManyCount',
	'',
	'',
	'SelectManyCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145746,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145746,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145746,
	3145729,
	3145745,
	'SelectAnyWhereCount',
	'',
	'',
	'SelectAnyWhereCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145747,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145747,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145747,
	3145729,
	3145746,
	'TimerStartCount',
	'',
	'',
	'TimerStartCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145748,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145748,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145748,
	3145729,
	3145747,
	'ReturnStmtUsed',
	'',
	'',
	'ReturnStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145749,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145749,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145749,
	3145729,
	3145748,
	'BreakStmtUsed',
	'',
	'',
	'BreakStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145750,
	3145729);
INSERT INTO O_BATTR
	VALUES (3145750,
	3145729);
INSERT INTO O_ATTR
	VALUES (3145750,
	3145729,
	3145749,
	'ContinueStmtUsed',
	'',
	'',
	'ContinueStmtUsed',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	3145729);
INSERT INTO O_OIDA
	VALUES (3145729,
	3145729,
	0);
INSERT INTO O_RTIDA
	VALUES (3145729,
	3145729,
	0,
	4718607,
	4718622);
INSERT INTO O_RTIDA
	VALUES (3145729,
	3145729,
	0,
	3145729,
	3145729);
INSERT INTO O_OBJ
	VALUES (3145730,
	'Transformer Parameter',
	113,
	'O_TPARM',
	'This object is a parameter to a transformer.',
	3145734);
INSERT INTO O_NBATTR
	VALUES (3145751,
	3145730);
INSERT INTO O_BATTR
	VALUES (3145751,
	3145730);
INSERT INTO O_ATTR
	VALUES (3145751,
	3145730,
	0,
	'TParm_ID',
	'',
	'',
	'TParm_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (3145730,
	3145729,
	0,
	3145729,
	3145729,
	3145730,
	3145729,
	3145752,
	3145746,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145752,
	3145730,
	3145729,
	3145729,
	1);
INSERT INTO O_ATTR
	VALUES (3145752,
	3145730,
	3145751,
	'Tfr_ID',
	'',
	'',
	'Tfr_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145753,
	3145730);
INSERT INTO O_BATTR
	VALUES (3145753,
	3145730);
INSERT INTO O_ATTR
	VALUES (3145753,
	3145730,
	3145752,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_REF
	VALUES (3145730,
	1048584,
	0,
	1048643,
	3145730,
	3145732,
	3145731,
	3145754,
	3145747,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145754,
	3145730,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (3145754,
	3145730,
	3145753,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145755,
	3145730);
INSERT INTO O_BATTR
	VALUES (3145755,
	3145730);
INSERT INTO O_ATTR
	VALUES (3145755,
	3145730,
	3145754,
	'By_Ref',
	'Full Name: Pass Parameter By Reference

When a parameter is defined as pass by reference, the parameter may be written to in the application BPAL (BP V5.0 or greater).

Data Domain:
0 == Pass by "value" (or const &)
1 == Pass by "reference"
',
	'',
	'By_Ref',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145756,
	3145730);
INSERT INTO O_BATTR
	VALUES (3145756,
	3145730);
INSERT INTO O_ATTR
	VALUES (3145756,
	3145730,
	3145755,
	'Order',
	'Attribute provided for the translation engine to specify a relative order in which instances of Transformer Parameter need to be processed. ',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145757,
	3145730);
INSERT INTO O_BATTR
	VALUES (3145757,
	3145730);
INSERT INTO O_ATTR
	VALUES (3145757,
	3145730,
	3145756,
	'ParamBuffer',
	'A string buffer provided for the translation engine to hold intermediate code fragments when processing a parameter list (e.g., fragment generation ''param_*'' functions.',
	'',
	'ParamBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718666,
	3145730);
INSERT INTO O_BATTR
	VALUES (4718666,
	3145730);
INSERT INTO O_ATTR
	VALUES (4718666,
	3145730,
	3145757,
	'OALParamBuffer',
	'',
	'',
	'OALParamBuffer',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	3145730);
INSERT INTO O_OIDA
	VALUES (3145751,
	3145730,
	0);
INSERT INTO O_RTIDA
	VALUES (3145751,
	3145730,
	0,
	4718608,
	4718623);
INSERT INTO O_OBJ
	VALUES (3145731,
	'Attribute',
	103,
	'O_ATTR',
	'An Attribute is an abstraction of a single characteristic possessed by an Object.  Usually Objects contain a set of attributes to completely capture all pertinent information.  Each Attribute is given a unique name within an Object.',
	3145734);
INSERT INTO O_NBATTR
	VALUES (3145758,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145758,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145758,
	3145731,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (3145731,
	3145732,
	0,
	3145773,
	3145733,
	3145737,
	3145738,
	3145759,
	3145748,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (3145731,
	3145731,
	0,
	3145759,
	3145734,
	3145740,
	3145739,
	3145759,
	3145749,
	3145748,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145759,
	3145731,
	3145773,
	3145732,
	0);
INSERT INTO O_ATTR
	VALUES (3145759,
	3145731,
	3145758,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145731,
	3145731,
	0,
	3145758,
	3145734,
	3145740,
	3145739,
	3145760,
	3145750,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145760,
	3145731,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145760,
	3145731,
	3145759,
	'PAttr_ID',
	'',
	'P',
	'Attr_ID',
	1,
	524296);
INSERT INTO O_DBATTR
	VALUES (3145761,
	3145731,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (3145761,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145761,
	3145731,
	3145760,
	'Name',
	'The name of the object attribute as it appears on the OIM of the application analysis domain.

The name of the object attribute is mathematically derived from ''O_ATTR.Root_Nam'', ''O_ATTR.Prefix'', and ''O_ATTR.Prx_Mode''.',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145762,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145762,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145762,
	3145731,
	3145761,
	'Descrip',
	'A textual description of the object attribute as specified in the application analysis domain.',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145763,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145763,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145763,
	3145731,
	3145762,
	'Prefix',
	'',
	'',
	'Prefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145764,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145764,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145764,
	3145731,
	3145763,
	'Root_Nam',
	'',
	'',
	'Root_Nam',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145765,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145765,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145765,
	3145731,
	3145764,
	'Pfx_Mode',
	'Full Name: Prefix Mode

Data Domain:
0 = uses no prefix
1 = uses local prefix
2 = uses referred to prefix',
	'',
	'Pfx_Mode',
	0,
	524291);
INSERT INTO O_REF
	VALUES (3145731,
	1048584,
	0,
	1048643,
	3145735,
	3145742,
	3145741,
	3145766,
	3145751,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145766,
	3145731,
	1048643,
	1048584,
	1);
INSERT INTO O_ATTR
	VALUES (3145766,
	3145731,
	3145765,
	'DT_ID',
	'',
	'',
	'DT_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145767,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145767,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145767,
	3145731,
	3145766,
	'Used',
	'A flag to indicate to the translation engine that this attribute is used (either read from or written to) in the application analysis action language. If TRUE, the attribute is accessed in the BPAL. If FALSE, the attribute is never accessed.

Note that this attribute must be set (to TRUE) by a first pass fragment generation process. The default value is FALSE. In a multi-pass fragment generation architecture, no storage will be generated for attributes which are never accessed (in particular, referential attributes).',
	'',
	'Used',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145768,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145768,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145768,
	3145731,
	3145767,
	'AssignUsed',
	'',
	'',
	'AssignUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145769,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145769,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145769,
	3145731,
	3145768,
	'Included',
	'A general purpose flag which may be used by the translation engine to indicate that this object attribute is ''included'' in a translation algorithm.',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145770,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145770,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145770,
	3145731,
	3145769,
	'Order',
	'A value used by the translation engine to indicate a (transient) relative ordering of ''Attribute'' instances during code generation.',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145771,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145771,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145771,
	3145731,
	3145770,
	'ParamBuffer',
	'A string buffer provided for the translation engine to hold intermediate code fragments when processing a parameter list (e.g., fragment generation ''param_*'' functions.',
	'',
	'ParamBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145772,
	3145731);
INSERT INTO O_BATTR
	VALUES (3145772,
	3145731);
INSERT INTO O_ATTR
	VALUES (3145772,
	3145731,
	4718665,
	'Persistent',
	'A flag indicating if this attribute is colored as persistent. A value of TRUE indicates the attribute is presistent. A value of FALSE indicates the attribute is transient. This flag is for use by architectures that support coloring of  persistence at a per attribute boundary.',
	'',
	'Persistent',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718665,
	3145731);
INSERT INTO O_BATTR
	VALUES (4718665,
	3145731);
INSERT INTO O_ATTR
	VALUES (4718665,
	3145731,
	3145771,
	'OALParamBuffer',
	'',
	'',
	'OALParamBuffer',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	3145731);
INSERT INTO O_OIDA
	VALUES (3145759,
	3145731,
	0);
INSERT INTO O_RTIDA
	VALUES (3145759,
	3145731,
	0,
	3145736,
	3145743);
INSERT INTO O_RTIDA
	VALUES (3145759,
	3145731,
	0,
	2097171,
	2097193);
INSERT INTO O_RTIDA
	VALUES (3145759,
	3145731,
	0,
	3145741,
	3145755);
INSERT INTO O_RTIDA
	VALUES (3145759,
	3145731,
	0,
	3145734,
	3145739);
INSERT INTO O_RTIDA
	VALUES (3145759,
	3145731,
	0,
	4718605,
	4718618);
INSERT INTO O_OIDA
	VALUES (3145758,
	3145731,
	0);
INSERT INTO O_RTIDA
	VALUES (3145758,
	3145731,
	0,
	3145741,
	3145755);
INSERT INTO O_RTIDA
	VALUES (3145758,
	3145731,
	0,
	4718605,
	4718618);
INSERT INTO O_RTIDA
	VALUES (3145758,
	3145731,
	0,
	2097171,
	2097193);
INSERT INTO O_RTIDA
	VALUES (3145758,
	3145731,
	0,
	3145734,
	3145739);
INSERT INTO O_RTIDA
	VALUES (3145758,
	3145731,
	0,
	3145736,
	3145743);
INSERT INTO O_OBJ
	VALUES (3145732,
	'Class',
	101,
	'O_OBJ',
	'An Object represents an abstraction of a real world thing.  All instances of an Object have the same characteristics and comform to the same set of rules.  The characteristics of an Object are captured as attributes.  Each Object within a Domain are assigned a unique name, number, and keyletter.',
	3145734);
INSERT INTO O_NBATTR
	VALUES (3145773,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145773,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145773,
	3145732,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (3145774,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145774,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145774,
	3145732,
	3145773,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145775,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145775,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145775,
	3145732,
	3145774,
	'Numb',
	'',
	'',
	'Numb',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145776,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145776,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145776,
	3145732,
	3145775,
	'Key_Lett',
	'',
	'',
	'Key_Lett',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145777,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145777,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145777,
	3145732,
	3145776,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_REF
	VALUES (3145732,
	1048578,
	0,
	1048594,
	1048594,
	1048615,
	1048614,
	3145778,
	3145729,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145778,
	3145732,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (3145778,
	3145732,
	3145777,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145779,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145779,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145779,
	3145732,
	3145778,
	'Included',
	'',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145780,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145780,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145780,
	3145732,
	3145779,
	'IsBridgeObject',
	'If TRUE, this object is a Funky Bridge Object (FBO). False otherwise.',
	'',
	'IsBridgeObject',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145781,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145781,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145781,
	3145732,
	3145780,
	'IsInitObject',
	'If TRUE, this object is an initialization object. FALSE otherwise.',
	'',
	'IsInitObject',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145782,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145782,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145782,
	3145732,
	3145781,
	'IsAsyncObject',
	'',
	'',
	'IsAsyncObject',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145783,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145783,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145783,
	3145732,
	4718660,
	'IsStaticPopulate',
	'',
	'',
	'IsStaticPopulate',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145784,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145784,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145784,
	3145732,
	3145783,
	'IsReadOnly',
	'',
	'',
	'IsReadOnly',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145785,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145785,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145785,
	3145732,
	3145784,
	'StaticExtentSize',
	'',
	'',
	'StaticExtentSize',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145786,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145786,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145786,
	3145732,
	3145785,
	'ExcludeFromGen',
	'Full Name: Exclude From Code Generation.
A flag to indicate that an object has been ''colored out'' from code generation.
FALSE indicates that the object is not excluded, and code will be generated for the object. TRUE indicates the object is excluded, and no code will be generated for it.',
	'',
	'ExcludeFromGen',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145787,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145787,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145787,
	3145732,
	3145786,
	'MaxExtentSize',
	'The maximum number of instance allowed in a fixed allocation architecture. If zero (0), instances are dynamically allocated.',
	'',
	'MaxExtentSize',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145788,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145788,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145788,
	3145732,
	3145787,
	'SelfCreated',
	'A flag used by the translation engine to indicate that this object is self created (formerly "asynchronous creation") in the action language of the application analysis domain. If TRUE, there is at least one creation event generated towards this object in the domains action langauge.
',
	'',
	'SelfCreated',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145789,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145789,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145789,
	3145732,
	3145788,
	'NonSelfCreated',
	'A flag used by the translation engine to indicate that this object is created by non-self (formerly "synchronous creation") in the action language of the application analysis domain.',
	'',
	'NonSelfCreated',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145790,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145790,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145790,
	3145732,
	3145789,
	'DeleteAccessor',
	'A flag used by the translation engine to indictate that an instance deletion accessor is needed for the implementation of this object. If TRUE, this object may be deleted by the application analysis action language. If FALSE, this object may be created, but is not deleted, during the application life cycle.',
	'',
	'DeleteAccessor',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145791,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145791,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145791,
	3145732,
	4718661,
	'ExtendedSetOps',
	'A flag used by the translation engine to indicate if "extended operations" on variables of type inst_ref_set<Object>, such as set(in)equality comparisons, need to be supported. ',
	'',
	'ExtendedSetOps',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145792,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145792,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145792,
	3145732,
	3145791,
	'Persistent',
	'This is a coloring attribute for specifying object level persistence. If TRUE, the generated code will support instance level persistence. If FALSE (default), all instances of the object will be transient.',
	'',
	'Persistent',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145793,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145793,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145793,
	3145732,
	3145792,
	'Order',
	'This attribute is provided to allow the archetypes to sort a collection of Object  instance in a particular order. For example, sorting an instance reference set of objects in ascending order relative to the Object.Num attribute.

A utlity attribute for the archetypes to specify a particular order of the subsystems in the domain. 
This attribute is a "work around" until the archetype language supports an "ORDERED BY" clause.
',
	'',
	'Order',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145794,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145794,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145794,
	3145732,
	3145793,
	'IsTrace',
	'',
	'',
	'IsTrace',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145795,
	3145732);
INSERT INTO O_BATTR
	VALUES (3145795,
	3145732);
INSERT INTO O_ATTR
	VALUES (3145795,
	3145732,
	3145794,
	'IsSynchronizedSelfEvent',
	'',
	'',
	'IsSynchronizedSelfEvent',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718659,
	3145732);
INSERT INTO O_BATTR
	VALUES (4718659,
	3145732);
INSERT INTO O_ATTR
	VALUES (4718659,
	3145732,
	3145782,
	'PEIsDefinedInData',
	'',
	'',
	'PEIsDefinedInData',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718660,
	3145732);
INSERT INTO O_BATTR
	VALUES (4718660,
	3145732);
INSERT INTO O_ATTR
	VALUES (4718660,
	3145732,
	4718659,
	'IsFixedPopulation',
	'',
	'',
	'IsFixedPopulation',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718661,
	3145732);
INSERT INTO O_BATTR
	VALUES (4718661,
	3145732);
INSERT INTO O_ATTR
	VALUES (4718661,
	3145732,
	3145790,
	'CreateAccessor',
	'',
	'',
	'CreateAccessor',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718662,
	3145732);
INSERT INTO O_BATTR
	VALUES (4718662,
	3145732);
INSERT INTO O_ATTR
	VALUES (4718662,
	3145732,
	3145795,
	'Include_File',
	'',
	'',
	'Include_File',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718663,
	3145732);
INSERT INTO O_BATTR
	VALUES (4718663,
	3145732);
INSERT INTO O_ATTR
	VALUES (4718663,
	3145732,
	4718662,
	'ContainerIndex',
	'',
	'',
	'ContainerIndex',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718664,
	3145732);
INSERT INTO O_BATTR
	VALUES (4718664,
	3145732);
INSERT INTO O_ATTR
	VALUES (4718664,
	3145732,
	4718663,
	'Task',
	'',
	'',
	'Task',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	3145732);
INSERT INTO O_OIDA
	VALUES (3145773,
	3145732,
	0);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	2621455,
	2621477);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	3145732,
	3145736);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	2097169,
	2097189);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	4194315,
	4194335);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	2621456,
	2621479);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	3145733,
	3145738);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	3145743,
	3145760);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	4718604,
	4718616);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	1572865,
	1572866);
INSERT INTO O_RTIDA
	VALUES (3145773,
	3145732,
	0,
	3145742,
	3145759);
INSERT INTO O_ID
	VALUES (1,
	3145732);
INSERT INTO O_OIDA
	VALUES (3145776,
	3145732,
	1);
INSERT INTO O_RTIDA
	VALUES (3145776,
	3145732,
	1,
	4194305,
	4194305);
INSERT INTO O_OBJ
	VALUES (3145733,
	'Base Attribute',
	106,
	'O_BATTR',
	'A Base Attribute is a non-referential attribute.',
	3145734);
INSERT INTO O_REF
	VALUES (3145733,
	3145731,
	0,
	3145758,
	3145736,
	3145744,
	3145743,
	3145796,
	3145730,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145796,
	3145733,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145796,
	3145733,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145733,
	3145731,
	0,
	3145759,
	3145736,
	3145744,
	3145743,
	3145797,
	3145731,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145797,
	3145733,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145797,
	3145733,
	3145796,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	3145733);
INSERT INTO O_OIDA
	VALUES (3145797,
	3145733,
	0);
INSERT INTO O_RTIDA
	VALUES (3145797,
	3145733,
	0,
	3145737,
	3145746);
INSERT INTO O_RTIDA
	VALUES (3145797,
	3145733,
	0,
	3145738,
	3145748);
INSERT INTO O_OIDA
	VALUES (3145796,
	3145733,
	0);
INSERT INTO O_RTIDA
	VALUES (3145796,
	3145733,
	0,
	3145737,
	3145746);
INSERT INTO O_RTIDA
	VALUES (3145796,
	3145733,
	0,
	3145738,
	3145748);
INSERT INTO O_OBJ
	VALUES (3145734,
	'Referential Attribute ',
	109,
	'O_RATTR',
	'A Referential Attribute captures the formalization of a relationship.  A Referential Attribute refers to an Identifying Attribute in the Object at the other end of the rrelationship which it formalizes.',
	3145734);
INSERT INTO O_REF
	VALUES (3145734,
	3145731,
	0,
	3145758,
	3145736,
	3145745,
	3145743,
	3145798,
	3145732,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145798,
	3145734,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145798,
	3145734,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145734,
	3145731,
	0,
	3145759,
	3145736,
	3145745,
	3145743,
	3145799,
	3145733,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145799,
	3145734,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145799,
	3145734,
	3145798,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145734,
	3145733,
	0,
	3145796,
	3145737,
	3145747,
	3145746,
	3145800,
	3145752,
	0,
	1,
	'');
INSERT INTO O_RATTR
	VALUES (3145800,
	3145734,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145800,
	3145734,
	3145799,
	'BAttr_ID',
	'Reference IS CONSTRAINED such that Base Attribute related across R113 is same Base Attribute which is found by navigating back through the referred to attributes until Base Attribute is found.',
	'B',
	'Attr_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (3145734,
	3145733,
	0,
	3145797,
	3145737,
	3145747,
	3145746,
	3145801,
	3145753,
	0,
	1,
	'');
INSERT INTO O_RATTR
	VALUES (3145801,
	3145734,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145801,
	3145734,
	3145800,
	'BObj_ID',
	'Reference IS CONSTRAINED such that Base Attribute related across R113 is same Base Attribute which is found by navigating back through the referred to attributes until Base Attribute is found.',
	'B',
	'Obj_ID',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145802,
	3145734);
INSERT INTO O_BATTR
	VALUES (3145802,
	3145734);
INSERT INTO O_ATTR
	VALUES (3145802,
	3145734,
	3145801,
	'Ref_Mode',
	'',
	'',
	'Ref_Mode',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	3145734);
INSERT INTO O_OIDA
	VALUES (3145799,
	3145734,
	0);
INSERT INTO O_RTIDA
	VALUES (3145799,
	3145734,
	0,
	3145739,
	3145752);
INSERT INTO O_OIDA
	VALUES (3145798,
	3145734,
	0);
INSERT INTO O_RTIDA
	VALUES (3145798,
	3145734,
	0,
	3145739,
	3145752);
INSERT INTO O_OBJ
	VALUES (3145735,
	'Derived Based Attribute',
	107,
	'O_DBATTR',
	'A Derived Attribute is the result of an algorithm used to derive the value.',
	3145734);
INSERT INTO O_REF
	VALUES (3145735,
	3145733,
	0,
	3145796,
	3145738,
	3145749,
	3145748,
	3145803,
	3145734,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145803,
	3145735,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145803,
	3145735,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145735,
	3145733,
	0,
	3145797,
	3145738,
	3145749,
	3145748,
	3145804,
	3145735,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145804,
	3145735,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145804,
	3145735,
	3145803,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145805,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145805,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145805,
	3145735,
	3145804,
	'Action_Semantics',
	'',
	'',
	'Action_Semantics',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3145806,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145806,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145806,
	3145735,
	3145805,
	'Suc_Pars',
	'',
	'',
	'Suc_Pars',
	0,
	524291);
INSERT INTO O_REF
	VALUES (3145735,
	4194312,
	0,
	4194380,
	4194310,
	4194320,
	4194315,
	3145807,
	3145754,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145807,
	3145735,
	4194380,
	4194312,
	1);
INSERT INTO O_ATTR
	VALUES (3145807,
	3145735,
	3145806,
	'AutID',
	'',
	'',
	'AutID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145735,
	4194313,
	0,
	4194384,
	4194311,
	4194324,
	4194321,
	3145808,
	3145755,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145808,
	3145735,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (3145808,
	3145735,
	3145807,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145809,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145809,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145809,
	3145735,
	3145808,
	'Included',
	'',
	'',
	'Included',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145810,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145810,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145810,
	3145735,
	3145809,
	'SelfEventCount',
	'',
	'',
	'SelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145811,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145811,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145811,
	3145735,
	3145810,
	'NonSelfEventCount',
	'',
	'',
	'NonSelfEventCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145812,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145812,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145812,
	3145735,
	3145811,
	'SelectManyCount',
	'',
	'',
	'SelectManyCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145813,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145813,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145813,
	3145735,
	3145812,
	'SelectAnyWhereCount',
	'',
	'',
	'SelectAnyWhereCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145814,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145814,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145814,
	3145735,
	3145813,
	'TimerStartCount',
	'',
	'',
	'TimerStartCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3145815,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145815,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145815,
	3145735,
	3145814,
	'ReturnStmtUsed',
	'',
	'',
	'ReturnStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145816,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145816,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145816,
	3145735,
	3145815,
	'BreakStmtUsed',
	'',
	'',
	'BreakStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145817,
	3145735);
INSERT INTO O_BATTR
	VALUES (3145817,
	3145735);
INSERT INTO O_ATTR
	VALUES (3145817,
	3145735,
	3145816,
	'ContinueStmtUsed',
	'',
	'',
	'ContinueStmtUsed',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	3145735);
INSERT INTO O_OIDA
	VALUES (3145804,
	3145735,
	0);
INSERT INTO O_OIDA
	VALUES (3145803,
	3145735,
	0);
INSERT INTO O_OBJ
	VALUES (3145736,
	'New Base Attribute ',
	108,
	'O_NBATTR',
	'A New Base Attribute is a non-derived base attribute.',
	3145734);
INSERT INTO O_REF
	VALUES (3145736,
	3145733,
	0,
	3145796,
	3145738,
	3145750,
	3145748,
	3145818,
	3145736,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145818,
	3145736,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145818,
	3145736,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145736,
	3145733,
	0,
	3145797,
	3145738,
	3145750,
	3145748,
	3145819,
	3145737,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145819,
	3145736,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145819,
	3145736,
	3145818,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	3145736);
INSERT INTO O_OIDA
	VALUES (3145819,
	3145736,
	0);
INSERT INTO O_OIDA
	VALUES (3145818,
	3145736,
	0);
INSERT INTO O_OBJ
	VALUES (3145737,
	'Attribute Reference in Object ',
	110,
	'O_REF',
	'The Object represents an R# which follows a referential attribute.',
	3145734);
INSERT INTO O_REF
	VALUES (3145737,
	3145734,
	0,
	3145799,
	3145739,
	3145751,
	3145752,
	3145820,
	3145738,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (3145737,
	1572881,
	0,
	1572936,
	3145746,
	3145769,
	3145767,
	3145820,
	3145756,
	3145738,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145820,
	3145737,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145820,
	3145737,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	3145741,
	0,
	3145845,
	3145746,
	3145769,
	3145768,
	3145821,
	3145757,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145821,
	3145737,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145821,
	3145737,
	3145820,
	'RObj_ID',
	'',
	'R',
	'Obj_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	3145741,
	0,
	3145846,
	3145746,
	3145769,
	3145768,
	3145822,
	3145758,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145822,
	3145737,
	3145832,
	3145738,
	1);
INSERT INTO O_ATTR
	VALUES (3145822,
	3145737,
	3145821,
	'ROid_ID',
	'',
	'R',
	'Oid_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	3145741,
	0,
	3145844,
	3145746,
	3145769,
	3145768,
	3145823,
	3145759,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145823,
	3145737,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145823,
	3145737,
	3145822,
	'RAttr_ID',
	'',
	'R',
	'Attr_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	1572881,
	0,
	1572937,
	3145746,
	3145769,
	3145767,
	3145824,
	3145760,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (3145737,
	3145741,
	0,
	3145847,
	3145746,
	3145769,
	3145768,
	3145824,
	3145761,
	3145760,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145824,
	3145737,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (3145824,
	3145737,
	3145823,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	1572881,
	0,
	1572938,
	3145746,
	3145769,
	3145767,
	3145825,
	3145762,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145825,
	3145737,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (3145825,
	3145737,
	3145824,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	3145741,
	0,
	3145848,
	3145746,
	3145769,
	3145768,
	3145826,
	3145763,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145826,
	3145737,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (3145826,
	3145737,
	3145825,
	'ROIR_ID',
	'',
	'R',
	'OIR_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (3145737,
	3145734,
	0,
	3145798,
	3145739,
	3145751,
	3145752,
	3145827,
	3145739,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145827,
	3145737,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145827,
	3145737,
	3145826,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145828,
	3145737);
INSERT INTO O_BATTR
	VALUES (3145828,
	3145737);
INSERT INTO O_ATTR
	VALUES (3145828,
	3145737,
	3145827,
	'ARef_ID',
	'',
	'',
	'ARef_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (3145737,
	3145737,
	1,
	3145828,
	3145740,
	3145754,
	3145753,
	3145829,
	3145764,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145829,
	3145737,
	3145828,
	3145737,
	1);
INSERT INTO O_ATTR
	VALUES (3145829,
	3145737,
	3145828,
	'PARef_ID',
	'',
	'P',
	'ARef_ID',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145830,
	3145737);
INSERT INTO O_BATTR
	VALUES (3145830,
	3145737);
INSERT INTO O_ATTR
	VALUES (3145830,
	3145737,
	3145829,
	'Is_Cstrd',
	'Full Name:

FLASE = not constained
TRUE = constained',
	'',
	'Is_Cstrd',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3145831,
	3145737);
INSERT INTO O_BATTR
	VALUES (3145831,
	3145737);
INSERT INTO O_ATTR
	VALUES (3145831,
	3145737,
	3145830,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	3145737);
INSERT INTO O_OIDA
	VALUES (3145822,
	3145737,
	0);
INSERT INTO O_OIDA
	VALUES (3145820,
	3145737,
	0);
INSERT INTO O_OIDA
	VALUES (3145823,
	3145737,
	0);
INSERT INTO O_OIDA
	VALUES (3145824,
	3145737,
	0);
INSERT INTO O_OIDA
	VALUES (3145825,
	3145737,
	0);
INSERT INTO O_OIDA
	VALUES (3145826,
	3145737,
	0);
INSERT INTO O_OIDA
	VALUES (3145821,
	3145737,
	0);
INSERT INTO O_ID
	VALUES (1,
	3145737);
INSERT INTO O_OIDA
	VALUES (3145828,
	3145737,
	1);
INSERT INTO O_RTIDA
	VALUES (3145828,
	3145737,
	1,
	3145740,
	3145753);
INSERT INTO O_OBJ
	VALUES (3145738,
	'Class Identifier',
	104,
	'O_ID',
	'A set of one or more Attributes which uniquely distinguishes each instance of an object is an Object Identifier.  An Object may have several Identifiers.',
	3145734);
INSERT INTO O_NBATTR
	VALUES (3145832,
	3145738);
INSERT INTO O_BATTR
	VALUES (3145832,
	3145738);
INSERT INTO O_ATTR
	VALUES (3145832,
	3145738,
	0,
	'Oid_ID',
	'The identifying attribute set number.

0 = Primary Identifer Set (e.g., *)
1 = Secondary Identifier Set (e.g., *2)
2 = Third Identifier Set (e.g., *3)',
	'',
	'Oid_ID',
	0,
	524291);
INSERT INTO O_REF
	VALUES (3145738,
	3145732,
	0,
	3145773,
	3145742,
	3145758,
	3145759,
	3145833,
	3145740,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145833,
	3145738,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145833,
	3145738,
	3145832,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145834,
	3145738);
INSERT INTO O_BATTR
	VALUES (3145834,
	3145738);
INSERT INTO O_ATTR
	VALUES (3145834,
	3145738,
	3145833,
	'WhereKey',
	'A flag used by the translation engine to indicate that this object identifier set is used as a ''where clause'' specification in the action language of the application analysis.',
	'',
	'WhereKey',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	3145738);
INSERT INTO O_OIDA
	VALUES (3145833,
	3145738,
	0);
INSERT INTO O_RTIDA
	VALUES (3145833,
	3145738,
	0,
	3145741,
	3145756);
INSERT INTO O_RTIDA
	VALUES (3145833,
	3145738,
	0,
	3145745,
	3145765);
INSERT INTO O_OIDA
	VALUES (3145832,
	3145738,
	0);
INSERT INTO O_RTIDA
	VALUES (3145832,
	3145738,
	0,
	3145741,
	3145756);
INSERT INTO O_RTIDA
	VALUES (3145832,
	3145738,
	0,
	3145745,
	3145765);
INSERT INTO O_OBJ
	VALUES (3145739,
	'Class Identifier Attribute ',
	105,
	'O_OIDA',
	'An Attribute that is part of ab Object Identifier is an Object Identifier Attribute.',
	3145734);
INSERT INTO O_REF
	VALUES (3145739,
	3145731,
	0,
	3145758,
	3145741,
	3145757,
	3145755,
	3145835,
	3145765,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145835,
	3145739,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145835,
	3145739,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145739,
	3145738,
	0,
	3145833,
	3145741,
	3145757,
	3145756,
	3145836,
	3145766,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (3145739,
	3145731,
	0,
	3145759,
	3145741,
	3145757,
	3145755,
	3145836,
	3145767,
	3145766,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145836,
	3145739,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145836,
	3145739,
	3145835,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145739,
	3145738,
	0,
	3145832,
	3145741,
	3145757,
	3145756,
	3145837,
	3145768,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145837,
	3145739,
	3145832,
	3145738,
	1);
INSERT INTO O_ATTR
	VALUES (3145837,
	3145739,
	3145836,
	'Oid_ID',
	'',
	'',
	'Oid_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	3145739);
INSERT INTO O_OIDA
	VALUES (3145837,
	3145739,
	0);
INSERT INTO O_RTIDA
	VALUES (3145837,
	3145739,
	0,
	3145744,
	3145763);
INSERT INTO O_OIDA
	VALUES (3145835,
	3145739,
	0);
INSERT INTO O_RTIDA
	VALUES (3145835,
	3145739,
	0,
	3145744,
	3145763);
INSERT INTO O_OIDA
	VALUES (3145836,
	3145739,
	0);
INSERT INTO O_RTIDA
	VALUES (3145836,
	3145739,
	0,
	3145744,
	3145763);
INSERT INTO O_OBJ
	VALUES (3145740,
	'Imported Class',
	102,
	'O_IOBJ',
	'Objects can have interactions with Objects in other Subsystems.  In order to capture these spanning interactions, Objects can be imported into another subsystem.  Spanning interactions can be relationships, event communications, or data accesses and are captured in Object Information Model, Object Communication Model, and Object Access Model, respectively.  Spanning interactions provide the data for derivation of the Subsystem Relationship Model, Subsystem Communication Model, and Subsystem Access Model.',
	3145734);
INSERT INTO O_NBATTR
	VALUES (3145838,
	3145740);
INSERT INTO O_BATTR
	VALUES (3145838,
	3145740);
INSERT INTO O_ATTR
	VALUES (3145838,
	3145740,
	0,
	'IObj_ID',
	'',
	'',
	'IObj_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (3145740,
	3145732,
	0,
	3145773,
	3145743,
	3145761,
	3145760,
	3145839,
	3145769,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145839,
	3145740,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145839,
	3145740,
	3145838,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (3145840,
	3145740);
INSERT INTO O_BATTR
	VALUES (3145840,
	3145740);
INSERT INTO O_ATTR
	VALUES (3145840,
	3145740,
	3145839,
	'Modl_Typ',
	'Value indicates what type of model the Imported Object is in:
Value 5 indicates Object Information Model
Value 6 indicates Object Communication Model
Value 7 indicates Object Access Model',
	'',
	'Modl_Typ',
	0,
	524291);
INSERT INTO O_REF
	VALUES (3145740,
	1048578,
	0,
	1048594,
	1048598,
	1048623,
	1048622,
	3145841,
	3145741,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145841,
	3145740,
	1048594,
	1048578,
	1);
INSERT INTO O_ATTR
	VALUES (3145841,
	3145740,
	3145840,
	'SS_ID',
	'',
	'',
	'SS_ID',
	0,
	524296);
INSERT INTO O_DBATTR
	VALUES (3145842,
	3145740,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (3145842,
	3145740);
INSERT INTO O_ATTR
	VALUES (3145842,
	3145740,
	3145841,
	'Obj_Name',
	'',
	'',
	'Obj_Name',
	0,
	524293);
INSERT INTO O_DBATTR
	VALUES (3145843,
	3145740,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (3145843,
	3145740);
INSERT INTO O_ATTR
	VALUES (3145843,
	3145740,
	3145842,
	'Obj_KL',
	'',
	'',
	'Obj_KL',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	3145740);
INSERT INTO O_OIDA
	VALUES (3145838,
	3145740,
	0);
INSERT INTO O_RTIDA
	VALUES (3145838,
	3145740,
	0,
	1572879,
	1572905);
INSERT INTO O_RTIDA
	VALUES (3145838,
	3145740,
	0,
	2097166,
	2097181);
INSERT INTO O_RTIDA
	VALUES (3145838,
	3145740,
	0,
	2097176,
	2097203);
INSERT INTO O_RTIDA
	VALUES (3145838,
	3145740,
	0,
	2097172,
	2097194);
INSERT INTO O_RTIDA
	VALUES (3145838,
	3145740,
	0,
	2097177,
	2097204);
INSERT INTO O_OBJ
	VALUES (3145741,
	'Referred To Identifier Attribute ',
	111,
	'O_RTIDA',
	'This object serves a linkage betwwen R# (Attribute Reference in Object ) and the referred to Object Identifier Attribute.',
	3145734);
INSERT INTO O_REF
	VALUES (3145741,
	3145739,
	0,
	3145835,
	3145744,
	3145764,
	3145763,
	3145844,
	3145770,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145844,
	3145741,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (3145844,
	3145741,
	0,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145741,
	1572880,
	1,
	1572931,
	3145744,
	3145764,
	3145762,
	3145845,
	3145771,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (3145741,
	3145739,
	0,
	3145836,
	3145744,
	3145764,
	3145763,
	3145845,
	3145772,
	3145771,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145845,
	3145741,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (3145845,
	3145741,
	3145844,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145741,
	1572880,
	1,
	1572934,
	3145744,
	3145764,
	3145762,
	3145846,
	3145773,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (3145741,
	3145739,
	0,
	3145837,
	3145744,
	3145764,
	3145763,
	3145846,
	3145774,
	3145773,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145846,
	3145741,
	3145832,
	3145738,
	1);
INSERT INTO O_ATTR
	VALUES (3145846,
	3145741,
	3145845,
	'Oid_ID',
	'',
	'',
	'Oid_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145741,
	1572880,
	1,
	1572932,
	3145744,
	3145764,
	3145762,
	3145847,
	3145775,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145847,
	3145741,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (3145847,
	3145741,
	3145846,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (3145741,
	1572880,
	1,
	1572933,
	3145744,
	3145764,
	3145762,
	3145848,
	3145776,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (3145848,
	3145741,
	1572929,
	1572879,
	1);
INSERT INTO O_ATTR
	VALUES (3145848,
	3145741,
	3145847,
	'OIR_ID',
	'',
	'',
	'OIR_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	3145741);
INSERT INTO O_OIDA
	VALUES (3145846,
	3145741,
	0);
INSERT INTO O_RTIDA
	VALUES (3145846,
	3145741,
	0,
	3145746,
	3145768);
INSERT INTO O_OIDA
	VALUES (3145844,
	3145741,
	0);
INSERT INTO O_RTIDA
	VALUES (3145844,
	3145741,
	0,
	3145746,
	3145768);
INSERT INTO O_OIDA
	VALUES (3145845,
	3145741,
	0);
INSERT INTO O_RTIDA
	VALUES (3145845,
	3145741,
	0,
	3145746,
	3145768);
INSERT INTO O_OIDA
	VALUES (3145848,
	3145741,
	0);
INSERT INTO O_RTIDA
	VALUES (3145848,
	3145741,
	0,
	3145746,
	3145768);
INSERT INTO O_OIDA
	VALUES (3145847,
	3145741,
	0);
INSERT INTO O_RTIDA
	VALUES (3145847,
	3145741,
	0,
	3145746,
	3145768);
INSERT INTO O_IOBJ
	VALUES (3145729,
	1048584,
	5,
	3145734,
	'Data Type',
	'S_DT');
INSERT INTO O_IOBJ
	VALUES (3145730,
	1572880,
	5,
	3145734,
	'Referred To Object in Rel',
	'R_RTO');
INSERT INTO O_IOBJ
	VALUES (3145731,
	1572881,
	5,
	3145734,
	'Referring Object In Rel',
	'R_RGO');
INSERT INTO R_SIMP
	VALUES (3145729);
INSERT INTO R_REL
	VALUES (3145729,
	117,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (3145729,
	3145729,
	3145729,
	0,
	0,
	'is part of ');
INSERT INTO R_RTO
	VALUES (3145729,
	3145729,
	3145729,
	0);
INSERT INTO R_OIR
	VALUES (3145729,
	3145729,
	3145729,
	0);
INSERT INTO R_FORM
	VALUES (3145730,
	3145729,
	3145730,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (3145730,
	3145729,
	3145730);
INSERT INTO R_OIR
	VALUES (3145730,
	3145729,
	3145730,
	0);
INSERT INTO R_SIMP
	VALUES (3145730);
INSERT INTO R_REL
	VALUES (3145730,
	118,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (1048584,
	3145730,
	3145731,
	0,
	0,
	'is defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	3145730,
	3145731,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	3145730,
	3145731,
	3145729);
INSERT INTO R_FORM
	VALUES (3145730,
	3145730,
	3145732,
	1,
	1,
	'defines the type of ');
INSERT INTO R_RGO
	VALUES (3145730,
	3145730,
	3145732);
INSERT INTO R_OIR
	VALUES (3145730,
	3145730,
	3145732,
	0);
INSERT INTO R_SIMP
	VALUES (3145731);
INSERT INTO R_REL
	VALUES (3145731,
	116,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (1048584,
	3145731,
	3145733,
	0,
	0,
	'return code is defined by');
INSERT INTO R_RTO
	VALUES (1048584,
	3145731,
	3145733,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	3145731,
	3145733,
	3145729);
INSERT INTO R_FORM
	VALUES (3145729,
	3145731,
	3145734,
	1,
	1,
	'defines the type of return code');
INSERT INTO R_RGO
	VALUES (3145729,
	3145731,
	3145734);
INSERT INTO R_OIR
	VALUES (3145729,
	3145731,
	3145734,
	0);
INSERT INTO R_SIMP
	VALUES (3145732);
INSERT INTO R_REL
	VALUES (3145732,
	115,
	'',
	3145734);
INSERT INTO R_FORM
	VALUES (3145729,
	3145732,
	3145735,
	1,
	1,
	'may contain');
INSERT INTO R_RGO
	VALUES (3145729,
	3145732,
	3145735);
INSERT INTO R_OIR
	VALUES (3145729,
	3145732,
	3145735,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	3145732,
	3145736,
	0,
	0,
	'is associated with');
INSERT INTO R_RTO
	VALUES (3145732,
	3145732,
	3145736,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	3145732,
	3145736,
	0);
INSERT INTO R_SIMP
	VALUES (3145733);
INSERT INTO R_REL
	VALUES (3145733,
	102,
	'',
	3145734);
INSERT INTO R_FORM
	VALUES (3145731,
	3145733,
	3145737,
	1,
	1,
	'has characteristics abstracted by');
INSERT INTO R_RGO
	VALUES (3145731,
	3145733,
	3145737);
INSERT INTO R_OIR
	VALUES (3145731,
	3145733,
	3145737,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	3145733,
	3145738,
	0,
	0,
	'abstracts characteristics of');
INSERT INTO R_RTO
	VALUES (3145732,
	3145733,
	3145738,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	3145733,
	3145738,
	0);
INSERT INTO R_SIMP
	VALUES (3145734);
INSERT INTO R_REL
	VALUES (3145734,
	103,
	'This relationship specifies the order in which an objects attributes appear on the OIM. The instance for which no instance ''preceeds'' is the first (top) object attribute on the OIM. The instance for which no instance ''succeeds'' is the last (bottom) object attribute on the OIM.',
	3145734);
INSERT INTO R_PART
	VALUES (3145731,
	3145734,
	3145739,
	0,
	1,
	'precedes');
INSERT INTO R_RTO
	VALUES (3145731,
	3145734,
	3145739,
	0);
INSERT INTO R_OIR
	VALUES (3145731,
	3145734,
	3145739,
	0);
INSERT INTO R_FORM
	VALUES (3145731,
	3145734,
	3145740,
	0,
	1,
	'succeeds');
INSERT INTO R_RGO
	VALUES (3145731,
	3145734,
	3145740);
INSERT INTO R_OIR
	VALUES (3145731,
	3145734,
	3145740,
	0);
INSERT INTO R_SIMP
	VALUES (3145735);
INSERT INTO R_REL
	VALUES (3145735,
	114,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (1048584,
	3145735,
	3145741,
	0,
	0,
	'defines type of');
INSERT INTO R_RTO
	VALUES (1048584,
	3145735,
	3145741,
	0);
INSERT INTO R_OIR
	VALUES (1048584,
	3145735,
	3145741,
	3145729);
INSERT INTO R_FORM
	VALUES (3145731,
	3145735,
	3145742,
	1,
	1,
	'is defined by');
INSERT INTO R_RGO
	VALUES (3145731,
	3145735,
	3145742);
INSERT INTO R_OIR
	VALUES (3145731,
	3145735,
	3145742,
	0);
INSERT INTO R_SUBSUP
	VALUES (3145736);
INSERT INTO R_REL
	VALUES (3145736,
	106,
	'',
	3145734);
INSERT INTO R_SUPER
	VALUES (3145731,
	3145736,
	3145743);
INSERT INTO R_RTO
	VALUES (3145731,
	3145736,
	3145743,
	0);
INSERT INTO R_OIR
	VALUES (3145731,
	3145736,
	3145743,
	0);
INSERT INTO R_SUB
	VALUES (3145733,
	3145736,
	3145744);
INSERT INTO R_RGO
	VALUES (3145733,
	3145736,
	3145744);
INSERT INTO R_OIR
	VALUES (3145733,
	3145736,
	3145744,
	0);
INSERT INTO R_SUB
	VALUES (3145734,
	3145736,
	3145745);
INSERT INTO R_RGO
	VALUES (3145734,
	3145736,
	3145745);
INSERT INTO R_OIR
	VALUES (3145734,
	3145736,
	3145745,
	0);
INSERT INTO R_SIMP
	VALUES (3145737);
INSERT INTO R_REL
	VALUES (3145737,
	113,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (3145733,
	3145737,
	3145746,
	0,
	0,
	'navigates back to');
INSERT INTO R_RTO
	VALUES (3145733,
	3145737,
	3145746,
	0);
INSERT INTO R_OIR
	VALUES (3145733,
	3145737,
	3145746,
	0);
INSERT INTO R_FORM
	VALUES (3145734,
	3145737,
	3145747,
	1,
	1,
	'can be the base of');
INSERT INTO R_RGO
	VALUES (3145734,
	3145737,
	3145747);
INSERT INTO R_OIR
	VALUES (3145734,
	3145737,
	3145747,
	0);
INSERT INTO R_SUBSUP
	VALUES (3145738);
INSERT INTO R_REL
	VALUES (3145738,
	107,
	'',
	3145734);
INSERT INTO R_SUPER
	VALUES (3145733,
	3145738,
	3145748);
INSERT INTO R_RTO
	VALUES (3145733,
	3145738,
	3145748,
	0);
INSERT INTO R_OIR
	VALUES (3145733,
	3145738,
	3145748,
	0);
INSERT INTO R_SUB
	VALUES (3145735,
	3145738,
	3145749);
INSERT INTO R_RGO
	VALUES (3145735,
	3145738,
	3145749);
INSERT INTO R_OIR
	VALUES (3145735,
	3145738,
	3145749,
	0);
INSERT INTO R_SUB
	VALUES (3145736,
	3145738,
	3145750);
INSERT INTO R_RGO
	VALUES (3145736,
	3145738,
	3145750);
INSERT INTO R_OIR
	VALUES (3145736,
	3145738,
	3145750,
	0);
INSERT INTO R_SIMP
	VALUES (3145739);
INSERT INTO R_REL
	VALUES (3145739,
	108,
	'',
	3145734);
INSERT INTO R_FORM
	VALUES (3145737,
	3145739,
	3145751,
	1,
	0,
	'resolves ');
INSERT INTO R_RGO
	VALUES (3145737,
	3145739,
	3145751);
INSERT INTO R_OIR
	VALUES (3145737,
	3145739,
	3145751,
	0);
INSERT INTO R_PART
	VALUES (3145734,
	3145739,
	3145752,
	0,
	0,
	'is resolved by');
INSERT INTO R_RTO
	VALUES (3145734,
	3145739,
	3145752,
	0);
INSERT INTO R_OIR
	VALUES (3145734,
	3145739,
	3145752,
	0);
INSERT INTO R_SIMP
	VALUES (3145740);
INSERT INTO R_REL
	VALUES (3145740,
	112,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (3145737,
	3145740,
	3145753,
	0,
	1,
	'precedes');
INSERT INTO R_RTO
	VALUES (3145737,
	3145740,
	3145753,
	1);
INSERT INTO R_OIR
	VALUES (3145737,
	3145740,
	3145753,
	0);
INSERT INTO R_FORM
	VALUES (3145737,
	3145740,
	3145754,
	0,
	1,
	'succeeds');
INSERT INTO R_RGO
	VALUES (3145737,
	3145740,
	3145754);
INSERT INTO R_OIR
	VALUES (3145737,
	3145740,
	3145754,
	0);
INSERT INTO R_ASSOC
	VALUES (3145741);
INSERT INTO R_REL
	VALUES (3145741,
	105,
	'',
	3145734);
INSERT INTO R_AOTH
	VALUES (3145731,
	3145741,
	3145755,
	1,
	1,
	'is made up of ');
INSERT INTO R_RTO
	VALUES (3145731,
	3145741,
	3145755,
	0);
INSERT INTO R_OIR
	VALUES (3145731,
	3145741,
	3145755,
	0);
INSERT INTO R_AONE
	VALUES (3145738,
	3145741,
	3145756,
	1,
	1,
	'is part of ');
INSERT INTO R_RTO
	VALUES (3145738,
	3145741,
	3145756,
	0);
INSERT INTO R_OIR
	VALUES (3145738,
	3145741,
	3145756,
	0);
INSERT INTO R_ASSR
	VALUES (3145739,
	3145741,
	3145757,
	0);
INSERT INTO R_RGO
	VALUES (3145739,
	3145741,
	3145757);
INSERT INTO R_OIR
	VALUES (3145739,
	3145741,
	3145757,
	0);
INSERT INTO R_SIMP
	VALUES (3145742);
INSERT INTO R_REL
	VALUES (3145742,
	104,
	'',
	3145734);
INSERT INTO R_FORM
	VALUES (3145738,
	3145742,
	3145758,
	1,
	1,
	'is identified by');
INSERT INTO R_RGO
	VALUES (3145738,
	3145742,
	3145758);
INSERT INTO R_OIR
	VALUES (3145738,
	3145742,
	3145758,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	3145742,
	3145759,
	0,
	0,
	'idenifies');
INSERT INTO R_RTO
	VALUES (3145732,
	3145742,
	3145759,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	3145742,
	3145759,
	0);
INSERT INTO R_SIMP
	VALUES (3145743);
INSERT INTO R_REL
	VALUES (3145743,
	101,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (3145732,
	3145743,
	3145760,
	0,
	0,
	'represents');
INSERT INTO R_RTO
	VALUES (3145732,
	3145743,
	3145760,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	3145743,
	3145760,
	0);
INSERT INTO R_FORM
	VALUES (3145740,
	3145743,
	3145761,
	1,
	1,
	'has presence in other subsystems');
INSERT INTO R_RGO
	VALUES (3145740,
	3145743,
	3145761);
INSERT INTO R_OIR
	VALUES (3145740,
	3145743,
	3145761,
	0);
INSERT INTO R_ASSOC
	VALUES (3145744);
INSERT INTO R_REL
	VALUES (3145744,
	110,
	'',
	3145734);
INSERT INTO R_AONE
	VALUES (1572880,
	3145744,
	3145762,
	1,
	1,
	'identifies for this relationship');
INSERT INTO R_RTO
	VALUES (1572880,
	3145744,
	3145762,
	1);
INSERT INTO R_OIR
	VALUES (1572880,
	3145744,
	3145762,
	3145730);
INSERT INTO R_AOTH
	VALUES (3145739,
	3145744,
	3145763,
	1,
	0,
	'is identified in this relationship by');
INSERT INTO R_RTO
	VALUES (3145739,
	3145744,
	3145763,
	0);
INSERT INTO R_OIR
	VALUES (3145739,
	3145744,
	3145763,
	0);
INSERT INTO R_ASSR
	VALUES (3145741,
	3145744,
	3145764,
	0);
INSERT INTO R_RGO
	VALUES (3145741,
	3145744,
	3145764);
INSERT INTO R_OIR
	VALUES (3145741,
	3145744,
	3145764,
	0);
INSERT INTO R_SIMP
	VALUES (3145745);
INSERT INTO R_REL
	VALUES (3145745,
	109,
	'',
	3145734);
INSERT INTO R_PART
	VALUES (3145738,
	3145745,
	3145765,
	0,
	1,
	'is identified in this relationship by');
INSERT INTO R_RTO
	VALUES (3145738,
	3145745,
	3145765,
	0);
INSERT INTO R_OIR
	VALUES (3145738,
	3145745,
	3145765,
	0);
INSERT INTO R_FORM
	VALUES (1572880,
	3145745,
	3145766,
	1,
	1,
	'identifies for this relationship ');
INSERT INTO R_RGO
	VALUES (1572880,
	3145745,
	3145766);
INSERT INTO R_OIR
	VALUES (1572880,
	3145745,
	3145766,
	3145730);
INSERT INTO R_ASSOC
	VALUES (3145746);
INSERT INTO R_REL
	VALUES (3145746,
	111,
	'',
	3145734);
INSERT INTO R_AONE
	VALUES (1572881,
	3145746,
	3145767,
	1,
	0,
	'is used to refer object by');
INSERT INTO R_RTO
	VALUES (1572881,
	3145746,
	3145767,
	0);
INSERT INTO R_OIR
	VALUES (1572881,
	3145746,
	3145767,
	3145731);
INSERT INTO R_AOTH
	VALUES (3145741,
	3145746,
	3145768,
	1,
	0,
	'refers across relationship via');
INSERT INTO R_RTO
	VALUES (3145741,
	3145746,
	3145768,
	0);
INSERT INTO R_OIR
	VALUES (3145741,
	3145746,
	3145768,
	0);
INSERT INTO R_ASSR
	VALUES (3145737,
	3145746,
	3145769,
	0);
INSERT INTO R_RGO
	VALUES (3145737,
	3145746,
	3145769);
INSERT INTO R_OIR
	VALUES (3145737,
	3145746,
	3145769,
	0);
INSERT INTO S_SS
	VALUES (3670023,
	'Version Management',
	'

Major OIM Modeling Decisions & Alternatives:


Notes:

',
	'V',
	900,
	94514,
	3670023);
INSERT INTO O_OBJ
	VALUES (3670017,
	'Component Version in Configuration Version',
	905,
	'V_CIOV',
	'

Restrictions applied to Object:

Notes:
',
	3670023);
INSERT INTO O_NBATTR
	VALUES (3670017,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670017,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670017,
	3670017,
	0,
	'Domain_Name',
	'The domain name as known by the model repository.',
	'',
	'Domain_Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3670018,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670018,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670018,
	3670017,
	3670017,
	'Component_id',
	'The number of the component.
This number <N> corrosponds with the model repository as  [V_CIOV.Domain_Name].rep/component_<N>.',
	'',
	'Component_id',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (3670019,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670019,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670019,
	3670017,
	3670018,
	'Parent_Component_id',
	'The component id of the "container" for the component.  
For example, a domain is a  parent of a subsystem, and a subsystem is the parent of a statechart.

',
	'',
	'Parent_Component_id',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (3670020,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670020,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670020,
	3670017,
	3670019,
	'Component_type',
	'The type of the component "container".
Data Domain:
  1 == Domain
  2 == Subsystem
  3 == State Model

  1000 == OOA Configration Version (an MC extension)',
	'',
	'Component_type',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3670021,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670021,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670021,
	3670017,
	3670020,
	'Component_Branch_Name',
	'The name of the branch on which this component resides.
This string  <STR> corrosponds with the model repository as  [V_CIOV.Domain_Name].rep/component_[num]/branch_<STR>',
	'',
	'Component_Branch_Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (3670022,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670022,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670022,
	3670017,
	3670021,
	'Component_Version_Num',
	'The version number of the component.',
	'',
	'Component_Version_Num',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (3670023,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670023,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670023,
	3670017,
	3670022,
	'Pinned',
	'Data Domain:
  FALSE == Not pinned.
  TRUE == Pinned.',
	'',
	'Pinned',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (3670024,
	3670017);
INSERT INTO O_BATTR
	VALUES (3670024,
	3670017);
INSERT INTO O_ATTR
	VALUES (3670024,
	3670017,
	3670023,
	'Abstract',
	'An abstract (description) of this component.',
	'',
	'Abstract',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	3670017);
INSERT INTO O_OIDA
	VALUES (3670018,
	3670017,
	0);
INSERT INTO O_OIDA
	VALUES (3670017,
	3670017,
	0);
INSERT INTO O_OIDA
	VALUES (3670021,
	3670017,
	0);
INSERT INTO O_OIDA
	VALUES (3670022,
	3670017,
	0);
INSERT INTO S_SS
	VALUES (4194312,
	'Translation Extensions',
	'This subsystem contains meta objects to assist in the translation process. These objects are not know to Model Builder. The instantiation (via SQL table inserts) must be provided via import operations to the Generator Database.',
	'TE',
	2000,
	94514,
	4194312);
INSERT INTO O_OBJ
	VALUES (4194305,
	'Special Where Clause',
	2000,
	'TE_SWC',
	'',
	4194312);
INSERT INTO O_REF
	VALUES (4194305,
	3145732,
	1,
	3145776,
	4194305,
	4194306,
	4194305,
	4194305,
	4194306,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194305,
	4194305,
	3145776,
	3145732,
	0);
INSERT INTO O_ATTR
	VALUES (4194305,
	4194305,
	0,
	'Obj_Kl',
	'Key letters of the object this instance of ''special where clause'' is associated with.
NOTE: The attribute name (in lower case) ''obj_kl'' is built in (unfortunately) to the ModelCompiler back end. If one attempts to use a different name for the attribute, the archetype primative ''special_where add <inst_ref>'' will fail.',
	'',
	'Obj_Kl',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4194306,
	4194305);
INSERT INTO O_BATTR
	VALUES (4194306,
	4194305);
INSERT INTO O_ATTR
	VALUES (4194306,
	4194305,
	4194305,
	'Where_Spec',
	'Full Name: Where Specification
The Where Specification is a character string that describes the where clause(s) that the architect has a special implementation for.
NOTE: The attribute name (in lower case) ''where_spec'' is built in (unfortunately) to the ModelCompiler back end. If one attempts to use a different name for the attribute, the archetype primative ''special_where add <inst_ref>'' will fail.',
	'',
	'Where_Spec',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194307,
	4194305);
INSERT INTO O_BATTR
	VALUES (4194307,
	4194305);
INSERT INTO O_ATTR
	VALUES (4194307,
	4194305,
	4194306,
	'Key',
	'Key is a string that identifies a special where clause to the architecture. The action language parser will pass this string back to the architecture when a special where clause is encountered. The Key must uniquely identify each special where clause.
NOTE: The attribute name (in lower case) ''key'' is built in (unfortunately) to the ModelCompiler back end. If one attempts to use a different name for the attribute, the archetype primative ''special_where add <inst_ref>'' will fail.',
	'',
	'Key',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194308,
	4194305);
INSERT INTO O_BATTR
	VALUES (4194308,
	4194305);
INSERT INTO O_ATTR
	VALUES (4194308,
	4194305,
	4194307,
	'Ret_Val',
	'Full Name: Return Value
On completion of an archetype command involving a special where, indicates the results of the operation (TRUE for success, FALSE for failure).
NOTE: The attribute name (in lower case) ''ret_val'' is built in (unfortunately) to the ModelCompiler back end. If one attempts to use a different name for the attribute, the archetype primative ''special_where add <inst_ref>'' will fail.',
	'',
	'Ret_Val',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194309,
	4194305);
INSERT INTO O_BATTR
	VALUES (4194309,
	4194305);
INSERT INTO O_ATTR
	VALUES (4194309,
	4194305,
	4194308,
	'Built_In',
	'Note: Extendend attribute.
A flag used by the translation engine to indicate that this instance of ''Special Where Clause'' has been built in by the model compiler. If TRUE, the where clause criteria delineated by ''Where_Spec'' is a generated optimization on the part of the model compiler. If FALSE, the where clause evaluation is assumed to be hand crafted by the system architect.',
	'',
	'Built_In',
	0,
	524290);
INSERT INTO O_DBATTR
	VALUES (4194310,
	4194305,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (4194310,
	4194305);
INSERT INTO O_ATTR
	VALUES (4194310,
	4194305,
	4194309,
	'Oid_ID',
	'A value used to specify the (complete) object identifying attribute set that this where clause is evaluated against. It is mathematically dependent on a coorosponding instance of ''O_ID.Obj_ID'', if the where clause critera maps exclusively to an identifying attribute set.

Data domain of the identifying attribute set number:
0  = Primary Identifer Set (e.g., *)
1  = Secondary Identifier Set (e.g., *2)
2  = Third Identifier Set (e.g., *3)
-1 = "No such value"',
	'',
	'Oid_ID',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	4194305);
INSERT INTO O_OIDA
	VALUES (4194307,
	4194305,
	0);
INSERT INTO O_ID
	VALUES (1,
	4194305);
INSERT INTO O_OIDA
	VALUES (4194305,
	4194305,
	1);
INSERT INTO O_OIDA
	VALUES (4194307,
	4194305,
	1);
INSERT INTO O_OBJ
	VALUES (4194306,
	'Action Scratch Pad',
	2001,
	'TE_ASP',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194311,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194311,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194311,
	4194306,
	0,
	'AspID',
	'Full Name: Action Scratch Pad Identifier',
	'',
	'AspID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194312,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194312,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194312,
	4194306,
	4194311,
	'Sync_Supp_Data',
	'',
	'',
	'Sync_Supp_Data',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194313,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194313,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194313,
	4194306,
	4194312,
	'SpecialWhereValid',
	'',
	'',
	'SpecialWhereValid',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194314,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194314,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194314,
	4194306,
	4194313,
	'Indent_Level',
	'Full Name: Indentation Level
The current indentation level (e.g., column position) to be used in the generated action code.',
	'',
	'Indent_Level',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194315,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194315,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194315,
	4194306,
	4194314,
	'Indentation',
	'The current indentation to be used in the generated action code.',
	'',
	'Indentation',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194316,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194316,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194316,
	4194306,
	4194315,
	'IsBridgeObject',
	'A flag to indicate to the fragment generation archetypes if the state action being translated is a pseudo-state associated with a Funky Bridge Object (FBO). If TRUE, the object is an FBO. If FALSE, the object is not an FBO.',
	'',
	'IsBridgeObject',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194317,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194317,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194317,
	4194306,
	4194316,
	'CurrentBlock',
	'',
	'',
	'CurrentBlock',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194318,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194318,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194318,
	4194306,
	4194317,
	'CurrentBlockDepth',
	'',
	'',
	'CurrentBlockDepth',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194319,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194319,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194319,
	4194306,
	4194318,
	'LoopDepth',
	'',
	'',
	'LoopDepth',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194320,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194320,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194320,
	4194306,
	4194319,
	'OIV_Counter',
	'',
	'',
	'OIV_Counter',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194321,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194321,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194321,
	4194306,
	4194320,
	'ReturnStmtUsed',
	'',
	'',
	'ReturnStmtUsed',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194322,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194322,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194322,
	4194306,
	4194321,
	'ObjVarTracking',
	'Full Name: Object Variable Tracking
A flag used by the translation engine to indicate that object instance variables are being tracked for specialization during action semantics translation.',
	'',
	'ObjVarTracking',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194323,
	4194306);
INSERT INTO O_BATTR
	VALUES (4194323,
	4194306);
INSERT INTO O_ATTR
	VALUES (4194323,
	4194306,
	4194322,
	'RvalReturnTracking',
	'A flag used by the translation engine to indicate that special processing is required for return statements which return a value.',
	'',
	'RvalReturnTracking',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	4194306);
INSERT INTO O_OIDA
	VALUES (4194311,
	4194306,
	0);
INSERT INTO O_RTIDA
	VALUES (4194311,
	4194306,
	0,
	4194309,
	4194313);
INSERT INTO O_OBJ
	VALUES (4194307,
	'Static Analysis Information',
	2002,
	'TE_SAIB',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194324,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194324,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194324,
	4194307,
	0,
	'RegisteredDomName',
	'',
	'',
	'RegisteredDomName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194325,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194325,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194325,
	4194307,
	4194324,
	'RegisteredDomID',
	'',
	'',
	'RegisteredDomID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194326,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194326,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194326,
	4194307,
	4194325,
	'RepositoryName',
	'',
	'',
	'RepositoryName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194327,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194327,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194327,
	4194307,
	4194326,
	'RepositoryVersion',
	'',
	'',
	'RepositoryVersion',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194328,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194328,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194328,
	4194307,
	4194327,
	'StartTimeStamp',
	'A time stamp representing when the archetype which calculates the embodied static analysis information began execution.',
	'',
	'StartTimeStamp',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194329,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194329,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194329,
	4194307,
	4194328,
	'EndTimeStamp',
	'A time stamp representing when the archetype which calculates the embodied static analysis information completed execution.',
	'',
	'EndTimeStamp',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194330,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194330,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194330,
	4194307,
	4194329,
	'TextBuffer',
	'',
	'',
	'TextBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194331,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194331,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194331,
	4194307,
	4194330,
	'SpecialWhereBuffer',
	'',
	'',
	'SpecialWhereBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194332,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194332,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194332,
	4194307,
	4194331,
	'MaxSelfEvents',
	'The maximum number of self directed events which may be (potentially) generated by any one state action in the domain.',
	'',
	'MaxSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194333,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194333,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194333,
	4194307,
	4194332,
	'MaxNonSelfEvents',
	'The maximum number of non-self directed events which may be (potentially) generated by any one state action in the domain.',
	'',
	'MaxNonSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194334,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194334,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194334,
	4194307,
	4194333,
	'MaxManyDeclared',
	'The maximum number of application analysis implicate declarations of  instance handle sets ( inst_ref_set<Object> ) which may be in scope during any state action on the domain. ',
	'',
	'MaxManyDeclared',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194335,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194335,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194335,
	4194307,
	4194334,
	'MaxManyTransient',
	'The maximum number of transient variable instance handle set  ( inst_ref_set<Object> ) declarations which may be in scope during any state action on the domain .
A transient collection (set) may be/is used by the translation engine when implementing application analysis action language selection statements involving keyword "MANY".',
	'',
	'MaxManyTransient',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194336,
	4194307);
INSERT INTO O_BATTR
	VALUES (4194336,
	4194307);
INSERT INTO O_ATTR
	VALUES (4194336,
	4194307,
	4194335,
	'TIM_MaxTimers',
	'The total number of TIM::timer_start and TIM::timer_start_recuring bridge statements in theaction language of the analysis domain. This number may be used by the system architect to estimate the maximum number of outstanding timers that may exist in the system.',
	'',
	'TIM_MaxTimers',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	4194307);
INSERT INTO O_OIDA
	VALUES (4194324,
	4194307,
	0);
INSERT INTO O_ID
	VALUES (1,
	4194307);
INSERT INTO O_OIDA
	VALUES (4194325,
	4194307,
	1);
INSERT INTO O_OBJ
	VALUES (4194308,
	'Domain Limits System Populator',
	2003,
	'TE_DLSP',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194337,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194337,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194337,
	4194308,
	0,
	'RegisteredDomName',
	'Full Name: Registered Domain Name',
	'',
	'RegisteredDomName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194338,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194338,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194338,
	4194308,
	4194337,
	'RegisteredDomID',
	'Full Name: Registered Domain Indentifier',
	'',
	'RegisteredDomID',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194308,
	4194309,
	0,
	4194350,
	4194306,
	4194308,
	4194307,
	4194339,
	4194307,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194339,
	4194308,
	4194350,
	4194309,
	1);
INSERT INTO O_ATTR
	VALUES (4194339,
	4194308,
	4194338,
	'SystemID',
	'',
	'',
	'SystemID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4194340,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194340,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194340,
	4194308,
	4194339,
	'RepositoryName',
	'Full Name: Project Model Repository Name',
	'',
	'RepositoryName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194341,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194341,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194341,
	4194308,
	4194340,
	'RepositoryVersion',
	'Full Name: Project Model Repository Configuration Version',
	'',
	'RepositoryVersion',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194342,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194342,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194342,
	4194308,
	4194341,
	'MaxObjExtent',
	'Full Name: Maximum Object Extent Size',
	'',
	'MaxObjExtent',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194343,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194343,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194343,
	4194308,
	4194342,
	'MaxRelExtent',
	'Full Name: Maximum Relationship Extent Size',
	'',
	'MaxRelExtent',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194344,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194344,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194344,
	4194308,
	4194343,
	'MaxSelectExtent',
	'Full Name: Maximum Select Statement Extent Size',
	'',
	'MaxSelectExtent',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194345,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194345,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194345,
	4194308,
	4194344,
	'MaxSelfEvents',
	'The maximum number of self directed events which may be (potentially) generated by any one state action in the domain.',
	'',
	'MaxSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194346,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194346,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194346,
	4194308,
	4194345,
	'MaxNonSelfEvents',
	'The maximum number of non-self directed events which may be (potentially) generated by any one state action in the domain.',
	'',
	'MaxNonSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194347,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194347,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194347,
	4194308,
	4194346,
	'MaxPriorityEvents',
	'',
	'',
	'MaxPriorityEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194348,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194348,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194348,
	4194308,
	4194347,
	'MaxTimers',
	'',
	'',
	'MaxTimers',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194349,
	4194308);
INSERT INTO O_BATTR
	VALUES (4194349,
	4194308);
INSERT INTO O_ATTR
	VALUES (4194349,
	4194308,
	4194348,
	'InterleavedBridges',
	'',
	'',
	'InterleavedBridges',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718671,
	4194308);
INSERT INTO O_BATTR
	VALUES (4718671,
	4194308);
INSERT INTO O_ATTR
	VALUES (4718671,
	4194308,
	4194349,
	'CharacterEncoding',
	'',
	'',
	'CharacterEncoding',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718672,
	4194308);
INSERT INTO O_BATTR
	VALUES (4718672,
	4194308);
INSERT INTO O_ATTR
	VALUES (4718672,
	4194308,
	4718671,
	'PEIClassCount',
	'',
	'',
	'PEIClassCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718674,
	4194308);
INSERT INTO O_BATTR
	VALUES (4718674,
	4194308);
INSERT INTO O_ATTR
	VALUES (4718674,
	4194308,
	4718672,
	'PersistentClassCount',
	'',
	'',
	'PersistentClassCount',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	4194308);
INSERT INTO O_OIDA
	VALUES (4194337,
	4194308,
	0);
INSERT INTO O_OBJ
	VALUES (4194309,
	'System',
	2004,
	'TE_SYS',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194350,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194350,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194350,
	4194309,
	0,
	'SystemID',
	'',
	'',
	'SystemID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194351,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194351,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194351,
	4194309,
	4194350,
	'ModelCompilerName',
	'',
	'',
	'ModelCompilerName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194352,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194352,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194352,
	4194309,
	4194351,
	'ModelCompilerVersion',
	'',
	'',
	'ModelCompilerVersion',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194353,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194353,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194353,
	4194309,
	4194352,
	'ModelCompilerSerNum',
	'',
	'',
	'ModelCompilerSerNum',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194354,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194354,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194354,
	4194309,
	4194353,
	'ModelCompilerKey',
	'',
	'',
	'ModelCompilerKey',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194355,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194355,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194355,
	4194309,
	4194354,
	'BridgePointLicenseKey',
	'',
	'',
	'BridgePointLicenseKey',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194356,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194356,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194356,
	4194309,
	4194355,
	'TextBuffer',
	'',
	'',
	'TextBuffer',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194357,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194357,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194357,
	4194309,
	4194356,
	'ExecutableName',
	'',
	'',
	'ExecutableName',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194358,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194358,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194358,
	4194309,
	4194357,
	'MaxStringLen',
	'',
	'',
	'MaxStringLen',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194359,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194359,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194359,
	4194309,
	4194358,
	'MaxObjExtent',
	'',
	'',
	'MaxObjExtent',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194360,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194360,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194360,
	4194309,
	4194359,
	'MaxRelExtent',
	'',
	'',
	'MaxRelExtent',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194361,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194361,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194361,
	4194309,
	4194360,
	'MaxSelectExtent',
	'',
	'',
	'MaxSelectExtent',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194362,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194362,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194362,
	4194309,
	4718675,
	'MaxSelfEvents',
	'',
	'',
	'MaxSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194363,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194363,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194363,
	4194309,
	4194362,
	'MaxNonSelfEvents',
	'',
	'',
	'MaxNonSelfEvents',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194364,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194364,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194364,
	4194309,
	4194363,
	'MaxTimers',
	'',
	'',
	'MaxTimers',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194365,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194365,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194365,
	4194309,
	4194364,
	'MaxInterleavedBridges',
	'',
	'',
	'MaxInterleavedBridges',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194366,
	4194309);
INSERT INTO O_BATTR
	VALUES (4194366,
	4194309);
INSERT INTO O_ATTR
	VALUES (4194366,
	4194309,
	4194365,
	'MaxInterleavedBridgeDataSize',
	'This attribute gets colored by the user when the default
size for parameter data across interleaved bridges is too
small.  This allows the protected area to be colored larger
or smaller.',
	'',
	'MaxInterleavedBridgeDataSize',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718675,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718675,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718675,
	4194309,
	4194361,
	'TotalContainers',
	'',
	'',
	'TotalContainers',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718676,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718676,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718676,
	4194309,
	4194366,
	'CollectionsFlavor',
	'',
	'',
	'CollectionsFlavor',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718677,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718677,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718677,
	4194309,
	4718676,
	'TargetMonitorEnabled',
	'',
	'',
	'TargetMonitorEnabled',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718678,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718678,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718678,
	4194309,
	4718677,
	'ForcePriorityEvents',
	'',
	'',
	'ForcePriorityEvents',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718679,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718679,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718679,
	4194309,
	4718678,
	'SystemPrefix',
	'',
	'',
	'SystemPrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718680,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718680,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718680,
	4194309,
	4718679,
	'SystemMethodPrefix',
	'',
	'',
	'SystemMethodPrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718681,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718681,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718681,
	4194309,
	4718680,
	'SystemTypePrefix',
	'',
	'',
	'SystemTypePrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718682,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718682,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718682,
	4194309,
	4718681,
	'SystemDefinePrefix',
	'',
	'',
	'SystemDefinePrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718683,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718683,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718683,
	4194309,
	4718682,
	'SystemFilePrefix',
	'',
	'',
	'SystemFilePrefix',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718684,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718684,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718684,
	4194309,
	4718683,
	'PEIClassCount',
	'',
	'',
	'PEIClassCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718685,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718685,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718685,
	4194309,
	4718684,
	'PersistentClassCount',
	'',
	'',
	'PersistentClassCount',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718686,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718686,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718686,
	4194309,
	4718685,
	'PersistInstanceCacheDepth',
	'',
	'',
	'PersistInstanceCacheDepth',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718687,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718687,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718687,
	4194309,
	4718720,
	'TaskingFlavor',
	'',
	'',
	'TaskingFlavor',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4718688,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718688,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718688,
	4194309,
	4718687,
	'NumberOfTasks',
	'',
	'',
	'NumberOfTasks',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4718689,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718689,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718689,
	4194309,
	4718688,
	'SerializeProcessing',
	'',
	'',
	'SerializeProcessing',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4718720,
	4194309);
INSERT INTO O_BATTR
	VALUES (4718720,
	4194309);
INSERT INTO O_ATTR
	VALUES (4718720,
	4194309,
	4718686,
	'PersistLinkCacheDepth',
	'',
	'',
	'PersistLinkCacheDepth',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	4194309);
INSERT INTO O_OIDA
	VALUES (4194350,
	4194309,
	0);
INSERT INTO O_RTIDA
	VALUES (4194350,
	4194309,
	0,
	4194306,
	4194307);
INSERT INTO O_RTIDA
	VALUES (4194350,
	4194309,
	0,
	4194307,
	4194309);
INSERT INTO O_OBJ
	VALUES (4194310,
	'Dispatcher',
	2005,
	'TE_DISP',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194367,
	4194310);
INSERT INTO O_BATTR
	VALUES (4194367,
	4194310);
INSERT INTO O_ATTR
	VALUES (4194367,
	4194310,
	0,
	'Dispatcher_ID',
	'',
	'',
	'Dispatcher_ID',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194310,
	4194309,
	0,
	4194350,
	4194307,
	4194310,
	4194309,
	4194368,
	4194308,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194368,
	4194310,
	4194350,
	4194309,
	1);
INSERT INTO O_ATTR
	VALUES (4194368,
	4194310,
	4194367,
	'SystemID',
	'',
	'',
	'SystemID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4194369,
	4194310);
INSERT INTO O_BATTR
	VALUES (4194369,
	4194310);
INSERT INTO O_ATTR
	VALUES (4194369,
	4194310,
	4194368,
	'Name',
	'',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194370,
	4194310);
INSERT INTO O_BATTR
	VALUES (4194370,
	4194310);
INSERT INTO O_ATTR
	VALUES (4194370,
	4194310,
	4194369,
	'Descrip',
	'',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4194310);
INSERT INTO O_OIDA
	VALUES (4194367,
	4194310,
	0);
INSERT INTO O_RTIDA
	VALUES (4194367,
	4194310,
	0,
	4194308,
	4194311);
INSERT INTO O_OBJ
	VALUES (4194311,
	'Message Queue',
	2006,
	'TE_QUEUE',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194371,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194371,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194371,
	4194311,
	0,
	'Queue_ID',
	'',
	'',
	'Queue_ID',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194311,
	4194310,
	0,
	4194367,
	4194308,
	4194312,
	4194311,
	4194372,
	4194309,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194372,
	4194311,
	4194367,
	4194310,
	1);
INSERT INTO O_ATTR
	VALUES (4194372,
	4194311,
	4194371,
	'Dispatcher_ID',
	'',
	'',
	'Dispatcher_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4194373,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194373,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194373,
	4194311,
	4194372,
	'Type',
	'The type of the queue.

Data Domain:
0  = Undefined
1  = Self directed OOA events
2  = Non-self directed OOA events
3  = System control
4  = External non-OOA task communications',
	'',
	'Type',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194374,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194374,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194374,
	4194311,
	4194373,
	'Descrip',
	'Full Name: Description

A textual description of this message queue.',
	'',
	'Descrip',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194375,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194375,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194375,
	4194311,
	4194374,
	'RenderCode',
	'A flag used by the translation engine to indicate that this message queue needs to be rendered in the generated code.',
	'',
	'RenderCode',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194376,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194376,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194376,
	4194311,
	4194375,
	'MaxDepth',
	'Full Name: Maximum Queue Depth

A value of zero (0) indicates that this queue has no predefined maximum depth.',
	'',
	'MaxDepth',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194377,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194377,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194377,
	4194311,
	4194376,
	'Blocking',
	'',
	'',
	'Blocking',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194378,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194378,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194378,
	4194311,
	4194377,
	'PriorityLevel',
	'',
	'',
	'PriorityLevel',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194379,
	4194311);
INSERT INTO O_BATTR
	VALUES (4194379,
	4194311);
INSERT INTO O_ATTR
	VALUES (4194379,
	4194311,
	4194378,
	'InstEnabled',
	'Full Name: Instrumentation Enabled',
	'',
	'InstEnabled',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	4194311);
INSERT INTO O_OIDA
	VALUES (4194371,
	4194311,
	0);
INSERT INTO O_OBJ
	VALUES (4194312,
	'Action Under Translation',
	2007,
	'TE_AUT',
	'This object provides the translation engine with an efficient means by which to identify an Action Semantics home being translated.',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194380,
	4194312);
INSERT INTO O_BATTR
	VALUES (4194380,
	4194312);
INSERT INTO O_ATTR
	VALUES (4194380,
	4194312,
	0,
	'AutID',
	'',
	'',
	'AutID',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194312,
	4194306,
	0,
	4194311,
	4194309,
	4194314,
	4194313,
	4194381,
	4194310,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194381,
	4194312,
	4194311,
	4194306,
	1);
INSERT INTO O_ATTR
	VALUES (4194381,
	4194312,
	4194380,
	'AspID',
	'',
	'',
	'AspID',
	0,
	524296);
INSERT INTO O_DBATTR
	VALUES (4194382,
	4194312,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (4194382,
	4194312);
INSERT INTO O_ATTR
	VALUES (4194382,
	4194312,
	4194381,
	'SemanticsType',
	'The type of the action semantics currently being translated.

Data Domain:

0  == Instance State Model (SM_ACT)
1  == Assigner State Model (SM_ACT)
2  == Transformer (O_TFR)
3  == Synchronous Service (S_SYNC)
4  == Bridge (S_BRG)
5  == Derived Attribute (O_DBATTR)
-1 == Unknown sematics home',
	'',
	'SemanticsType',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194312,
	4194313,
	0,
	4194384,
	4194316,
	4194336,
	4194337,
	4194383,
	4194311,
	0,
	1,
	'Full Name: Action Block Anchor Identifier
This attribute is constrained such that R2016 is equivalent to navigating TE_AUT[R2009]->{semantics home}[R2010].
This relationship of convenience is used to reduce complexity in the archetypes when translating an action semantics home.');
INSERT INTO O_RATTR
	VALUES (4194383,
	4194312,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (4194383,
	4194312,
	4194382,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4194312);
INSERT INTO O_OIDA
	VALUES (4194380,
	4194312,
	0);
INSERT INTO O_RTIDA
	VALUES (4194380,
	4194312,
	0,
	4194310,
	4194315);
INSERT INTO O_OBJ
	VALUES (4194313,
	'Action Block Anchor',
	2008,
	'TE_ABA',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194384,
	4194313);
INSERT INTO O_BATTR
	VALUES (4194384,
	4194313);
INSERT INTO O_ATTR
	VALUES (4194384,
	4194313,
	0,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4194313);
INSERT INTO O_OIDA
	VALUES (4194384,
	4194313,
	0);
INSERT INTO O_RTIDA
	VALUES (4194384,
	4194313,
	0,
	4194316,
	4194337);
INSERT INTO O_RTIDA
	VALUES (4194384,
	4194313,
	0,
	4194312,
	4194327);
INSERT INTO O_RTIDA
	VALUES (4194384,
	4194313,
	0,
	4194311,
	4194321);
INSERT INTO O_OBJ
	VALUES (4194314,
	'Action Block',
	2009,
	'TE_BLOCK',
	'',
	4194312);
INSERT INTO O_REF
	VALUES (4194314,
	4194313,
	0,
	4194384,
	4194312,
	4194328,
	4194327,
	4194385,
	4194312,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4194314,
	4194314,
	0,
	4194385,
	4194313,
	4194329,
	4194330,
	4194385,
	4194313,
	4194312,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194385,
	4194314,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (4194385,
	4194314,
	0,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4194386,
	4194314);
INSERT INTO O_BATTR
	VALUES (4194386,
	4194314);
INSERT INTO O_ATTR
	VALUES (4194386,
	4194314,
	4194385,
	'Number',
	'',
	'',
	'Number',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194314,
	4194314,
	0,
	4194386,
	4194313,
	4194329,
	4194330,
	4194387,
	4194314,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194387,
	4194314,
	4194386,
	4194314,
	1);
INSERT INTO O_ATTR
	VALUES (4194387,
	4194314,
	4194386,
	'PreviousNumber',
	'',
	'Previous',
	'Number',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (4194388,
	4194314);
INSERT INTO O_BATTR
	VALUES (4194388,
	4194314);
INSERT INTO O_ATTR
	VALUES (4194388,
	4194314,
	4194387,
	'Depth',
	'',
	'',
	'Depth',
	0,
	524291);
INSERT INTO O_DBATTR
	VALUES (4194389,
	4194314,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (4194389,
	4194314);
INSERT INTO O_ATTR
	VALUES (4194389,
	4194314,
	4194388,
	'Type',
	'The statement and scope type of this block.

Data Domain:
1 == Outer Most Scope
2 == IF
3 == ELIF
4 == ELSE
5 == FOR
6 == WHILE
',
	'',
	'Type',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194390,
	4194314);
INSERT INTO O_BATTR
	VALUES (4194390,
	4194314);
INSERT INTO O_ATTR
	VALUES (4194390,
	4194314,
	4194389,
	'Closing',
	'A flag used by the translation engine to indicate the this blocks logic has been "closed", but the block may still be active. For example, an END IF statement will set the blocks state to ''closing'', but additional semantics may be present in the block which have not yet been translated.',
	'',
	'Closing',
	0,
	524290);
INSERT INTO O_NBATTR
	VALUES (4194391,
	4194314);
INSERT INTO O_BATTR
	VALUES (4194391,
	4194314);
INSERT INTO O_ATTR
	VALUES (4194391,
	4194314,
	4194390,
	'Active',
	'A flag used by the translation engine to indicate that this block is currently active.',
	'',
	'Active',
	0,
	524290);
INSERT INTO O_ID
	VALUES (0,
	4194314);
INSERT INTO O_OIDA
	VALUES (4194385,
	4194314,
	0);
INSERT INTO O_RTIDA
	VALUES (4194385,
	4194314,
	0,
	4194313,
	4194330);
INSERT INTO O_RTIDA
	VALUES (4194385,
	4194314,
	0,
	4194314,
	4194332);
INSERT INTO O_OIDA
	VALUES (4194386,
	4194314,
	0);
INSERT INTO O_RTIDA
	VALUES (4194386,
	4194314,
	0,
	4194314,
	4194332);
INSERT INTO O_RTIDA
	VALUES (4194386,
	4194314,
	0,
	4194313,
	4194330);
INSERT INTO O_OBJ
	VALUES (4194315,
	'Object Instance Variable',
	2010,
	'TE_OIV',
	'',
	4194312);
INSERT INTO O_NBATTR
	VALUES (4194392,
	4194315);
INSERT INTO O_BATTR
	VALUES (4194392,
	4194315);
INSERT INTO O_ATTR
	VALUES (4194392,
	4194315,
	0,
	'OivID',
	'',
	'',
	'OivID',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194393,
	4194315);
INSERT INTO O_BATTR
	VALUES (4194393,
	4194315);
INSERT INTO O_ATTR
	VALUES (4194393,
	4194315,
	4194392,
	'Name',
	'The name of the variable as known in the application analysis.',
	'',
	'Name',
	0,
	524293);
INSERT INTO O_NBATTR
	VALUES (4194394,
	4194315);
INSERT INTO O_BATTR
	VALUES (4194394,
	4194315);
INSERT INTO O_ATTR
	VALUES (4194394,
	4194315,
	4194393,
	'VarName',
	'The name of the variable as know in the generated code.',
	'',
	'VarName',
	0,
	524293);
INSERT INTO O_DBATTR
	VALUES (4194395,
	4194315,
	'',
	0);
INSERT INTO O_BATTR
	VALUES (4194395,
	4194315);
INSERT INTO O_ATTR
	VALUES (4194395,
	4194315,
	4194394,
	'TypeCode',
	'All ''var_*'' fragments contain output attribute ''type_code'', which can can be used by the other fragments to determine what type of variable fragment is being processed (e.g., originating ''var_declare*'' function).

Data Domain:
0 == Self                   var_declare_self_obj_inst_ref
1 == inst_ref<Object>       var_declare_obj_inst_ref
2 == inst_ref_set<Object>   var_declare_obj_inst_ref_set
3 == inst_ref<Event>        var_declare_evt_inst_ref
4 == Transient (*)          var_declare

(*) When a transient variable is first encountered in the BPAL, it''s type
code will not be known until the first assignment to it (via an invocation
of ''stmt_assign_transient_var'').
',
	'',
	'TypeCode',
	0,
	524291);
INSERT INTO O_NBATTR
	VALUES (4194396,
	4194315);
INSERT INTO O_BATTR
	VALUES (4194396,
	4194315);
INSERT INTO O_ATTR
	VALUES (4194396,
	4194315,
	4194395,
	'DeclareBlock',
	'The number of the block (TE_BLOCK.Number) in which this variable was declared.',
	'',
	'DeclareBlock',
	0,
	524291);
INSERT INTO O_REF
	VALUES (4194315,
	3145732,
	0,
	3145773,
	4194315,
	4194334,
	4194335,
	4194397,
	4194305,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194397,
	4194315,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4194397,
	4194315,
	4194396,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4194315);
INSERT INTO O_OIDA
	VALUES (4194392,
	4194315,
	0);
INSERT INTO O_RTIDA
	VALUES (4194392,
	4194315,
	0,
	4194314,
	4194331);
INSERT INTO O_OBJ
	VALUES (4194316,
	'Object Instance Reference',
	2011,
	'TE_OIR',
	'',
	4194312);
INSERT INTO O_REF
	VALUES (4194316,
	4194314,
	0,
	4194385,
	4194314,
	4194333,
	4194332,
	4194398,
	4194315,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194398,
	4194316,
	4194384,
	4194313,
	1);
INSERT INTO O_ATTR
	VALUES (4194398,
	4194316,
	0,
	'AbaID',
	'',
	'',
	'AbaID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4194316,
	4194314,
	0,
	4194386,
	4194314,
	4194333,
	4194332,
	4194399,
	4194316,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194399,
	4194316,
	4194386,
	4194314,
	1);
INSERT INTO O_ATTR
	VALUES (4194399,
	4194316,
	4194398,
	'Number',
	'',
	'',
	'Number',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4194316,
	4194315,
	0,
	4194392,
	4194314,
	4194333,
	4194331,
	4194400,
	4194317,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4194400,
	4194316,
	4194392,
	4194315,
	1);
INSERT INTO O_ATTR
	VALUES (4194400,
	4194316,
	4194399,
	'OivID',
	'',
	'',
	'OivID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4194316);
INSERT INTO O_OIDA
	VALUES (4194399,
	4194316,
	0);
INSERT INTO O_OIDA
	VALUES (4194400,
	4194316,
	0);
INSERT INTO O_OIDA
	VALUES (4194398,
	4194316,
	0);
INSERT INTO O_OBJ
	VALUES (4718620,
	'Domain Under Translation',
	2012,
	'TE_DUT',
	'',
	4194312);
INSERT INTO O_REF
	VALUES (4718620,
	1048577,
	0,
	1048577,
	4718638,
	4718690,
	4718691,
	4718721,
	4718657,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718721,
	4718620,
	1048577,
	1048577,
	1);
INSERT INTO O_ATTR
	VALUES (4718721,
	4718620,
	0,
	'Dom_ID',
	'',
	'',
	'Dom_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718620);
INSERT INTO O_OIDA
	VALUES (4718721,
	4718620,
	0);
INSERT INTO O_IOBJ
	VALUES (4194305,
	1048587,
	5,
	4194312,
	'Bridge',
	'S_BRG');
INSERT INTO O_IOBJ
	VALUES (4194306,
	1048590,
	5,
	4194312,
	'Function',
	'S_SYNC');
INSERT INTO O_IOBJ
	VALUES (4194307,
	2621455,
	5,
	4194312,
	'Action',
	'SM_ACT');
INSERT INTO O_IOBJ
	VALUES (4194308,
	3145729,
	5,
	4194312,
	'Transformer',
	'O_TFR');
INSERT INTO O_IOBJ
	VALUES (4194309,
	3145732,
	5,
	4194312,
	'Class',
	'O_OBJ');
INSERT INTO O_IOBJ
	VALUES (4194310,
	3145735,
	5,
	4194312,
	'Derived Based Attribute',
	'O_DBATTR');
INSERT INTO O_IOBJ
	VALUES (4718607,
	1048577,
	0,
	4194312,
	'Domain',
	'S_DOM');
INSERT INTO R_SIMP
	VALUES (4194305);
INSERT INTO R_REL
	VALUES (4194305,
	2001,
	'',
	4194312);
INSERT INTO R_PART
	VALUES (3145732,
	4194305,
	4194305,
	0,
	1,
	'optimizes instance selection of');
INSERT INTO R_RTO
	VALUES (3145732,
	4194305,
	4194305,
	1);
INSERT INTO R_OIR
	VALUES (3145732,
	4194305,
	4194305,
	4194309);
INSERT INTO R_FORM
	VALUES (4194305,
	4194305,
	4194306,
	1,
	1,
	'instance may be selected by');
INSERT INTO R_RGO
	VALUES (4194305,
	4194305,
	4194306);
INSERT INTO R_OIR
	VALUES (4194305,
	4194305,
	4194306,
	0);
INSERT INTO R_SIMP
	VALUES (4194306);
INSERT INTO R_REL
	VALUES (4194306,
	2002,
	'',
	4194312);
INSERT INTO R_PART
	VALUES (4194309,
	4194306,
	4194307,
	0,
	1,
	'constrains resources of');
INSERT INTO R_RTO
	VALUES (4194309,
	4194306,
	4194307,
	0);
INSERT INTO R_OIR
	VALUES (4194309,
	4194306,
	4194307,
	0);
INSERT INTO R_FORM
	VALUES (4194308,
	4194306,
	4194308,
	1,
	1,
	'is bounded by');
INSERT INTO R_RGO
	VALUES (4194308,
	4194306,
	4194308);
INSERT INTO R_OIR
	VALUES (4194308,
	4194306,
	4194308,
	0);
INSERT INTO R_SIMP
	VALUES (4194307);
INSERT INTO R_REL
	VALUES (4194307,
	2003,
	'',
	4194312);
INSERT INTO R_PART
	VALUES (4194309,
	4194307,
	4194309,
	0,
	1,
	'');
INSERT INTO R_RTO
	VALUES (4194309,
	4194307,
	4194309,
	0);
INSERT INTO R_OIR
	VALUES (4194309,
	4194307,
	4194309,
	0);
INSERT INTO R_FORM
	VALUES (4194310,
	4194307,
	4194310,
	1,
	1,
	'');
INSERT INTO R_RGO
	VALUES (4194310,
	4194307,
	4194310);
INSERT INTO R_OIR
	VALUES (4194310,
	4194307,
	4194310,
	0);
INSERT INTO R_SIMP
	VALUES (4194308);
INSERT INTO R_REL
	VALUES (4194308,
	2004,
	'',
	4194312);
INSERT INTO R_PART
	VALUES (4194310,
	4194308,
	4194311,
	0,
	1,
	'is managed by');
INSERT INTO R_RTO
	VALUES (4194310,
	4194308,
	4194311,
	0);
INSERT INTO R_OIR
	VALUES (4194310,
	4194308,
	4194311,
	0);
INSERT INTO R_FORM
	VALUES (4194311,
	4194308,
	4194312,
	1,
	1,
	'manages');
INSERT INTO R_RGO
	VALUES (4194311,
	4194308,
	4194312);
INSERT INTO R_OIR
	VALUES (4194311,
	4194308,
	4194312,
	0);
INSERT INTO R_SIMP
	VALUES (4194309);
INSERT INTO R_REL
	VALUES (4194309,
	2000,
	'',
	4194312);
INSERT INTO R_PART
	VALUES (4194306,
	4194309,
	4194313,
	0,
	1,
	'supports');
INSERT INTO R_RTO
	VALUES (4194306,
	4194309,
	4194313,
	0);
INSERT INTO R_OIR
	VALUES (4194306,
	4194309,
	4194313,
	0);
INSERT INTO R_FORM
	VALUES (4194312,
	4194309,
	4194314,
	0,
	1,
	'assists translation of');
INSERT INTO R_RGO
	VALUES (4194312,
	4194309,
	4194314);
INSERT INTO R_OIR
	VALUES (4194312,
	4194309,
	4194314,
	0);
INSERT INTO R_SUBSUP
	VALUES (4194310);
INSERT INTO R_REL
	VALUES (4194310,
	2009,
	'Note that relationship is only valid when an action sematics home is being translated.',
	4194312);
INSERT INTO R_SUPER
	VALUES (4194312,
	4194310,
	4194315);
INSERT INTO R_RTO
	VALUES (4194312,
	4194310,
	4194315,
	0);
INSERT INTO R_OIR
	VALUES (4194312,
	4194310,
	4194315,
	0);
INSERT INTO R_SUB
	VALUES (3145729,
	4194310,
	4194316);
INSERT INTO R_RGO
	VALUES (3145729,
	4194310,
	4194316);
INSERT INTO R_OIR
	VALUES (3145729,
	4194310,
	4194316,
	4194308);
INSERT INTO R_SUB
	VALUES (1048590,
	4194310,
	4194317);
INSERT INTO R_RGO
	VALUES (1048590,
	4194310,
	4194317);
INSERT INTO R_OIR
	VALUES (1048590,
	4194310,
	4194317,
	4194306);
INSERT INTO R_SUB
	VALUES (2621455,
	4194310,
	4194318);
INSERT INTO R_RGO
	VALUES (2621455,
	4194310,
	4194318);
INSERT INTO R_OIR
	VALUES (2621455,
	4194310,
	4194318,
	4194307);
INSERT INTO R_SUB
	VALUES (1048587,
	4194310,
	4194319);
INSERT INTO R_RGO
	VALUES (1048587,
	4194310,
	4194319);
INSERT INTO R_OIR
	VALUES (1048587,
	4194310,
	4194319,
	4194305);
INSERT INTO R_SUB
	VALUES (3145735,
	4194310,
	4194320);
INSERT INTO R_RGO
	VALUES (3145735,
	4194310,
	4194320);
INSERT INTO R_OIR
	VALUES (3145735,
	4194310,
	4194320,
	4194310);
INSERT INTO R_SUBSUP
	VALUES (4194311);
INSERT INTO R_REL
	VALUES (4194311,
	2010,
	'Note that relationship is only valid when an action sematics home is being translated.',
	4194312);
INSERT INTO R_SUPER
	VALUES (4194313,
	4194311,
	4194321);
INSERT INTO R_RTO
	VALUES (4194313,
	4194311,
	4194321,
	0);
INSERT INTO R_OIR
	VALUES (4194313,
	4194311,
	4194321,
	0);
INSERT INTO R_SUB
	VALUES (3145729,
	4194311,
	4194322);
INSERT INTO R_RGO
	VALUES (3145729,
	4194311,
	4194322);
INSERT INTO R_OIR
	VALUES (3145729,
	4194311,
	4194322,
	4194308);
INSERT INTO R_SUB
	VALUES (1048587,
	4194311,
	4194323);
INSERT INTO R_RGO
	VALUES (1048587,
	4194311,
	4194323);
INSERT INTO R_OIR
	VALUES (1048587,
	4194311,
	4194323,
	4194305);
INSERT INTO R_SUB
	VALUES (3145735,
	4194311,
	4194324);
INSERT INTO R_RGO
	VALUES (3145735,
	4194311,
	4194324);
INSERT INTO R_OIR
	VALUES (3145735,
	4194311,
	4194324,
	4194310);
INSERT INTO R_SUB
	VALUES (1048590,
	4194311,
	4194325);
INSERT INTO R_RGO
	VALUES (1048590,
	4194311,
	4194325);
INSERT INTO R_OIR
	VALUES (1048590,
	4194311,
	4194325,
	4194306);
INSERT INTO R_SUB
	VALUES (2621455,
	4194311,
	4194326);
INSERT INTO R_RGO
	VALUES (2621455,
	4194311,
	4194326);
INSERT INTO R_OIR
	VALUES (2621455,
	4194311,
	4194326,
	4194307);
INSERT INTO R_SIMP
	VALUES (4194312);
INSERT INTO R_REL
	VALUES (4194312,
	2011,
	'',
	4194312);
INSERT INTO R_PART
	VALUES (4194313,
	4194312,
	4194327,
	0,
	1,
	'scopes statements of');
INSERT INTO R_RTO
	VALUES (4194313,
	4194312,
	4194327,
	0);
INSERT INTO R_OIR
	VALUES (4194313,
	4194312,
	4194327,
	0);
INSERT INTO R_FORM
	VALUES (4194314,
	4194312,
	4194328,
	1,
	1,
	'contains');
INSERT INTO R_RGO
	VALUES (4194314,
	4194312,
	4194328);
INSERT INTO R_OIR
	VALUES (4194314,
	4194312,
	4194328,
	0);
INSERT INTO R_SIMP
	VALUES (4194313);
INSERT INTO R_REL
	VALUES (4194313,
	2012,
	'',
	4194312);
INSERT INTO R_FORM
	VALUES (4194314,
	4194313,
	4194329,
	0,
	1,
	'succeeds');
INSERT INTO R_RGO
	VALUES (4194314,
	4194313,
	4194329);
INSERT INTO R_OIR
	VALUES (4194314,
	4194313,
	4194329,
	0);
INSERT INTO R_PART
	VALUES (4194314,
	4194313,
	4194330,
	0,
	1,
	'preceeds');
INSERT INTO R_RTO
	VALUES (4194314,
	4194313,
	4194330,
	0);
INSERT INTO R_OIR
	VALUES (4194314,
	4194313,
	4194330,
	0);
INSERT INTO R_ASSOC
	VALUES (4194314);
INSERT INTO R_REL
	VALUES (4194314,
	2014,
	'',
	4194312);
INSERT INTO R_AONE
	VALUES (4194315,
	4194314,
	4194331,
	1,
	1,
	'references');
INSERT INTO R_RTO
	VALUES (4194315,
	4194314,
	4194331,
	0);
INSERT INTO R_OIR
	VALUES (4194315,
	4194314,
	4194331,
	0);
INSERT INTO R_AOTH
	VALUES (4194314,
	4194314,
	4194332,
	1,
	1,
	'is referenced by');
INSERT INTO R_RTO
	VALUES (4194314,
	4194314,
	4194332,
	0);
INSERT INTO R_OIR
	VALUES (4194314,
	4194314,
	4194332,
	0);
INSERT INTO R_ASSR
	VALUES (4194316,
	4194314,
	4194333,
	0);
INSERT INTO R_RGO
	VALUES (4194316,
	4194314,
	4194333);
INSERT INTO R_OIR
	VALUES (4194316,
	4194314,
	4194333,
	0);
INSERT INTO R_SIMP
	VALUES (4194315);
INSERT INTO R_REL
	VALUES (4194315,
	2015,
	'',
	4194312);
INSERT INTO R_FORM
	VALUES (4194315,
	4194315,
	4194334,
	0,
	1,
	'');
INSERT INTO R_RGO
	VALUES (4194315,
	4194315,
	4194334);
INSERT INTO R_OIR
	VALUES (4194315,
	4194315,
	4194334,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	4194315,
	4194335,
	0,
	1,
	'');
INSERT INTO R_RTO
	VALUES (3145732,
	4194315,
	4194335,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	4194315,
	4194335,
	4194309);
INSERT INTO R_SIMP
	VALUES (4194316);
INSERT INTO R_REL
	VALUES (4194316,
	2016,
	'',
	4194312);
INSERT INTO R_FORM
	VALUES (4194312,
	4194316,
	4194336,
	0,
	1,
	'is short cut to');
INSERT INTO R_RGO
	VALUES (4194312,
	4194316,
	4194336);
INSERT INTO R_OIR
	VALUES (4194312,
	4194316,
	4194336,
	0);
INSERT INTO R_PART
	VALUES (4194313,
	4194316,
	4194337,
	0,
	1,
	'has a');
INSERT INTO R_RTO
	VALUES (4194313,
	4194316,
	4194337,
	0);
INSERT INTO R_OIR
	VALUES (4194313,
	4194316,
	4194337,
	0);
INSERT INTO R_SIMP
	VALUES (4718638);
INSERT INTO R_REL
	VALUES (4718638,
	2017,
	'',
	4194312);
INSERT INTO R_FORM
	VALUES (4718620,
	4718638,
	4718690,
	0,
	1,
	'is current');
INSERT INTO R_RGO
	VALUES (4718620,
	4718638,
	4718690);
INSERT INTO R_OIR
	VALUES (4718620,
	4718638,
	4718690,
	0);
INSERT INTO R_PART
	VALUES (1048577,
	4718638,
	4718691,
	0,
	0,
	'is one of');
INSERT INTO R_RTO
	VALUES (1048577,
	4718638,
	4718691,
	0);
INSERT INTO R_OIR
	VALUES (1048577,
	4718638,
	4718691,
	4718607);
INSERT INTO S_SS
	VALUES (4718601,
	'Instance',
	'',
	'I',
	600,
	94514,
	4718601);
INSERT INTO O_OBJ
	VALUES (4718593,
	'Link',
	602,
	'I_LNK',
	'',
	4718601);
INSERT INTO O_NBATTR
	VALUES (4718593,
	4718593);
INSERT INTO O_BATTR
	VALUES (4718593,
	4718593);
INSERT INTO O_ATTR
	VALUES (4718593,
	4718593,
	0,
	'Link_ID',
	'',
	'',
	'Link_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718593,
	1572865,
	0,
	1572865,
	4718606,
	4718619,
	4718620,
	4718594,
	4718593,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718594,
	4718593,
	1572865,
	1572865,
	1);
INSERT INTO O_ATTR
	VALUES (4718594,
	4718593,
	4718593,
	'Rel_ID',
	'',
	'',
	'Rel_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718593,
	4718594,
	0,
	4718601,
	4718602,
	4718611,
	4718612,
	4718595,
	4718602,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718595,
	4718593,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718595,
	4718593,
	4718594,
	'From_Obj_ID',
	'',
	'From_',
	'Obj_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (4718593,
	4718594,
	0,
	4718602,
	4718602,
	4718611,
	4718612,
	4718596,
	4718603,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718596,
	4718593,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718596,
	4718593,
	4718595,
	'From_Inst_ID',
	'',
	'From_',
	'Inst_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (4718593,
	4718594,
	0,
	4718601,
	4718601,
	4718609,
	4718610,
	4718597,
	4718604,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718597,
	4718593,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718597,
	4718593,
	4718596,
	'To_Obj_ID',
	'',
	'To_',
	'Obj_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (4718593,
	4718594,
	0,
	4718602,
	4718601,
	4718609,
	4718610,
	4718598,
	4718605,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718598,
	4718593,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718598,
	4718593,
	4718597,
	'To_Inst_ID',
	'',
	'To_',
	'Inst_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (4718593,
	4718594,
	0,
	4718601,
	4718600,
	4718607,
	4718608,
	4718599,
	4718606,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718599,
	4718593,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718599,
	4718593,
	4718598,
	'Assoc_Obj_ID',
	'',
	'Assoc_',
	'Obj_ID',
	1,
	524296);
INSERT INTO O_REF
	VALUES (4718593,
	4718594,
	0,
	4718602,
	4718600,
	4718607,
	4718608,
	4718600,
	4718607,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718600,
	4718593,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718600,
	4718593,
	4718599,
	'Assoc_Inst_ID',
	'',
	'Assoc_',
	'Inst_ID',
	1,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718670,
	4718593);
INSERT INTO O_BATTR
	VALUES (4718670,
	4718593);
INSERT INTO O_ATTR
	VALUES (4718670,
	4718593,
	4718600,
	'Txt_Phrs',
	'',
	'',
	'Txt_Phrs',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718593);
INSERT INTO O_OIDA
	VALUES (4718594,
	4718593,
	0);
INSERT INTO O_OIDA
	VALUES (4718593,
	4718593,
	0);
INSERT INTO O_OBJ
	VALUES (4718594,
	'Instance',
	600,
	'I_INS',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718594,
	3145732,
	0,
	3145773,
	4718604,
	4718615,
	4718616,
	4718601,
	4718594,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718601,
	4718594,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718601,
	4718594,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718602,
	4718594);
INSERT INTO O_BATTR
	VALUES (4718602,
	4718594);
INSERT INTO O_ATTR
	VALUES (4718602,
	4718594,
	4718601,
	'Inst_ID',
	'',
	'',
	'Inst_ID',
	0,
	524294);
INSERT INTO O_NBATTR
	VALUES (4718668,
	4718594);
INSERT INTO O_BATTR
	VALUES (4718668,
	4718594);
INSERT INTO O_ATTR
	VALUES (4718668,
	4718594,
	4718602,
	'Array_Index',
	'',
	'',
	'Array_Index',
	0,
	524291);
INSERT INTO O_ID
	VALUES (0,
	4718594);
INSERT INTO O_OIDA
	VALUES (4718602,
	4718594,
	0);
INSERT INTO O_RTIDA
	VALUES (4718602,
	4718594,
	0,
	4718602,
	4718612);
INSERT INTO O_RTIDA
	VALUES (4718602,
	4718594,
	0,
	4718596,
	4718599);
INSERT INTO O_RTIDA
	VALUES (4718602,
	4718594,
	0,
	4718593,
	4718593);
INSERT INTO O_RTIDA
	VALUES (4718602,
	4718594,
	0,
	4718601,
	4718610);
INSERT INTO O_RTIDA
	VALUES (4718602,
	4718594,
	0,
	4718600,
	4718608);
INSERT INTO O_RTIDA
	VALUES (4718602,
	4718594,
	0,
	4718603,
	4718613);
INSERT INTO O_OIDA
	VALUES (4718601,
	4718594,
	0);
INSERT INTO O_RTIDA
	VALUES (4718601,
	4718594,
	0,
	4718593,
	4718593);
INSERT INTO O_RTIDA
	VALUES (4718601,
	4718594,
	0,
	4718596,
	4718599);
INSERT INTO O_RTIDA
	VALUES (4718601,
	4718594,
	0,
	4718601,
	4718610);
INSERT INTO O_RTIDA
	VALUES (4718601,
	4718594,
	0,
	4718600,
	4718608);
INSERT INTO O_RTIDA
	VALUES (4718601,
	4718594,
	0,
	4718602,
	4718612);
INSERT INTO O_RTIDA
	VALUES (4718601,
	4718594,
	0,
	4718603,
	4718613);
INSERT INTO O_OBJ
	VALUES (4718595,
	'Value',
	601,
	'I_AVL',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718595,
	3145731,
	0,
	3145759,
	4718605,
	4718617,
	4718618,
	4718603,
	4718595,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4718595,
	4718594,
	0,
	4718601,
	4718603,
	4718614,
	4718613,
	4718603,
	4718608,
	4718595,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718603,
	4718595,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718603,
	4718595,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718595,
	4718594,
	0,
	4718602,
	4718603,
	4718614,
	4718613,
	4718604,
	4718609,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718604,
	4718595,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718604,
	4718595,
	4718603,
	'Inst_ID',
	'',
	'',
	'Inst_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718595,
	3145731,
	0,
	3145758,
	4718605,
	4718617,
	4718618,
	4718605,
	4718596,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718605,
	4718595,
	3145758,
	3145731,
	1);
INSERT INTO O_ATTR
	VALUES (4718605,
	4718595,
	4718604,
	'Attr_ID',
	'',
	'',
	'Attr_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718606,
	4718595);
INSERT INTO O_BATTR
	VALUES (4718606,
	4718595);
INSERT INTO O_ATTR
	VALUES (4718606,
	4718595,
	4718605,
	'Value',
	'',
	'',
	'Value',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718595);
INSERT INTO O_OIDA
	VALUES (4718605,
	4718595,
	0);
INSERT INTO O_OIDA
	VALUES (4718603,
	4718595,
	0);
INSERT INTO O_OIDA
	VALUES (4718604,
	4718595,
	0);
INSERT INTO O_OBJ
	VALUES (4718596,
	'Event Instance',
	603,
	'I_EVI',
	'',
	4718601);
INSERT INTO O_NBATTR
	VALUES (4718607,
	4718596);
INSERT INTO O_BATTR
	VALUES (4718607,
	4718596);
INSERT INTO O_ATTR
	VALUES (4718607,
	4718596,
	0,
	'EvtInst_ID',
	'',
	'',
	'EvtInst_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718596,
	4718600,
	0,
	4718625,
	4718597,
	4718602,
	4718601,
	4718608,
	4718610,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718608,
	4718596,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718608,
	4718596,
	4718607,
	'Inst_ID',
	'',
	'',
	'Inst_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718596,
	2621443,
	1,
	2621454,
	4718611,
	4718630,
	4718629,
	4718609,
	4718611,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4718596,
	4718600,
	0,
	4718626,
	4718597,
	4718602,
	4718601,
	4718609,
	4718612,
	4718611,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718609,
	4718596,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (4718609,
	4718596,
	4718608,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718596,
	2621443,
	1,
	2621453,
	4718611,
	4718630,
	4718629,
	4718610,
	4718613,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718610,
	4718596,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (4718610,
	4718596,
	4718609,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718596,
	2621443,
	1,
	2621455,
	4718611,
	4718630,
	4718629,
	4718611,
	4718614,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718611,
	4718596,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (4718611,
	4718596,
	4718610,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4718596);
INSERT INTO O_OIDA
	VALUES (4718607,
	4718596,
	0);
INSERT INTO O_RTIDA
	VALUES (4718607,
	4718596,
	0,
	4718599,
	4718605);
INSERT INTO O_OIDA
	VALUES (4718610,
	4718596,
	0);
INSERT INTO O_RTIDA
	VALUES (4718610,
	4718596,
	0,
	4718599,
	4718605);
INSERT INTO O_OIDA
	VALUES (4718611,
	4718596,
	0);
INSERT INTO O_RTIDA
	VALUES (4718611,
	4718596,
	0,
	4718599,
	4718605);
INSERT INTO O_OIDA
	VALUES (4718609,
	4718596,
	0);
INSERT INTO O_RTIDA
	VALUES (4718609,
	4718596,
	0,
	4718599,
	4718605);
INSERT INTO O_OBJ
	VALUES (4718597,
	'Actual Data Item',
	604,
	'I_ADI',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718597,
	4718596,
	0,
	4718607,
	4718599,
	4718606,
	4718605,
	4718612,
	4718615,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718612,
	4718597,
	4718607,
	4718596,
	1);
INSERT INTO O_ATTR
	VALUES (4718612,
	4718597,
	0,
	'EvtInst_ID',
	'',
	'',
	'EvtInst_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718597,
	4718596,
	0,
	4718609,
	4718599,
	4718606,
	4718605,
	4718613,
	4718616,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4718597,
	2621458,
	0,
	2621542,
	4718612,
	4718632,
	4718631,
	4718613,
	4718617,
	4718616,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718613,
	4718597,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (4718613,
	4718597,
	4718612,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718597,
	4718596,
	0,
	4718610,
	4718599,
	4718606,
	4718605,
	4718614,
	4718618,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718614,
	4718597,
	2621453,
	2621443,
	1);
INSERT INTO O_ATTR
	VALUES (4718614,
	4718597,
	4718613,
	'SMevt_ID',
	'',
	'',
	'SMevt_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718597,
	4718596,
	0,
	4718611,
	4718599,
	4718606,
	4718605,
	4718615,
	4718619,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4718597,
	2621458,
	0,
	2621541,
	4718612,
	4718632,
	4718631,
	4718615,
	4718620,
	4718619,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718615,
	4718597,
	2621537,
	2621457,
	1);
INSERT INTO O_ATTR
	VALUES (4718615,
	4718597,
	4718614,
	'SMspd_ID',
	'',
	'',
	'SMspd_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718597,
	2621458,
	0,
	2621540,
	4718612,
	4718632,
	4718631,
	4718616,
	4718621,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718616,
	4718597,
	2621530,
	2621456,
	1);
INSERT INTO O_ATTR
	VALUES (4718616,
	4718597,
	4718615,
	'SMedi_ID',
	'',
	'',
	'SMedi_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718617,
	4718597);
INSERT INTO O_BATTR
	VALUES (4718617,
	4718597);
INSERT INTO O_ATTR
	VALUES (4718617,
	4718597,
	4718616,
	'Value',
	'',
	'',
	'Value',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718597);
INSERT INTO O_OIDA
	VALUES (4718616,
	4718597,
	0);
INSERT INTO O_OIDA
	VALUES (4718615,
	4718597,
	0);
INSERT INTO O_OIDA
	VALUES (4718613,
	4718597,
	0);
INSERT INTO O_OIDA
	VALUES (4718612,
	4718597,
	0);
INSERT INTO O_OBJ
	VALUES (4718598,
	'Function Invocation',
	605,
	'I_FIN',
	'',
	4718601);
INSERT INTO O_NBATTR
	VALUES (4718618,
	4718598);
INSERT INTO O_BATTR
	VALUES (4718618,
	4718598);
INSERT INTO O_ATTR
	VALUES (4718618,
	4718598,
	0,
	'FuncInv_ID',
	'',
	'',
	'FuncInv_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718598,
	1048590,
	0,
	1048689,
	4718614,
	4718636,
	4718635,
	4718619,
	4718622,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718619,
	4718598,
	1048689,
	1048590,
	1);
INSERT INTO O_ATTR
	VALUES (4718619,
	4718598,
	4718618,
	'Sync_ID',
	'',
	'',
	'Sync_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4718598);
INSERT INTO O_OIDA
	VALUES (4718618,
	4718598,
	0);
INSERT INTO O_RTIDA
	VALUES (4718618,
	4718598,
	0,
	4718598,
	4718603);
INSERT INTO O_OIDA
	VALUES (4718619,
	4718598,
	0);
INSERT INTO O_RTIDA
	VALUES (4718619,
	4718598,
	0,
	4718598,
	4718603);
INSERT INTO O_OBJ
	VALUES (4718599,
	'Actual Function Parameter',
	606,
	'I_AFP',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718599,
	4718598,
	0,
	4718618,
	4718598,
	4718604,
	4718603,
	4718620,
	4718623,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718620,
	4718599,
	4718618,
	4718598,
	1);
INSERT INTO O_ATTR
	VALUES (4718620,
	4718599,
	0,
	'FuncInv_ID',
	'',
	'',
	'FuncInv_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718599,
	1048591,
	1,
	1048708,
	4718615,
	4718637,
	4718638,
	4718621,
	4718597,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4718599,
	4718598,
	0,
	4718619,
	4718598,
	4718604,
	4718603,
	4718621,
	4718624,
	4718597,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718621,
	4718599,
	1048689,
	1048590,
	1);
INSERT INTO O_ATTR
	VALUES (4718621,
	4718599,
	4718620,
	'Sync_ID',
	'',
	'',
	'Sync_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718599,
	1048591,
	1,
	1048707,
	4718615,
	4718637,
	4718638,
	4718622,
	4718598,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718622,
	4718599,
	1048707,
	1048591,
	1);
INSERT INTO O_ATTR
	VALUES (4718622,
	4718599,
	4718621,
	'SParm_ID',
	'',
	'',
	'SParm_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718623,
	4718599);
INSERT INTO O_BATTR
	VALUES (4718623,
	4718599);
INSERT INTO O_ATTR
	VALUES (4718623,
	4718599,
	4718622,
	'Value',
	'',
	'',
	'Value',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718599);
INSERT INTO O_OIDA
	VALUES (4718620,
	4718599,
	0);
INSERT INTO O_OIDA
	VALUES (4718622,
	4718599,
	0);
INSERT INTO O_OIDA
	VALUES (4718621,
	4718599,
	0);
INSERT INTO O_OBJ
	VALUES (4718600,
	'State Machine',
	607,
	'I_SMC',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718600,
	4718594,
	0,
	4718601,
	4718596,
	4718600,
	4718599,
	4718624,
	4718625,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718624,
	4718600,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718624,
	4718600,
	0,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718600,
	4718594,
	0,
	4718602,
	4718596,
	4718600,
	4718599,
	4718625,
	4718626,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718625,
	4718600,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718625,
	4718600,
	4718624,
	'Inst_ID',
	'',
	'',
	'Inst_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718600,
	2621460,
	1,
	2621547,
	4718610,
	4718628,
	4718627,
	4718626,
	4718627,
	0,
	0,
	'');
INSERT INTO O_REF
	VALUES (4718600,
	2621459,
	1,
	2621543,
	4718609,
	4718626,
	4718625,
	4718626,
	4718628,
	4718627,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718626,
	4718600,
	2621441,
	2621441,
	1);
INSERT INTO O_ATTR
	VALUES (4718626,
	4718600,
	4718625,
	'SM_ID',
	'',
	'',
	'SM_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718627,
	4718600);
INSERT INTO O_BATTR
	VALUES (4718627,
	4718600);
INSERT INTO O_ATTR
	VALUES (4718627,
	4718600,
	4718626,
	'SMstt_ID',
	'',
	'',
	'SMstt_ID',
	0,
	524294);
INSERT INTO O_ID
	VALUES (0,
	4718600);
INSERT INTO O_OIDA
	VALUES (4718626,
	4718600,
	0);
INSERT INTO O_RTIDA
	VALUES (4718626,
	4718600,
	0,
	4718597,
	4718601);
INSERT INTO O_OIDA
	VALUES (4718625,
	4718600,
	0);
INSERT INTO O_RTIDA
	VALUES (4718625,
	4718600,
	0,
	4718597,
	4718601);
INSERT INTO O_OBJ
	VALUES (4718601,
	'Transformer Invocation',
	608,
	'I_TRI',
	'',
	4718601);
INSERT INTO O_NBATTR
	VALUES (4718628,
	4718601);
INSERT INTO O_BATTR
	VALUES (4718628,
	4718601);
INSERT INTO O_ATTR
	VALUES (4718628,
	4718601,
	0,
	'TrInv_ID',
	'',
	'',
	'TrInv_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718601,
	3145729,
	0,
	3145729,
	4718607,
	4718621,
	4718622,
	4718629,
	4718599,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718629,
	4718601,
	3145729,
	3145729,
	1);
INSERT INTO O_ATTR
	VALUES (4718629,
	4718601,
	4718628,
	'Tfr_ID',
	'',
	'',
	'Tfr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718601,
	4718594,
	0,
	4718601,
	4718593,
	4718594,
	4718593,
	4718630,
	4718629,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718630,
	4718601,
	3145773,
	3145732,
	1);
INSERT INTO O_ATTR
	VALUES (4718630,
	4718601,
	4718629,
	'Obj_ID',
	'',
	'',
	'Obj_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718601,
	4718594,
	0,
	4718602,
	4718593,
	4718594,
	4718593,
	4718631,
	4718630,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718631,
	4718601,
	4718602,
	4718594,
	1);
INSERT INTO O_ATTR
	VALUES (4718631,
	4718601,
	4718630,
	'Inst_ID',
	'',
	'',
	'Inst_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4718601);
INSERT INTO O_OIDA
	VALUES (4718629,
	4718601,
	0);
INSERT INTO O_RTIDA
	VALUES (4718629,
	4718601,
	0,
	4718595,
	4718597);
INSERT INTO O_OIDA
	VALUES (4718628,
	4718601,
	0);
INSERT INTO O_RTIDA
	VALUES (4718628,
	4718601,
	0,
	4718595,
	4718597);
INSERT INTO O_OBJ
	VALUES (4718602,
	'Actual Transformer Parameter',
	609,
	'I_ATP',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718602,
	4718601,
	0,
	4718628,
	4718595,
	4718598,
	4718597,
	4718632,
	4718631,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718632,
	4718602,
	4718628,
	4718601,
	1);
INSERT INTO O_ATTR
	VALUES (4718632,
	4718602,
	0,
	'TrInv_ID',
	'',
	'',
	'TrInv_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718602,
	4718601,
	0,
	4718629,
	4718595,
	4718598,
	4718597,
	4718633,
	4718632,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718633,
	4718602,
	3145729,
	3145729,
	1);
INSERT INTO O_ATTR
	VALUES (4718633,
	4718602,
	4718632,
	'Tfr_ID',
	'',
	'',
	'Tfr_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718602,
	3145730,
	0,
	3145751,
	4718608,
	4718624,
	4718623,
	4718634,
	4718633,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718634,
	4718602,
	3145751,
	3145730,
	1);
INSERT INTO O_ATTR
	VALUES (4718634,
	4718602,
	4718633,
	'TParm_ID',
	'',
	'',
	'TParm_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718635,
	4718602);
INSERT INTO O_BATTR
	VALUES (4718635,
	4718602);
INSERT INTO O_ATTR
	VALUES (4718635,
	4718602,
	4718634,
	'Value',
	'',
	'',
	'Value',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718602);
INSERT INTO O_OIDA
	VALUES (4718634,
	4718602,
	0);
INSERT INTO O_OIDA
	VALUES (4718633,
	4718602,
	0);
INSERT INTO O_OIDA
	VALUES (4718632,
	4718602,
	0);
INSERT INTO O_OBJ
	VALUES (4718603,
	'Bridge Invocation',
	610,
	'I_BRI',
	'',
	4718601);
INSERT INTO O_NBATTR
	VALUES (4718636,
	4718603);
INSERT INTO O_BATTR
	VALUES (4718636,
	4718603);
INSERT INTO O_ATTR
	VALUES (4718636,
	4718603,
	0,
	'BrgInv_ID',
	'',
	'',
	'BrgInv_ID',
	0,
	524294);
INSERT INTO O_REF
	VALUES (4718603,
	1048587,
	0,
	1048660,
	4718613,
	4718633,
	4718634,
	4718637,
	4718600,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718637,
	4718603,
	1048660,
	1048587,
	1);
INSERT INTO O_ATTR
	VALUES (4718637,
	4718603,
	4718636,
	'Brg_ID',
	'',
	'',
	'Brg_ID',
	0,
	524296);
INSERT INTO O_ID
	VALUES (0,
	4718603);
INSERT INTO O_OIDA
	VALUES (4718636,
	4718603,
	0);
INSERT INTO O_RTIDA
	VALUES (4718636,
	4718603,
	0,
	4718594,
	4718595);
INSERT INTO O_OIDA
	VALUES (4718637,
	4718603,
	0);
INSERT INTO O_RTIDA
	VALUES (4718637,
	4718603,
	0,
	4718594,
	4718595);
INSERT INTO O_OBJ
	VALUES (4718604,
	'Actual Bridge Parameter',
	611,
	'I_ABP',
	'',
	4718601);
INSERT INTO O_REF
	VALUES (4718604,
	4718603,
	0,
	4718636,
	4718594,
	4718596,
	4718595,
	4718638,
	4718634,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718638,
	4718604,
	4718636,
	4718603,
	1);
INSERT INTO O_ATTR
	VALUES (4718638,
	4718604,
	0,
	'BrgInv_ID',
	'',
	'',
	'BrgInv_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718604,
	4718603,
	0,
	4718637,
	4718594,
	4718596,
	4718595,
	4718639,
	4718635,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718639,
	4718604,
	1048660,
	1048587,
	1);
INSERT INTO O_ATTR
	VALUES (4718639,
	4718604,
	4718638,
	'Brg_ID',
	'',
	'',
	'Brg_ID',
	0,
	524296);
INSERT INTO O_REF
	VALUES (4718604,
	1048588,
	0,
	1048679,
	4718616,
	4718639,
	4718640,
	4718640,
	4718601,
	0,
	0,
	'');
INSERT INTO O_RATTR
	VALUES (4718640,
	4718604,
	1048679,
	1048588,
	1);
INSERT INTO O_ATTR
	VALUES (4718640,
	4718604,
	4718639,
	'BParm_ID',
	'',
	'',
	'BParm_ID',
	0,
	524296);
INSERT INTO O_NBATTR
	VALUES (4718641,
	4718604);
INSERT INTO O_BATTR
	VALUES (4718641,
	4718604);
INSERT INTO O_ATTR
	VALUES (4718641,
	4718604,
	4718640,
	'Value',
	'',
	'',
	'Value',
	0,
	524293);
INSERT INTO O_ID
	VALUES (0,
	4718604);
INSERT INTO O_OIDA
	VALUES (4718640,
	4718604,
	0);
INSERT INTO O_OIDA
	VALUES (4718638,
	4718604,
	0);
INSERT INTO O_OIDA
	VALUES (4718639,
	4718604,
	0);
INSERT INTO O_IOBJ
	VALUES (4718593,
	3145732,
	5,
	4718601,
	'Class',
	'O_OBJ');
INSERT INTO O_IOBJ
	VALUES (4718594,
	3145731,
	5,
	4718601,
	'Attribute',
	'O_ATTR');
INSERT INTO O_IOBJ
	VALUES (4718595,
	1572865,
	5,
	4718601,
	'Relationship',
	'R_REL');
INSERT INTO O_IOBJ
	VALUES (4718596,
	3145729,
	5,
	4718601,
	'Transformer',
	'O_TFR');
INSERT INTO O_IOBJ
	VALUES (4718597,
	3145730,
	5,
	4718601,
	'Transformer Parameter',
	'O_TPARM');
INSERT INTO O_IOBJ
	VALUES (4718598,
	2621459,
	5,
	4718601,
	'Instance State Model',
	'SM_ISM');
INSERT INTO O_IOBJ
	VALUES (4718599,
	2621460,
	5,
	4718601,
	'Assigner State Model',
	'SM_ASM');
INSERT INTO O_IOBJ
	VALUES (4718600,
	2621443,
	5,
	4718601,
	'State Model Event',
	'SM_EVT');
INSERT INTO O_IOBJ
	VALUES (4718601,
	2621458,
	5,
	4718601,
	'Supplemental Data Items',
	'SM_SDI');
INSERT INTO O_IOBJ
	VALUES (4718602,
	1048587,
	5,
	4718601,
	'Bridge',
	'S_BRG');
INSERT INTO O_IOBJ
	VALUES (4718603,
	1048590,
	5,
	4718601,
	'Function',
	'S_SYNC');
INSERT INTO O_IOBJ
	VALUES (4718604,
	1048588,
	5,
	4718601,
	'Bridge Parameter',
	'S_BPARM');
INSERT INTO O_IOBJ
	VALUES (4718605,
	1048591,
	5,
	4718601,
	'Function Parameter',
	'S_SPARM');
INSERT INTO R_SIMP
	VALUES (4718593);
INSERT INTO R_REL
	VALUES (4718593,
	623,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718594,
	4718593,
	4718593,
	0,
	1,
	'is invoked on');
INSERT INTO R_RTO
	VALUES (4718594,
	4718593,
	4718593,
	0);
INSERT INTO R_OIR
	VALUES (4718594,
	4718593,
	4718593,
	0);
INSERT INTO R_FORM
	VALUES (4718601,
	4718593,
	4718594,
	1,
	1,
	'has invoked on');
INSERT INTO R_RGO
	VALUES (4718601,
	4718593,
	4718594);
INSERT INTO R_OIR
	VALUES (4718601,
	4718593,
	4718594,
	0);
INSERT INTO R_SIMP
	VALUES (4718594);
INSERT INTO R_REL
	VALUES (4718594,
	621,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718603,
	4718594,
	4718595,
	0,
	0,
	'');
INSERT INTO R_RTO
	VALUES (4718603,
	4718594,
	4718595,
	0);
INSERT INTO R_OIR
	VALUES (4718603,
	4718594,
	4718595,
	0);
INSERT INTO R_FORM
	VALUES (4718604,
	4718594,
	4718596,
	1,
	1,
	'');
INSERT INTO R_RGO
	VALUES (4718604,
	4718594,
	4718596);
INSERT INTO R_OIR
	VALUES (4718604,
	4718594,
	4718596,
	0);
INSERT INTO R_SIMP
	VALUES (4718595);
INSERT INTO R_REL
	VALUES (4718595,
	618,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718601,
	4718595,
	4718597,
	0,
	0,
	'carried by');
INSERT INTO R_RTO
	VALUES (4718601,
	4718595,
	4718597,
	0);
INSERT INTO R_OIR
	VALUES (4718601,
	4718595,
	4718597,
	0);
INSERT INTO R_FORM
	VALUES (4718602,
	4718595,
	4718598,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (4718602,
	4718595,
	4718598);
INSERT INTO R_OIR
	VALUES (4718602,
	4718595,
	4718598,
	0);
INSERT INTO R_SIMP
	VALUES (4718596);
INSERT INTO R_REL
	VALUES (4718596,
	616,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718594,
	4718596,
	4718599,
	0,
	1,
	'represents current state of');
INSERT INTO R_RTO
	VALUES (4718594,
	4718596,
	4718599,
	0);
INSERT INTO R_OIR
	VALUES (4718594,
	4718596,
	4718599,
	0);
INSERT INTO R_FORM
	VALUES (4718600,
	4718596,
	4718600,
	0,
	1,
	'may have');
INSERT INTO R_RGO
	VALUES (4718600,
	4718596,
	4718600);
INSERT INTO R_OIR
	VALUES (4718600,
	4718596,
	4718600,
	0);
INSERT INTO R_SIMP
	VALUES (4718597);
INSERT INTO R_REL
	VALUES (4718597,
	613,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718600,
	4718597,
	4718601,
	0,
	0,
	'is waiting in queue of');
INSERT INTO R_RTO
	VALUES (4718600,
	4718597,
	4718601,
	0);
INSERT INTO R_OIR
	VALUES (4718600,
	4718597,
	4718601,
	0);
INSERT INTO R_FORM
	VALUES (4718596,
	4718597,
	4718602,
	1,
	1,
	'has enqueued');
INSERT INTO R_RGO
	VALUES (4718596,
	4718597,
	4718602);
INSERT INTO R_OIR
	VALUES (4718596,
	4718597,
	4718602,
	0);
INSERT INTO R_SIMP
	VALUES (4718598);
INSERT INTO R_REL
	VALUES (4718598,
	611,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718598,
	4718598,
	4718603,
	0,
	0,
	'carried by');
INSERT INTO R_RTO
	VALUES (4718598,
	4718598,
	4718603,
	0);
INSERT INTO R_OIR
	VALUES (4718598,
	4718598,
	4718603,
	0);
INSERT INTO R_FORM
	VALUES (4718599,
	4718598,
	4718604,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (4718599,
	4718598,
	4718604);
INSERT INTO R_OIR
	VALUES (4718599,
	4718598,
	4718604,
	0);
INSERT INTO R_SIMP
	VALUES (4718599);
INSERT INTO R_REL
	VALUES (4718599,
	608,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718596,
	4718599,
	4718605,
	0,
	0,
	'is carried by');
INSERT INTO R_RTO
	VALUES (4718596,
	4718599,
	4718605,
	0);
INSERT INTO R_OIR
	VALUES (4718596,
	4718599,
	4718605,
	0);
INSERT INTO R_FORM
	VALUES (4718597,
	4718599,
	4718606,
	1,
	1,
	'carries');
INSERT INTO R_RGO
	VALUES (4718597,
	4718599,
	4718606);
INSERT INTO R_OIR
	VALUES (4718597,
	4718599,
	4718606,
	0);
INSERT INTO R_SIMP
	VALUES (4718600);
INSERT INTO R_REL
	VALUES (4718600,
	606,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718593,
	4718600,
	4718607,
	1,
	1,
	'');
INSERT INTO R_RGO
	VALUES (4718593,
	4718600,
	4718607);
INSERT INTO R_OIR
	VALUES (4718593,
	4718600,
	4718607,
	0);
INSERT INTO R_PART
	VALUES (4718594,
	4718600,
	4718608,
	0,
	1,
	'has associative');
INSERT INTO R_RTO
	VALUES (4718594,
	4718600,
	4718608,
	0);
INSERT INTO R_OIR
	VALUES (4718594,
	4718600,
	4718608,
	0);
INSERT INTO R_SIMP
	VALUES (4718601);
INSERT INTO R_REL
	VALUES (4718601,
	605,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718593,
	4718601,
	4718609,
	1,
	0,
	'');
INSERT INTO R_RGO
	VALUES (4718593,
	4718601,
	4718609);
INSERT INTO R_OIR
	VALUES (4718593,
	4718601,
	4718609,
	0);
INSERT INTO R_PART
	VALUES (4718594,
	4718601,
	4718610,
	0,
	0,
	'refers to');
INSERT INTO R_RTO
	VALUES (4718594,
	4718601,
	4718610,
	0);
INSERT INTO R_OIR
	VALUES (4718594,
	4718601,
	4718610,
	0);
INSERT INTO R_SIMP
	VALUES (4718602);
INSERT INTO R_REL
	VALUES (4718602,
	604,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718593,
	4718602,
	4718611,
	1,
	1,
	'');
INSERT INTO R_RGO
	VALUES (4718593,
	4718602,
	4718611);
INSERT INTO R_OIR
	VALUES (4718593,
	4718602,
	4718611,
	0);
INSERT INTO R_PART
	VALUES (4718594,
	4718602,
	4718612,
	0,
	0,
	'refers from');
INSERT INTO R_RTO
	VALUES (4718594,
	4718602,
	4718612,
	0);
INSERT INTO R_OIR
	VALUES (4718594,
	4718602,
	4718612,
	0);
INSERT INTO R_SIMP
	VALUES (4718603);
INSERT INTO R_REL
	VALUES (4718603,
	602,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (4718594,
	4718603,
	4718613,
	0,
	0,
	'defines value of characteristic');
INSERT INTO R_RTO
	VALUES (4718594,
	4718603,
	4718613,
	0);
INSERT INTO R_OIR
	VALUES (4718594,
	4718603,
	4718613,
	0);
INSERT INTO R_FORM
	VALUES (4718595,
	4718603,
	4718614,
	1,
	1,
	'has characteristrics defined by');
INSERT INTO R_RGO
	VALUES (4718595,
	4718603,
	4718614);
INSERT INTO R_OIR
	VALUES (4718595,
	4718603,
	4718614,
	0);
INSERT INTO R_SIMP
	VALUES (4718604);
INSERT INTO R_REL
	VALUES (4718604,
	600,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718594,
	4718604,
	4718615,
	1,
	1,
	'has instances');
INSERT INTO R_RGO
	VALUES (4718594,
	4718604,
	4718615);
INSERT INTO R_OIR
	VALUES (4718594,
	4718604,
	4718615,
	0);
INSERT INTO R_PART
	VALUES (3145732,
	4718604,
	4718616,
	0,
	0,
	'is instance of');
INSERT INTO R_RTO
	VALUES (3145732,
	4718604,
	4718616,
	0);
INSERT INTO R_OIR
	VALUES (3145732,
	4718604,
	4718616,
	4718593);
INSERT INTO R_SIMP
	VALUES (4718605);
INSERT INTO R_REL
	VALUES (4718605,
	601,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718595,
	4718605,
	4718617,
	1,
	1,
	'represents abstraction');
INSERT INTO R_RGO
	VALUES (4718595,
	4718605,
	4718617);
INSERT INTO R_OIR
	VALUES (4718595,
	4718605,
	4718617,
	0);
INSERT INTO R_PART
	VALUES (3145731,
	4718605,
	4718618,
	0,
	0,
	'is systematically abstracted by');
INSERT INTO R_RTO
	VALUES (3145731,
	4718605,
	4718618,
	0);
INSERT INTO R_OIR
	VALUES (3145731,
	4718605,
	4718618,
	4718594);
INSERT INTO R_SIMP
	VALUES (4718606);
INSERT INTO R_REL
	VALUES (4718606,
	603,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718593,
	4718606,
	4718619,
	1,
	1,
	'has instances');
INSERT INTO R_RGO
	VALUES (4718593,
	4718606,
	4718619);
INSERT INTO R_OIR
	VALUES (4718593,
	4718606,
	4718619,
	0);
INSERT INTO R_PART
	VALUES (1572865,
	4718606,
	4718620,
	0,
	0,
	'is instance of');
INSERT INTO R_RTO
	VALUES (1572865,
	4718606,
	4718620,
	0);
INSERT INTO R_OIR
	VALUES (1572865,
	4718606,
	4718620,
	4718595);
INSERT INTO R_SIMP
	VALUES (4718607);
INSERT INTO R_REL
	VALUES (4718607,
	617,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718601,
	4718607,
	4718621,
	1,
	1,
	'has invocations');
INSERT INTO R_RGO
	VALUES (4718601,
	4718607,
	4718621);
INSERT INTO R_OIR
	VALUES (4718601,
	4718607,
	4718621,
	0);
INSERT INTO R_PART
	VALUES (3145729,
	4718607,
	4718622,
	0,
	0,
	'is invocation of');
INSERT INTO R_RTO
	VALUES (3145729,
	4718607,
	4718622,
	0);
INSERT INTO R_OIR
	VALUES (3145729,
	4718607,
	4718622,
	4718596);
INSERT INTO R_SIMP
	VALUES (4718608);
INSERT INTO R_REL
	VALUES (4718608,
	619,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (3145730,
	4718608,
	4718623,
	0,
	0,
	'is actual value of');
INSERT INTO R_RTO
	VALUES (3145730,
	4718608,
	4718623,
	0);
INSERT INTO R_OIR
	VALUES (3145730,
	4718608,
	4718623,
	4718597);
INSERT INTO R_FORM
	VALUES (4718602,
	4718608,
	4718624,
	1,
	1,
	'has actual value');
INSERT INTO R_RGO
	VALUES (4718602,
	4718608,
	4718624);
INSERT INTO R_OIR
	VALUES (4718602,
	4718608,
	4718624,
	0);
INSERT INTO R_SIMP
	VALUES (4718609);
INSERT INTO R_REL
	VALUES (4718609,
	614,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (2621459,
	4718609,
	4718625,
	0,
	1,
	'is instance of');
INSERT INTO R_RTO
	VALUES (2621459,
	4718609,
	4718625,
	1);
INSERT INTO R_OIR
	VALUES (2621459,
	4718609,
	4718625,
	4718598);
INSERT INTO R_FORM
	VALUES (4718600,
	4718609,
	4718626,
	1,
	1,
	'has instances');
INSERT INTO R_RGO
	VALUES (4718600,
	4718609,
	4718626);
INSERT INTO R_OIR
	VALUES (4718600,
	4718609,
	4718626,
	0);
INSERT INTO R_SIMP
	VALUES (4718610);
INSERT INTO R_REL
	VALUES (4718610,
	615,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (2621460,
	4718610,
	4718627,
	0,
	1,
	'is instance of');
INSERT INTO R_RTO
	VALUES (2621460,
	4718610,
	4718627,
	1);
INSERT INTO R_OIR
	VALUES (2621460,
	4718610,
	4718627,
	4718599);
INSERT INTO R_FORM
	VALUES (4718600,
	4718610,
	4718628,
	0,
	0,
	'has instances');
INSERT INTO R_RGO
	VALUES (4718600,
	4718610,
	4718628);
INSERT INTO R_OIR
	VALUES (4718600,
	4718610,
	4718628,
	0);
INSERT INTO R_SIMP
	VALUES (4718611);
INSERT INTO R_REL
	VALUES (4718611,
	607,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (2621443,
	4718611,
	4718629,
	0,
	0,
	'is instance of');
INSERT INTO R_RTO
	VALUES (2621443,
	4718611,
	4718629,
	1);
INSERT INTO R_OIR
	VALUES (2621443,
	4718611,
	4718629,
	4718600);
INSERT INTO R_FORM
	VALUES (4718596,
	4718611,
	4718630,
	1,
	1,
	'has instances');
INSERT INTO R_RGO
	VALUES (4718596,
	4718611,
	4718630);
INSERT INTO R_OIR
	VALUES (4718596,
	4718611,
	4718630,
	0);
INSERT INTO R_SIMP
	VALUES (4718612);
INSERT INTO R_REL
	VALUES (4718612,
	609,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (2621458,
	4718612,
	4718631,
	0,
	0,
	'is actual value of');
INSERT INTO R_RTO
	VALUES (2621458,
	4718612,
	4718631,
	0);
INSERT INTO R_OIR
	VALUES (2621458,
	4718612,
	4718631,
	4718601);
INSERT INTO R_FORM
	VALUES (4718597,
	4718612,
	4718632,
	1,
	1,
	'has actual value');
INSERT INTO R_RGO
	VALUES (4718597,
	4718612,
	4718632);
INSERT INTO R_OIR
	VALUES (4718597,
	4718612,
	4718632,
	0);
INSERT INTO R_SIMP
	VALUES (4718613);
INSERT INTO R_REL
	VALUES (4718613,
	620,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718603,
	4718613,
	4718633,
	1,
	1,
	'has invocations');
INSERT INTO R_RGO
	VALUES (4718603,
	4718613,
	4718633);
INSERT INTO R_OIR
	VALUES (4718603,
	4718613,
	4718633,
	0);
INSERT INTO R_PART
	VALUES (1048587,
	4718613,
	4718634,
	0,
	0,
	'is invocation of');
INSERT INTO R_RTO
	VALUES (1048587,
	4718613,
	4718634,
	0);
INSERT INTO R_OIR
	VALUES (1048587,
	4718613,
	4718634,
	4718602);
INSERT INTO R_SIMP
	VALUES (4718614);
INSERT INTO R_REL
	VALUES (4718614,
	610,
	'',
	4718601);
INSERT INTO R_PART
	VALUES (1048590,
	4718614,
	4718635,
	0,
	0,
	'is invocation of');
INSERT INTO R_RTO
	VALUES (1048590,
	4718614,
	4718635,
	0);
INSERT INTO R_OIR
	VALUES (1048590,
	4718614,
	4718635,
	4718603);
INSERT INTO R_FORM
	VALUES (4718598,
	4718614,
	4718636,
	1,
	1,
	'has invocations');
INSERT INTO R_RGO
	VALUES (4718598,
	4718614,
	4718636);
INSERT INTO R_OIR
	VALUES (4718598,
	4718614,
	4718636,
	0);
INSERT INTO R_SIMP
	VALUES (4718615);
INSERT INTO R_REL
	VALUES (4718615,
	612,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718599,
	4718615,
	4718637,
	1,
	1,
	'has actual value');
INSERT INTO R_RGO
	VALUES (4718599,
	4718615,
	4718637);
INSERT INTO R_OIR
	VALUES (4718599,
	4718615,
	4718637,
	0);
INSERT INTO R_PART
	VALUES (1048591,
	4718615,
	4718638,
	0,
	0,
	'is actual value of');
INSERT INTO R_RTO
	VALUES (1048591,
	4718615,
	4718638,
	1);
INSERT INTO R_OIR
	VALUES (1048591,
	4718615,
	4718638,
	4718605);
INSERT INTO R_SIMP
	VALUES (4718616);
INSERT INTO R_REL
	VALUES (4718616,
	622,
	'',
	4718601);
INSERT INTO R_FORM
	VALUES (4718604,
	4718616,
	4718639,
	1,
	1,
	'has actual value');
INSERT INTO R_RGO
	VALUES (4718604,
	4718616,
	4718639);
INSERT INTO R_OIR
	VALUES (4718604,
	4718616,
	4718639,
	0);
INSERT INTO R_PART
	VALUES (1048588,
	4718616,
	4718640,
	0,
	0,
	'is actual value of');
INSERT INTO R_RTO
	VALUES (1048588,
	4718616,
	4718640,
	0);
INSERT INTO R_OIR
	VALUES (1048588,
	4718616,
	4718640,
	4718604);

