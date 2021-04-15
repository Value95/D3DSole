#pragma once



// CFeatureView �� ���Դϴ�.

class CFeatureView : public CFormView
{
	DECLARE_DYNCREATE(CFeatureView)
private:
	CMainFrame* m_main;
	CProjectView* m_projectView;
	CHierarchyView* m_hierarchyView;
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
	afx_msg void NavMeshMode();

private:
	void SaveWstring(HANDLE* file, DWORD* dwByte, std::wstring str);
	std::wstring LoadWstring(HANDLE* file, DWORD* dwByte);
	void ReSetProject();
public:
	afx_msg void UIMode();
};


