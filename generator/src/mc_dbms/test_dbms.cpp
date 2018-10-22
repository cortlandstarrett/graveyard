/*========================================================================
 *
 * File:      $RCSfile: test_dbms.cpp,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:43:00 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <iostream>
#include <string>
#include <mc_dbms/mc_dbms.hh>
#include <mc_dbms/external_object.h>
#include <list>

char* mcdbms_RestoreExternalObject(TrackedType typeID)
{
	return 0;
}

#define AssertEqual(cond) \
	if (!( cond )) { \
		std::cout << "Error! line: " << __LINE__ << "  " << #cond << std::endl; \
		return; \
	} 

/**
 * This class is used to monitor progress of the test.  It tells us when we
 * enter and leave each test.
 */
class EntryWatcher {
public:
	EntryWatcher(const std::string& objectName, const std::string& msg = "") : 
		m_watching(objectName) 
	{ 
		std::cout << "Entering: " << m_watching << "  " << msg << std::endl; 
	}
	
	~EntryWatcher()
	{
		std::cout << "Exiting: " << m_watching << std::endl; 
	} 
	
private:
	std::string m_watching;
};

/**
 * This is a dummy-class used just to instantiate some of the templated
 * classes that need to be exercised.
 */
class Foo {
public:
	Foo() { }
	~Foo() { }	
	static mc_dbms_typespec* get_mc_dbms_typespec() {return &type; }
	static mc_dbms_typespec type;
	
	int var;
	
};

#ifdef REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test

class rel_test_2;
class rel_test_1 {
public:
	rel_test_1() { }
	~rel_test_1() { }
	static mc_dbms_typespec* get_mc_dbms_typespec() {return &type; }
	static mc_dbms_typespec type;
	
	int m_var;
	
	mc_dbms_relationship_1_1(rel_test_1, m_test_1_1, rel_test_2, m_test_1_1, rel_test_2*) m_test_1_1;
	mc_dbms_relationship_m_1(rel_test_1, m_test_m_1, rel_test_2, m_test_1_m, mc_dbms_List< rel_test_2 * > ) m_test_m_1;
	mc_dbms_relationship_m_m(rel_test_1, m_test_m_m, rel_test_2, m_test_m_m, mc_dbms_List< rel_test_2 * > ) m_test_m_m;
};

class rel_test_2 {
public:
	rel_test_2() { }
	~rel_test_2() { }
	static mc_dbms_typespec* get_mc_dbms_typespec() {return &type; }
	static mc_dbms_typespec type;
	
	int m_var;
	
	mc_dbms_relationship_1_1(rel_test_2, m_test_1_1, rel_test_1, m_test_1_1, rel_test_1*) m_test_1_1;
	mc_dbms_relationship_1_m(rel_test_2, m_test_1_m, rel_test_1, m_test_m_1, rel_test_2 *) m_test_1_m;
	mc_dbms_relationship_m_m(rel_test_2, m_test_m_m, rel_test_1, m_test_m_m, mc_dbms_List< rel_test_1 * > ) m_test_m_m;
};

mc_dbms_typespec rel_test_1::type("rel_test_1", sizeof(rel_test_1));
mc_dbms_typespec rel_test_2::type("rel_test_2", sizeof(rel_test_2));
mc_dbms_relationship_1_m_body(rel_test_2, m_test_1_m, rel_test_1, m_test_m_1);
mc_dbms_relationship_1_1_body(rel_test_1, m_test_1_1, rel_test_2, m_test_1_1);
mc_dbms_relationship_1_1_body(rel_test_2, m_test_1_1, rel_test_1, m_test_1_1);
mc_dbms_relationship_m_1_body(rel_test_1, m_test_m_1, rel_test_2, m_test_1_m);

/* 1-to-1 test */
rel_test_1 foo1;
rel_test_2 foo2;

/* 1-to-many test */
rel_test_1 foo_1_m;
rel_test_2 foo2_1_m1;
rel_test_2 foo2_1_m2;
rel_test_2 foo2_1_m3;

