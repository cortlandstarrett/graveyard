/*** value_list.hh ***/

#include "error.hh"
#include <string.h>


class entry
{
protected:
	entry *rest;
public:
	// these two are the only one for users
	virtual float get_float_value() const = 0;
	virtual const char *get_string_value() const = 0;

	// internal use -- make private, friends?
	void set_rest(entry* e) {rest = e;}
	entry *get_rest() const {return rest;}

	// dtor 
        virtual ~entry() {delete rest;}
};


class float_entry : public entry
{
private:
	float first;
public:
	float_entry(float f) {first = f; rest = 0;}

	float get_float_value() const {return first;}
	const char *get_string_value() const {
	  error("not a string entry"); 
	  return 0;
	}

        ~float_entry() {}
};


class string_entry : public entry
{
private:
	char *first;
public:
	string_entry(const char *s){
		first = new char[strlen(s)+1](); 
		strcpy(first, s);
		rest = 0;
	}

	float get_float_value() const {
	  error("not a float entry");
	  return 0;
	}

	const char *get_string_value() const {return first;}

        ~string_entry() {delete[] first;}

};
	


	

class value_list 
{
private:
	entry *current;
	entry *first_entry;
	entry *last_entry;

public:
	const entry *first() {current = first_entry; return first_entry;}
	const entry *next()  {
		if (current) current = current->get_rest(); 
		return current;
	}

	void insert(float f) {
	        float_entry *fe = new float_entry(f);
	        if (last_entry) 
		  last_entry->set_rest(fe);
		last_entry = fe;
		if (!first_entry)
		  first_entry = fe;
	}
	void insert(const char *s) {
	        string_entry *se = new string_entry(s);
	        if (last_entry) 
		  last_entry->set_rest(se);
		last_entry = se;
		if (!first_entry)
		  first_entry = se;
	}

	value_list() {current = 0; first_entry = 0; last_entry = 0;}

	// dtor
  ~value_list() {delete first_entry;}
};








