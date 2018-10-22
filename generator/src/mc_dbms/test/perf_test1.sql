--========================================================================
--
--File:      $RCSfile: perf_test1.sql,v $
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
-- This takes asubset of data from escher_ooa_schema.sql and mc3020_meta.sql. It
-- is just enough to allows us to run exercise<1-6>.arc.  It contains only the 
--O_OBJ abd O_ATTR objectjects and their relationship data.
--
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

CREATE TABLE S_CDT (
	DT_ID	UNIQUE_ID,
	Core_Typ	INTEGER );

CREATE TABLE S_UDT (
	DT_ID	UNIQUE_ID,
	CDT_ID	UNIQUE_ID,
	Gen_Type	INTEGER );

CREATE TABLE S_EDT (
	DT_ID	UNIQUE_ID,
	Initial_Value	STRING );

CREATE ROP REF_ID R102	FROM MC O_ATTR	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

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
INSERT INTO O_OBJ
	VALUES (1048577,
	'Domain',
	1,
	'S_DOM',
	'A typical software system generally consists of distinct and independent subject matters. A Shlaer/Mellor analysis partition is based within each of these subject matters - each subject matter is called a Domain. A Domain is inhabited by its  own conceptual entities (call objects). A domain may be partitioned into subsystems depending upon its complexity. Each Domain is given a mission statement which provides a charter for the construction of the OOA models.
',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048585,
	'Core Data Type',
	10,
	'S_CDT',
	'Core Data Types are those data types which are
fundamental, or core, to all data types.
',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048587,
	'Bridge',
	12,
	'S_BRG',
	'A Bridge is a method associated with an External Entity
 - bridges can be synchronously called from Action Specifications.
',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048588,
	'Bridge Parameter',
	13,
	'S_BPARM',
	'A paramter to a bridge.',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048589,
	'External Entity Event Data',
	8,
	'S_EEEDT',
	'This object serves as a correlation table.
',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048590,
	'Function',
	16,
	'S_SYNC',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048591,
	'Function Parameter',
	17,
	'S_SPARM',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048592,
	'Enumeration Data Type',
	14,
	'S_EDT',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1048593,
	'Enumerator',
	15,
	'S_ENUM',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718605,
	'System Model',
	18,
	'S_SYS',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718606,
	'Function Package',
	19,
	'S_FPK',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718607,
	'Function in Package',
	20,
	'S_FIP',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718608,
	'Function Package in Package',
	21,
	'S_FPIP',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718609,
	'External Entity Package',
	22,
	'S_EEPK',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718610,
	'EE Package in Package',
	24,
	'S_EEPIP',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718611,
	'External Entity in Package',
	23,
	'S_EEIP',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718612,
	'Datatype Package',
	25,
	'S_DPK',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718613,
	'Datatype in Package',
	26,
	'S_DIP',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718614,
	'Datatype Package in Package',
	27,
	'S_DPIP',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (4718615,
	'Subsystem in Subsystem',
	30,
	'S_SIS',
	'',
	1048578);
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
INSERT INTO O_OBJ
	VALUES (1572865,
	'Relationship',
	201,
	'R_REL',
	'A Relationship captures an association that exists between things in the real world. A Relationship is stated in terms of the formal Objects that participate in the association.',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572866,
	'Simple Relationship',
	205,
	'R_SIMP',
	'A Simple Relationship is a relationship between two objects which is formalized with referential attributes.',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572867,
	'Associative Relationship',
	208,
	'R_ASSOC',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572868,
	'Subtype-Supertype Relationship',
	212,
	'R_SUBSUP',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572869,
	'Composition Relationship',
	215,
	'R_COMP',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572870,
	'Object As Simple Participant',
	206,
	'R_PART',
	'An Object As Simple Participant is the referred to object in a simple relationship.',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572871,
	'Object As Simple Formalizer',
	207,
	'R_FORM',
	'An Object As Simple Formalizer is the referring object in a simple relationsip.',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572872,
	'Object As Associated One Side',
	209,
	'R_AONE',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572873,
	'Object As Associated Other Side',
	210,
	'R_AOTH',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572874,
	'Object As Associator',
	211,
	'R_ASSR',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572875,
	'Object As Supertype',
	213,
	'R_SUPER',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572876,
	'Object As Subtype',
	214,
	'R_SUB',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572877,
	'Object As Composition One Side',
	216,
	'R_CONE',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572878,
	'Object As Composition Other Side',
	217,
	'R_COTH',
	'',
	1572867);
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
INSERT INTO O_OBJ
	VALUES (1572879,
	'Object In Relationship',
	202,
	'R_OIR',
	'An Object In Relationship captures the role which an object plays in participating in a relationship.',
	1572867);
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