/* many-to-many test */
rel_test_1 foo_m_m;
rel_test_2 foo2_m_m;

#endif // REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test

mc_dbms_typespec Foo::type( "I_Attribute", 178 );

void test_typespec()
{
    EntryWatcher monitor("test_typespec");
    mc_dbms_typespec get_name_test("test", sizeof(Foo));
    AssertEqual( !strcmp("test",get_name_test.get_name( ) ) );
    	
    mc_dbms_typespec copy_const_test( get_name_test );
    AssertEqual( !strcmp("test",copy_const_test.get_name( ) ) );
		
	mc_dbms_typespec assignment_test( "foo", sizeof(Foo) );
	assignment_test = get_name_test;
	AssertEqual( !strcmp("test",assignment_test.get_name( ) ) );
		
	mc_dbms_typespec comp1_test( "foo ", sizeof(Foo) );
	mc_dbms_typespec comp2_test( "test", sizeof(Foo) );
	AssertEqual( !(comp1_test == get_name_test) );
	
	mc_dbms_typespec* get_char1 = mc_dbms_typespec::get_char( );
	mc_dbms_typespec* get_char2 = mc_dbms_typespec::get_char( );
	AssertEqual( get_char1 != NULL || get_char1 == get_char2 ) ;

		
	mc_dbms_typespec* get_unsigned_char1 = mc_dbms_typespec::get_unsigned_char( );
	mc_dbms_typespec* get_unsigned_char2 = mc_dbms_typespec::get_unsigned_char( );
	AssertEqual( get_unsigned_char1 != NULL || get_unsigned_char1 == get_unsigned_char2 );
		
	mc_dbms_typespec* get_unsigned_long1 = mc_dbms_typespec::get_unsigned_long( );
	mc_dbms_typespec* get_unsigned_long2 = mc_dbms_typespec::get_unsigned_long( );
	AssertEqual( get_unsigned_long1 != NULL || get_unsigned_long1 == get_unsigned_long2 );
		
	mc_dbms_typespec* get_unsigned_short1 = mc_dbms_typespec::get_unsigned_short( );
	mc_dbms_typespec* get_unsigned_short2 = mc_dbms_typespec::get_unsigned_short( );
	AssertEqual( get_unsigned_short1 != NULL || get_unsigned_short1 == get_unsigned_short2 );
}

void test_Collection()
{
    EntryWatcher monitor("test_Collection");
    mc_dbms_Collection<Foo*> foo;
    
    Foo i;
    Foo j;
    Foo k;
    Foo l;
    i.var = 1;
    int temp;
    foo.insert( &i );
    AssertEqual( foo.cardinality() == 1 );
    
    j.var = 2;
    foo.insert( &j );
    temp = (*(foo.pick( ))).var;
    AssertEqual( temp == 1 );

    temp = (*(foo.retrieve( 0 ))).var;
    AssertEqual( temp == 1 );
    	
    foo.remove( &i );
    Foo* val;
    int place = 0;
    while( ( val = foo.retrieve(place) ) != 0 )
    {
		int value = (*val).var;
      	AssertEqual( value != 1 );
		place++;
	}

    foo.clear();
	l.var = 5;
	k.var = 3;
    foo.insert( &i );
    foo.insert_last( &j );
    foo.insert_last( &l );
    AssertEqual( (*(foo.retrieve( 1 ))).var == 2 );
		
	foo.insert_before( &k, 2 );
    AssertEqual( (*(foo.retrieve( 2 ))).var == 3 );
	
	foo.clear();
	foo.insert( &i );
    foo.insert_last( &k );
    foo.replace_at( &l,0 );
	AssertEqual( (*(foo.retrieve( 0 ))).var == 5 );
}

