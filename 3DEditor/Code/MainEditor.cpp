#include "stdafx.h"
#include "MainEditor.h"
#include "EditorScene.h"

CMainEditor::CMainEditor()
{
}


CMainEditor::~CMainEditor()
{
	OnDestroy();
}

SHARED(CMainEditor) CMainEditor::Create(void)
{
	SHARED(CMainEditor) pMainEditor(new CMainEditor, Engine::SmartDeleter<CMainEditor>);

	return pMainEditor;
}

void CMainEditor::Awake(void)
{
	m_main = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());

	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CStaticMeshRenderManager::GetInstance()->Awake();
	Engine::CUIManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
}

void CMainEditor::Start(void)
{
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CStaticMeshRenderManager::GetInstance()->Start();
	Engine::CUIManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CEditorScene::Create());
}

_uint CMainEditor::FixedUpdate(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CStaticMeshRenderManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CSceneManager::GetInstance()->FixedUpdate())	return event;

	return event;
}

_uint CMainEditor::Update(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CStaticMeshRenderManager::GetInstance()->Update())	return event;
	if (event = Engine::CInputManager::GetInstance()->Update())		return event;
	if (event = Engine::CSceneManager::GetInstance()->Update())		return event;

	return event;
}

_uint CMainEditor::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CSceneManager::GetInstance()->LateUpdate())		return event;

	return event;
}

_uint CMainEditor::Render(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->Render())	return event;

	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
	{
		if (event = CNavMeshManager::GetInstance()->PreRender()) return event;
		if (event = CNavMeshManager::GetInstance()->Render()) return event;
	}
	
	if (m_main->m_mode == CMainFrame::Mode::UI)
	{
		if (event = Engine::CUIManager::GetInstance()->PreRender())	return event;
		if (event = Engine::CUIManager::GetInstance()->Render())		return event;
	}

	if (event = Engine::CDebugRendeerManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->Render())	return event;


	return event;
}

_uint CMainEditor::PostRender(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->PostRender())	return event;

	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
		if (event = CNavMeshManager::GetInstance()->PostRender()) return event;

	if (m_main->m_mode == CMainFrame::Mode::UI)
		if (event = Engine::CUIManager::GetInstance()->PostRender()) return event;

	if (event = Engine::CDebugRendeerManager::GetInstance()->PostRender())	return event;

	return event;
}

void CMainEditor::OnDestroy(void)
{
	Engine::CStaticMeshRenderManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CObjectFactory::GetInstance()->DestroyInstance();
	Engine::CDataStore::GetInstance()->DestroyInstance();
	Engine::CMeshStore::GetInstance()->DestroyInstance();
	Engine::CTextureStore::GetInstance()->DestroyInstance();
	Engine::CDebugRendeerManager::GetInstance()->DestroyInstance();
	Engine::CUIManager::GetInstance()->DestroyInstance();
	CNavMeshManager::DestroyInstance();
	CColliderManager::GetInstance()->DestroyInstance();
}

void CMainEditor::OnEnable(void)
{
}

void CMainEditor::OnDisable(void)
{
}
