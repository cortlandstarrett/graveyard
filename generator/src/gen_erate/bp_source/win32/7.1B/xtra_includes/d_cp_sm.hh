/*========================================================================
 *
 * File:      $RCSfile: d_cp_sm.hh,v $
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
#ifndef D_CPSM_HH
#define D_CPSM_HH

#include <u_desc.hh>
#include <u_id.hh>
#include <d_exespec.hh>
#include <d_sm_pm.hh>    // enum t_sm_spt_pm_type
#include <d_smasnr.hh>

class D_sm_spt_pm;
class D_sm_event_data_item;
class D_supplemental_data;
class D_supplemental_data_item;
class D_sm_state;
class D_sm_event;
class D_polymorphic_event;
class D_event_ignored;
class D_cant_happen;
class D_state_event_matrix_entry;
class D_no_event_transition;
class D_new_state_transition;
class D_creation_transition;
class D_transition;
class D_moore_action_home;
class D_mealy_action_home;
class D_action_home;
class D_action;
class AL_Bush_action;
class D_execution_spec;

class D_cp_sm_spt_pm
{
public:
	D_cp_sm_spt_pm (D_sm_spt_pm* copy_sp_spt_pm);
	~D_cp_sm_spt_pm ();

	t_uint get_sql_id()
	    { return sql_id; }
	D_sm_spt_pm::t_sm_spt_pm_type get_sm_spt_pm_type()
	    { return m_sm_spt_pm_type; };
	Description get_description()
	    { return m_description; };

	Id paste_sm_spt_pm(Domain* p_domain_ptr,
                     Id p_new_obj_id,
                     const Description &p_branch_name);

	void set_paste_ptr( D_sm_spt_pm* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_sm_spt_pm* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_sm_spt_pm * pick_sm_spt_pm (t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_sm_spt_pm *> *cut_paste_ptr;
	t_uint		sql_id;
	D_sm_spt_pm::t_sm_spt_pm_type m_sm_spt_pm_type;
	Description m_description;
  t_uint m_assigner_value[D_dd_assigners::num_id_assigners_e];
  D_sm_spt_pm* m_paste_ptr;
};


class D_cp_event_data_item
{
public:
	D_cp_event_data_item (D_sm_event_data_item*, D_sm_spt_pm* copy_sp_spt_pm);
	~D_cp_event_data_item ();

	t_uint get_sql_id()
	    { return sql_id; }
    t_uint get_sm_id()
	    { return m_sm_id; }
    Description get_name()
	    { return m_name; }
    Description get_description()
	    { return m_description; }
	Id get_data_type_id()
	    { return m_data_type_id; }

	void set_paste_ptr( D_sm_event_data_item* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_sm_event_data_item* get_paste_ptr()
	  { return m_paste_ptr; }

	static mc_dbms_List<D_cp_event_data_item *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_event_data_item * pick_event_data_item (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_event_data_item *> *cut_paste_ptr;
	t_uint		sql_id;
    t_uint m_sm_id;
    Description m_name;
    Description m_description;
	Id m_data_type_id;
    D_sm_event_data_item* m_paste_ptr;

};

class D_cp_supplemental_data
{
public:
	D_cp_supplemental_data (D_supplemental_data*, D_sm_spt_pm* copy_sp_spt_pm);
	~D_cp_supplemental_data ();

	t_uint get_sql_id()
	    { return sql_id; }
    t_uint get_sm_id()
	    { return m_sm_id; }
	t_boolean get_non_local()
		{ return m_non_local; }

	void set_paste_ptr( D_supplemental_data* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_supplemental_data* get_paste_ptr()
	  { return m_paste_ptr; }

	static mc_dbms_List<D_cp_supplemental_data *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_supplemental_data * pick_supplemental_data (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_supplemental_data *> *cut_paste_ptr;
	t_uint		sql_id;
    t_uint m_sm_id;
	t_boolean m_non_local;
	D_supplemental_data* m_paste_ptr;

};

class D_cp_supplemental_data_item
{
public:
	D_cp_supplemental_data_item (D_supplemental_data_item*, D_sm_spt_pm* copy_sp_spt_pm);
	~D_cp_supplemental_data_item ();

    t_uint get_spd_id()
	    { return spd_id; }
    t_uint get_edi_id()
	    { return edi_id; }
    t_uint get_sm_id()
	    { return m_sm_id; }

	void set_paste_ptr( D_supplemental_data_item* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_supplemental_data_item* get_paste_ptr()
	  { return m_paste_ptr; }

	static mc_dbms_List<D_cp_supplemental_data_item *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_supplemental_data_item * pick_supplemental_data_item (
		t_uint p_sm_id, 
		t_uint p_edi_id,
		t_uint p_spd_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_supplemental_data_item *> *cut_paste_ptr;
	t_uint		spd_id;
	t_uint		edi_id;
    t_uint m_sm_id;
	D_supplemental_data_item* m_paste_ptr;


};

class D_cp_state
{
public:
	D_cp_state (D_sm_state* copy_sm);
	~D_cp_state ();

	t_uint get_sql_id()
	    { return sql_id; }
    t_uint get_sm_id()
	    { return m_sm_id; }
    Id get_spd_id()
	    { return m_spd_id; }
    int get_state_number()
	    { return m_state_number; }
    Description get_state_name()
	    { return m_state_name; }
	t_boolean get_deletion_final_state()
	    { return m_deletion_final_state; }

	Id paste_sm_state(D_sm_spt_pm* p_ptr);

	void set_paste_ptr( D_sm_state* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_sm_state* get_paste_ptr()
	  { return m_paste_ptr; }

	void set_action_paste_ptr( D_action* p_ptr )
	  { m_action_paste_ptr = p_ptr; }
	D_action* get_action_paste_ptr()
	  { return m_action_paste_ptr; }

	static mc_dbms_List<D_cp_state *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_state * pick_state (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_state *> *cut_paste_ptr;
	t_uint		sql_id;  /* SMstt_ID */
	t_uint m_sm_id;
	Id m_spd_id;

    int m_state_number;
    Description m_state_name;
    t_boolean m_deletion_final_state;
	D_sm_state* m_paste_ptr;
	D_action* m_action_paste_ptr;

};

