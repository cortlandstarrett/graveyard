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

//#include "..\..\include\external\ostore\oscstring.h"
#include <ostore\oscstring.h>

#include <afxtempl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const unsigned HASH_SHIFT = 5;

/////////////////////////////////////////////////////////////////////////////
// static class data, special inlines

// afxChNil is left for backward compatibility
AFX_DATADEF TCHAR afxChNil = '\0';

//////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

os_CString::os_CString() :
	m_pchData(NULL)
{
	AllocBuffer(0);
}

os_CString::os_CString(const os_CString& stringSrc) :
	m_pchData (NULL)
{
	ASSERT(stringSrc.GetData()->nRefs != 0);
	if (stringSrc.GetData()->nRefs >= 0 && 
		os_database::of(this) == os_database::of(stringSrc)) {
		ASSERT(stringSrc.GetData() != 0);	/* os_CString is different from MFC CString */
		m_pchData = stringSrc.m_pchData;
		InterlockedIncrement(&GetData()->nRefs);
	}
	else {
		*this = stringSrc.m_pchData;
	}
}

// Implementation of this is based on persistent allocation and thus 
// different from CString::AllocBuffer
#ifdef _DEBUG
#undef new	// kill off the MFC DEBUG new.
#endif

void os_CString::AllocBuffer(int nLen)
// always allocate one extra character for '\0' termination
// assumes [optimistically] that data length will equal allocation length
{
	ASSERT(nLen >= 0);
	ASSERT(nLen <= INT_MAX-1);    // max size (enough room for 1 extra)

	int length = sizeof(os_CStringData) + (nLen+1) * sizeof(TCHAR);
	os_CStringData* pData =
	    (os_CStringData*)new(os_cluster::with(this),
				 os_typespec::get_char(), length) BYTE[length];
	pData->nRefs = 1;
	pData->data()[nLen] = '\0';
	pData->nDataLength = nLen;
	pData->nAllocLength = nLen;
	m_pchData = pData->data();
}

void os_CString::Release()
{
	if (m_pchData) {
		ASSERT(GetData()->nRefs != 0);
		if (InterlockedDecrement(&GetData()->nRefs) <= 0) {
			delete[] (BYTE*)GetData();
		}
		m_pchData = NULL;
	}
}

void PASCAL os_CString::Release(os_CStringData* pData)
{
	if (pData) {
		ASSERT(pData->nRefs != 0);
		if (InterlockedDecrement(&pData->nRefs) <= 0)
			delete[] (BYTE*)pData;
	}
}

void os_CString::Empty()
{
	Release();
	AllocBuffer(0);
	ASSERT(GetData()->nDataLength == 0);
}

void os_CString::CopyBeforeWrite()
{
	if (GetData()->nRefs > 1) {
		os_CStringData* pData = GetData();
		Release();
		AllocBuffer(pData->nDataLength);
		memcpy(m_pchData, pData->data(), (pData->nDataLength+1)*sizeof(TCHAR));
	}
	ASSERT(GetData()->nRefs <= 1);
}

void os_CString::AllocBeforeWrite(int nLen)
{
	if (!GetData() || GetData()->nRefs > 1 || nLen > GetData()->nAllocLength) {
		Release();
		AllocBuffer(nLen);
	}
	ASSERT(GetData()->nRefs <= 1);
}

os_CString::~os_CString()
//  free any attached data
{
	Release ();
}

//////////////////////////////////////////////////////////////////////////////
// Helpers for the rest of the implementation

void os_CString::AllocCopy(os_CString& dest, int nCopyLen, int nCopyIndex,
	 int nExtraLen) const
{
	// will clone the data attached to this string
	// allocating 'nExtraLen' characters
	// Places results in uninitialized string 'dest'
	// Will copy the part or all of original data to start of new string

	const int nNewLen = nCopyLen + nExtraLen;
	dest.AllocBuffer(nNewLen);
	if (nNewLen != 0) {
		memcpy(dest.m_pchData, m_pchData+nCopyIndex, nCopyLen*sizeof(TCHAR));
	}
}

//////////////////////////////////////////////////////////////////////////////
// More sophisticated construction

