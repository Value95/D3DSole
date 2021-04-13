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
	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CUIManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
}

void CMainEditor::Start(void)
{
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CUIManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CEditorScene::Create());
}

_uint CMainEditor::FixedUpdate(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CGraphicsManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CSceneManager::GetInstance()->FixedUpdate())	return event;

	return event;
}

_uint CMainEditor::Update(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CGraphicsManager::GetInstance()->Update())	return event;
	if (event = Engine::CInputManager::GetInstance()->Update())		return event;
	if (event = Engine::CSceneManager::GetInstance()->Update())		return event;

	return event;
}

_uint CMainEditor::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CGraphicsManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CSceneManager::GetInstance()->LateUpdate())		return event;

	return event;
}

_uint CMainEditor::Render(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CGraphicsManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CGraphicsManager::GetInstance()->Render())	return event;

	if (event = CNavMeshManager::GetInstance()->PreRender()) return event;
	if (event = CNavMeshManager::GetInstance()->Render()) return event;

	if (event = Engine::CUIManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CUIManager::GetInstance()->Render())		return event;

	if (event = Engine::CDebugRendeerManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->Render())	return event;


	return event;
}

_uint CMainEditor::PostRender(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CGraphicsManager::GetInstance()->PostRender())	return event;
	if (event = CNavMeshManager::GetInstance()->PostRender()) return event;
	if (event = Engine::CUIManager::GetInstance()->PostRender()) return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->PostRender())	return event;

	return event;
}

void CMainEditor::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
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
