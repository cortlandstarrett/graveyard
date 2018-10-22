#include <iostream.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>

class student;
class grade;
class course;

/* -------------------- class student -- -----------------------*/
class student {
public:
  int get_id() const { return _id; }

  const char* get_name() { return _name; }

  int add_course(course* c, grade* g = 0);
  void remove_course(course* c);

  grade* get_grade_for_course(course*) const;
  void   set_grade_for_course(course* c, grade* g);

  os_Collection<course*>& get_course_with_grade(grade*) const;

  os_Collection<course*>* get_courses(grade*)
    { return courses; }

  float get_gpa() const;

  student(int id, const char* n = 0);
  ~student();

  static os_typespec* get_os_typespec();

protected:
  int _id;
  char* _name;
  os_Collection<course*>* courses;
  os_Dictionary<void*,grade*>* course_grade;
  os_Dictionary<void*,course*>* grade_course;
};

/* ------------------ class grade  -----------------------------*/

class grade {
public:
  const char* get_name() const
    { return _name; }

  const float get_value() const
    { return _value; }

  grade(const char* name, float value);
  ~grade();

  static os_typespec* get_os_typespec();

protected:
  char* _name;
  float _value;
};

class course {
public:
  course(char* name, int num);
  ~course();
  const char* name() const { return _name; }
  const int   number() const { return _num; }

  static os_typespec* get_os_typespec();
protected:
  char* _name;
  int _num;
};

