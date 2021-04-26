#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CStaticMeshRenderManager final : public CEngine
{
	DECLARE_SINGLETON(CStaticMeshRenderManager)
private:
	std::vector<SHARED(CStaticMeshRenderComponent)>	m_vRenderList[(_uint)ERenderID::NumOfRenderID];
	SHARED(CSkyBoxComponent) m_skyBox;
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

	_uint AddToRenderList(ERenderID renderID,	SHARED(CStaticMeshRenderComponent) pGC);
	_uint AddToSkyBox(SHARED(CSkyBoxComponent) skyBox);
};
END
#endif