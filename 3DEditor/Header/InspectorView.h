#pragma once
#include "afxwin.h"



// CInspectorView �� ���Դϴ�.

class CInspectorView : public CFormView
{
	DECLARE_DYNCREATE(CInspectorView)
public:
	Engine::CGameObject* m_gameObejct;
	BOOL m_enable;
	CString m_name;
	float m_positionX;
	float m_positionY;
	float m_positionZ;
	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;
	float m_scaleX;
	float m_scaleY;
	float m_scaleZ;
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
	void SetData(Engine::CGameObject* gameObject);
private:
	void InputData();
public:

};


