/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
 * os_int64, os_unsigned_int64
 * 
 * Class definitions for a portable 8-byte signed/unsigned integer.  
 * The classes include basic arithmetic operations, type coercion, and
 * printing members.
 *
 * They are implemented as the native 64-bit type on those platforms which 
 * support it, otherwise they are not yet implemented.
 * 
 */

#ifndef _OSINT64_HH_
#define _OSINT64_HH_

#include <ostore/portypes.hh>
#include <ostore/os_types/paddef.hh>

class os_typespec;

// ostream isn't necessarily a class, don't make assumptions
// class ostream;
#include <iostream.h>

class _OS_DLLIMPORT(_OS_LOW) os_int64 {
private:
  /* make sure the class is 8 byte aligned */
  OS_ALIGN_CLASS(8);
#if defined (_OS_INT64_NATIVE) 
  os_platform_int64 data;
#else
/* Note - there is currently no implementation for platforms 
   without a native 64 bit integer. */
#endif

public:
  /* Allow persistent allocation */
  static os_typespec* get_os_typespec();

  /* constructors/coercion functions */
  os_int64(os_platform_uint64 num) : data(num) { }
#if !defined (_OS_64BIT_NATIVE)
  os_int64(long num) : data(num) { }
#endif
#if defined (_OS_INT64_NATIVE) 
  os_int64(os_platform_int64 num) : data(num) { }
  /* This constructor will be defined, but differently, 
    for platforms without a native 64 bit integer. */
  os_int64(os_unsigned_int32 num1, os_unsigned_int32 num2) :
    data((os_platform_int64)num1 << 32 | num2) { }
#endif
  os_int64(os_int32 num) : data(num) { }
  os_int64(os_unsigned_int32 num) : data(num) { }
  os_int64(const os_int64 &num) : data(num.data) { }
  os_int64() { data = 0; }

#if defined (_OS_INT64_NATIVE) 
  /* On platforms which support a native 64-bit integer define a type conversion. */
  operator os_platform_int64() const { return data; } 
#endif

  /* Operators - 
     Operators fall into several categories depending on the platform type.
     (i.e. whether the platform defines a native 64-bit integer or not)
     On platforms which do NOT have a native int64 we provide a full complement
     of operators.  On platforms which DO have a native type, we provide a 
     conversion to the native type.  On such platforms providing a full 
     complement of operators would introduce type conversion ambiguity.  
     Instead we rely on the native type conversion and the pre-defined operators.
  */

  /* Operators that are defined the same way on both types of platforms. */
  os_boolean operator!() const { return !data; }
  os_int64 operator~() const { return ~data; }
  os_int64 operator++ (int) { 
    os_int64 old_value = *this; ++(*this); return old_value; }
  os_int64 operator-- (int) { 
    os_int64 old_value = *this; --(*this); return old_value; }
  os_int64 operator>>(os_int32 num) const { return (data >> num); }
  os_int64 operator<<(os_int32 num) const { return (data << num); }
  os_int64& operator<<=(os_int32 num) {
    *this = operator<<(num);return *this; }
  os_int64& operator>>=(os_int32 num) {
    *this = operator>>(num);return *this; }

  friend ostream & operator<<(ostream& os, os_int64 num);