void test_collection()
{
    EntryWatcher monitor("test_collection");
	mc_dbms_collection foo;
	mc_dbms_collection foo2;
	
	Foo i;
	Foo j;
	Foo k;
	Foo l;
	Foo m;
	
	i.var = 1;
	j.var = 2;
	k.var = 3;
	l.var = 4;
	m.var = 5;
	foo.insert( &i );
	foo.insert( &j );
	
	AssertEqual( foo.cardinality( ) == 2 );
		
	foo.clear();
	AssertEqual( foo.cardinality( ) == 0 );
		
	foo.insert( &i );
	foo.insert( &j );
	AssertEqual( (*(Foo*)(foo.retrieve_first( ) )).var == i.var );
		
    int temp = (*(Foo*)foo.retrieve( 0 )).var;
    AssertEqual( temp == 1 );
    
    int temp2 = (*(Foo*)foo.pick( )).var;
    AssertEqual( temp2 == 1 );

    foo.clear();
    foo.insert( &i );
    foo.insert_last( &j );
    foo.insert_last( &l );
    AssertEqual( (*(Foo*)(foo.retrieve( 1 ))).var == 2 );
    		
    foo.clear();
    foo.insert( &i );
    foo.insert_last( &j );
    foo.insert_last( &l );
	foo.insert_before( &k, 2 );
    AssertEqual( (*(Foo*)(foo.retrieve( 2 ))).var == 3 );
	
	foo.remove( &i );
	AssertEqual( (*(Foo*)foo.retrieve( 0 )).var == 2 );
	
    foo.replace_at( &l,0 );
	AssertEqual( (*(Foo*)foo.retrieve( 0 )).var == 4 );
	
	foo.clear();	
    foo.insert( &i );
	int size = foo;
	AssertEqual( size == 1 );
	
	foo2.insert( &i );
	AssertEqual( foo == foo2 );

	foo2.insert( &j );
	AssertEqual( !(foo == foo2) );
		
	AssertEqual( foo == &i );
	AssertEqual( !( foo == &j ) );
		
	foo.clear( );
	foo.insert( &i );
	foo2.clear( );
	foo2.insert( &j );
	mc_dbms_collection res = (foo |= foo2 );
	AssertEqual( foo.cardinality() == 2 && res.cardinality() == 2 );

	foo.clear( );
	foo.insert( &i );		 
	mc_dbms_collection res2 = (foo |= &k );
	AssertEqual( foo.cardinality() == 2 && res2.cardinality() == 2 );
	
	foo.clear();
	foo2.clear();
	foo.insert( &j );
	foo.insert( &k );
	foo.insert( &k );
	foo.insert( &l );
	
	foo2.insert( &j );
	foo2.insert( &k );
	
	mc_dbms_collection res3 = (foo &= foo2 );
	AssertEqual( foo.cardinality() == 2 && res3.cardinality() == 2 && (((Foo*)res3.retrieve(0))->var == 2 || ((Foo*)res3.retrieve(0))->var == 3 ) );
	
	foo.clear();
	foo.insert( &j );
	foo.insert( &k );
	foo.insert( &k );
	foo.insert( &l );
	mc_dbms_collection res4 = (foo &= &k );
	AssertEqual( foo.cardinality() == 1 && res4.cardinality() == 1 && ((Foo*)res4.retrieve_first())->var == 3 );

	foo.clear();
	foo2.clear();
	foo.insert( &j );
	foo.insert( &k );
	foo.insert( &k );
	foo.insert( &l );
	foo2.insert( &k );
	foo2.insert( &k );
	foo2.insert( &k );
	
	mc_dbms_collection res5 = (foo -= foo2 );
	AssertEqual( foo.cardinality() == 2 && res5.cardinality() == 2 && ((Foo*)res5.retrieve(1))->var != 3 || ((Foo*)res5.retrieve(0))->var != 3 );

	foo.clear();
	foo2.clear();
	foo.insert( &j );
	foo.insert( &k );
	foo.insert( &k );
	foo.insert( &l );
	foo2.insert( &k );
	
	mc_dbms_collection res7 = (foo -= foo2 );
	AssertEqual( foo.cardinality() == 3 && res7.cardinality() == 3 && ((Foo*)res7.retrieve(2))->var != 3 && ((Foo*)res7.retrieve(1))->var == 3 )
			
	foo.clear();
	foo2.clear();
	foo.insert( &j );
	foo.insert( &k );
	foo.insert( &k );
	foo.insert( &l );
	foo2.insert( &k );
	mc_dbms_collection res6 = (foo -= &k );
	AssertEqual( foo.cardinality() == 3 && res6.cardinality() == 3 && ((Foo*)res6.retrieve(2))->var != 3  )
}

