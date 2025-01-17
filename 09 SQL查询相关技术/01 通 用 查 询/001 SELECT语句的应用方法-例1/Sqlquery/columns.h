#if !defined(AFX_COLUMNS_H__7F01E333_5949_4D10_8920_8AC0B877B9DF__INCLUDED_)
#define AFX_COLUMNS_H__7F01E333_5949_4D10_8920_8AC0B877B9DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CColumn;

/////////////////////////////////////////////////////////////////////////////
// CColumns wrapper class

class CColumns : public COleDispatchDriver
{
public:
	CColumns() {}		// Calls COleDispatchDriver default constructor
	CColumns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CColumns(const CColumns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	CColumn Add(short Index);
	CColumn GetItem(const VARIANT& Index);
	void Remove(const VARIANT& Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLUMNS_H__7F01E333_5949_4D10_8920_8AC0B877B9DF__INCLUDED_)
