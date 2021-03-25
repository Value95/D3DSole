// ../Code/ProjectView.cpp : ���� �����Դϴ�.
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


// CProjectView �����Դϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CProjectView::TextureListClick()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CProjectView::PrefabListClick()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

