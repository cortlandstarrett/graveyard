/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// Changes and additions Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.
// Patent Pending.

#ifndef __OSCSTRING_H__
#define __OSCSTRING_H__

#include <afx.h>

/////////////////////////////////////////////////////////////////////////////
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/coll/indexkey.hh>

class os_CString;                        // growable string type

/////////////////////////////////////////////////////////////////////////////
// Other includes from standard "C" runtimes

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _OSMFCDLL
__declspec(dllexport)
#endif
int _ODI_lstrlenA(LPCSTR lpString);

#ifdef _OSMFCDLL
__declspec(dllexport)
#endif
int _ODI_lstrlenW(LPCWSTR lpString);

#ifdef UNICODE
#define _ODI_lstrlen  _ODI_lstrlenW
#else
#define _ODI_lstrlen  _ODI_lstrlenA
#endif // !UNICODE

// _OSMFCDLL is used to export os_CString symbols and thus should be
// only used when creating O4PMFC DLL.
#ifdef _OSMFCDLL
struct __declspec(dllexport) os_CStringData
#else
struct os_CStringData
#endif
{
	long nRefs;     // reference count
	int nDataLength;
	int nAllocLength;
	// TCHAR data[nAllocLength]

	TCHAR* data()
		{ return (TCHAR*)(this+1); }
};

#ifdef _OSMFCDLL
class __declspec(dllexport) os_CString
#else
class os_CString
#endif
{
public:
// Constructors
	os_CString();
	os_CString(const os_CString& stringSrc);
	os_CString(TCHAR ch, int nRepeat = 1);
	os_CString(LPCSTR lpsz);
	os_CString(LPCWSTR lpsz);
	os_CString(LPCTSTR lpch, int nLength);
	os_CString(const unsigned char* psz);

// Attributes & Operations
	// as an array of characters
	int GetLength() const;
	BOOL IsEmpty() const;
	void Empty();                       // free up the data

	TCHAR GetAt(int nIndex) const;      // 0 based
	TCHAR operator[](int nIndex) const; // same as GetAt
	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;           // as a C string

	// overloaded assignment
	const os_CString& operator=(const os_CString& stringSrc);
	const os_CString& operator=(TCHAR ch);
// Assign CString object to os_CString
	const os_CString& operator=(const CString& stringSrc);
#ifdef _UNICODE
	const os_CString& operator=(char ch);
#endif
	const os_CString& operator=(LPCSTR lpsz);
	const os_CString& operator=(LPCWSTR lpsz);
	const os_CString& operator=(const unsigned char* psz);

	// string concatenation
	const os_CString& operator+=(const os_CString& string);
	const os_CString& operator+=(TCHAR ch);
#ifdef _UNICODE
	const os_CString& operator+=(char ch);
#endif
	const os_CString& operator+=(LPCTSTR lpsz);

	friend os_CString AFXAPI operator+(const os_CString& string1,
			const os_CString& string2);
	friend os_CString AFXAPI operator+(const os_CString& string, TCHAR ch);
	friend os_CString AFXAPI operator+(TCHAR ch, const os_CString& string);
#ifdef _UNICODE
	friend os_CString AFXAPI operator+(const os_CString& string, char ch);
	friend os_CString AFXAPI operator+(char ch, const os_CString& string);
#endif
	friend os_CString AFXAPI operator+(const os_CString& string, LPCTSTR lpsz);
	friend os_CString AFXAPI operator+(LPCTSTR lpsz, const os_CString& string);

	// string comparison
	int Compare(LPCTSTR lpsz) const;         // straight character
	int CompareNoCase(LPCTSTR lpsz) const;   // ignore case
	int Collate(LPCTSTR lpsz) const;         // NLS aware

	// simple sub-string extraction
	os_CString Mid(int nFirst, int nCount) const;
	os_CString Mid(int nFirst) const;
	os_CString Left(int nCount) const;
	os_CString Right(int nCount) const;

	os_CString SpanIncluding(LPCTSTR lpszCharSet) const;
	os_CString SpanExcluding(LPCTSTR lpszCharSet) const;

	// upper/lower/reverse conversion
	void MakeUpper();
	void MakeLower();
	void MakeReverse();

	// trimming whitespace (either side)
	void TrimRight();
	void TrimLeft();

	// searching (return starting index, or -1 if not found)
	// look for a single character match
	int Find(TCHAR ch) const;               // like "C" strchr
	int ReverseFind(TCHAR ch) const;
	int FindOneOf(LPCTSTR lpszCharSet) const;

	// look for a specific sub-string
	int Find(LPCTSTR lpszSub) const;        // like "C" strstr

	// simple formatting
	void AFX_CDECL Format(LPCTSTR lpszFormat, ...);
	void AFX_CDECL Format(UINT nFormatID, ...);

#ifndef _MAC
	// formatting for localization (uses FormatMessage API)
	void AFX_CDECL FormatMessage(LPCTSTR lpszFormat, ...);
	void AFX_CDECL FormatMessage(UINT nFormatID, ...);
#endif

	// input and output
#ifdef _DEBUG
	friend CDumpContext& AFXAPI operator<<(CDumpContext& dc,
				const os_CString& string);
#endif
	friend CArchive& AFXAPI operator<<(CArchive& ar, const os_CString& string);
	friend CArchive& AFXAPI operator>>(CArchive& ar, os_CString& string);

	// Windows support
	BOOL LoadString(UINT nID);          // load from string resource
										// 255 chars max
#ifndef _UNICODE
	// ANSI <-> OEM support (convert string in place)
	void AnsiToOem();
	void OemToAnsi();
#endif

#ifndef _AFX_NO_BSTR_SUPPORT
	// OLE BSTR support (use for OLE automation)
	BSTR AllocSysString() const;
	BSTR SetSysString(BSTR* pbstr) const;
#endif

	// Access to string implementation buffer as "C" character array
	LPTSTR GetBuffer(int nMinBufLength);
	void ReleaseBuffer(int nNewLength = -1);
	LPTSTR GetBufferSetLength(int nNewLength);
	void FreeExtra();

	// Use LockBuffer/UnlockBuffer to turn refcounting off
	LPTSTR LockBuffer();
	void UnlockBuffer();

// Implementation
public:
	~os_CString();
	int GetAllocLength() const;

//Objectstore related declarations.
	void static os_register();
	unsigned hash() const;
	static os_typespec *get_os_typespec();
        static void os_CString::mash(unsigned& hash, unsigned chars);
	static unsigned int string_hash(const void *x);
	static int string_rank(const void *arg1, const void *arg2);
//Cast operatore to cast os_CString object to CString
	operator CString& () const;
	//Copy CString Object to os_CString
	void CopyCString(const CString &stringSrc);
	//Copy os_CString object to CString
	void CopyToCString(CString &stringDest);
// End ObjectStore Related Declarations

protected:
	LPTSTR m_pchData;   // pointer to ref counted string data

	// implementation helpers
	os_CStringData* GetData() const;
	void AllocCopy(os_CString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void AllocBuffer(int nLen);
	void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);
	void ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data, int nSrc2Len, LPCTSTR lpszSrc2Data);
	void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData);
	void FormatV(LPCTSTR lpszFormat, va_list argList);
	void CopyBeforeWrite();
	void AllocBeforeWrite(int nLen);
	void Release();
	static void PASCAL Release(os_CStringData* pData);
	static int PASCAL SafeStrlen(LPCTSTR lpsz);
private:
};

// Globals
extern AFX_DATA TCHAR afxChNil;

/////////////////////////////////////////////////////////////////////////////
// inline function declarations
#include "oscstring.inl"
#endif // __OSCSTRING_H__
