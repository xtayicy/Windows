// MFCMultipleDemoDoc.h : interface of the CMFCMultipleDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMULTIPLEDEMODOC_H__D1718511_D03B_49E7_B9EA_40A6BEC6F961__INCLUDED_)
#define AFX_MFCMULTIPLEDEMODOC_H__D1718511_D03B_49E7_B9EA_40A6BEC6F961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCMultipleDemoDoc : public CDocument
{
protected: // create from serialization only
	CMFCMultipleDemoDoc();
	DECLARE_DYNCREATE(CMFCMultipleDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMultipleDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCMultipleDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMultipleDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMULTIPLEDEMODOC_H__D1718511_D03B_49E7_B9EA_40A6BEC6F961__INCLUDED_)