void test_Bag()
{
    EntryWatcher monitor("test_Bag");
	mc_dbms_Bag< class Foo * > bag1;
	mc_dbms_Bag< class Foo * >& bag2 = mc_dbms_Bag<class Foo *>::create(mc_dbms_database::get_transient_database());
}

void test_List()
{
    EntryWatcher monitor("test_List");
	mc_dbms_List<class Foo *> list;
	mc_dbms_List< class Foo * >& bag2 = mc_dbms_List<class Foo *>::create(mc_dbms_database::get_transient_database());
}

void test_Set()
{
    EntryWatcher monitor("test_Set");
	mc_dbms_Set<class Foo *>	set;
	mc_dbms_Set< class Foo * >& bag2 = mc_dbms_Set<class Foo *>::create(mc_dbms_database::get_transient_database());
}

void test_Cursor()
{
    /* TODO: replicate this for a list */
    mc_dbms_Collection< Foo* > foo;
    EntryWatcher monitor("test_Cursor");
   	mc_dbms_Cursor< Foo* > foo1(foo);
   	AssertEqual( !foo1.null() );

    Foo i;
    Foo j;
    Foo k;
    
	i.var = 3;
	j.var = 2;
	k.var = 1;
    foo.insert( &i );
    foo.insert( &j );
    foo.insert( &k );
	mc_dbms_Cursor< Foo* > cursor_foo( foo );
	
	int last_test = (*(cursor_foo.last())).var; // 1
	int first_test = (*(cursor_foo.first())).var; // 3
	int next_test = (*(cursor_foo.next())).var; // 2
	int prev_test = (*(cursor_foo.previous())).var; // 3
	int ret_test = (*(cursor_foo.retrieve())).var; // 3
	int plus_test = (*(++cursor_foo)).var; // 2
	int minus_test = (*(--cursor_foo)).var; // 3
	int func_test = (*(cursor_foo)).var; // 3

	AssertEqual( last_test == 1 );
	AssertEqual( first_test == 3 );
	AssertEqual( next_test == 2 );
	AssertEqual( prev_test == 3 );
	AssertEqual( ret_test == 3 );
	AssertEqual( plus_test == 2 );
	AssertEqual( minus_test == 3 );
	AssertEqual( func_test == 3 );
	mc_dbms_typespec* temp = cursor_foo.get_mc_dbms_typespec( );
	AssertEqual( !strcmp( temp->get_name(), "mc_dbms_cursor" ) );
}

void test_cursor()
{
    EntryWatcher monitor("test_cursor");
	mc_dbms_cursor foo;
	mc_dbms_typespec* temp = foo.get_mc_dbms_typespec( );
	AssertEqual( !strcmp( temp->get_name(), "mc_dbms_cursor" ) );
}

void test_database()
{
    EntryWatcher monitor("test_database");
	mc_dbms_database foo;
	mc_dbms_database* transient = mc_dbms_database::get_transient_database();
	
	AssertEqual( transient != NULL );
	
	AssertEqual( transient->is_transient_database() );
		
	transient = mc_dbms_database::of( 0 );
	AssertEqual( transient != NULL );

	mc_dbms_database* persist = mc_dbms_database::get_persistent_database(  );
	AssertEqual( persist != NULL && !persist->is_transient_database() );
		
	mc_dbms_segment* new_seg = foo.create_segment();
	AssertEqual( new_seg != 0 );
		
	foo.create_root( "root1" );
	foo.create_root( "root2" );
	
	mc_dbms_database_root* temp_root = foo.find_root( "root1" );
	AssertEqual( temp_root != 0 );

	AssertEqual( foo.get_n_roots() == 2 );
}

