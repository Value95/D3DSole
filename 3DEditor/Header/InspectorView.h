#pragma once
#include "afxwin.h"



// CInspectorView 폼 뷰입니다.

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
	CInspectorView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	void SetData(Engine::CGameObject* gameObject);
private:
	void InputData();
public:

};


