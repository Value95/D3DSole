#pragma once



// CInspectorView �� ���Դϴ�.

class CInspectorView : public CFormView
{
	DECLARE_DYNCREATE(CInspectorView)
public:
	bool m_enable;
	std::wstring m_name;
	float m_positionX;
	float m_positionY;
	float m_positionZ;
	float m_rotatioX;
	float m_rotatioY;
	float m_rotatioZ;
	bool m_scaleX;
	float m_scaleY;
	float m_scaleZ;
	Engine::CGameObject* m_gameObejct;
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

public:
	void SetDate(Engine::CGameObject* gameObject);
private:
	void InputDate();
};