void test_database_root()
{
    EntryWatcher monitor("test_database_root");
	mc_dbms_database_root foo;
	mc_dbms_database db;
	mc_dbms_typespec ts( "I_Attribute", 178 );
	Foo* root_test = new(&db, &ts)Foo;
	root_test->var = 1;
		
	foo.set_value( root_test );
	
	AssertEqual( root_test == foo.get_value( ));
}

void test_config()
{
	/*  This has been implemented, but there are no possible tests to run. */
    EntryWatcher monitor("test_config");
}

void test_segment()
{
    EntryWatcher monitor("test_segment");
    mc_dbms_segment seg1;
    mc_dbms_segment seg2;
    AssertEqual( seg2.get_number() == 1 || (seg1.get_number() + 1 != seg2.get_number() ) );
    	
    AssertEqual( !seg2.is_deleted() )
    	
    AssertEqual( seg2.is_empty() )
	
	AssertEqual( mc_dbms_segment::get_transient_segment() )
}

void test_setup_rel_tests()
{
#ifdef REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test

	/* set up the 1-to-1 relationship */
	foo1.m_var = 1;
	foo2.m_var = 2;
	/* 1-to-many test */
	foo_1_m.m_var = 3;
	foo2_1_m1.m_var = 4;
	foo2_1_m2.m_var = 5;
	foo2_1_m3.m_var = 6;

	/* many-to-many test */
	foo_m_m.m_var = 7;
	foo2_m_m.m_var = 9;

	
	foo1.m_test_1_1 = &foo2;	
	
	/* set up the 1-to-m relationship */
	/* 1-to-many test */
	foo_1_m.m_test_m_1.insert(&foo2_1_m3);
	foo_1_m.m_test_m_1.insert(&foo2_1_m2);
	foo_1_m.m_test_m_1.insert(&foo2_1_m1);
	
	foo2_1_m1.m_test_1_m = &foo_1_m;
	foo2_1_m2.m_test_1_m = &foo_1_m;
	foo2_1_m3.m_test_1_m = &foo_1_m;

	/* many-to-many test */
	foo_m_m.m_test_m_m.insert(&foo2_m_m);
	foo2_m_m.m_test_m_m.insert(&foo_m_m);
#endif
}
void test_rel_1_1()
{
#ifdef REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test
	EntryWatcher monitor("test_rel_1_1");
	
	AssertEqual( (foo1.m_test_1_1.getvalue()->m_var) == 2 );
#endif  
}
void test_rel_m_1()
{
#ifdef REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test
	EntryWatcher monitor("test_rel_m_1");
	
	bool test_passed = true;
	for(int i = 0;i < 3;i++)
	{
		int result = foo_1_m.m_test_m_1.retrieve( i )->m_var;
		if( (result != 6-i ) ) {
			test_passed = false;
		}
	}
	
	AssertEqual( test_passed );
	
	AssertEqual( foo_1_m.m_test_m_1.retrieve_first()->m_var == 6 );

		
	AssertEqual( foo_1_m.m_test_m_1.getvalue().cardinality() == 4 );
#endif
}

void test_rel_1_m()
{
#ifdef REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test
	EntryWatcher monitor("test_rel_1_m");
	AssertEqual( (foo2_1_m1.m_test_1_m.getvalue()->m_var) == 3 && (foo2_1_m2.m_test_1_m.getvalue()->m_var) == 3  
	    && (foo2_1_m3.m_test_1_m.getvalue()->m_var) == 3)	
#endif
}
void test_rel_m_m()
{
#ifdef REMOVE_RELATIONSHIP_TEST_BECAUSE_OF_STATIC_Initialization_Problem_with_this_test
	EntryWatcher monitor("test_rel_m_m");
	bool test_passed = true;
	if( foo_m_m.m_test_m_m.retrieve( 0 )->m_var != 9 )
	{
		test_passed = false;
	}
	
	AssertEqual( test_passed );
	
	AssertEqual( foo_m_m.m_test_m_m.pick()->m_var == 9 );
		
	AssertEqual( foo_m_m.m_test_m_m.getvalue().cardinality() == 1 );
#endif
}

