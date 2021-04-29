#ifndef ANIMMESHRENDERMANAGER_H
#define ANIMMESHRENDERMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CAnimMeshRenderManager final : public CEngine
{
	DECLARE_SINGLETON(CAnimMeshRenderManager)
private:
	std::vector<SHARED(CAnimMeshRenderComponent)> m_animRenderList[(_uint)ERenderID::NumOfRenderID];
	std::vector<SHARED(CEffectComponent)> m_effectRenderList;

public:
	void Awake(void);
	void Start(void);

	_uint FixedUpdate(void);
	_uint Update(void);
	_uint LateUpdate(void);

	_uint PreRender(void);
	_uint Render(void);
	_uint PostRender(void);

	void OnDestroy(void);

	void OnEnable(void);
	void OnDisable(void);

	_uint AddToRenderList(ERenderID renderID,	SHARED(CAnimMeshRenderComponent) pGC);
	_uint AddToEffectRenderList(SHARED(CEffectComponent) effectComPonent);

private:
	_uint AnimMeshRender();
	_uint EffectMeshRender();
};
END
#endif