  /* Operators that are defined differently depending on platform type */
#if defined (_OS_INT64_NATIVE) 
  /* These operator definitions use the pre-defined operators on the 
    native-type data member */
  os_int64& operator++() { data = data + 1; return *this; }
  os_int64& operator--() { data = data - 1; return *this; }
  os_int64& operator+=(const os_int64& num) { data = data + num.data; return *this; }
  os_int64& operator-=(const os_int64& num) { data = data - num.data; return *this; }
  os_int64& operator*=(const os_int64& num) { data = data * num.data; return *this; }
  os_int64& operator/=(const os_int64& num) { data = data / num.data; return *this; }
  os_int64& operator%=(const os_int64 num) { data = data % num.data; return *this; }
  os_int64& operator&=(const os_int64 num) { data = data & num.data; return *this; }
  os_int64& operator|=(const os_int64 num) { data = data | num.data; return *this; }
  os_int64& operator^=(const os_int64 num) { data = data ^ num.data; return *this; }
#else
  /* These operator definitions do not rely on a native type */
  os_int64& operator++() { *this = *this + 1; return *this; }
  os_int64& operator--() { *this = *this - 1; return *this; }
  os_int64& operator+=(const os_int64& num) { *this = *this + num; return *this; }
  os_int64& operator-=(const os_int64& num) { *this = *this - num; return *this; }
  os_int64& operator*=(const os_int64& num) { *this = *this * num; return *this; }
  os_int64& operator/=(const os_int64& num) { *this = *this / num; return *this; }
  os_int64& operator%=(const os_int64 num) { *this = *this % num; return *this; }
  os_int64& operator&=(const os_int64 num) { *this = *this & num; return *this; }
  os_int64& operator|=(const os_int64 num) { *this = *this | num; return *this; }
  os_int64& operator^=(const os_int64 num) { *this = *this ^ num; return *this; }
#endif

