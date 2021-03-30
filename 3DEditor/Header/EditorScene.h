#pragma once
#include "Scene.h"

class CEditorScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER
private:
	Engine::CGameObject* m_PreSelectedObject = nullptr;
	Engine::CGameObject* m_CurSelectedObject = nullptr;

	Engine::CGameObject* m_pickingObject = nullptr;
	_int m_pickNumber = -1;

	CMainFrame * m_main;
	CMy3DEditorView* m_editorView;
	CProjectView* m_projectView;
	CHierarchyView* hierarchyView;
	CInspectorView* inspectorView;
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
	
	void SetPickingObject(Engine::CGameObject* value) { m_pickingObject = value; }
	Engine::CGameObject* GetPickingObject() { return m_pickingObject; }
private:
	void Camera();
	void ObjectCreate();
	void ObjectPicking();
	void ObjectMove();
};

