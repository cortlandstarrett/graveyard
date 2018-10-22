#ifndef _included_external_object_
#define _included_external_object_ 1

#include <mc_dbms/typespec.h>

/**
 * This method provides an iterface from the mcdbms library to the application
 * using the library.  The purpose is to assist with serialization.  Specifically,
 * when mcdbms needs to restore an instance of a type that contains embedded pointers, 
 * it requires the user to have defined that class containing embedded pointers to 
 * inherit from type SerializableObject.  MCDBMS takes advantage of this to serialize these
 * classes.  When it's time to restore them, this function will be called. The
 * external application will have defined this function to instantiate an instance
 * of the specifed type and call the restore() method (defined by the SerializableObject interface)
 * on that instantiated instance. 
 *
 * @see SerializableObject
 *
 * @param typeID The type to restore.
 * @return Returns a pointer to the instantiated and properly restored instance. An
 *         std::exception will be thrown if there is an error.
 */
char* mcdbms_RestoreExternalObject(TrackedType typeID);

#endif
