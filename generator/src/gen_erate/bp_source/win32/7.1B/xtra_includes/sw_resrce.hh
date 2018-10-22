/*========================================================================
 *
 * File:      $RCSfile: sw_resrce.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SW_RESRCE_HH
#define SW_RESRCE_HH

#ifndef vnameINCLUDED
#include <vname.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
	_sim_ooa_Glyph_Images,
	_sim_ooa_printpaperdict,
	_sim_ooa_Synch_Service_Window,
	_sim_ooa_Apply_Attribute_Value,
	_sim_ooa_Clock_Window,
	_sim_ooa_Loaded_OOA_DB_List,
	_sim_ooa_Clock_label_bridge,
	_sim_ooa_Instance_Image,
	_sim_ooa_Index_Window,
	_sim_ooa_a0,
	_sim_ooa_a1,
	_sim_ooa_a2,
	_sim_ooa_a3,
	_sim_ooa_Clock_label_while_initial,
	_sim_ooa_a4,
	_sim_ooa_Subsystem_Version_Selector,
	_sim_ooa_a5,
	_sim_ooa_a6,
	_sim_ooa_Error_Notice,
	_sim_ooa_System_Test_File,
	_sim_ooa_Apply_Parameter_Value,
	_sim_ooa_Reset_Parameter_Value,
	_sim_ooa_Delete_Event,
	_sim_ooa_Index_File_Menu,
	_sim_ooa_Loaded_SIM_Database,
	_sim_ooa_HOME,
	_sim_ooa_legal,
	_sim_ooa_Supplemental_Data_Value,
	_sim_ooa_Synch_Service_Image,
	_sim_ooa_Model_Slider,
	_sim_ooa_RecentSubMenu,
	_sim_ooa_Clock_while_initial,
	_sim_ooa_PT_DEBUG,
	_sim_ooa_BPStates,
	_sim_ooa_Value,
	_sim_ooa_LabelItem,
	_sim_ooa_CreateNewSimErrorLabel,
	_sim_ooa_Action_Level,
	_sim_ooa_Blank_Image,
	_sim_ooa_Cut_Event,
	_sim_ooa_Quit_Simulator,
	_sim_ooa_Clock_select_from_instances_of,
	_sim_ooa_System_Test_Description,
	_sim_ooa_Window_States_Slider,
	_sim_ooa_Create_Instance,
	_sim_ooa_Synch_Service,
	_sim_ooa_Synch_Invoke_Dequeue,
	_sim_ooa_Clock_elif,
	_sim_ooa_Dequeue_Domain_Event,
	_sim_ooa_Stop_TICK,
	_sim_ooa_StringField,
	_sim_ooa_About_Window,
	_sim_ooa_Clock_relate,
	_sim_ooa_Sync_To_Current_Model_Workspace,
	_sim_ooa_OK_Notice,
	_sim_ooa_About_Continue,
	_sim_ooa_Galaxy,
	_sim_ooa_Instance_Window,
	_sim_ooa_Stop_System_Test,
	_sim_ooa_Clock_label_elif,
	_sim_ooa_Clock_break,
	_sim_ooa_Synchronous_Services_Label,
	_sim_ooa_Domain_Name,
	_sim_ooa_Windows_NT,
	_sim_ooa_Clock_unrelate,
	_sim_ooa_State_Machine_Event_Queue_Label,
	_sim_ooa_Xlate_Slider,
	_sim_ooa_Clock_for_iteration,
	_sim_ooa_Title,
	_sim_ooa_Apply_Supplemental_Data_Value,
	_sim_ooa_Left_Footer_Message,
	_sim_ooa_All_Files,
	_sim_ooa_Reset_Trace_Settings,
	_sim_ooa_Select_State,
	_sim_ooa_Preferences,
	_sim_ooa_Clock_label_relate,
	_sim_ooa_Cancel_Notice,
	_sim_ooa_System_Test_Message,
	_sim_ooa_Clock_label_title,
	_sim_ooa_Reset_Supplemental_Data_Value,
	_sim_ooa_Clock_label_wile_iteration,
	_sim_ooa_Subsystem_List_Label,
	_sim_ooa_Index_Menu_Bar,
	_sim_ooa_Support_Properties_Catagory_Selector,
	_sim_ooa_CloseSim,
	_sim_ooa_Delete_Instance,
	_sim_ooa_Version_String,
	_sim_ooa_SIM_FileChooser,
	_sim_ooa_Clock_create_object_instance,
	_sim_ooa_Right_Footer_Message,
	_sim_ooa_Cancel,
	_sim_ooa_Editable_Text,
	_sim_ooa_Clock_label_select_from_instances_of,
	_sim_ooa_Case_Insensitive,
	_sim_ooa_Data_Slider,
	_sim_ooa_No,
	_sim_ooa_Instance_Event_Queue,
	_sim_ooa_Clock_while_iteration,
	_sim_ooa_Real_Time_Delay,
	_sim_ooa_UNIX,
	_sim_ooa_State_Machine_Window,
	_sim_ooa_System_Test_Number,
	_sim_ooa_Clock_return,
	_sim_ooa_Ok,
	_sim_ooa_Yes_No_Notice,
	_sim_ooa_Clock_action,
	_sim_ooa_Clock_select_related_by,
	_sim_ooa_Clock_label_create_event_instance,
	_sim_ooa_Elan_Info,
	_sim_ooa_Action_Trace_Log,
	_sim_ooa_Reset_Attribute_Value,
	_sim_ooa_Clock_label_return,
	_sim_ooa_TextItemModelFile,
	_sim_ooa_Clock_create_event_instance,
	_sim_ooa_Apply_Trace_Settings,
	_sim_ooa_Clock_label_if,
	_sim_ooa_OOA_File,
	_sim_ooa_Canvas_States_Slider,
	_sim_ooa_Support_Properties_Window,
	_sim_ooa_Dequeue_Event,
	_sim_ooa_States_Sub_Menu,
	_sim_ooa_Support_Properties,
	_sim_ooa_Palette_Objects,
	_sim_ooa_OOA_FileChooser,
	_sim_ooa_Support_Properties_Container,
	_sim_ooa_CreateNewSimulation,
	_sim_ooa_Action_Trace_Level,
	_sim_ooa_About_Image,
	_sim_ooa_Email_Trace_Settings,
	_sim_ooa_Clock_label_transformer,
	_sim_ooa_Clock_continue,
	_sim_ooa_Recent,
	_sim_ooa_Clock_bridge,
	_sim_ooa_Attribute_Value,
	_sim_ooa_Domain_Event_Queue_Label,
	_sim_ooa_Show_Instance_Data,
	_sim_ooa_MC_DBMS_Info,
	_sim_ooa_ItemList,
	_sim_ooa_Clock_delete_object_instance,
	_sim_ooa_Clock_label_for_iteration,
	_sim_ooa_Clock_synch_service,
	_sim_ooa_Render_Slider,
	_sim_ooa_Supplemental_Data_List,
	_sim_ooa_Detached,
	_sim_ooa_Statement_Level,
	_sim_ooa_Clock_label_for_initial,
	_sim_ooa_Open_Simulation_Workspace,
	_sim_ooa_Clock_Value,
	_sim_ooa_Add_Creation_Event,
	_sim_ooa_Filter_Types,
	_sim_ooa_State_Machine_Domain,
	_sim_ooa_Parameter_Value,
	_sim_ooa_Synch_Invoke,
	_sim_ooa_Parameter_List,
	_sim_ooa_Clock_label_generate,
	_sim_ooa_System_Test_Container,
	_sim_ooa_Attribute_List,
	_sim_ooa_Object_Version_Selector,
	_sim_ooa_Clock_label_continue,
	_sim_ooa_Subsystem_List,
	_sim_ooa_Clock_label_select_related_by,
	_sim_ooa_PT_RENDER_OVAL_AS_RECT,
	_sim_ooa_letter,
	_sim_ooa_Object_List_Label,
	_sim_ooa_Clock_assign,
	_sim_ooa_Add_Event,
	_sim_ooa_Domain_Name_Label,
	_sim_ooa_Object_Instance_List,
	_sim_ooa_Clock_label_assign,
	_sim_ooa_Product_Info,
	_sim_ooa_Clock_label_action,
	_sim_ooa_Clock_tick,
	_sim_ooa_Domain_Event_Queue,
	_sim_ooa_GUI_Stubs_Slider,
	_sim_ooa_Clock_transformer,
	_sim_ooa_Trace_Container,
	_sim_ooa_Start_System_Test,
	_sim_ooa_GUI_Drivers_Slider,
	_sim_ooa_Create_New_Simulation_Workspace,
	_sim_ooa_Import_Export_Slider,
	_sim_ooa_Clock_label_create_object_instance,
	_sim_ooa_Clock_label_delete_object_instance,
	_sim_ooa_Clock_label_tick,
	_sim_ooa_Action_Slider,
	_sim_ooa_Notebook_Slider,
	_sim_ooa_11x17,
	_sim_ooa_Clock_label_break,
	_sim_ooa_Passive_Object_Label,
	_sim_ooa_Simulator_Image,
	_sim_ooa_Object_List,
	_sim_ooa_Create_New_Cancel,
	_sim_ooa_Start_TICK,
	_sim_ooa_PT_AUDIT_SM,
	_sim_ooa_Toggle_Trace_Settings,
	_sim_ooa_SIM_File,
	_sim_ooa_Clock_label_synch_service,
	_sim_ooa_Object_Instances_Label,
	_sim_ooa_Window_Slider,
	_sim_ooa_Domain_Version_Selector,
	_sim_ooa_Clock_if,
	_sim_ooa_Synch_Service_List,
	_sim_ooa_Clock_label_unrealte,
	_sim_ooa_MenuList,
	_sim_ooa_PT_OOA_DIR,
	_sim_ooa_TextItemSimFile,
	_sim_ooa_Clock_for_initial,
	_sim_ooa_Clock_generate,
	_sim_ooa_Component_Level,
	_sim_ooa_CreateSimulatorFile,
	_sim_ooaCOUNT
};


#define sim_ooa_Glyph_Images		 _sim_ooaPredefs[_sim_ooa_Glyph_Images]
#define sim_ooa_printpaperdict		 _sim_ooaPredefs[_sim_ooa_printpaperdict]
#define sim_ooa_Synch_Service_Window		 _sim_ooaPredefs[_sim_ooa_Synch_Service_Window]
#define sim_ooa_Apply_Attribute_Value		 _sim_ooaPredefs[_sim_ooa_Apply_Attribute_Value]
#define sim_ooa_Clock_Window		 _sim_ooaPredefs[_sim_ooa_Clock_Window]
#define sim_ooa_Loaded_OOA_DB_List		 _sim_ooaPredefs[_sim_ooa_Loaded_OOA_DB_List]
#define sim_ooa_Clock_label_bridge		 _sim_ooaPredefs[_sim_ooa_Clock_label_bridge]
#define sim_ooa_Instance_Image		 _sim_ooaPredefs[_sim_ooa_Instance_Image]
#define sim_ooa_Index_Window		 _sim_ooaPredefs[_sim_ooa_Index_Window]
#define sim_ooa_a0		 _sim_ooaPredefs[_sim_ooa_a0]
#define sim_ooa_a1		 _sim_ooaPredefs[_sim_ooa_a1]
#define sim_ooa_a2		 _sim_ooaPredefs[_sim_ooa_a2]
#define sim_ooa_a3		 _sim_ooaPredefs[_sim_ooa_a3]
#define sim_ooa_Clock_label_while_initial		 _sim_ooaPredefs[_sim_ooa_Clock_label_while_initial]
#define sim_ooa_a4		 _sim_ooaPredefs[_sim_ooa_a4]
#define sim_ooa_Subsystem_Version_Selector		 _sim_ooaPredefs[_sim_ooa_Subsystem_Version_Selector]
#define sim_ooa_a5		 _sim_ooaPredefs[_sim_ooa_a5]
#define sim_ooa_a6		 _sim_ooaPredefs[_sim_ooa_a6]
#define sim_ooa_Error_Notice		 _sim_ooaPredefs[_sim_ooa_Error_Notice]
#define sim_ooa_System_Test_File		 _sim_ooaPredefs[_sim_ooa_System_Test_File]
#define sim_ooa_Apply_Parameter_Value		 _sim_ooaPredefs[_sim_ooa_Apply_Parameter_Value]
#define sim_ooa_Reset_Parameter_Value		 _sim_ooaPredefs[_sim_ooa_Reset_Parameter_Value]
#define sim_ooa_Delete_Event		 _sim_ooaPredefs[_sim_ooa_Delete_Event]
#define sim_ooa_Index_File_Menu		 _sim_ooaPredefs[_sim_ooa_Index_File_Menu]
#define sim_ooa_Loaded_SIM_Database		 _sim_ooaPredefs[_sim_ooa_Loaded_SIM_Database]
#define sim_ooa_HOME		 _sim_ooaPredefs[_sim_ooa_HOME]
#define sim_ooa_legal		 _sim_ooaPredefs[_sim_ooa_legal]
#define sim_ooa_Supplemental_Data_Value		 _sim_ooaPredefs[_sim_ooa_Supplemental_Data_Value]
#define sim_ooa_Synch_Service_Image		 _sim_ooaPredefs[_sim_ooa_Synch_Service_Image]
#define sim_ooa_Model_Slider		 _sim_ooaPredefs[_sim_ooa_Model_Slider]
#define sim_ooa_RecentSubMenu		 _sim_ooaPredefs[_sim_ooa_RecentSubMenu]
#define sim_ooa_Clock_while_initial		 _sim_ooaPredefs[_sim_ooa_Clock_while_initial]
#define sim_ooa_PT_DEBUG		 _sim_ooaPredefs[_sim_ooa_PT_DEBUG]
#define sim_ooa_BPStates		 _sim_ooaPredefs[_sim_ooa_BPStates]
#define sim_ooa_Value		 _sim_ooaPredefs[_sim_ooa_Value]
#define sim_ooa_LabelItem		 _sim_ooaPredefs[_sim_ooa_LabelItem]
#define sim_ooa_CreateNewSimErrorLabel		 _sim_ooaPredefs[_sim_ooa_CreateNewSimErrorLabel]
#define sim_ooa_Action_Level		 _sim_ooaPredefs[_sim_ooa_Action_Level]
#define sim_ooa_Blank_Image		 _sim_ooaPredefs[_sim_ooa_Blank_Image]
#define sim_ooa_Cut_Event		 _sim_ooaPredefs[_sim_ooa_Cut_Event]
#define sim_ooa_Quit_Simulator		 _sim_ooaPredefs[_sim_ooa_Quit_Simulator]
#define sim_ooa_Clock_select_from_instances_of		 _sim_ooaPredefs[_sim_ooa_Clock_select_from_instances_of]
#define sim_ooa_System_Test_Description		 _sim_ooaPredefs[_sim_ooa_System_Test_Description]
#define sim_ooa_Window_States_Slider		 _sim_ooaPredefs[_sim_ooa_Window_States_Slider]
#define sim_ooa_Create_Instance		 _sim_ooaPredefs[_sim_ooa_Create_Instance]
#define sim_ooa_Synch_Service		 _sim_ooaPredefs[_sim_ooa_Synch_Service]
#define sim_ooa_Synch_Invoke_Dequeue		 _sim_ooaPredefs[_sim_ooa_Synch_Invoke_Dequeue]
#define sim_ooa_Clock_elif		 _sim_ooaPredefs[_sim_ooa_Clock_elif]
#define sim_ooa_Dequeue_Domain_Event		 _sim_ooaPredefs[_sim_ooa_Dequeue_Domain_Event]
#define sim_ooa_Stop_TICK		 _sim_ooaPredefs[_sim_ooa_Stop_TICK]
#define sim_ooa_StringField		 _sim_ooaPredefs[_sim_ooa_StringField]
#define sim_ooa_About_Window		 _sim_ooaPredefs[_sim_ooa_About_Window]
#define sim_ooa_Clock_relate		 _sim_ooaPredefs[_sim_ooa_Clock_relate]
#define sim_ooa_Sync_To_Current_Model_Workspace		 _sim_ooaPredefs[_sim_ooa_Sync_To_Current_Model_Workspace]
#define sim_ooa_OK_Notice		 _sim_ooaPredefs[_sim_ooa_OK_Notice]
#define sim_ooa_About_Continue		 _sim_ooaPredefs[_sim_ooa_About_Continue]
#define sim_ooa_Galaxy		 _sim_ooaPredefs[_sim_ooa_Galaxy]
#define sim_ooa_Instance_Window		 _sim_ooaPredefs[_sim_ooa_Instance_Window]
#define sim_ooa_Stop_System_Test		 _sim_ooaPredefs[_sim_ooa_Stop_System_Test]
#define sim_ooa_Clock_label_elif		 _sim_ooaPredefs[_sim_ooa_Clock_label_elif]
#define sim_ooa_Clock_break		 _sim_ooaPredefs[_sim_ooa_Clock_break]
#define sim_ooa_Synchronous_Services_Label		 _sim_ooaPredefs[_sim_ooa_Synchronous_Services_Label]
#define sim_ooa_Domain_Name		 _sim_ooaPredefs[_sim_ooa_Domain_Name]
#define sim_ooa_Windows_NT		 _sim_ooaPredefs[_sim_ooa_Windows_NT]
#define sim_ooa_Clock_unrelate		 _sim_ooaPredefs[_sim_ooa_Clock_unrelate]
#define sim_ooa_State_Machine_Event_Queue_Label		 _sim_ooaPredefs[_sim_ooa_State_Machine_Event_Queue_Label]
#define sim_ooa_Xlate_Slider		 _sim_ooaPredefs[_sim_ooa_Xlate_Slider]
#define sim_ooa_Clock_for_iteration		 _sim_ooaPredefs[_sim_ooa_Clock_for_iteration]
#define sim_ooa_Title		 _sim_ooaPredefs[_sim_ooa_Title]
#define sim_ooa_Apply_Supplemental_Data_Value		 _sim_ooaPredefs[_sim_ooa_Apply_Supplemental_Data_Value]
#define sim_ooa_Left_Footer_Message		 _sim_ooaPredefs[_sim_ooa_Left_Footer_Message]
#define sim_ooa_All_Files		 _sim_ooaPredefs[_sim_ooa_All_Files]
#define sim_ooa_Reset_Trace_Settings		 _sim_ooaPredefs[_sim_ooa_Reset_Trace_Settings]
#define sim_ooa_Select_State		 _sim_ooaPredefs[_sim_ooa_Select_State]
#define sim_ooa_Preferences		 _sim_ooaPredefs[_sim_ooa_Preferences]
#define sim_ooa_Clock_label_relate		 _sim_ooaPredefs[_sim_ooa_Clock_label_relate]
#define sim_ooa_Cancel_Notice		 _sim_ooaPredefs[_sim_ooa_Cancel_Notice]
#define sim_ooa_System_Test_Message		 _sim_ooaPredefs[_sim_ooa_System_Test_Message]
#define sim_ooa_Clock_label_title		 _sim_ooaPredefs[_sim_ooa_Clock_label_title]
#define sim_ooa_Reset_Supplemental_Data_Value		 _sim_ooaPredefs[_sim_ooa_Reset_Supplemental_Data_Value]
#define sim_ooa_Clock_label_wile_iteration		 _sim_ooaPredefs[_sim_ooa_Clock_label_wile_iteration]
#define sim_ooa_Subsystem_List_Label		 _sim_ooaPredefs[_sim_ooa_Subsystem_List_Label]
#define sim_ooa_Index_Menu_Bar		 _sim_ooaPredefs[_sim_ooa_Index_Menu_Bar]
#define sim_ooa_Support_Properties_Catagory_Selector		 _sim_ooaPredefs[_sim_ooa_Support_Properties_Catagory_Selector]
#define sim_ooa_CloseSim		 _sim_ooaPredefs[_sim_ooa_CloseSim]
#define sim_ooa_Delete_Instance		 _sim_ooaPredefs[_sim_ooa_Delete_Instance]
#define sim_ooa_Version_String		 _sim_ooaPredefs[_sim_ooa_Version_String]
#define sim_ooa_SIM_FileChooser		 _sim_ooaPredefs[_sim_ooa_SIM_FileChooser]
#define sim_ooa_Clock_create_object_instance		 _sim_ooaPredefs[_sim_ooa_Clock_create_object_instance]
#define sim_ooa_Right_Footer_Message		 _sim_ooaPredefs[_sim_ooa_Right_Footer_Message]
#define sim_ooa_Cancel		 _sim_ooaPredefs[_sim_ooa_Cancel]
#define sim_ooa_Editable_Text		 _sim_ooaPredefs[_sim_ooa_Editable_Text]
#define sim_ooa_Clock_label_select_from_instances_of		 _sim_ooaPredefs[_sim_ooa_Clock_label_select_from_instances_of]
#define sim_ooa_Case_Insensitive		 _sim_ooaPredefs[_sim_ooa_Case_Insensitive]
#define sim_ooa_Data_Slider		 _sim_ooaPredefs[_sim_ooa_Data_Slider]
#define sim_ooa_No		 _sim_ooaPredefs[_sim_ooa_No]
#define sim_ooa_Instance_Event_Queue		 _sim_ooaPredefs[_sim_ooa_Instance_Event_Queue]
#define sim_ooa_Clock_while_iteration		 _sim_ooaPredefs[_sim_ooa_Clock_while_iteration]
#define sim_ooa_Real_Time_Delay		 _sim_ooaPredefs[_sim_ooa_Real_Time_Delay]
#define sim_ooa_UNIX		 _sim_ooaPredefs[_sim_ooa_UNIX]
#define sim_ooa_State_Machine_Window		 _sim_ooaPredefs[_sim_ooa_State_Machine_Window]
#define sim_ooa_System_Test_Number		 _sim_ooaPredefs[_sim_ooa_System_Test_Number]
#define sim_ooa_Clock_return		 _sim_ooaPredefs[_sim_ooa_Clock_return]
#define sim_ooa_Ok		 _sim_ooaPredefs[_sim_ooa_Ok]
#define sim_ooa_Yes_No_Notice		 _sim_ooaPredefs[_sim_ooa_Yes_No_Notice]
#define sim_ooa_Clock_action		 _sim_ooaPredefs[_sim_ooa_Clock_action]
#define sim_ooa_Clock_select_related_by		 _sim_ooaPredefs[_sim_ooa_Clock_select_related_by]
#define sim_ooa_Clock_label_create_event_instance		 _sim_ooaPredefs[_sim_ooa_Clock_label_create_event_instance]
#define sim_ooa_Elan_Info		 _sim_ooaPredefs[_sim_ooa_Elan_Info]
#define sim_ooa_Action_Trace_Log		 _sim_ooaPredefs[_sim_ooa_Action_Trace_Log]
#define sim_ooa_Reset_Attribute_Value		 _sim_ooaPredefs[_sim_ooa_Reset_Attribute_Value]
#define sim_ooa_Clock_label_return		 _sim_ooaPredefs[_sim_ooa_Clock_label_return]
#define sim_ooa_TextItemModelFile		 _sim_ooaPredefs[_sim_ooa_TextItemModelFile]
#define sim_ooa_Clock_create_event_instance		 _sim_ooaPredefs[_sim_ooa_Clock_create_event_instance]
#define sim_ooa_Apply_Trace_Settings		 _sim_ooaPredefs[_sim_ooa_Apply_Trace_Settings]
#define sim_ooa_Clock_label_if		 _sim_ooaPredefs[_sim_ooa_Clock_label_if]
#define sim_ooa_OOA_File		 _sim_ooaPredefs[_sim_ooa_OOA_File]
#define sim_ooa_Canvas_States_Slider		 _sim_ooaPredefs[_sim_ooa_Canvas_States_Slider]
#define sim_ooa_Support_Properties_Window		 _sim_ooaPredefs[_sim_ooa_Support_Properties_Window]
#define sim_ooa_Dequeue_Event		 _sim_ooaPredefs[_sim_ooa_Dequeue_Event]
#define sim_ooa_States_Sub_Menu		 _sim_ooaPredefs[_sim_ooa_States_Sub_Menu]
#define sim_ooa_Support_Properties		 _sim_ooaPredefs[_sim_ooa_Support_Properties]
#define sim_ooa_Palette_Objects		 _sim_ooaPredefs[_sim_ooa_Palette_Objects]
#define sim_ooa_OOA_FileChooser		 _sim_ooaPredefs[_sim_ooa_OOA_FileChooser]
#define sim_ooa_Support_Properties_Container		 _sim_ooaPredefs[_sim_ooa_Support_Properties_Container]
#define sim_ooa_CreateNewSimulation		 _sim_ooaPredefs[_sim_ooa_CreateNewSimulation]
#define sim_ooa_Action_Trace_Level		 _sim_ooaPredefs[_sim_ooa_Action_Trace_Level]
#define sim_ooa_About_Image		 _sim_ooaPredefs[_sim_ooa_About_Image]
#define sim_ooa_Email_Trace_Settings		 _sim_ooaPredefs[_sim_ooa_Email_Trace_Settings]
#define sim_ooa_Clock_label_transformer		 _sim_ooaPredefs[_sim_ooa_Clock_label_transformer]
#define sim_ooa_Clock_continue		 _sim_ooaPredefs[_sim_ooa_Clock_continue]
#define sim_ooa_Recent		 _sim_ooaPredefs[_sim_ooa_Recent]
#define sim_ooa_Clock_bridge		 _sim_ooaPredefs[_sim_ooa_Clock_bridge]
#define sim_ooa_Attribute_Value		 _sim_ooaPredefs[_sim_ooa_Attribute_Value]
#define sim_ooa_Domain_Event_Queue_Label		 _sim_ooaPredefs[_sim_ooa_Domain_Event_Queue_Label]
#define sim_ooa_Show_Instance_Data		 _sim_ooaPredefs[_sim_ooa_Show_Instance_Data]
#define sim_ooa_MC_DBMS_Info		 _sim_ooaPredefs[_sim_ooa_MC_DBMS_Info]
#define sim_ooa_ItemList		 _sim_ooaPredefs[_sim_ooa_ItemList]
#define sim_ooa_Clock_delete_object_instance		 _sim_ooaPredefs[_sim_ooa_Clock_delete_object_instance]
#define sim_ooa_Clock_label_for_iteration		 _sim_ooaPredefs[_sim_ooa_Clock_label_for_iteration]
#define sim_ooa_Clock_synch_service		 _sim_ooaPredefs[_sim_ooa_Clock_synch_service]
#define sim_ooa_Render_Slider		 _sim_ooaPredefs[_sim_ooa_Render_Slider]
#define sim_ooa_Supplemental_Data_List		 _sim_ooaPredefs[_sim_ooa_Supplemental_Data_List]
#define sim_ooa_Detached		 _sim_ooaPredefs[_sim_ooa_Detached]
#define sim_ooa_Statement_Level		 _sim_ooaPredefs[_sim_ooa_Statement_Level]
#define sim_ooa_Clock_label_for_initial		 _sim_ooaPredefs[_sim_ooa_Clock_label_for_initial]
#define sim_ooa_Open_Simulation_Workspace		 _sim_ooaPredefs[_sim_ooa_Open_Simulation_Workspace]
#define sim_ooa_Clock_Value		 _sim_ooaPredefs[_sim_ooa_Clock_Value]
#define sim_ooa_Add_Creation_Event		 _sim_ooaPredefs[_sim_ooa_Add_Creation_Event]
#define sim_ooa_Filter_Types		 _sim_ooaPredefs[_sim_ooa_Filter_Types]
#define sim_ooa_State_Machine_Domain		 _sim_ooaPredefs[_sim_ooa_State_Machine_Domain]
#define sim_ooa_Parameter_Value		 _sim_ooaPredefs[_sim_ooa_Parameter_Value]
#define sim_ooa_Synch_Invoke		 _sim_ooaPredefs[_sim_ooa_Synch_Invoke]
#define sim_ooa_Parameter_List		 _sim_ooaPredefs[_sim_ooa_Parameter_List]
#define sim_ooa_Clock_label_generate		 _sim_ooaPredefs[_sim_ooa_Clock_label_generate]
#define sim_ooa_System_Test_Container		 _sim_ooaPredefs[_sim_ooa_System_Test_Container]
#define sim_ooa_Attribute_List		 _sim_ooaPredefs[_sim_ooa_Attribute_List]
#define sim_ooa_Object_Version_Selector		 _sim_ooaPredefs[_sim_ooa_Object_Version_Selector]
#define sim_ooa_Clock_label_continue		 _sim_ooaPredefs[_sim_ooa_Clock_label_continue]
#define sim_ooa_Subsystem_List		 _sim_ooaPredefs[_sim_ooa_Subsystem_List]
#define sim_ooa_Clock_label_select_related_by		 _sim_ooaPredefs[_sim_ooa_Clock_label_select_related_by]
#define sim_ooa_PT_RENDER_OVAL_AS_RECT		 _sim_ooaPredefs[_sim_ooa_PT_RENDER_OVAL_AS_RECT]
#define sim_ooa_letter		 _sim_ooaPredefs[_sim_ooa_letter]
#define sim_ooa_Object_List_Label		 _sim_ooaPredefs[_sim_ooa_Object_List_Label]
#define sim_ooa_Clock_assign		 _sim_ooaPredefs[_sim_ooa_Clock_assign]
#define sim_ooa_Add_Event		 _sim_ooaPredefs[_sim_ooa_Add_Event]
#define sim_ooa_Domain_Name_Label		 _sim_ooaPredefs[_sim_ooa_Domain_Name_Label]
#define sim_ooa_Object_Instance_List		 _sim_ooaPredefs[_sim_ooa_Object_Instance_List]
#define sim_ooa_Clock_label_assign		 _sim_ooaPredefs[_sim_ooa_Clock_label_assign]
#define sim_ooa_Product_Info		 _sim_ooaPredefs[_sim_ooa_Product_Info]
#define sim_ooa_Clock_label_action		 _sim_ooaPredefs[_sim_ooa_Clock_label_action]
#define sim_ooa_Clock_tick		 _sim_ooaPredefs[_sim_ooa_Clock_tick]
#define sim_ooa_Domain_Event_Queue		 _sim_ooaPredefs[_sim_ooa_Domain_Event_Queue]
#define sim_ooa_GUI_Stubs_Slider		 _sim_ooaPredefs[_sim_ooa_GUI_Stubs_Slider]
#define sim_ooa_Clock_transformer		 _sim_ooaPredefs[_sim_ooa_Clock_transformer]
#define sim_ooa_Trace_Container		 _sim_ooaPredefs[_sim_ooa_Trace_Container]
#define sim_ooa_Start_System_Test		 _sim_ooaPredefs[_sim_ooa_Start_System_Test]
#define sim_ooa_GUI_Drivers_Slider		 _sim_ooaPredefs[_sim_ooa_GUI_Drivers_Slider]
#define sim_ooa_Create_New_Simulation_Workspace		 _sim_ooaPredefs[_sim_ooa_Create_New_Simulation_Workspace]
#define sim_ooa_Import_Export_Slider		 _sim_ooaPredefs[_sim_ooa_Import_Export_Slider]
#define sim_ooa_Clock_label_create_object_instance		 _sim_ooaPredefs[_sim_ooa_Clock_label_create_object_instance]
#define sim_ooa_Clock_label_delete_object_instance		 _sim_ooaPredefs[_sim_ooa_Clock_label_delete_object_instance]
#define sim_ooa_Clock_label_tick		 _sim_ooaPredefs[_sim_ooa_Clock_label_tick]
#define sim_ooa_Action_Slider		 _sim_ooaPredefs[_sim_ooa_Action_Slider]
#define sim_ooa_Notebook_Slider		 _sim_ooaPredefs[_sim_ooa_Notebook_Slider]
#define sim_ooa_11x17		 _sim_ooaPredefs[_sim_ooa_11x17]
#define sim_ooa_Clock_label_break		 _sim_ooaPredefs[_sim_ooa_Clock_label_break]
#define sim_ooa_Passive_Object_Label		 _sim_ooaPredefs[_sim_ooa_Passive_Object_Label]
#define sim_ooa_Simulator_Image		 _sim_ooaPredefs[_sim_ooa_Simulator_Image]
#define sim_ooa_Object_List		 _sim_ooaPredefs[_sim_ooa_Object_List]
#define sim_ooa_Create_New_Cancel		 _sim_ooaPredefs[_sim_ooa_Create_New_Cancel]
#define sim_ooa_Start_TICK		 _sim_ooaPredefs[_sim_ooa_Start_TICK]
#define sim_ooa_PT_AUDIT_SM		 _sim_ooaPredefs[_sim_ooa_PT_AUDIT_SM]
#define sim_ooa_Toggle_Trace_Settings		 _sim_ooaPredefs[_sim_ooa_Toggle_Trace_Settings]
#define sim_ooa_SIM_File		 _sim_ooaPredefs[_sim_ooa_SIM_File]
#define sim_ooa_Clock_label_synch_service		 _sim_ooaPredefs[_sim_ooa_Clock_label_synch_service]
#define sim_ooa_Object_Instances_Label		 _sim_ooaPredefs[_sim_ooa_Object_Instances_Label]
#define sim_ooa_Window_Slider		 _sim_ooaPredefs[_sim_ooa_Window_Slider]
#define sim_ooa_Domain_Version_Selector		 _sim_ooaPredefs[_sim_ooa_Domain_Version_Selector]
#define sim_ooa_Clock_if		 _sim_ooaPredefs[_sim_ooa_Clock_if]
#define sim_ooa_Synch_Service_List		 _sim_ooaPredefs[_sim_ooa_Synch_Service_List]
#define sim_ooa_Clock_label_unrealte		 _sim_ooaPredefs[_sim_ooa_Clock_label_unrealte]
#define sim_ooa_MenuList		 _sim_ooaPredefs[_sim_ooa_MenuList]
#define sim_ooa_PT_OOA_DIR		 _sim_ooaPredefs[_sim_ooa_PT_OOA_DIR]
#define sim_ooa_TextItemSimFile		 _sim_ooaPredefs[_sim_ooa_TextItemSimFile]
#define sim_ooa_Clock_for_initial		 _sim_ooaPredefs[_sim_ooa_Clock_for_initial]
#define sim_ooa_Clock_generate		 _sim_ooaPredefs[_sim_ooa_Clock_generate]
#define sim_ooa_Component_Level		 _sim_ooaPredefs[_sim_ooa_Component_Level]
#define sim_ooa_CreateSimulatorFile		 _sim_ooaPredefs[_sim_ooa_CreateSimulatorFile]

/*
 * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * *
 */

extern const vname	 *_sim_ooaPredefs[];

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void sim_ooaInternNames( void ); 


vportEND_CPLUSPLUS_EXTERN_C

#endif
