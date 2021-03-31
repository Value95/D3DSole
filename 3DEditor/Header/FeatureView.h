#pragma once



// CFeatureView 폼 뷰입니다.

class CFeatureView : public CFormView
{
	DECLARE_DYNCREATE(CFeatureView)
private:
	CProjectView* hierarchyView;
protected:
	CFeatureView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void PrefabCreate();
	afx_msg void Save();
	afx_msg void Load();
	afx_msg void PrefabDelete();
	virtual void OnInitialUpdate();
};


