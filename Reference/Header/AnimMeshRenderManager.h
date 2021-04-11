#ifndef ANIMMESHRENDERMANAGER_H
#define ANIMMESHRENDERMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CAnimMeshRenderManager final : public CEngine
{
	DECLARE_SINGLETON(CAnimMeshRenderManager)
private:
	std::vector<SHARED(CAnimMeshRenderComponent)>	m_vRenderList[(_uint)ERenderID::NumOfRenderID];

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
};
END
#endif