class TestInstanceTracker {
public:
	TestInstanceTracker() { }
	~TestInstanceTracker() { }
	
	void test()
	{
	   	EntryWatcher monitor("test_InstanceTracker");
	   	InstanceTracker::report(true);
	   	
	   	InstanceTracker::purge();
	   	AssertEqual(InstanceTracker::instanceCount() == 0);
	   
	   	const int testSize = 178;
	   	mc_dbms_typespec ts("I_Attribute", testSize);	// Use a real name but make up size
	   	mc_dbms_database db;
	   
	   	// See if purge is working
	   	void* ptr = new(&db, &ts)Foo;
	   	AssertEqual(InstanceTracker::instanceCount() == 1);
	   	AssertEqual(InstanceTracker::instanceCount(&ts) == 1);
	   	InstanceTracker::purge();
	   	AssertEqual(InstanceTracker::instanceCount() == 0);
	   	InstanceTracker::purge();
	   	AssertEqual(InstanceTracker::instanceCount(&ts) == 0);
	   	AssertEqual(InstanceTracker::instanceCount() == 0);
	
	   	// Check the values of the element inserted
	   	ptr = new(&db, &ts)Foo;
		AssertEqual( InstanceTracker::m_instances.size() == 1 );
		InstanceTracker::InstanceContainer::iterator instIter = InstanceTracker::m_instances.begin();
		AssertEqual( InstanceTracker::m_instances.size() == 1 );
		
		
		AssertEqual( ts.get_type_id() == 37);
	   	AssertEqual( instIter->second->m_type == ts.get_type_id());
	   	AssertEqual( instIter->second->m_typeSize*instIter->second->m_numInstances == testSize );
	   	AssertEqual( instIter->second->m_instanceID == 2 );  // The instance ID was bumped once (or it should have been)
	   	AssertEqual( instIter->second->m_block != 0 );	
	   	
	   	// Clear out the database, insert an element, persist it, and try to read it 
	   	// back.
	   	system("rm _test_.db");
	   	InstanceTracker::purge();
	   	void* ptr2 = new(&db, &ts)Foo;
	   	((Foo*)ptr2)->var = 2;
	   	Persistence::persist("_test_.db");
	   	InstanceTracker::purge();
	  	Persistence::restore("_test_.db");
	  	AssertEqual( InstanceTracker::m_instances.size() == 1 );
	  	instIter = InstanceTracker::m_instances.begin();
		AssertEqual( InstanceTracker::m_instances.size() == 1 );
		instIter = InstanceTracker::m_instances.begin();
	  	
	   	AssertEqual( instIter->second->m_typeSize*instIter->second->m_numInstances == testSize );
	   	AssertEqual( instIter->second->m_type == ts.get_type_id() );
	   	AssertEqual( instIter->second->m_instanceID == 3 );  // The instance ID was bumped once (or it should have been)
	   	AssertEqual( *(int*)(instIter->second->m_block) != 2 );	
	}
};


int main(int, char**)
{
    EntryWatcher monitor("test_dbms::main()");
	test_typespec();
	test_Collection();
	test_collection();
	test_Bag();
	test_List();
	test_Set();
	test_Cursor();
	test_cursor();
	test_database();
	test_database_root();
	test_config();
	test_segment();
	TestInstanceTracker testTracker;   testTracker.test();
	test_setup_rel_tests();
	test_rel_1_1();
	test_rel_m_1();
	test_rel_1_m();
	test_rel_m_m();
    std::cout << "Done!" << std::endl;
	return 0;
}