class D_cp_event
{
public:
	D_cp_event (D_sm_event* copy_sm);
	~D_cp_event ();

	t_uint get_sql_id()
	    { return sql_id; }
    t_uint get_sm_id()
	    { return m_sm_id; }
    Id get_spd_id()
	    { return m_spd_id; }
    Description get_event_label()
	    { return m_event_label; }
    Description get_event_meaning()
	    { return m_event_meaning; }
    int get_event_number()
	    { return m_event_number; }
    t_boolean get_event_label_is_unique()
	    { return m_event_label_is_unique; }
    Description get_description()
	    { return m_description; }
	Id get_poly_sm_evt_id()
	    { return m_poly_sm_evt_id; }
    Id get_poly_sm_id()
	    { return m_poly_sm_id; }
    // i2822.2.6 deletion
    Description get_local_meaning()
	    { return m_local_meaning; }

	void set_paste_ptr( D_sm_event* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_sm_event* get_paste_ptr()
	  { return m_paste_ptr; }

	t_boolean is_polymorphic()
		{ return m_event_subtype == POLY_EVENT; }

	t_boolean is_non_local()
		{ return m_event_subtype == NONLOCAL_EVENT; }

	t_boolean is_local()
		{ return m_event_subtype == LOCAL_EVENT; }

	static mc_dbms_List<D_cp_event *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_event * pick_event (t_uint p_sm_id, t_uint p_sql_id);

	static void relate_polymorphic_events ();

	void paste_event(D_sm_spt_pm* p_ptr, int p_initial_num_events);

	static void initialize_query();
	static void destroy_query();

	void reset ();

private:
	static mc_dbms_List<D_cp_event *> *cut_paste_ptr;
	t_uint		sql_id;  /* SMevt_ID */
    t_uint m_sm_id;
	Id m_spd_id;

    Description m_event_label;
    Description m_event_meaning;
    int m_event_number;

    t_boolean m_event_label_is_unique;
	enum event_types { POLY_EVENT, NONLOCAL_EVENT, LOCAL_EVENT }
		m_event_subtype;

    Description m_description;
	D_sm_event* m_paste_ptr;
	Id m_poly_sm_evt_id;
	Id m_poly_sm_id;
    // i2822.2.6 deletion
    Description m_local_meaning;

};

class D_cp_event_ignored
{
public:
	D_cp_event_ignored (D_event_ignored* copy_sm);
	~D_cp_event_ignored ();

	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_evt_id()
	    { return m_evt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }
    Description get_description()
	    { return m_description; }

