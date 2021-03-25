// ../Code/ProjectView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "ProjectView.h"
#include "MeshStore.h"
#include "TextureStore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CProjectView

IMPLEMENT_DYNCREATE(CProjectView, CFormView)

CProjectView::CProjectView()
	: CFormView(IDD_PROJECTVIEW)
{

}

CProjectView::~CProjectView()
{
}

void CProjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_textureList);
	DDX_Control(pDX, IDC_LIST2, m_messList);
	DDX_Control(pDX, IDC_LIST1, m_prefabList);

	m_messList.ResetContent();
	m_messList.AddString(L"Default");
	for (auto& value : Engine::CMeshStore::GetInstance()->GetStaticMeshData())
	{
		TCHAR szFileName[MAX_PATH] = L"";
		std::wstring strFileName = (&value)->second->name;
		lstrcpy(szFileName, strFileName.c_str());
		m_messList.AddString(szFileName);
	}

	m_textureList.ResetContent();
	m_textureList.AddString(L"Default");
	for (auto& value : Engine::CTextureStore::GetInstance()->GetStaticTextureData())
	{
		if ((&value)->second->name == L"Error")
		{
			continue;
		}

		TCHAR szFileName[MAX_PATH] = L"";
		std::wstring strFileName = (&value)->second->name;
		lstrcpy(szFileName, strFileName.c_str());
		m_textureList.AddString(szFileName);
	}
}


BEGIN_MESSAGE_MAP(CProjectView, CFormView)

	ON_LBN_SELCHANGE(IDC_LIST2, &CProjectView::MessListClick)
	ON_LBN_SELCHANGE(IDC_LIST3, &CProjectView::TextureListClick)
	ON_LBN_SELCHANGE(IDC_LIST1, &CProjectView::PrefabListClick)
END_MESSAGE_MAP()


// CProjectView 진단입니다.

#ifdef _DEBUG
void CProjectView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProjectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CProjectView::MessListClick()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CProjectView::TextureListClick()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CProjectView::PrefabListClick()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

