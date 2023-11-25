// MFCSingleDemoDoc.h : interface of the CMFCSingleDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCSINGLEDEMODOC_H__A31A2FE0_C4A8_4B36_950B_2637DA913C30__INCLUDED_)
#define AFX_MFCSINGLEDEMODOC_H__A31A2FE0_C4A8_4B36_950B_2637DA913C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCSingleDemoDoc : public CDocument
{
protected: // create from serialization only
	CMFCSingleDemoDoc();
	DECLARE_DYNCREATE(CMFCSingleDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSingleDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCSingleDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCSingleDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSINGLEDEMODOC_H__A31A2FE0_C4A8_4B36_950B_2637DA913C30__INCLUDED_)
