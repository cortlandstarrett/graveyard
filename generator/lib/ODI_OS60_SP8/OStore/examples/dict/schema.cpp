#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>
#include <ostore/manschem.hh>

#include "dnary.hh"

OS_MARK_SCHEMA_TYPE (student);
OS_MARK_SCHEMA_TYPE (course);
OS_MARK_SCHEMA_TYPE (grade);

OS_MARK_DICTIONARY(void*,course*);
OS_MARK_DICTIONARY(os_char_star_nocopy,course*);
OS_MARK_DICTIONARY(void*,grade*);
OS_MARK_DICTIONARY(char*,grade*);

OS_MARK_SCHEMA_TYPE(os_Set<student*>);