	static mc_dbms_List<D_cp_event_ignored *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_event_ignored * pick_event_ignored (
		t_uint p_sm_id, t_uint p_stt_id, t_uint p_evt_id, t_uint p_spd_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_event_ignored *> *cut_paste_ptr;
	t_uint		m_stt_id;
	t_uint		m_evt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;
    Description m_description;


};

class D_cp_cant_happen
{
public:
	D_cp_cant_happen (D_cant_happen* copy_sm);
	~D_cp_cant_happen ();

	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_evt_id()
	    { return m_evt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }
    Description get_description()
	    { return m_description; }

	static mc_dbms_List<D_cp_cant_happen *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_cant_happen * pick_cant_happen
		(t_uint p_sm_id, t_uint p_stt_id, t_uint p_evt_id, t_uint p_spd_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_cant_happen *> *cut_paste_ptr;
	t_uint		m_stt_id;
	t_uint		m_evt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;
    Description m_description;


};

class D_cp_state_event_matrix_entry
{
public:
	D_cp_state_event_matrix_entry (D_state_event_matrix_entry* copy_sm);
	~D_cp_state_event_matrix_entry ();

	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_evt_id()
	    { return m_evt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	static D_cp_state_event_matrix_entry * pick_state_event_matrix_entry
		(t_uint p_sm_id, t_uint p_stt_id, t_uint p_evt_id, t_uint p_spd_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_state_event_matrix_entry *> *cut_paste_ptr;
	t_uint		m_stt_id;
	t_uint		m_evt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;


};



class D_cp_new_state_transition
{
public:
	D_cp_new_state_transition (D_new_state_transition* copy_sm);
	~D_cp_new_state_transition ();

	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_evt_id()
	    { return m_evt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }
	t_uint get_trans_id()
	    { return m_trans_id; }

	static mc_dbms_List<D_cp_new_state_transition *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_new_state_transition * pick_new_state_transition
		(t_uint p_sm_id, t_uint p_trans_id, t_uint p_spd_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_new_state_transition *> *cut_paste_ptr;
	t_uint		m_stt_id;
	t_uint		m_evt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;
	t_uint		m_trans_id;

};

class D_cp_no_event_transition
{
public:
	D_cp_no_event_transition (D_no_event_transition* copy_sm);
	~D_cp_no_event_transition ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	static mc_dbms_List<D_cp_no_event_transition *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_no_event_transition * pick_no_event_transition (
		t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_no_event_transition *> *cut_paste_ptr;
	t_uint		sql_id;  /* trans_id */
	t_uint		m_stt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;


};

class D_cp_creation_transition
{
public:
	D_cp_creation_transition (D_creation_transition* copy_sm);
	~D_cp_creation_transition ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_evt_id()
	    { return m_evt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	static mc_dbms_List<D_cp_creation_transition *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_creation_transition * pick_creation_transition (
		t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_creation_transition *> *cut_paste_ptr;
	t_uint		sql_id;   /* trans_id */
	t_uint		m_evt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;


};

class D_cp_transition
{
public:
	D_cp_transition (D_transition* copy_sm);
	~D_cp_transition ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_spd_id()
	    { return m_spd_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	void set_paste_ptr( D_transition* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_transition* get_paste_ptr()
	  { return m_paste_ptr; }

	Id paste_sm_transition(D_sm_spt_pm* p_ptr, int);

	static mc_dbms_List<D_cp_transition *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_transition * pick_transition (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_transition *> *cut_paste_ptr;
	t_uint		sql_id;
	t_uint		m_stt_id;
	t_uint		m_spd_id;
	t_uint		m_sm_id;
	D_transition* m_paste_ptr;

};


class D_cp_moore_action_home
{
public:
	D_cp_moore_action_home (D_moore_action_home* copy_sm);
	~D_cp_moore_action_home ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_stt_id()
	    { return m_stt_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	static mc_dbms_List<D_cp_moore_action_home *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_moore_action_home * pick_moore_action_home (t_uint p_sm_id, t_uint p_sql_id);
	static D_cp_moore_action_home * pick_moore_action_home2 (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_moore_action_home *> *cut_paste_ptr;
	t_uint		sql_id;   /* act_id */
	t_uint		m_stt_id;
	t_uint		m_sm_id;


};

class D_cp_mealy_action_home
{
public:
	D_cp_mealy_action_home (D_mealy_action_home* copy_sm);
	~D_cp_mealy_action_home ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_trans_id()
	    { return m_trans_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	static D_cp_mealy_action_home * pick_mealy_action_home (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_mealy_action_home *> *cut_paste_ptr;
	t_uint		sql_id;
	t_uint		m_trans_id;
	t_uint		m_sm_id;


};

class D_cp_action_home
{
public:
	D_cp_action_home (D_action_home* copy_sm);
	~D_cp_action_home ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }

	static D_cp_action_home * pick_action_home (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_action_home *> *cut_paste_ptr;
	t_uint		sql_id;
	t_uint		m_sm_id;


};

class D_cp_action;
class D_cp_execution_spec
{
public:
	D_cp_execution_spec (D_execution_spec* copy_sm);
	virtual ~D_cp_execution_spec ();

	t_uint get_sql_id()
	    { return sql_id; }
    Description get_verbatim_desc()
	    { return m_verbatim_desc; }
    Description get_tmp_desc()
	    { return m_tmp_desc; }
	D_execution_spec::t_desc_state get_desc_state()
	    { return m_desc_state; }
	D_execution_spec::t_parse_result get_last_parse_result()
	    { return m_last_parse_result; }
	t_boolean get_parse_on_apply()
	    { return m_parse_on_apply; }
	AL_Bush_action* get_AL_Action_ptr()
	    { return m_AL_Action_ptr; }

	virtual D_cp_action* get_cp_action_ptr();

	static void initialize_query();
	static void destroy_query();

protected:
	t_uint		sql_id;

    Description m_verbatim_desc;
    Description m_tmp_desc;

	D_execution_spec::t_desc_state m_desc_state;
	D_execution_spec::t_parse_result m_last_parse_result;

	t_boolean m_parse_on_apply;

	AL_Bush_action* m_AL_Action_ptr;
};

class D_cp_action: public D_cp_execution_spec
{
public:
	D_cp_action (D_action* copy_sm);
	~D_cp_action ();

	t_uint get_sql_id()
	    { return sql_id; }
	t_uint get_sm_id()
	    { return m_sm_id; }
    Description get_description()
	    { return m_descrip; }
    Description get_verbatim_desc()
	    { return m_verbatim_desc; }
    Description get_tmp_desc()
	    { return m_tmp_desc; }
	D_execution_spec::t_desc_state get_desc_state()
	    { return m_desc_state; }
	D_execution_spec::t_parse_result get_last_parse_result()
	    { return m_last_parse_result; }
	t_boolean get_parse_on_apply()
	    { return m_parse_on_apply; }
	AL_Bush_action* get_AL_Action_ptr()
	    { return m_AL_Action_ptr; }

	void set_paste_ptr( D_action* p_ptr )
	  { m_paste_ptr = p_ptr; }
	D_action* get_paste_ptr()
	  { return m_paste_ptr; }

	D_cp_action* get_cp_action_ptr();

	static mc_dbms_List<D_cp_action *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_action * pick_action (t_uint p_sm_id, t_uint p_sql_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_action *> *cut_paste_ptr;
	t_uint		m_sm_id;

	Description m_descrip;
	D_action* m_paste_ptr;
};


#endif
//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
