#pragma once
#include "Scene.h"

class CEditorScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER
private:
	Engine::CGameObject* m_PreSelectedObject = nullptr;
	Engine::CGameObject* m_CurSelectedObject = nullptr;



	CMainFrame * m_main;
	CMy3DEditorView* m_editorView;
	CProjectView* m_projectView;
	CHierarchyView* hierarchyView;
	CInspectorView* inspectorView;

public:
	Engine::CGameObject* m_pickingObject = nullptr;
	_int m_pickNumber = -1;

	SHARED(Engine::CGameObject) m_box;
	SHARED(Engine::CGameObject) m_sphere;
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
	void ColliderSesting(int value, Engine::CGameObject* object);
	void InspactorSesting(int value, Engine::CGameObject* object);
private:
	void Camera();
	void ObjectCreate();
	void ObjectPicking(std::wstring layerKey);
	void ObjectMove();
	void ObjectMoveToView();
};

