#if !defined(AFX_LINETREE_H__611C18A6_1A0E_4D4A_9C83_A1C00FCF1771__INCLUDED_)
#define AFX_LINETREE_H__611C18A6_1A0E_4D4A_9C83_A1C00FCF1771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineTree window

class CLineTree : public CTreeCtrl
{
// Construction
public:
	CLineTree();
	COLORREF m_clBk;			//������ɫ
	COLORREF m_clLine;			//������ɫ
	COLORREF m_clText;			//�ı���ɫ
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineTree)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLineTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINETREE_H__611C18A6_1A0E_4D4A_9C83_A1C00FCF1771__INCLUDED_)
