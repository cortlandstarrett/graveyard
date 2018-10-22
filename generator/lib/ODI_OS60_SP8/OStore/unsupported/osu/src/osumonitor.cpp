#include "OSUMonitor.h"
#include "osu_monitor.hh"

JNIEXPORT void JNICALL
Java_com_odi_consulting_Monitor__1initialize(JNIEnv *, jclass)
{
  osu_monitor::initialize();
}

JNIEXPORT void JNICALL
Java_com_odi_consulting_Monitor__1initializeAll(JNIEnv *, jclass)
{
  osu_monitor::initialize_all();
}


static void 
throwByName(JNIEnv *env, const char *name, const char *msg)
{
    jclass cls = env->FindClass(name);

    if (cls != 0) /* Otherwise an exception has already been thrown */
        env->ThrowNew(cls, msg);

    /* It's a good practice to clean up the local references. */
    env->DeleteLocalRef(cls);
}


/* Translates a Java string to a C string using the String.getBytes 
 * method, which uses default local encoding.
 */
static char *
getJavaString(JNIEnv *env, jstring jstr)
{
    jbyteArray hab = 0;
    jthrowable exc;
    char *result = 0;

    jclass    classString = env->FindClass("java/lang/String");
    jmethodID String_getBytes_ID = 
      env->GetMethodID(classString, "getBytes", "()[B");
    hab = (jbyteArray) env->CallObjectMethod(jstr, String_getBytes_ID);
    exc = env->ExceptionOccurred();
    if (!exc) {
        jint len = env->GetArrayLength(hab);
        result =  new char[len+1];
	if (result == 0) {
	    throwByName(env, "java/lang/OutOfMemoryError", 0);
	    env->DeleteLocalRef(hab);
	    return 0;
	}
	env->GetByteArrayRegion(hab, 0, len, (jbyte *)result);
	result[len] = 0; /* NULL-terminate */
    } else {
        env->DeleteLocalRef(exc);
    }
    env->DeleteLocalRef(hab);
    return result;
}


JNIEXPORT void JNICALL Java_com_odi_consulting_Monitor__1log
  (JNIEnv *env, jclass, jstring str) 
{
  char* s = getJavaString(env,str);
  osu_monitor::log(s);
  delete [] s;
}

