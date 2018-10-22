#ifndef osu_vector_hh
#define osu_vector_hh
#include <ostore/ostore.hh>

class osu_vec_rep {
  protected:
    unsigned short _allocatedSize;
    unsigned short _currentSize;
    void**       _elements;
  protected:
    //
    // currentSize should always be set after allocatedSize.
    //
    int  inlined() const { return (_allocatedSize < 3); }
    void currentSize(unsigned short size) {
	_currentSize = size;
    }
    unsigned short currentSize() const  { return _currentSize; }
    void allocatedSize(unsigned short size) {
	_allocatedSize = size;
    }
    unsigned short allocatedSize() const { return _allocatedSize; }
};

class osu_vector : private osu_vec_rep {
  private:
    void** array() const { return (inlined()) ? (void**) &_elements
			                      : (void**) _elements; }

  public:
    osu_vector(unsigned short esz);
    osu_vector(unsigned short esz, void **ptr);    
    osu_vector(const osu_vector& pv);
    ~osu_vector();
    
    const osu_vector& operator=(const osu_vector& v);
    void* operator[](unsigned short n)       const;
    void  append(const osu_vector& v);
    void  append(void* v) {
	unsigned short p = currentSize();
	REALLOC();
	array()[p] = v;
    }
    void  prepend(const osu_vector& v);
    void  prepend(void* v);
    void  placeAfter(unsigned short p, void* v);
    void  placeAfter(unsigned short p, const osu_vector& v);
    void  placeBefore(unsigned short p, void* v);
    void  placeBefore(unsigned short p, const osu_vector& v);
    void* removeFirst();
    void* removeLast();
    void* remove(unsigned short p);
    int   size() const { return currentSize(); }
    void  cleanOut() {
	currentSize(0);
    }
    int   indexValue(void*)        const;  // return -1 if not found.

  public:
    //
    // These functions were added to make osu_vector interface consistent
    // with os_Collection(s) interface for a few key routines.
    //
    void  insert(void* v)
    {
	append(v);
    }
    unsigned short   cardinality() const 
    {
	return currentSize();
    }
    int   contains(void* t) const
    {
	int ndx = indexValue(t);
	return  (ndx == -1) ? 0 : 1;
    }
    void  remove(void* t) {
	int  ndx = indexValue(t);
	if (ndx > -1) remove(ndx);
    }

    static os_typespec *get_os_typespec();
    
  protected:
    int  in_range(unsigned short);
  private:
    void move(unsigned short from, unsigned short to, unsigned short n);
    void REDUCE(unsigned short  to);
    void REALLOC();	      	      // One more.
    void REALLOC(unsigned short more);  // Reallocate to handle more elements.
    void ALLOC(unsigned short size);
    void FREE();
};


#endif







