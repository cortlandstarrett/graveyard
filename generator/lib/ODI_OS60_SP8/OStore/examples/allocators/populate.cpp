#include <ostore/allocators/afalloc.cc>
#include <ostore/allocators/afcontxt.hh>
#include <ostore/allocators/afalcreg.hh>
#include <ostore/allocators/afruleng.hh>
#include <ostore/allocators/afsetdb.hh>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/afttrait.hh>
#include <ostore/allocators/afclaloc.hh>
#include "dbname.h"

os_Trait_List * Setup_Traits(os_unsigned_int32,
			     os_unsigned_int32,
			     os_unsigned_int32);

os_string Rules_root_name("Rules");
os_string Allocators_root_name("Allocators");

void populate_rule_db()
{

  OS_BEGIN_TXN(pop_rule_db_txn, 0, os_transaction::update) {
    os_index_key( os_string, string_rank, string_hash ) ;
    os_database* db = 0 ;

    db = os_database::open( rules_db_name, 0, 0666 ) ;

    os_rule_engine::rule_db( db->get_pathname(), Rules_root_name );
    os_rule_engine* rul_eng = os_rule_engine::instance() ;
    os_database_root *a_root = db->find_root( Rules_root_name ) ;
    if( !a_root )
    {
	char string_name[][100] =
	{"String->stringalloc",
	 "Employee=Manager->Manageralloc",
	 "Employee=SalesPerson->Employeealloc",
	 "WageEmployee->Employeealloc",
	 "EmployeeList->Employeealloc"
	};

	char rule_name[][10]  = {
	  "Rule1",
	  "Rule2",
	  "Rule3",
	  "Rule4",
	  "Rule5"
	};

	os_string new_rule_name ;
	os_string new_rule_str ;
	os_boolean result  ;
	for ( int n = 0; n<4; n++)
	{
          new_rule_name = rule_name[n];
          new_rule_str = string_name[n];
          os_string* user_rule_str = new( db, os_string::get_os_typespec() )
            os_string( new_rule_str);
          result = rul_eng->create_rule( new_rule_name, (os_string&)*user_rule_str ) ;
          rul_eng->register_rule( new_rule_name ) ;
        }
	a_root =  db->create_root( Rules_root_name ) ;
	a_root->set_value( rul_eng ) ;
    }
    else
    {
      cout<< "Database already exists ";
    }
    db->close() ;

  } OS_END_TXN(pop_rule_db_txn);
}

void populate_alloc_db()
{

  OS_BEGIN_TXN(pop_alloc_db_txn, 0, os_transaction::update) {

    os_database* db = 0 ;
    os_extended_allocator* p_ext_alloc = 0;
    os_segment * ps;
    os_cluster * pc;

    char allocator_name[][20] = {"stringalloc",
				 "Manageralloc",
				 "Employeealloc",
				 "defaultalloc" };
    os_index_key( os_string, string_rank, string_hash ) ;

    db = os_database::open( allocator_db_name, 0, 0644 ) ;

    os_allocator_registry::alloc_db( db->get_pathname(), Allocators_root_name);

    os_database_root *a_root = db->find_root( Allocators_root_name ) ;

    if( !a_root )
    {
      os_boolean result ;
      os_allocator_registry* aloc_reg = os_allocator_registry::instance() ;
      os_string default_database( example_db_name ) ;

      os_database * usr_db = os_database::open (example_db_name, 0,0666);

      os_cluster_allocator* usr_alloc =
                   new(db, os_cluster_allocator::get_os_typespec())
                              os_cluster_allocator(usr_db,
						   1,
						   2097152,
						   2);

      os_trait_iterator* p_itr = usr_alloc->get_traits() ;

      for (os_Trait<os_Trait_unsigned_int32, os_string>* p_trait = (
           os_Trait<os_Trait_unsigned_int32, os_string>*)p_itr->first();
           p_trait;
           p_trait = (os_Trait<os_Trait_unsigned_int32, os_string>*)p_itr->next()
          )
      {
        display_traits(*p_trait);
      }

      result = aloc_reg->enter(allocator_name[0] , usr_alloc ) ;

      ps = usr_db->get_segment(usr_alloc->get_segment_number());
      pc = ps->create_cluster();

      usr_alloc = new(db, os_cluster_allocator::get_os_typespec())
                      os_cluster_allocator(pc);

      for(os_unsigned_int32 clustrs = 1; clustrs < 2; clustrs++)
      {
        pc = ps->create_cluster();
        usr_alloc->add_to_cluster_list(pc);
      }

      os_Trait_List * p_traits = Setup_Traits(2,
					      2,
					      2097152);
      usr_alloc->insert_traits(p_traits);

      result = aloc_reg->enter(allocator_name[1] , usr_alloc ) ;

      delete p_traits;

      pc = ps->create_cluster();

      usr_alloc = new(db, os_cluster_allocator::get_os_typespec())
                      os_cluster_allocator(pc);

      for(os_unsigned_int32 clust = 1; clust < 2; clust++)
      {
        pc = ps->create_cluster();
        usr_alloc->add_to_cluster_list(pc);
      }

      p_traits = Setup_Traits(2, 2, 2097152);
      usr_alloc->insert_traits(p_traits);

      result = aloc_reg->enter(allocator_name[2] , usr_alloc ) ;

      delete p_traits;

      pc = ps->create_cluster();

      usr_alloc = new(db, os_cluster_allocator::get_os_typespec())
                      os_cluster_allocator(pc);

      p_traits = Setup_Traits(2, 1, 2097152);
      usr_alloc->insert_traits(p_traits);

      result = aloc_reg->enter(allocator_name[3] , usr_alloc ) ;

      delete p_traits;

      usr_db->close();

      a_root = db->create_root( Allocators_root_name ) ;
      a_root->set_value( aloc_reg ) ;
    }
  else
    {
      cout << "Allocator already exists";
    }

    db->close() ;

  } OS_END_TXN( pop_alloc_db_txn );
}

os_Trait_List * Setup_Traits(os_unsigned_int32 segments,
			     os_unsigned_int32 clusters,
			     os_unsigned_int32 clust_size)
{
  os_Trait_List * p_Traits = new os_Trait_List;

  os_Trait<os_Trait_unsigned_int32, os_string> * trait1 =
    new os_Trait< os_Trait_unsigned_int32, os_string>(
             os_string(DB_MAX_SEGS_PER_DB_TRAIT),
             os_Trait_unsigned_int32::to_string(segments)
             );

  p_Traits->insert(trait1);

  os_Trait<os_Trait_unsigned_int32, os_string> * trait2 =
    new os_Trait< os_Trait_unsigned_int32, os_string>(
             os_string(DB_MAX_CLUSTERS_PER_SEG_TRAIT),
             os_Trait_unsigned_int32::to_string(clusters)
             );

  p_Traits->insert(trait2);

  os_Trait<os_Trait_unsigned_int32, os_string> * trait3 =
    new os_Trait< os_Trait_unsigned_int32, os_string>(
             os_string(DB_MAX_CLUSTER_SIZE_TRAIT),
             os_Trait_unsigned_int32::to_string(clust_size)
             );

  p_Traits->insert(trait3);

  return p_Traits;
}

