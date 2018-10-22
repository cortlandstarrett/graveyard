#include "dnary.hh"
#include "dbname.h"

extern os_Dictionary<char*,grade*>* grades;

/* Note that the key-type for the courses dictionary is */
/* os_char_star_nocopy - behaves just ike a char*, but dow */
/* allocate a new string on insert. */
/* It simply maintains a pointer to the char* key. */
/* Since for the os_char_star_nocopy key-type the dictionary */
/* does not have to allocate a a string to copy the key, */
/* the insertion operation are relatively faster.        */
extern os_Dictionary<os_char_star_nocopy, course*>* courses;

os_Set<student*> *student_extent = 0;

void load(os_database* db)
{

  grades =
    &os_Dictionary<char*,grade*>::create(db);
  db->create_root("grade_root")->set_value(grades);

  grades->insert((char*)"A", new(db, grade::get_os_typespec()) grade("A", 4.0));
  grades->insert((char*)"A-", new(db, grade::get_os_typespec()) grade("A-", 3.75));
  grades->insert((char*)"B", new(db, grade::get_os_typespec())grade("B", 3.0));
  grades->insert((char*)"B-", new(db, grade::get_os_typespec()) grade("B-", 2.75));
  grades->insert((char*)"C", new(db, grade::get_os_typespec()) grade("C", 2.0));
  grades->insert((char*)"C-", new(db, grade::get_os_typespec()) grade("C-", 1.75));
  grades->insert((char*)"D", new(db, grade::get_os_typespec()) grade("D", 1.0));
  grades->insert((char*)"F", new(db, grade::get_os_typespec()) grade("F", 0.0));

  courses =
    &os_Dictionary<os_char_star_nocopy,course*>::create(db);
  db->create_root("course_root")->set_value(courses);

  course* c = new(db, course::get_os_typespec()) course((char*)"Physics I", 101);
/* Note that for os_char_star_nocopy key-type the dictionary */
/* simply maintains a pointer to the key. */
/* Proper care must be taken to ensure that the key stays around */
/* for at least as long as the dictionary's life-time. */
  courses->insert(c->name(), c);

  c = new(db, course::get_os_typespec())  course((char*)"Physics II", 201);
  courses->insert(c->name(), c);

  c = new(db, course::get_os_typespec())  course((char*)"Basic Algebra", 101);
  courses->insert(c->name(), c);

  c = new(db, course::get_os_typespec())  course((char*)"Algebra", 201);
  courses->insert(c->name(), c);

  c = new(db, course::get_os_typespec())  course((char*)"Data structure", 200);
  courses->insert(c->name(), c);

  c = new(db, course::get_os_typespec())  course((char*)"Operating Systems", 501);
  courses->insert(c->name(), c);

  c = new(db, course::get_os_typespec())  course((char*)"Compilers", 502);
  courses->insert(c->name(), c );

  c = new(db, course::get_os_typespec())  course((char*)"Algorithm", 503);
  courses->insert(c->name(), c);
}

int main()
{
  objectstore::initialize();
  os_collection::initialize();
  OS_ESTABLISH_FAULT_HANDLER

  printf("\ndict: creating database %s\n", example_db_name);

  os_database *db = os_database::create(example_db_name);

  os_typespec *student_extent_type = os_Set<student*>::get_os_typespec();

  printf("dict: beginning a transaction\n");
  OS_BEGIN_TXN(tx1, 0, os_transaction::update)

    printf("dict: loading dictionaries with courses and grades\n");
    load(db);

    student_extent = &os_Set<student*>::create(db);
    db->create_root("student_extent_root")
      ->set_value(student_extent, student_extent_type);

    printf("dict:   creating student:\n");
    printf("\tStudent Name: %s\n\t          id: %d\n", "Bidhan Patnaik", 222);
    student* std1 = new(db,student::get_os_typespec()) student(222, "Bidhan Patnaik");

    printf("\ndict: searching for the course \"Data structure\" in courses dictionary\n");
    course* c1 = courses->pick("Data structure");
    if (c1)
      printf("dict: found course \"%s\"\n", c1->name());

    printf("\ndict: searching for the course \"Operating Systems\" in courses dictionary\n");
    course* c2 = courses->pick("Operating Systems");
    if (c1)
      printf("dict: found course \"%s\"\n", c2->name());

    printf("\ndict: searching for the grade *A* in grades dictionary\n");
    grade* g1 = grades->pick((char*)"A");
    if (g1)
      printf("dict: found grade *A*\n");

    printf("\ndict: searching for the grade *B* in grades dictionary\n");
    grade* g2 = grades->pick((char*)"B");
    if (g2)
      printf("dict: found grade *B*\n");

    printf("\ndict: adding courses \"%s\" and \"%s\" to student\n",c1->name(), c2->name());
    std1->add_course(c1, g1);
    std1->add_course(c2, g2);

    printf("\ndict: searching for grades received\n");
    g1 = std1->get_grade_for_course(c1);
    g2 = std1->get_grade_for_course(c2);
    printf("dict: found:\n");
    printf("\tcourse: %s, grade: %s\n", c1->name(), g1->get_name());
    printf("\tcourse: %s, grade: %s\n", c2->name(), g2->get_name());

    printf("\ndict: ending transaction\n");

  OS_END_TXN(tx1)

  printf("\ndict: closing database %s\n\n", example_db_name);

  db->close();

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

