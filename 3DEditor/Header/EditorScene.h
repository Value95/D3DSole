#pragma once
#include "Scene.h"

class CEditorScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER
private:
	_bool m_isPickingMode = false;
	_bool m_AddFistCubeToListBox = true;
	class Engine::CGameObject* m_PreSelectedObject = nullptr;
	class Engine::CGameObject* m_CurSelectedObject = nullptr;

	CMainFrame * m_main;
	CMy3DEditorView* m_editorView;
	CProjectView* m_projectView;

public:
	explicit CEditorScene();
	~CEditorScene();

public:
	static			SHARED(Engine::CScene)	Create(void);

	virtual void Awake(void) override;
	virtual void Start(void) override;
	virtual _uint FixedUpdate(void) override;
	virtual _uint Update(void) override;
	virtual _uint LateUpdate(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;
	virtual void InitLayers(void) override;
	virtual void InitPrototypes(void) override;
	

private:

};

