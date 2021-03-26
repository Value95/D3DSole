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
	, m_enable(FALSE)
	, m_name(_T(""))
	, m_positionX(0)
	, m_positionY(0)
	, m_positionZ(0)
	, m_rotationX(0)
	, m_rotationY(0)
	, m_rotationZ(0)
	, m_scaleX(0)
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
	DDX_Check(pDX, IDC_CHECK2, m_enable);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_positionX);
	DDX_Text(pDX, IDC_EDIT2, m_positionY);
	DDX_Text(pDX, IDC_EDIT4, m_positionZ);
	DDX_Text(pDX, IDC_EDIT6, m_rotationX);
	DDX_Text(pDX, IDC_EDIT5, m_rotationY);
	DDX_Text(pDX, IDC_EDIT7, m_rotationZ);
	DDX_Text(pDX, IDC_EDIT9, m_scaleX);
	DDX_Text(pDX, IDC_EDIT8, m_scaleY);
	DDX_Text(pDX, IDC_EDIT10, m_scaleZ);
}

void CInspectorView::SetData(Engine::CGameObject* gameObject)
{
	UpdateData(TRUE);
	m_gameObejct = gameObject;
	m_enable = m_gameObejct->GetIsEnabled();
	m_name = m_gameObejct->GetName().c_str();
	m_positionX = m_gameObejct->GetPosition().x;
	m_positionY = m_gameObejct->GetPosition().y;
	m_positionZ = m_gameObejct->GetPosition().z;
	m_rotationX = m_gameObejct->GetRotation().x;
	m_rotationY = m_gameObejct->GetRotation().y;
	m_rotationZ = m_gameObejct->GetRotation().z;
	m_scaleX = m_gameObejct->GetScale().x;
	m_scaleY = m_gameObejct->GetScale().y;
	m_scaleZ = m_gameObejct->GetScale().z;
	UpdateData(FALSE);
}

void CInspectorView::InputData()
{
	m_gameObejct->GetIsEnabled() = m_enable;
	m_gameObejct->GetName() = m_name;
	m_gameObejct->SetPositionX(m_positionX);
	m_gameObejct->SetPositionY(m_positionY);
	m_gameObejct->SetPositionZ(m_positionZ);
	m_gameObejct->SetRotationX(m_rotationX);
	m_gameObejct->SetRotationY(m_rotationY);
	m_gameObejct->SetRotationZ(m_rotationZ);
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