  /* Operators that are only defined on platforms without a native int64. */
#if !defined (_OS_INT64_NATIVE) 
  const os_int64& operator+() const { return *this; }
  os_int64 operator-() const { return -data; }

  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator+(const os_int64& num1, 
				     const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator-(const os_int64& num1,
				     const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator*(const os_int64& num1, 
				     const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator/(const os_int64& num1, 
				     const os_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator%(const os_int64& num1, 
				     const os_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator&(const os_int64& num1, 
				     const os_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator^(const os_int64& num1, 
				     const os_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_int64 operator|(const os_int64& num1, 
				     const os_int64 & num2);

  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator<(const os_int64& num1,
			  const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator>(const os_int64& num1,
			  const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator<=(const os_int64& num1,
			   const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator>=(const os_int64& num1,
			   const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator==(const os_int64& num1,
			   const os_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator!=(const os_int64& num1,
			   const os_int64& num2);
#endif

  os_unsigned_int32 get_low() const { return (os_unsigned_int32) (data & 0xffffffff); }
  os_unsigned_int32 get_high() const { return (os_unsigned_int32) (data >> 32); }
  void sprint(char *result, os_int32 base = 10) const;
};

#if !defined (_OS_INT64_NATIVE) 
inline os_int64
operator+(const os_int64& num1, const os_int64& num2) {
  return (num1.data + num2.data); 
}

inline os_int64
operator-(const os_int64& num1, const os_int64& num2) {
  return (num1.data - num2.data); 
}

inline os_int64
operator*(const os_int64& num1, const os_int64& num2) {
  return (num1.data * num2.data); 
}

inline os_int64
operator/(const os_int64& num1, const os_int64& num2) {
  return (num1.data / num2.data); 
}

inline os_int64
operator%(const os_int64& num1, const os_int64& num2) {
  return (num1.data % num2.data); 
}

inline os_int64
operator&(const os_int64& num1, const os_int64& num2) {
  return (num1.data & num2.data); 
}

inline os_int64
operator^(const os_int64& num1, const os_int64& num2) {
  return (num1.data ^ num2.data); 
}

inline os_int64
operator|(const os_int64& num1, const os_int64& num2) {
  return (num1.data | num2.data); 
}

inline os_boolean
operator<(const os_int64& num1, const os_int64& num2) {
  return (num1.data < num2.data); 
}

inline os_boolean
operator>(const os_int64& num1, const os_int64& num2) {
  return (num1.data > num2.data); 
}

inline os_boolean
operator==(const os_int64& num1, const os_int64& num2) {
  return (num1.data == num2.data);
}

inline os_boolean
operator!=(const os_int64& num1, const os_int64& num2) {
  return !(num1.data == num2.data);
}

inline os_boolean
operator<=(const os_int64& num1, const os_int64& num2) {
  return (num1.data <= num2.data);
}

inline os_boolean
operator>=(const os_int64& num1, const os_int64& num2) {
  return (num1.data >= num2.data);
}
#endif


class _OS_DLLIMPORT(_OS_LOW) os_unsigned_int64 {
private:
#if defined (_OS_INT64_NATIVE) 
  os_platform_uint64 data;
#else
/* Note - there is currently no implementation for platforms 
   without a native 64 bit integer. */
#endif

public:
  /* make sure the class is 8 byte aligned */
  OS_ALIGN_CLASS(8);

  /* Allow persistent allocation */
  static os_typespec* get_os_typespec();

  /* constructors/coercion functions */
  os_unsigned_int64(os_platform_uint64 num) : data(num) { }
#if !defined (_OS_64BIT_NATIVE)
  os_unsigned_int64(unsigned long num) : data(num) { }
#endif
#if defined (_OS_INT64_NATIVE) 
  /* A conversion from a signed type is required in order to use literal constants,
    which C++ defines as const int.  This is the best we can do to exclude negative values.*/
  os_unsigned_int64(os_platform_int64 num) {num > 0 ? (data = num) : (data = 0); }
  /* This constructor will be defined, but differently, 
    for platforms without a native 64 bit integer. */
  os_unsigned_int64(os_unsigned_int32 num1, os_unsigned_int32 num2) :
    data((os_platform_uint64)num1 << 32 | num2) { }
#endif
  os_unsigned_int64(os_int32 num) {num > 0 ? (data = num) : (data = 0);}
  os_unsigned_int64(os_unsigned_int32 num) : data(num) { }
  os_unsigned_int64(const os_unsigned_int64 &num) : data(num.data) { }
  os_unsigned_int64() { data = 0; }

#if defined (_OS_INT64_NATIVE) 
  /* On platforms which support a native 64-bit integer define a type conversion. */
  operator os_platform_uint64() const { return data; } 
#endif

  /* Operators - 
     Operators fall into several categories depending on the platform type.
     (i.e. whether the platform defines a native 64-bit integer or not)
     On platforms which do NOT have a native int64 we provide a full complement
     of operators.  On platforms which DO have a native type, we provide a 
     conversion to the native type.  On such platforms providing a full 
     complement of operators would introduce type conversion ambiguity.  
     Instead we rely on the native type conversion and the pre-defined operators.
  */

  /* Operators that are defined the same way on both types of platforms. */
  os_boolean operator!() const { return !data; }
  os_unsigned_int64 operator~() const { return ~data; }
  os_unsigned_int64 operator++ (int) { 
    os_unsigned_int64 old_value = *this; ++(*this); return old_value; }
  os_unsigned_int64 operator-- (int) { 
    os_unsigned_int64 old_value = *this; --(*this); return old_value; }
  os_unsigned_int64 operator>>(os_int32 num) const { return (data >> num); }
  os_unsigned_int64 operator<<(os_int32 num) const { return (data << num); }
  os_unsigned_int64& operator<<=(os_int32 num) {
    *this = operator<<(num);return *this; }
  os_unsigned_int64& operator>>=(os_int32 num) {
    *this = operator>>(num);return *this; }

  friend ostream & operator<<(ostream& os, os_unsigned_int64 num);

  /* Operators that are defined differently depending on platform type */
#if defined (_OS_INT64_NATIVE) 
  /* These operator definitions use the pre-defined operators on the 
    native-type data member */
  os_unsigned_int64& operator++() { data = data + 1; return *this; }
  os_unsigned_int64& operator--() { data = data - 1; return *this; }
  os_unsigned_int64& operator+=(const os_unsigned_int64& num) { 
    data = data + num.data; return *this; }
  os_unsigned_int64& operator-=(const os_unsigned_int64& num) { 
    data = data - num.data; return *this; }
  os_unsigned_int64& operator*=(const os_unsigned_int64& num) {
    data = data * num.data; return *this; }
  os_unsigned_int64& operator/=(const os_unsigned_int64& num) {
    data = data / num.data; return *this; }
  os_unsigned_int64& operator%=(const os_unsigned_int64 num) { data = data % num.data; return *this; }
  os_unsigned_int64& operator&=(const os_unsigned_int64 num) { data = data & num.data; return *this; }
  os_unsigned_int64& operator|=(const os_unsigned_int64 num) { data = data | num.data; return *this; }
  os_unsigned_int64& operator^=(const os_unsigned_int64 num) { data = data ^ num.data; return *this; }
#else
  /* These operator definitions do not rely a native type */
  os_unsigned_int64& operator++() { *this = *this + 1; return *this; }
  os_unsigned_int64& operator--() { *this = *this - 1; return *this; }
  os_unsigned_int64& operator+=(const os_unsigned_int64& num) { 
    *this = *this + num; return *this; }
  os_unsigned_int64& operator-=(const os_unsigned_int64& num) { 
    *this = *this - num; return *this; }
  os_unsigned_int64& operator%=(const os_unsigned_int64 num) { *this = *this % num; return *this; }
  os_unsigned_int64& operator&=(const os_unsigned_int64 num) { *this = *this & num; return *this; }
  os_unsigned_int64& operator|=(const os_unsigned_int64 num) { *this = *this | num; return *this; }
  os_unsigned_int64& operator^=(const os_unsigned_int64 num) { *this = *this ^ num; return *this; }
  os_unsigned_int64& operator*=(const os_unsigned_int64& num) {
    *this = *this*num; return *this; }
  os_unsigned_int64& operator/=(const os_unsigned_int64& num) {
    *this = *this/num; return *this; }
#endif

  /* Operators that are only defined on platforms without a native int64. */
#if !defined (_OS_INT64_NATIVE) 
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator+(const os_unsigned_int64& num1, 
				     const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator-(const os_unsigned_int64& num1,
				     const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator*(const os_unsigned_int64& num1, 
				     const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator/(const os_unsigned_int64& num1, 
				     const os_unsigned_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator%(const os_unsigned_int64& num1, 
				     const os_unsigned_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator&(const os_unsigned_int64& num1, 
				     const os_unsigned_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator^(const os_unsigned_int64& num1, 
				     const os_unsigned_int64 & num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_unsigned_int64 operator|(const os_unsigned_int64& num1, 
				     const os_unsigned_int64 & num2);

  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator<(const os_unsigned_int64& num1,
			  const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator>(const os_unsigned_int64& num1,
			  const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator<=(const os_unsigned_int64& num1,
			   const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator>=(const os_unsigned_int64& num1,
			   const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator==(const os_unsigned_int64& num1,
			   const os_unsigned_int64& num2);
  _OS_DLLIMPORT(_OS_LOW) friend os_boolean operator!=(const os_unsigned_int64& num1,
			   const os_unsigned_int64& num2);
#endif

  os_unsigned_int32 get_low() const { return (os_unsigned_int32) (data & 0xffffffff); }
  os_unsigned_int32 get_high() const { return (os_unsigned_int32) (data >> 32); }
  void sprint(char *result, os_int32 base = 10) const;
};


#if !defined (_OS_INT64_NATIVE) 
inline os_unsigned_int64
operator+(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data + num2.data); 
}

inline os_unsigned_int64
operator-(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data - num2.data); 
}

inline os_unsigned_int64
operator*(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data * num2.data); 
}

inline os_unsigned_int64
operator/(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data / num2.data); 
}

inline os_unsigned_int64
operator%(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data % num2.data); 
}

inline os_unsigned_int64
operator&(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data & num2.data); 
}

inline os_unsigned_int64
operator^(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data ^ num2.data); 
}

inline os_unsigned_int64
operator|(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data | num2.data); 
}

inline os_boolean
operator<(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data < num2.data); 
}

inline os_boolean
operator>(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data > num2.data); 
}

#if !defined (_OS_INT64_NATIVE) 
inline os_boolean
operator==(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data == num2.data);
}

inline os_boolean
operator!=(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return !(num1.data == num2.data);
}
#endif

inline os_boolean
operator<=(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data <= num2.data);
}

inline os_boolean
operator>=(const os_unsigned_int64& num1, const os_unsigned_int64& num2) {
  return (num1.data >= num2.data);
}
#endif

#endif /* _OSINT64_HH_ */
