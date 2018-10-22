/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _MSGEXCPT_H
#define _MSGEXCPT_H

#if defined(_OS_CPP_EXCEPTIONS)
class os_Exception
   {
public:
   os_Exception(char* _name,char* _msg,os_Exception* _parent)
      : name(_name), msg(_msg), parent(_parent) {}
   virtual ~os_Exception() 
     {
       /* TBD: The following delete is exposing some kind of
               heap corruption on NT during static destruction.
	       Later we need to fix this. --rick@odi.com */
       // delete[] msg;
     }
   char* get_name() {return name;}
   char* get_msg() {return msg;}
   void  set_msg(char* m){msg = m;}
   /* every derived class must reimplement toss in order
      for the exception to be typed correctly */
   virtual void toss()
      {
      throw *this;
      }
private:
   char* name;
   char* msg;
   os_Exception* parent;
   };
#else
class os_Exception : public objectstore_exception
   {
public:
   os_Exception(char* _name,char* _msg,os_Exception* _parent) :
      objectstore_exception(_name,_msg,_parent)
      {}
   char* get_name() {return "unknown";}
   char* get_msg() {return "unknown";}
   void  set_msg(char* m){/* ignore message */}
   virtual void  toss()
      {
      this->signal("");
      }
   };
#endif

#define OS_DEFINE_MESSAGE_EXCEPTION(name,message,parent) \
   DEFINE_EXCEPTION(tix_##name,message,parent); \
   os_Exception cpp_##name(#name,message,parent); \
   os_Message_exception name(cpp_##name,tix_##name);

class os_Message_exception
   {
public:
   os_Message_exception(os_Exception& _cpp,objectstore_exception& _tix);
   ~os_Message_exception();
   void toss();
   void signal(char* msg);
   void set_msg(char* msg);
private:
   os_Exception& cpp;
   objectstore_exception& tix;
   };

#endif
