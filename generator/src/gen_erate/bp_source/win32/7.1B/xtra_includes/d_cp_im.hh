/*========================================================================
 *
 * File:      $RCSfile: d_cp_im.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:08 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef D_CPIM_HH
#define D_CPIM_HH

#include <d_typdef.hh>
#include <u_desc.hh>
#include <u_id.hh>
#include <u_string.hh>
#include <u_typdef.hh>

class Object;
class Attribute;
class Imported_object;
class Referential_attribute;
class Attr_ref_in_object;
class Referred_to_ident_attr;
class Relationship;
class Object_in_relationship;
class Object_referred_to;
class Object_referring;
class Simple_relationship;
class Object_as_simple_participant;
class Object_as_simple_formalizer;
class Associative_relationship;
class Object_as_assoc_one_side;
class Object_as_assoc_other_side;
class Object_as_associator;
class Inheritance_relationship;
class Object_as_supertype;
class Object_as_subtype;
class Composition_relationship;
class Object_as_comp_one_end;
class Object_as_comp_other_end;
class Object_in_non_inh_relationship;

class D_im_ocm_oam;

class D_cp_o_obj
{
public:
	D_cp_o_obj (Object* copy_obj);
	~D_cp_o_obj ();

	t_uint get_obj_id()
	    { return m_obj_id; }

	void set_paste_ptr( Object* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Object* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_o_obj * pick_o_obj (t_uint p_obj_id);

	static mc_dbms_List<D_cp_o_obj *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_o_obj *> *cut_paste_ptr;
	t_uint		m_obj_id;

	Object*     m_paste_ptr;
};

class D_cp_o_attr
{
public:
	D_cp_o_attr (Attribute* copy_iobj);
	~D_cp_o_attr ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_attr_id()
	    { return m_attr_id; }

	void set_paste_ptr( Attribute* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Attribute* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_o_attr * pick_o_attr (t_uint p_obj_id, t_uint p_attr_id);

	static mc_dbms_List<D_cp_o_attr *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_o_attr *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_attr_id;

	Attribute*     m_paste_ptr;
};

class D_cp_o_iobj
{
public:
	D_cp_o_iobj (Imported_object* copy_iobj);
	~D_cp_o_iobj ();

	t_uint get_iobj_id()
	    { return m_iobj_id; }
	t_uint get_obj_id()
	    { return m_obj_id; }
	t_model_type get_model_type()
	    { return m_model_type; }
	t_uint get_ss_id()
	    { return m_ss_id; }
    Description get_obj_name()
        { return m_obj_name; }
    Description get_obj_kl()
        { return m_obj_kl; }

	Id paste_imported_object(D_im_ocm_oam *p_im_ocm_oam_ptr);

	void set_paste_ptr( Imported_object* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Imported_object* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_o_iobj * pick_o_iobj (t_uint p_iobj_id);
	static Object* find_object(D_im_ocm_oam *p_im_ocm_oam_ptr, t_uint p_obj_id);

	static mc_dbms_List<D_cp_o_iobj *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_o_iobj *> *cut_paste_ptr;
	t_uint		m_iobj_id;
	t_uint		m_obj_id;
	t_model_type  m_model_type;
	t_uint		m_ss_id;
    Description m_obj_name;
    Description m_obj_kl;

	Imported_object*     m_paste_ptr;
};

class D_cp_o_rattr
{
public:
	D_cp_o_rattr (Referential_attribute* copy_rattr);
	~D_cp_o_rattr ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_attr_id()
	    { return m_attr_id; }
	t_uint get_bobj_id()
	    { return m_bobj_id; }
	t_uint get_battr_id()
	    { return m_battr_id; }
	t_uint get_ref_mode()
	    { return m_ref_mode; }
	Description get_prefix()
		{ return m_prefix; }
	Description get_root()
		{ return m_root; }

	void set_paste_ptr( Referential_attribute* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Referential_attribute* get_paste_ptr()
	  { return m_paste_ptr; }

	static mc_dbms_List<D_cp_o_rattr *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_o_rattr * pick_o_rattr (t_uint p_obj_id, t_uint p_attr_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_o_rattr *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_attr_id;
	t_uint		m_bobj_id;
	t_uint		m_battr_id;
	int			m_ref_mode;

	Description m_prefix;
	Description m_root;

    Referential_attribute* m_paste_ptr;
};

class D_cp_o_ref
{
public:
	D_cp_o_ref (Attr_ref_in_object* copy_rattr,
				Attr_ref_in_object* previous_attr_ref);
	~D_cp_o_ref ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_robj_id()
	    { return m_robj_id; }
	t_uint get_roid_id()
	    { return m_roid_id; }
	t_uint get_rattr_id()
	    { return m_rattr_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_uint get_roir_id()
	    { return m_roir_id; }
	t_uint get_attr_id()
	    { return m_attr_id; }
	t_uint get_aref_id()
	    { return m_aref_id; }
	t_uint get_paref_id()
	    { return m_paref_id; }
	int get_is_constrained()
	    { return m_is_constrained; }
	Description get_descrip()
	    { return m_descrip; }

	void set_paste_ptr( Attr_ref_in_object* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Attr_ref_in_object* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_o_ref * pick_o_ref (t_uint p_aref_id);

	static mc_dbms_List<D_cp_o_ref *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_o_ref *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_robj_id;
	t_uint		m_roid_id;
	t_uint		m_rattr_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_uint		m_roir_id;
	t_uint		m_attr_id;
	t_uint		m_aref_id;
	t_uint		m_paref_id;
	t_uint		m_is_constrained;
	Description m_descrip;

    Attr_ref_in_object* m_paste_ptr;
};

class D_cp_o_rtida
{
public:
	D_cp_o_rtida (t_uint p_attr_id, 
		t_uint p_obj_id,
		t_uint p_oid_id,
		t_uint p_rel_id,
		t_uint p_oir_id
		);
	~D_cp_o_rtida ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_oid_id()
	    { return m_oid_id; }
	t_uint get_attr_id()
	    { return m_attr_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }

	void set_paste_ptr( Referred_to_ident_attr* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Referred_to_ident_attr* get_paste_ptr()
	  { return m_paste_ptr; }

	static mc_dbms_List<D_cp_o_rtida *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static D_cp_o_rtida * pick_o_rtida (t_uint p_attr_id, 
		t_uint p_obj_id,
		t_uint p_oid_id,
		t_uint p_rel_id,
		t_uint p_oir_id
		);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_o_rtida *> *cut_paste_ptr;
	t_uint		m_attr_id;
	t_uint		m_obj_id;
	t_uint		m_oid_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;

    Referred_to_ident_attr* m_paste_ptr;
};

class D_cp_r_rel
{
public:
	D_cp_r_rel (Relationship* copy_rattr);
	~D_cp_r_rel ();

	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_ss_id()
	    { return m_ss_id; }
	int get_rel_number()
	    { return m_numb; }
	Description get_descrip ()
	    { return m_descrip; }

	Id paste_relationship(D_im_ocm_oam * p_im_ocm_oam);
	void fix_ref_attrs(D_im_ocm_oam * p_im_ocm_oam);

	void set_paste_ptr( Relationship* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Relationship* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_r_rel * pick_r_rel (t_uint p_rel_id);

	static mc_dbms_List<D_cp_r_rel *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_rel *> *cut_paste_ptr;
	t_uint		m_rel_id;
	t_uint		m_ss_id;
	int			m_numb;
	Description m_descrip;

    Relationship* m_paste_ptr;
};

class D_cp_r_oir
{
public:
	D_cp_r_oir (Object_in_relationship* copy_rattr);
	~D_cp_r_oir ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_uint get_iobj_id()
	    { return m_iobj_id; }

	static D_cp_r_oir * pick_r_oir (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static mc_dbms_List<D_cp_r_oir *> *get_cut_paste_coll()
	  { return cut_paste_ptr; }

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_oir *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_uint		m_iobj_id;
};

class D_cp_r_rto
{
public:
	D_cp_r_rto (Object_referred_to* copy_rattr);
	~D_cp_r_rto ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_uint get_oid_id()
	    { return m_oid_id; }

	void set_paste_ptr( Object_referred_to* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Object_referred_to* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_r_rto * pick_r_rto (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_rto *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_uint		m_oid_id;

    Object_referred_to* m_paste_ptr;
};

class D_cp_r_rgo
{
public:
	D_cp_r_rgo (Object_referring* copy_rattr);
	~D_cp_r_rgo ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }

	void set_paste_ptr( Object_referring* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Object_referring* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_r_rgo * pick_r_rgo (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_rgo *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;

    Object_referring* m_paste_ptr;
};

class D_cp_r_oinir
{
public:
	D_cp_r_oinir (Object_in_non_inh_relationship* copy_rattr);
	D_cp_r_oinir (Object_as_assoc_one_side* copy_rattr);
	D_cp_r_oinir (Object_as_assoc_other_side* copy_rattr);
	~D_cp_r_oinir ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }
	
	void set_mult( t_multiplicity p_mult )
	    { m_mult = p_mult; }

	void set_paste_ptr( Object_in_non_inh_relationship* p_ptr )
	  { m_paste_ptr = p_ptr; }
	Object_in_non_inh_relationship* get_paste_ptr()
	  { return m_paste_ptr; }

	static D_cp_r_oinir * pick_r_oinir (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_oinir *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;

    Object_in_non_inh_relationship* m_paste_ptr;
};

class D_cp_r_simp
{
public:
	D_cp_r_simp (Simple_relationship* copy_rattr);
	D_cp_r_simp (Associative_relationship* copy_rattr);
	~D_cp_r_simp ();

	t_uint get_rel_id()
	    { return m_rel_id; }

	static D_cp_r_simp * pick_r_simp (t_uint p_rel_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_simp *> *cut_paste_ptr;
	t_uint		m_rel_id;
};

class D_cp_r_part
{
public:
	D_cp_r_part (Object_as_simple_participant* copy_rattr);
	~D_cp_r_part ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }
	

	static D_cp_r_part * pick_r_part (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_part *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;
};

class D_cp_r_form
{
public:
	D_cp_r_form (Object_as_simple_formalizer* copy_rattr);
	~D_cp_r_form ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }

	static D_cp_r_form * pick_r_form (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_form *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;
};

class D_cp_r_assoc
{
public:
	D_cp_r_assoc (Associative_relationship* copy_rattr);
	~D_cp_r_assoc ();

	t_uint get_rel_id()
	    { return m_rel_id; }

	static D_cp_r_assoc * pick_r_assoc (t_uint p_rel_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_assoc *> *cut_paste_ptr;
	t_uint		m_rel_id;
};

class D_cp_r_aone
{
public:
	D_cp_r_aone (Object_as_assoc_one_side* copy_rattr);
	~D_cp_r_aone ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }

	static D_cp_r_aone * pick_r_aone (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_aone *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;
};

class D_cp_r_aoth
{
public:
	D_cp_r_aoth (Object_as_assoc_other_side* copy_rattr);
	~D_cp_r_aoth ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }

	static D_cp_r_aoth * pick_r_aoth (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_aoth *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;
};

class D_cp_r_assr
{
public:
	D_cp_r_assr (Object_as_associator* copy_rattr);
	~D_cp_r_assr ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }

	static D_cp_r_assr * pick_r_assr (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_assr *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
};

class D_cp_r_subsup
{
public:
	D_cp_r_subsup (Inheritance_relationship* copy_rattr);
	~D_cp_r_subsup ();

	t_uint get_rel_id()
	    { return m_rel_id; }

	static D_cp_r_subsup * pick_r_subsup (t_uint p_rel_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_subsup *> *cut_paste_ptr;
	t_uint		m_rel_id;
};

class D_cp_r_super
{
public:
	D_cp_r_super (Object_as_supertype* copy_rattr);
	~D_cp_r_super ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }

	static D_cp_r_super * pick_r_super (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_super *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
};

class D_cp_r_sub
{
public:
	D_cp_r_sub (Object_as_subtype* copy_rattr);
	~D_cp_r_sub ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }

	static D_cp_r_sub * pick_r_sub (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_sub *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
};

class D_cp_r_comp
{
public:
	D_cp_r_comp (Composition_relationship* copy_rattr);
	~D_cp_r_comp ();

	t_uint get_rel_id()
	    { return m_rel_id; }
	String get_rel_chn()
	    { return m_rel_chn; }

	static D_cp_r_comp * pick_r_comp (t_uint p_rel_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_comp *> *cut_paste_ptr;
	t_uint		m_rel_id;
	String		m_rel_chn;
};

class D_cp_r_cone
{
public:
	D_cp_r_cone (Object_as_comp_one_end* copy_rattr);
	~D_cp_r_cone ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }

	static D_cp_r_cone * pick_r_cone (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_cone *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;
};

class D_cp_r_coth
{
public:
	D_cp_r_coth (Object_as_comp_other_end* copy_rattr);
	~D_cp_r_coth ();

	t_uint get_obj_id()
	    { return m_obj_id; }
	t_uint get_rel_id()
	    { return m_rel_id; }
	t_uint get_oir_id()
	    { return m_oir_id; }
	t_multiplicity get_mult()
	    { return m_mult; }
	t_conditionality get_cond()
	    { return m_cond; }
	Description get_txt_phrs()
	    { return m_txt_phrs; }

	static D_cp_r_coth * pick_r_coth (t_uint p_obj_id, 
		t_uint p_rel_id, t_uint p_oir_id);

	static void initialize_query();
	static void destroy_query();

private:
	static mc_dbms_List<D_cp_r_coth *> *cut_paste_ptr;
	t_uint		m_obj_id;
	t_uint		m_rel_id;
	t_uint		m_oir_id;
	t_multiplicity m_mult;
	t_conditionality m_cond;
	Description m_txt_phrs;
};


#endif 

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
