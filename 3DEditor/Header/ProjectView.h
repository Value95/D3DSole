#pragma once



// CProjectView �� ���Դϴ�.

class CProjectView : public CFormView
{
	DECLARE_DYNCREATE(CProjectView)

protected:
	CProjectView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CProjectView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECTVIEW };
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
};


