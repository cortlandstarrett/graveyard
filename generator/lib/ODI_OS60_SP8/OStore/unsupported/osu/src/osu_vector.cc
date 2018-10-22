#include "osu_vector.hh"

//#ifdef WIN32
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#define COPY(FROM,TO,NPTR) ::memmove(TO,FROM,NPTR*sizeof(void*))
#define ZERO(MEM,SZ)       ::memset(MEM,0,SZ)
/*
#else 
#include <stdlib.h>
#define COPY(FROM,TO,NPTR) ::bcopy(FROM,TO,NPTR*sizeof(void*))
#define ZERO(MEM,SZ)       ::bzero(MEM,SZ)
#endif
*/


#define PADSZ 20


inline int osu_vector::in_range(unsigned short p)
{
  return p < currentSize();
}


osu_vector::osu_vector(unsigned short esz)
{
  ALLOC(esz);
  currentSize(0);
}


osu_vector::osu_vector(unsigned short esz, void** ptr)
{
  _elements = (void**) ptr;
  _currentSize = 0;
  _allocatedSize = esz;    
  currentSize(0);
}


osu_vector::osu_vector(const osu_vector& pv)
{
  ALLOC(pv.currentSize());
  COPY(pv.array(),array(),pv.currentSize());
  currentSize(pv.currentSize());
}



osu_vector::~osu_vector()
{
  FREE();
  _allocatedSize = 0;
  _elements = 0;
}



const osu_vector& osu_vector::operator=(const osu_vector& v)
{
  if (&v != this) {
    if (v.currentSize() > allocatedSize()) {
      REALLOC(v.currentSize() - currentSize());
    } else if (v.currentSize() < allocatedSize()) {
      REDUCE(v.currentSize());
    }
	
    COPY(v.array(),array(),v.currentSize());
    currentSize(v.currentSize());
  }
  return *this;
}



void* osu_vector::operator[](unsigned short p)       const
{
  if ( p  < currentSize()) {
    return array()[p];
  } else {
    return 0;
  }
}



void  osu_vector::append(const osu_vector& v)
{
  int first = currentSize();
  REALLOC(v.currentSize());
  COPY( v.array(), array() + first, v.currentSize());
}



void  osu_vector::prepend(const osu_vector& v)
{
  unsigned short last = currentSize();
  REALLOC(v.currentSize());
  move(0, last, v.currentSize());
  COPY(v.array(),array(),v.currentSize());
}



void  osu_vector::prepend(void* v)
{
  int n = currentSize();
  REALLOC();
  move(0,1,n);
  array()[0] = v;
}


void osu_vector::move(unsigned short from, unsigned short to, unsigned short n)
{
  COPY(array()+from, array()+to, n*sizeof(void*));
}



void  osu_vector::placeAfter(unsigned short p, void* v)
{
  if (in_range(p+1)) {
    int n = currentSize();
    int pos = p+1;
    REALLOC();
    move(pos, pos+1, n - pos);
    array()[pos] = v;
  } else if (in_range(p)) {
    append(v);
  } else {
    // p out of range.
  }
}



void  osu_vector::placeAfter(unsigned short p, const osu_vector& v)
{
  if (in_range(p+1)) {
    int sz = currentSize();
    int pos = p+1;
    int n = v.currentSize();
    REALLOC(n);
    move(pos, pos+n, sz - pos);
    COPY(v.array(), array() + pos, n);
  } else if (in_range(p)) {
    append(v);
  } else {
    // p out of range.
  }
}



void  osu_vector::placeBefore(unsigned short p, void* v)
{
  if (in_range(p)) {
    int n = currentSize();
    REALLOC();
    move(p, p+1, n - p);
    array()[p] = v;
  } else {
    // p out of range.
  }
}



void  osu_vector::placeBefore(unsigned short p, const osu_vector& v)
{
  if (in_range(p)) {
    int sz = currentSize();
    int n = v.currentSize();
    REALLOC(n);
    move(p, p + n, sz - p);
    COPY(v.array(), array() + p, n);
  } else {
    // p out of range.
  }
}





