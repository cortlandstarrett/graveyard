#include "dnary.hh"
#include <ostore/coll/dict_pt.cc>

typedef os_Dictionary<void*,course*> grade_course_dnary;
typedef os_Dictionary<void*,grade*> course_grade_dnary;

os_Dictionary<char*,grade*>* grades = 0;
os_Dictionary<os_char_star_nocopy,course*>* courses = 0;

/* --------------------- student implementation -----------------------*/

int student::add_course(course* c, grade* g)
{
  if(courses->contains(c))
     return 0;

  courses->insert(c);
  if(g) {
    grade_course->insert(g,c);
    course_grade->insert(c,g);
  }
  return 1;
}

void student::remove_course(course* c)
{
  if (courses->contains(c)) {
    courses->remove(c);
    grade* g = course_grade->pick(c);
    grade_course->remove(g,c);
  }
}

grade* student::get_grade_for_course(course* c) const
{
  return course_grade->pick(c);
}

void   student::set_grade_for_course(course* c, grade* g)
{
  grade_course->remove(course_grade->pick(c),c);
  course_grade->remove_value(c);
  grade_course->insert(g,c);
  course_grade->insert(c,g);
}

os_Collection<course*>& student::get_course_with_grade(grade* g) const
{
  os_Collection<course*>& the_courses =
    os_Collection<course*>::create(os_database::get_transient_database());

  os_cursor cur(*grade_course, os_coll_range(os_collection::EQ, g));
  for (course* c = (course*) cur.first();
       cur.more();
       c = (course*) cur.next())
    the_courses.insert(c);

  return the_courses;
}

float student::get_gpa() const
{
  float sum = 0.0;
  os_cursor cur(*course_grade);
  for (grade* g = (grade*) cur.first();
       cur.more();
       g = (grade*) cur.next())
    sum += g->get_value();
  return sum / course_grade->cardinality();
}

student::student(int id, const char* n) : _id(id)
{
  courses = &os_Collection<course*>::create(os_segment::of(this));
  course_grade = &os_Dictionary<void*,grade*>::create(os_segment::of(this),
						     10);
  grade_course = &os_Dictionary<void*,course*>::create(os_segment::of(this),
						      10);
  if(n) {
    int len = ::strlen(n) + 1;
    _name = new(os_segment::of(this), os_typespec::get_char(), len) char[len];
    ::strcpy(_name, n);
  } else
    _name = 0;
}

student::~student()
{
  if (_name)
    delete [] _name;
  os_collection::destroy(*courses);
  os_collection::destroy(*grade_course);
  os_collection::destroy(*course_grade);
}

/* --------------------- grade implementation -----------------------*/

grade::grade(const char* name, float value)
  : _value(value)
{
  int len = ::strlen(name) + 1;
  _name = new(os_segment::of(this), os_typespec::get_char(), len) char[len];
  ::strcpy(_name, name);
}

grade::~grade()
{
  delete [] _name;
}

/* --------------------- course implementation -----------------------*/
course::course(char* name, int num)
  : _num(num)
{
  int len = ::strlen(name) + 1;
  _name = new(os_segment::of(this), os_typespec::get_char(), len) char[len];
  ::strcpy(_name, name);

}

course::~course()
{
  delete [] _name;
}

void force_vfts(void *) {
	force_vfts(new os_Dictionary<char *, grade *>);
	force_vfts(new os_Dictionary<os_char_star_nocopy, course *>);
	force_vfts(new os_Dictionary<void *, course *>);
	force_vfts(new os_Dictionary<void *, grade *>);
	force_vfts(new  os_List<student *>);
	force_vfts(new  os_List<course *>);
	force_vfts(new  os_Set<student *>);
	force_vfts(new  os_Set<course *>);
	force_vfts(new  os_Array<course *>);
	force_vfts(new  os_Array<student *>);
	force_vfts(new  os_Bag<student *>);
	force_vfts(new  os_Bag<course *>);
	force_vfts(new  os_Collection<student *>);
}

