// ../Code/FeatureView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "FeatureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFeatureView

IMPLEMENT_DYNCREATE(CFeatureView, CFormView)

CFeatureView::CFeatureView()
	: CFormView(IDD_FEATUREVIEW)
{

}

CFeatureView::~CFeatureView()
{
}

void CFeatureView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CFeatureView::PrefabCreate()
{
	// 하이어락키에 셋팅된 게임오브젝트의 속성값을 프리팹한테 넘겨준다.
	// 프리팹에 이름을 프로젝트뷰에 m_prefabList에 등록해준다.
	// 프리팹 삭제도 만들어야된다.
}


void CFeatureView::Save()
{
	
	CFileDialog Dlg(FALSE,// 저장(FALSE)할 것인지 불러(TRUE)올 것인지
		L"dat",
		L"*.dat",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) | *.dat||",
		this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			//MSG_BOX(__FILE__, L"Save File Failed");

			return;
		}
		
		std::unordered_map<std::wstring, SHARED(Engine::CLayer)> layers = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers();
		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		for (auto& layer : layers)
		{
			for (auto& gameObject : layer.second->GetGameObjects())
			{
				if (gameObject->GetLayerKey() == L"Camera")
					continue;

				WriteFile(hFile, &gameObject->GetName(), sizeof(std::wstring), &dwByte, nullptr);

				WriteFile(hFile, &gameObject->GetLayerKey(), sizeof(std::wstring), &dwByte, nullptr);

				WriteFile(hFile, &gameObject->GetObjectKey(), sizeof(std::wstring), &dwByte, nullptr);

				WriteFile(hFile, &gameObject->GetIsEnabled(), sizeof(bool), &dwByte, nullptr); // 활성화/비활성화
				WriteFile(hFile, &gameObject->GetPosition(), sizeof(vector3), &dwByte, nullptr); // 위치
				WriteFile(hFile, &gameObject->GetRotation(), sizeof(vector3), &dwByte, nullptr); // 회전
				WriteFile(hFile, &gameObject->GetScale(), sizeof(vector3), &dwByte, nullptr); // 크기
				WriteFile(hFile, &gameObject->GetComponent<Engine::CTextureComponent>()->GetTextureKey(), sizeof(std::wstring), &dwByte, nullptr); // 텍스쳐
				WriteFile(hFile, &gameObject->GetComponent<Engine::CMeshComponent>()->GetMeshKey(), sizeof(std::wstring), &dwByte, nullptr); // 메쉬

			}
		}

		
		
		CloseHandle(hFile);
	}
	
}


void CFeatureView::Load()
{
	CFileDialog Dlg(TRUE,// 저장(FALSE)할 것인지 불러(TRUE)올 것인지
		L"dat",
		L"*.dat",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) | *.dat||",
		this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}
		DWORD dwByte = 0;
		DWORD dwStringSize = 0;

		CHierarchyView* hierarchyView = dynamic_cast<CHierarchyView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_mainSplitter.GetPane(0, 1));
		hierarchyView->m_objectListBox.ResetContent();
		hierarchyView->m_objectPos.clear();
		while (true)
		{
			SHARED(Engine::CGameObject) obj = Engine::ADD_CLONE(L"Default", L"Default", false);
 
			ReadFile(hFile, &obj->GetName(), sizeof(std::wstring), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetLayerKey(), sizeof(std::wstring), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetObjectKey(), sizeof(std::wstring), &dwByte, nullptr);

			ReadFile(hFile, &obj->GetIsEnabled(), sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetPosition(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetRotation(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetScale(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetComponent<Engine::CTextureComponent>()->GetTextureKey(), sizeof(std::wstring), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetComponent<Engine::CMeshComponent>()->GetMeshKey(), sizeof(std::wstring), &dwByte, nullptr);

			if (0 == dwByte)
			{
				obj->OnDestroy();
				// 오브젝트 삭제
				break;
			}
			hierarchyView->m_objectListBox.AddString(obj.get()->GetName().c_str());
			hierarchyView->m_objectPos.emplace_back(obj.get()->GetPosition());

		}
		CloseHandle(hFile);
	}
}


BEGIN_MESSAGE_MAP(CFeatureView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON6, &CFeatureView::PrefabCreate)
	ON_BN_CLICKED(IDC_BUTTON1, &CFeatureView::Save)
	ON_BN_CLICKED(IDC_BUTTON2, &CFeatureView::Load)
END_MESSAGE_MAP()


// CFeatureView 진단입니다.

#ifdef _DEBUG
void CFeatureView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFeatureView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFeatureView 메시지 처리기입니다.


/*
dwStringSize = sizeof(wchar_t) * (gameObject->GetName().length() + 1); // 이름
WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
WriteFile(hFile, gameObject->GetName().c_str(), dwStringSize, &dwByte, nullptr);

dwStringSize = sizeof(wchar_t) * (gameObject->GetLayerKey().length() + 1); // 레이어키
WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
WriteFile(hFile, gameObject->GetLayerKey().c_str(), dwStringSize, &dwByte, nullptr);

dwStringSize = sizeof(wchar_t) * (gameObject->GetObjectKey().length() + 1); // 오브젝트키
WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
WriteFile(hFile, gameObject->GetObjectKey().c_str(), dwStringSize, &dwByte, nullptr);

WriteFile(hFile, &gameObject->GetIsEnabled(), sizeof(bool), &dwByte, nullptr); // 활성화/비활성화
WriteFile(hFile, &gameObject->GetPosition(), sizeof(vector3), &dwByte, nullptr); // 위치
WriteFile(hFile, &gameObject->GetRotation(), sizeof(vector3), &dwByte, nullptr); // 회전
WriteFile(hFile, &gameObject->GetScale(), sizeof(vector3), &dwByte, nullptr); // 크기
WriteFile(hFile, &gameObject->GetComponent<Engine::CTextureComponent>()->GetTextureKey(), sizeof(std::wstring), &dwByte, nullptr); // 텍스쳐
WriteFile(hFile, &gameObject->GetComponent<Engine::CMeshComponent>()->GetMeshKey(), sizeof(std::wstring), &dwByte, nullptr); // 메쉬
*/
/*
ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
TCHAR* strName = new TCHAR[dwStringSize];
ReadFile(hFile, strName, dwStringSize, &dwByte, nullptr);
obj->SetName(strName);

ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
TCHAR* layerKey = new TCHAR[dwStringSize];
ReadFile(hFile, layerKey, dwStringSize, &dwByte, nullptr);
obj->SetLayerKey(layerKey);

ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
TCHAR* objectKey = new TCHAR[dwStringSize];
ReadFile(hFile, objectKey, dwStringSize, &dwByte, nullptr);
obj->SetObjectKey(objectKey);
*/