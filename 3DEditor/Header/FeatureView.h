#pragma once



// CFeatureView �� ���Դϴ�.

class CFeatureView : public CFormView
{
	DECLARE_DYNCREATE(CFeatureView)
private:
	CProjectView* hierarchyView;
protected:
	CFeatureView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CFeatureView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREVIEW };
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
public:
	afx_msg void PrefabCreate();
	afx_msg void Save();
	afx_msg void Load();
	afx_msg void PrefabDelete();
	virtual void OnInitialUpdate();
};


