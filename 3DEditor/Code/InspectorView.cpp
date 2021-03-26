// ../Code/InspectorView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "InspectorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInspectorView

IMPLEMENT_DYNCREATE(CInspectorView, CFormView)

CInspectorView::CInspectorView()
	: CFormView(IDD_INSPECTORVIEW)
	, m_enable(false)
	, m_name(L"")
	, m_positionX(0)
	, m_positionY(0)
	, m_positionZ(0)
	, m_rotatioX(0)
	, m_rotatioY(0)
	, m_rotatioZ(0)
	, m_scaleX(false)
	, m_scaleY(0)
	, m_scaleZ(0)
{

}

CInspectorView::~CInspectorView()
{
}

void CInspectorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CInspectorView::SetDate(Engine::CGameObject* gameObject)
{
	m_gameObejct = gameObject;
	m_enable = m_gameObejct->GetIsEnabled();
	m_name = m_gameObejct->GetName();
	m_positionX = m_gameObejct->GetPosition().x;
	m_positionY = m_gameObejct->GetPosition().y;
	m_positionZ = m_gameObejct->GetPosition().z;
	m_rotatioX = m_gameObejct->GetRotation().x;
	m_rotatioY = m_gameObejct->GetRotation().y;
	m_rotatioZ = m_gameObejct->GetRotation().z;
	m_scaleX = m_gameObejct->GetScale().x;
	m_scaleY = m_gameObejct->GetScale().y;
	m_scaleZ = m_gameObejct->GetScale().z;
}

void CInspectorView::InputDate()
{
	m_gameObejct->GetIsEnabled() = m_enable;
	m_gameObejct->GetName() = m_name;
	m_gameObejct->SetPositionX(m_positionX);
	m_gameObejct->SetPositionY(m_positionY);
	m_gameObejct->SetPositionZ(m_positionZ);
	m_gameObejct->SetRotationX(m_rotatioX);
	m_gameObejct->SetRotationY(m_rotatioY);
	m_gameObejct->SetRotationZ(m_rotatioZ);
	m_gameObejct->SetScaleX(m_scaleX);
	m_gameObejct->SetScaleY(m_scaleY);
	m_gameObejct->SetScaleZ(m_scaleZ);
}

BEGIN_MESSAGE_MAP(CInspectorView, CFormView)
END_MESSAGE_MAP()


// CInspectorView 진단입니다.

#ifdef _DEBUG
void CInspectorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInspectorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInspectorView 메시지 처리기입니다.
