/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
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

// Inlines for oscstring.H

// os_CString

inline os_CStringData* os_CString::GetData() const
{
	if(m_pchData) {
		return ((os_CStringData*)m_pchData)-1;
	}
	else {
		return NULL;
	}
}

inline os_CString::os_CString(const unsigned char* lpsz) :
	m_pchData (NULL)
	{AllocBuffer(0); *this = (LPCSTR)lpsz; }
inline const os_CString& os_CString::operator=(const unsigned char* lpsz)
	{ *this = (LPCSTR)lpsz; return *this; }
#ifdef _UNICODE
inline const os_CString& os_CString::operator+=(char ch)
	{ *this += (TCHAR)ch; return *this; }
inline const os_CString& os_CString::operator=(char ch)
	{ *this = (TCHAR)ch; return *this; }
inline os_CString AFXAPI operator+(const os_CString& string, char ch)
	{ return string + (TCHAR)ch; }
inline os_CString AFXAPI operator+(char ch, const os_CString& string)
	{ return (TCHAR)ch + string; }
#endif

inline int os_CString::GetLength() const
	{ return GetData()->nDataLength; }
inline int os_CString::GetAllocLength() const
	{ return GetData()->nAllocLength; }
inline BOOL os_CString::IsEmpty() const
	{ return GetData()->nDataLength == 0; }
inline os_CString::operator LPCTSTR() const
	{ return m_pchData; }
inline int PASCAL os_CString::SafeStrlen(LPCTSTR lpsz)
	{ return _ODI_lstrlen(lpsz); }

// os_CString support (windows specific)
inline int os_CString::Compare(LPCTSTR lpsz) const
	{ return _tcscmp(m_pchData, lpsz); }    // MBCS/Unicode aware
inline int os_CString::CompareNoCase(LPCTSTR lpsz) const
	{ return _tcsicmp(m_pchData, lpsz); }   // MBCS/Unicode aware
// os_CString::Collate is often slower than Compare but is MBSC/Unicode
//  aware as well as locale-sensitive with respect to sort order.
inline int os_CString::Collate(LPCTSTR lpsz) const
	{ return _tcscoll(m_pchData, lpsz); }   // locale sensitive

inline TCHAR os_CString::GetAt(int nIndex) const
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}
inline TCHAR os_CString::operator[](int nIndex) const
{
	// same as GetAt
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}
inline os_CString::operator CString&() const 
	{ return *(CString*) this; }

