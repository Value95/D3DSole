#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Engine.h"
#include "Scene.h"

BEGIN(Engine)
class ENGINE_DLL CSceneManager final : public CEngine
{
	DECLARE_SINGLETON(CSceneManager)
private:
	std::stack<SHARED(CScene)>			m_sScene;

	GETTOR_SETTOR(bool,				m_needToBeCleaned,	false,			NeedToBeCleaned)
	GETTOR_SETTOR(SHARED(CScene),	m_pCurScene,		nullptr,		CurScene) // 현재씬
	GETTOR_SETTOR(SHARED(CScene),	m_pNextScene,		nullptr,		NextScene) // 다음씬 바뀌고자 할때 해당 변수에 씬을넣고 초기화후 현재씬과 교체한다.

	GETTOR(std::vector<UNITINFO>, m_vUnitInfo,{}, UnitInfo)
public:

	void Awake(void) override;
	void Start(void);
		 
	_uint FixedUpdate(void);
	_uint Update(void);
	_uint LateUpdate(void);
		 
	void OnDestroy(void);
		 
	void OnEnable(void);
	void OnDisable(void);
		 
	void SceneChange(SHARED(CScene) pScene, bool needToBeCleaned = true);
private:
					void				OrganizeScene(void);
};
END

#endif
