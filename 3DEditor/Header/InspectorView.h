#pragma once



// CInspectorView �� ���Դϴ�.

class CInspectorView : public CFormView
{
	DECLARE_DYNCREATE(CInspectorView)

protected:
	CInspectorView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CInspectorView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSPECTORVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnEnChangeEdit1();
};