void* osu_vector::removeFirst()
{
  void* t = array()[0];
  move(1,0,currentSize());
  currentSize(currentSize() - 1);
  array()[currentSize()] = 0;
  return t;
}



void* osu_vector::removeLast()
{
  void* t = array()[currentSize()-1];
  currentSize(currentSize() - 1);
  array()[currentSize()] = 0;
  return t;
}



void* osu_vector::remove(unsigned short p)
{
  if (in_range(p)) {
    if (p == 0) {
      return removeFirst();
    } else if (p == currentSize() - 1) {
      return removeLast();
    } else {
      void* t = array()[p];
      int pp1 = p+1;
      move(pp1,p, currentSize()-pp1);
      currentSize(currentSize() - 1);
      array()[currentSize()] = 0;
      return t;
    }
  } else {
    // p out of range.
    return 0;
  }
}



int   osu_vector::indexValue(void* t)        const
{
  int size = currentSize();
  for (int i = 0; i < size; i++) {
    if (t == array()[i]) return i;
  }
  return -1;
}

/*
 * Need to reimplement grow...
 */
void* grow(void* array, int nsize)
{
  os_segment* sptr = os_segment::of(array);
  if (sptr == os_segment::get_transient_segment()) {
    return ::realloc((char*)array, nsize*sizeof(void*));
  } else {
    void** _tarray = (void**) array;
#if OS_MAJOR_RELEASE < 6
    void** _narray = new(os_segment::of(array),os_typespec::get_pointer(),nsize) void*[nsize];
#else
    void** _narray = new(os_cluster::with(array),os_typespec::get_pointer(),nsize) void*[nsize];
#endif
    ZERO((void*)_narray,nsize*sizeof(void*));
    COPY((void*)_tarray,_narray,nsize);
    delete _tarray;
    return _narray;
  }
}



void osu_vector::REALLOC()
{
  if (currentSize() == allocatedSize()) {
    if (inlined()) {
      void* stypes[2];
      stypes[0] = array()[0];
      stypes[1] = array()[1];
      ALLOC(PADSZ);
      COPY(stypes,array(),2);
      currentSize(2);
    } else {
      allocatedSize( allocatedSize() + PADSZ);
      _elements =  (void**) grow((void*) _elements, allocatedSize());
    }
  }
  currentSize(currentSize() + 1);
}



void osu_vector::REALLOC(unsigned short size)
{
  if (size == 1) {
    REALLOC();
  } else {
    // Always realloc to _normal.
    if (currentSize()+size > allocatedSize()) {
      if (inlined()) {
	void* stypes[2];
	int csz = currentSize();
	stypes[0] = array()[0];
	stypes[1] = array()[1];
	ALLOC(size+PADSZ+2);
	COPY(stypes,array(),2);
	currentSize(csz);
      } else {
	allocatedSize( allocatedSize() + PADSZ);
	_elements =  (void**) grow((void*) _elements, allocatedSize());
      }
    }
    currentSize( currentSize() + size );
  }
}



void osu_vector::ALLOC(unsigned short size)
{
  if (size > 2) {
    void** array = 0;
    os_segment* sptr = os_segment::of(this);
    if (sptr == os_segment::get_transient_segment()) {
      unsigned short bytes = sizeof(void*)*size;
      array = (void**) ::malloc(bytes);
      ZERO(array, bytes);
    } else {
      array =  (void**) new(sptr, os_typespec::get_pointer(), size) void*[size];
    }

    _elements = array;
    _currentSize = 0;
    _allocatedSize = size;
  } else {
    _elements = 0;
    _allocatedSize = 0;
  }
}


void osu_vector::REDUCE(unsigned short size)
{
  if (size < allocatedSize()) {
    ZERO( array()+size, (allocatedSize() - size)*sizeof(void*));
  }
}


void osu_vector::FREE()
{
  if (!inlined()) {
    os_segment* sptr = os_segment::of(_elements);
    if (sptr == os_segment::get_transient_segment()) {
      ::free((char*)_elements);
    } else {
      delete [] _elements;
    }
  }
}