os_CString::os_CString(LPCTSTR lpsz) :
	m_pchData (NULL)
{
	if (lpsz != NULL && HIWORD(lpsz) == NULL)
	{
		UINT nID = LOWORD((DWORD)lpsz);
		if (!LoadString(nID))
			TRACE1("Warning: implicit LoadString(%u) failed\n", nID);
	}
	else {
		int nLen = SafeStrlen(lpsz);
		AllocBuffer(nLen);
		if (nLen != 0) {
			memcpy(m_pchData, lpsz, nLen*sizeof(TCHAR));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Special conversion constructors

#ifdef _UNICODE
os_CString::os_CString(LPCSTR lpsz) :
	m_pchData(NULL)
{
	const int nSrcLen = lpsz != NULL ? _ODI_lstrlenA(lpsz) : 0;
	AllocBuffer(nSrcLen);
	if (nSrcLen != 0)
	{
		_mbstowcsz(m_pchData, lpsz, nSrcLen+1);
		ReleaseBuffer();
	}
}
#else //_UNICODE
os_CString::os_CString(LPCWSTR lpsz) :
	m_pchData(NULL)
{
	const int nSrcLen = lpsz != NULL ? _ODI_lstrlenW(lpsz) : 0;
	AllocBuffer(nSrcLen*2);
	if (nSrcLen != 0)
	{
		_wcstombsz(m_pchData, lpsz, (nSrcLen*2)+1);
		ReleaseBuffer();
	}
}
#endif //!_UNICODE

//////////////////////////////////////////////////////////////////////////////
// Diagnostic support

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<(CDumpContext& dc, const os_CString& string)
{
	dc << string.m_pchData;
	return dc;
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
// Assignment operators
//  All assign a new value to the string
//      (a) first see if the buffer is big enough
//      (b) if enough room, copy on top of old buffer, set size and type
//      (c) otherwise free old string data, and create a new one
//
//  All routines return the new string (but as a 'const os_CString&' so that
//      assigning it again will cause a copy, eg: s1 = s2 = "hi there".
//

void os_CString::AssignCopy(int nSrcLen, LPCTSTR lpszSrcData)
{
	AllocBeforeWrite(nSrcLen);
	memcpy(m_pchData, lpszSrcData, nSrcLen*sizeof(TCHAR));
	GetData()->nDataLength = nSrcLen;
	m_pchData[nSrcLen] = '\0';
}

const os_CString& os_CString::operator=(const os_CString& stringSrc)
{
	if (m_pchData != stringSrc.m_pchData) {
		if ((GetData() != 0 && GetData()->nRefs < 0) ||
			stringSrc.GetData()->nRefs < 0 ||
			os_database::of(this) != os_database::of(&stringSrc))
		{
			// actual copy necessary since one of the strings is locked
			// or in another DB
			AssignCopy(stringSrc.GetData()->nDataLength, stringSrc.m_pchData);
		}
		else
		{
			// can just copy references around
			Release();
			ASSERT(stringSrc.GetData() != 0);
			m_pchData = stringSrc.m_pchData;
			InterlockedIncrement(&GetData()->nRefs);
		}
	}
	return *this;
}

const os_CString& os_CString::operator=(LPCTSTR lpsz)
{
	ASSERT(lpsz == NULL || AfxIsValidString(lpsz, FALSE));
	AssignCopy(SafeStrlen(lpsz), lpsz);
	return *this;
}

//Assign CString object to os_CString
const os_CString& os_CString::operator=(const CString& stringSrc)
{
	CopyCString(stringSrc);
	return *this;
}

//Copy CString to os_CSrting
void os_CString::CopyCString(const CString& stringSrc)
{
	// Make a copy of source string and typecast to os_CString
	// in order to be able to access the protected members of CString
	os_CString &srcCopy = (os_CString)stringSrc;

	AssignCopy(srcCopy.GetData()->nDataLength, srcCopy.m_pchData);
}

//Copy os_CString to CString  
void os_CString::CopyToCString(CString& stringDest)
{
	char *str = new char[GetLength()+1];	/* Amber 12456 */
	strcpy(str, m_pchData);
	stringDest = (CString)str;
	delete [] str;
}



/////////////////////////////////////////////////////////////////////////////
// Special conversion assignment

#ifdef _UNICODE
const os_CString& os_CString::operator=(LPCSTR lpsz)
{
	int nSrcLen = lpsz != NULL ? _ODI_lstrlenA(lpsz) : 0;
	AllocBeforeWrite(nSrcLen);
	_mbstowcsz(m_pchData, lpsz, nSrcLen+1);
	ReleaseBuffer();
	return *this;
}
#else //!_UNICODE
const os_CString& os_CString::operator=(LPCWSTR lpsz)
{
	int nSrcLen = lpsz != NULL ? _ODI_lstrlenW(lpsz) : 0;
	AllocBeforeWrite(nSrcLen*2);
	_wcstombsz(m_pchData, lpsz, (nSrcLen*2)+1);
	ReleaseBuffer();
	return *this;
}
#endif  //!_UNICODE

//////////////////////////////////////////////////////////////////////////////
// concatenation

// NOTE: "operator+" is done as friend functions for simplicity
//      There are three variants:
//          os_CString + os_CString
// and for ? = TCHAR, LPCTSTR
//          os_CString + ?
//          ? + os_CString

void os_CString::ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data,
	int nSrc2Len, LPCTSTR lpszSrc2Data)
{
  // -- master concatenation routine
  // Concatenate two sources
  // -- assume that 'this' is a new os_CString object

	int nNewLen = nSrc1Len + nSrc2Len;
	if (nNewLen != 0)
	{
		AllocBuffer(nNewLen);
		memcpy(m_pchData, lpszSrc1Data, nSrc1Len*sizeof(TCHAR));
		memcpy(m_pchData+nSrc1Len, lpszSrc2Data, nSrc2Len*sizeof(TCHAR));
	}
}

os_CString AFXAPI operator+(const os_CString& string1, const os_CString& string2)
{
	os_CString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData,
		string2.GetData()->nDataLength, string2.m_pchData);
	return s;
}

os_CString AFXAPI operator+(const os_CString& string, LPCTSTR lpsz)
{
	ASSERT(lpsz == NULL || AfxIsValidString(lpsz, FALSE));
	os_CString s;
	s.ConcatCopy(string.GetData()->nDataLength, string.m_pchData,
		os_CString::SafeStrlen(lpsz), lpsz);
	return s;
}

os_CString AFXAPI operator+(LPCTSTR lpsz, const os_CString& string)
{
	ASSERT(lpsz == NULL || AfxIsValidString(lpsz, FALSE));
	os_CString s;
	s.ConcatCopy(os_CString::SafeStrlen(lpsz), lpsz, string.GetData()->nDataLength,
		string.m_pchData);
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// concatenate in place

void os_CString::ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData)
{
	//  -- the main routine for += operators

	// concatenating an empty string is a no-op!
	if (nSrcLen == 0)
		return;

	// if the buffer is too small, or we have a width mis-match, just
	//   allocate a new buffer (slow but sure)
	if (GetData()->nRefs > 1 || GetData()->nDataLength + nSrcLen > GetData()->nAllocLength)
	{
		// we have to grow the buffer, use the ConcatCopy routine
		os_CStringData* pOldData = GetData();
		ConcatCopy(GetData()->nDataLength, m_pchData, nSrcLen, lpszSrcData);
		ASSERT(pOldData != NULL);
		os_CString::Release(pOldData);
	}
	else
	{
		// fast concatenation when buffer big enough
		memcpy(m_pchData+GetData()->nDataLength, lpszSrcData, nSrcLen*sizeof(TCHAR));
		GetData()->nDataLength += nSrcLen;
		ASSERT(GetData()->nDataLength <= GetData()->nAllocLength);
		m_pchData[GetData()->nDataLength] = '\0';
	}
}

const os_CString& os_CString::operator+=(LPCTSTR lpsz)
{
	ASSERT(lpsz == NULL || AfxIsValidString(lpsz, FALSE));
	ConcatInPlace(SafeStrlen(lpsz), lpsz);
	return *this;
}

const os_CString& os_CString::operator+=(TCHAR ch)
{
	ConcatInPlace(1, &ch);
	return *this;
}

const os_CString& os_CString::operator+=(const os_CString& string)
{
	ConcatInPlace(string.GetData()->nDataLength, string.m_pchData);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Advanced direct buffer access

LPTSTR os_CString::GetBuffer(int nMinBufLength)
{
	ASSERT(nMinBufLength >= 0);

	if (GetData()->nRefs > 1 || nMinBufLength > GetData()->nAllocLength)
	{
		// we have to grow the buffer
		os_CStringData* pOldData = GetData();
		int nOldLen = GetData()->nDataLength;   // AllocBuffer will tromp it
		if (nMinBufLength < nOldLen)
			nMinBufLength = nOldLen;
		AllocBuffer(nMinBufLength);
		memcpy(m_pchData, pOldData->data(), (nOldLen+1)*sizeof(TCHAR));
		GetData()->nDataLength = nOldLen;
		os_CString::Release(pOldData);
	}
	ASSERT(GetData()->nRefs <= 1);

	// return a pointer to the character storage for this string
	ASSERT(m_pchData != NULL);
	return m_pchData;
}

void os_CString::ReleaseBuffer(int nNewLength)
{
	CopyBeforeWrite();  // just in case GetBuffer was not called

	if (nNewLength == -1)
		nNewLength = _ODI_lstrlen(m_pchData); // zero terminated

	ASSERT(nNewLength <= GetData()->nAllocLength);
	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';
}

LPTSTR os_CString::GetBufferSetLength(int nNewLength)
{
	ASSERT(nNewLength >= 0);

	GetBuffer(nNewLength);
	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';
	return m_pchData;
}

void os_CString::FreeExtra()
{
	ASSERT(GetData()->nDataLength <= GetData()->nAllocLength);
	if (GetData()->nDataLength != GetData()->nAllocLength)
	{
		os_CStringData* pOldData = GetData();
		AllocBuffer(GetData()->nDataLength);
		memcpy(m_pchData, pOldData->data(), pOldData->nDataLength*sizeof(TCHAR));
		ASSERT(m_pchData[GetData()->nDataLength] == '\0');
		os_CString::Release(pOldData);
	}
	ASSERT(GetData() != NULL);
}

LPTSTR os_CString::LockBuffer()
{
	LPTSTR lpsz = GetBuffer(0);
	GetData()->nRefs = -1;
	return lpsz;
}

void os_CString::UnlockBuffer()
{
	ASSERT(GetData()->nRefs == -1);
	if (GetData() != 0)
		GetData()->nRefs = 1;
}

///////////////////////////////////////////////////////////////////////////////
// Commonly used routines (rarely used routines in STREX.CPP)

int os_CString::Find(TCHAR ch) const
{
	// find first single character
	LPTSTR lpsz = _tcschr(m_pchData, (_TUCHAR)ch);

	// return -1 if not found and index otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

int os_CString::FindOneOf(LPCTSTR lpszCharSet) const
{
	ASSERT(AfxIsValidString(lpszCharSet, FALSE));
	LPTSTR lpsz = _tcspbrk(m_pchData, lpszCharSet);
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

void os_CString::MakeUpper()
{
	CopyBeforeWrite();
	_tcsupr(m_pchData);
}

void os_CString::MakeLower()
{
	CopyBeforeWrite();
	_tcslwr(m_pchData);
}

void os_CString::MakeReverse()
{
	CopyBeforeWrite();
	_tcsrev(m_pchData);
}

void os_CString::SetAt(int nIndex, TCHAR ch)
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetData()->nDataLength);

	CopyBeforeWrite();
	m_pchData[nIndex] = ch;
}

#ifndef _UNICODE
void os_CString::AnsiToOem()
{
	CopyBeforeWrite();
	::AnsiToOem(m_pchData, m_pchData);
}
void os_CString::OemToAnsi()
{
	CopyBeforeWrite();
	::OemToAnsi(m_pchData, m_pchData);
}
#endif


//////////////////////////////////////////////////////////////////////////////
// More sophisticated construction

os_CString::os_CString(TCHAR ch, int nLength) :
	m_pchData(NULL)
{
	ASSERT(!_istlead(ch));    // can't create a lead byte string
	AllocBuffer(nLength);

#ifdef _UNICODE
	for (int i = 0; i < nLength; i++)
		m_pchData[i] = ch;
#else
	if (nLength >= 1) {
		memset(m_pchData, ch, nLength);
	}
#endif
}

os_CString::os_CString(LPCTSTR lpch, int nLength) :
	m_pchData(NULL)
{
	AllocBuffer (nLength);
	if (nLength != 0)
	{
		ASSERT(AfxIsValidAddress(lpch, nLength, FALSE));
		memcpy(m_pchData, lpch, nLength*sizeof(TCHAR));
	}
}

//////////////////////////////////////////////////////////////////////////////
// Assignment operators

const os_CString& os_CString::operator=(TCHAR ch)
{
	ASSERT(!_istlead(ch));    // can't set single lead byte
	AssignCopy(1, &ch);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////
// less common string expressions

os_CString AFXAPI operator+(const os_CString& string1, TCHAR ch)
{
	os_CString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData, 1, &ch);
	return s;
}

os_CString AFXAPI operator+(TCHAR ch, const os_CString& string)
{
	os_CString s;
	s.ConcatCopy(1, &ch, string.GetData()->nDataLength, string.m_pchData);
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// Very simple sub-string extraction

os_CString os_CString::Mid(int nFirst) const
{
	return Mid(nFirst, GetData()->nDataLength - nFirst);
}

os_CString os_CString::Mid(int nFirst, int nCount) const
{
	// out-of-bounds requests return sensible things
	if (nFirst < 0)
		nFirst = 0;
	if (nCount < 0)
		nCount = 0;

	if (nFirst + nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength - nFirst;
	if (nFirst > GetData()->nDataLength)
		nCount = 0;

	os_CString dest;
	AllocCopy(dest, nCount, nFirst, 0);
	return dest;
}

os_CString os_CString::Right(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	else if (nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength;

	os_CString dest;
	AllocCopy(dest, nCount, GetData()->nDataLength-nCount, 0);
	return dest;
}

os_CString os_CString::Left(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	else if (nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength;

	os_CString dest;
	AllocCopy(dest, nCount, 0, 0);
	return dest;
}

// strspn equivalent
os_CString os_CString::SpanIncluding(LPCTSTR lpszCharSet) const
{
	ASSERT(AfxIsValidString(lpszCharSet, FALSE));
	return Left(_tcsspn(m_pchData, lpszCharSet));
}

// strcspn equivalent
os_CString os_CString::SpanExcluding(LPCTSTR lpszCharSet) const
{
	ASSERT(AfxIsValidString(lpszCharSet, FALSE));
	return Left(_tcscspn(m_pchData, lpszCharSet));
}

//////////////////////////////////////////////////////////////////////////////
// Finding

int os_CString::ReverseFind(TCHAR ch) const
{
	// find last single character
	LPTSTR lpsz = _tcsrchr(m_pchData, (_TUCHAR)ch);

	// return -1 if not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

// find a sub-string (like strstr)
int os_CString::Find(LPCTSTR lpszSub) const
{
	ASSERT(AfxIsValidString(lpszSub, FALSE));

	// find first matching substring
	LPTSTR lpsz = _tcsstr(m_pchData, lpszSub);

	// return -1 for not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

/////////////////////////////////////////////////////////////////////////////
// os_CString formatting

#ifdef _MAC
	#define TCHAR_ARG   int
	#define WCHAR_ARG   unsigned
	#define CHAR_ARG    int
#else
	#define TCHAR_ARG   TCHAR
	#define WCHAR_ARG   WCHAR
	#define CHAR_ARG    char
#endif

#if defined(_68K_) || defined(_X86_)
	#define DOUBLE_ARG  _AFX_DOUBLE
#else
	#define DOUBLE_ARG  double
#endif


#define FORCE_ANSI      0x10000
#define FORCE_UNICODE   0x20000

void os_CString::FormatV(LPCTSTR lpszFormat, va_list argList)
{
	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argListSave = argList;

	// make a guess at the maximum length of the resulting string
	int nMaxLen = 0;
	for (LPCTSTR lpsz = lpszFormat; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
	{
		// handle '%' character, but watch out for '%%'
		if (*lpsz != '%' || *(lpsz = _tcsinc(lpsz)) == '%')
		{
			nMaxLen += _tclen(lpsz);
			continue;
		}

		int nItemLen = 0;

		// handle '%' character with format
		int nWidth = 0;
		for (; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
		{
			// check for valid flags
			if (*lpsz == '#')
				nMaxLen += 2;   // for '0x'
			else if (*lpsz == '*')
				nWidth = va_arg(argList, int);
			else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' ||
				*lpsz == ' ')
				;
			else // hit non-flag character
				break;
		}
		// get width and skip it
		if (nWidth == 0)
		{
			// width indicated by
			nWidth = _ttoi(lpsz);
			for (; *lpsz != '\0' && _istdigit(*lpsz); lpsz = _tcsinc(lpsz))
				;
		}
		ASSERT(nWidth >= 0);

		int nPrecision = 0;
		if (*lpsz == '.')
		{
			// skip past '.' separator (width.precision)
			lpsz = _tcsinc(lpsz);

			// get precision and skip it
			if (*lpsz == '*')
			{
				nPrecision = va_arg(argList, int);
				lpsz = _tcsinc(lpsz);
			}
			else
			{
				nPrecision = _ttoi(lpsz);
				for (; *lpsz != '\0' && _istdigit(*lpsz); lpsz = _tcsinc(lpsz))
					;
			}
			ASSERT(nPrecision >= 0);
		}

		// should be on type modifier or specifier
		int nModifier = 0;
		switch (*lpsz)
		{
		// modifiers that affect size
		case 'h':
			nModifier = FORCE_ANSI;
			lpsz = _tcsinc(lpsz);
			break;
		case 'l':
			nModifier = FORCE_UNICODE;
			lpsz = _tcsinc(lpsz);
			break;

		// modifiers that do not affect size
		case 'F':
		case 'N':
		case 'L':
			lpsz = _tcsinc(lpsz);
			break;
		}

		// now should be on specifier
		switch (*lpsz | nModifier)
		{
		// single characters
		case 'c':
		case 'C':
			nItemLen = 2;
			va_arg(argList, TCHAR_ARG);
			break;
		case 'c'|FORCE_ANSI:
		case 'C'|FORCE_ANSI:
			nItemLen = 2;
			va_arg(argList, CHAR_ARG);
			break;
		case 'c'|FORCE_UNICODE:
		case 'C'|FORCE_UNICODE:
			nItemLen = 2;
			va_arg(argList, WCHAR_ARG);
			break;

		// strings
		case 's':
		{
			LPCTSTR pstrNextArg = va_arg(argList, LPCTSTR);
			if (pstrNextArg == NULL)
			   nItemLen = 6;  // "(null)"
			else
			{
			   nItemLen = _ODI_lstrlen(pstrNextArg);
			   nItemLen = max(1, nItemLen);
			}
			break;
		}

		case 'S':
		{
#ifndef _UNICODE
			LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
			if (pstrNextArg == NULL)
			   nItemLen = 6;  // "(null)"
			else
			{
			   nItemLen = _ODI_lstrlenW(pstrNextArg);
			   nItemLen = max(1, nItemLen);
			}
#else  
			LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
			if (pstrNextArg == NULL)
			   nItemLen = 6; // "(null)"
			else
			{
			   nItemLen = _ODI_lstrlenA(pstrNextArg);
			   nItemLen = max(1, nItemLen);
			}
#endif
			break;
		}

		case 's'|FORCE_ANSI:
		case 'S'|FORCE_ANSI:
		{
			LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
			if (pstrNextArg == NULL)
			   nItemLen = 6; // "(null)"
			else
			{
			   nItemLen = _ODI_lstrlenA(pstrNextArg);
			   nItemLen = max(1, nItemLen);
			}
			break;
		}

#ifndef _MAC
		case 's'|FORCE_UNICODE:
		case 'S'|FORCE_UNICODE:
		{
			LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
			if (pstrNextArg == NULL)
			   nItemLen = 6; // "(null)"
			else
			{
			   nItemLen = _ODI_lstrlenW(pstrNextArg);
			   nItemLen = max(1, nItemLen);
			}
			break;
		}
#endif
		}

		// adjust nItemLen for strings
		if (nItemLen != 0)
		{
			nItemLen = max(nItemLen, nWidth);
			if (nPrecision != 0)
				nItemLen = min(nItemLen, nPrecision);
		}
		else
		{
			switch (*lpsz)
			{
			// integers
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				va_arg(argList, int);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			case 'e':
			case 'f':
			case 'g':
			case 'G':
				va_arg(argList, DOUBLE_ARG);
				nItemLen = 128;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			case 'p':
				va_arg(argList, void*);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			// no output
			case 'n':
				va_arg(argList, int*);
				break;

			default:
				ASSERT(FALSE);  // unknown formatting option
			}
		}

		// adjust nMaxLen for output nItemLen
		nMaxLen += nItemLen;
	}

	GetBuffer(nMaxLen);
	VERIFY(_vstprintf(m_pchData, lpszFormat, argListSave) <= GetAllocLength());
	ReleaseBuffer();

	va_end(argListSave);
}

// formatting (using wsprintf style formatting)
void AFX_CDECL os_CString::Format(LPCTSTR lpszFormat, ...)
{
	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argList;
	va_start(argList, lpszFormat);
	FormatV(lpszFormat, argList);
	va_end(argList);
}

void AFX_CDECL os_CString::Format(UINT nFormatID, ...)
{
	os_CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);

	va_list argList;
	va_start(argList, nFormatID);
	FormatV(strFormat, argList);
	va_end(argList);
}

#ifndef _MAC
// formatting (using FormatMessage style formatting)
void AFX_CDECL os_CString::FormatMessage(LPCTSTR lpszFormat, ...)
{
	// format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, lpszFormat);
	LPTSTR lpszTemp;
	::FormatMessage(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		lpszFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList);
	if (lpszTemp == NULL)
		AfxThrowMemoryException();

	// assign lpszTemp into the resulting string and free the temporary
	*this = lpszTemp;
	LocalFree(lpszTemp);
	va_end(argList);
}

void AFX_CDECL os_CString::FormatMessage(UINT nFormatID, ...)
{
	// get format string from string table
	os_CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);

	// format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, nFormatID);
	LPTSTR lpszTemp;
	::FormatMessage(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		strFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList);
	if (lpszTemp == NULL)
		AfxThrowMemoryException();

	// assign lpszTemp into the resulting string and free lpszTemp
	*this = lpszTemp;
	LocalFree(lpszTemp);
	va_end(argList);
}
#endif //!_MAC

void os_CString::TrimRight()
{
	CopyBeforeWrite();

	// find beginning of trailing spaces by starting at beginning (DBCS aware)
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;
	while (*lpsz != '\0')
	{
		if (_istspace(*lpsz))
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		lpsz = _tcsinc(lpsz);
	}

	if (lpszLast != NULL)
	{
		// truncate at trailing space start
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void os_CString::TrimLeft()
{
	CopyBeforeWrite();

	// find first non-space character
	LPCTSTR lpsz = m_pchData;
	while (_istspace(*lpsz))
		lpsz = _tcsinc(lpsz);

	// fix up data and length
	int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
	memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(TCHAR));
	GetData()->nDataLength = nDataLength;
}

/**
 * Return Case Sensitive hash value.
 **/
unsigned os_CString::hash() const
{
	unsigned hv = (unsigned)GetLength();
	unsigned i = GetLength() * sizeof(char)/sizeof(unsigned);
	const unsigned *p = (const unsigned *)m_pchData;
	
	while(i--)
		os_CString::mash(hv, *p++);	//XOR in the characters.

	//XOR in any remaining characters:
	if ((i = GetLength()*sizeof(char)%sizeof(unsigned)) != 0)
	{
		unsigned h = 0;
		const char *c = (const char *)p;
		while(i--)
			h = ((h << 8*sizeof(char)) | *c++);
		os_CString::mash(hv, h);
	}
	return hv;
}

/* static */
void os_CString::mash(unsigned& hash, unsigned chars)
{
  hash = (chars ^
       ((hash << HASH_SHIFT) |
        (hash >> (8*sizeof(unsigned) - HASH_SHIFT))));
}

int os_CString::string_rank(const void* arg1, const void* arg2)
{
	// Use global operators ==, < implemented with CString
	// as parameters for comparison
	CString* s1 = (CString*) arg1;
	CString* s2 = (CString*) arg2;
	return s1->Compare((LPCTSTR)(*s2));
}

unsigned int os_CString::string_hash(const void* x)
{
	os_CString* pStr = (os_CString*) x;
	return pStr->hash();
}

void
os_CString::os_register()
{
	static int registered = 0;
	if (!registered)
	{
		os_index_key(os_CString,string_rank,string_hash);
		registered++;
	}
}

// Load String from Resource into persistent space
BOOL os_CString::LoadString(UINT nID)
{
	CString s;
	BOOL ret = s.LoadString(nID);

	if (ret)
	   //Copy CString object loaded from Resource into persistent space
	   this->CopyCString(s);
	return ret;
}

int filter_pointer_exception (void* lpString)
{
	if (!objectstore::is_persistent(lpString)) {
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {
		return EXCEPTION_CONTINUE_SEARCH;
	}
}


int _ODI_lstrlenA(LPCSTR lpString)
{
	__try {
		return strlen(lpString);
	}
	__except(filter_pointer_exception((void*)lpString)) {
		return 0;
	}
}


int _ODI_lstrlenW(LPCWSTR lpString)
{
	__try {
		return wcslen(lpString);	
	}
	__except(filter_pointer_exception((void*)lpString)) {
		return 0;
	}
}



