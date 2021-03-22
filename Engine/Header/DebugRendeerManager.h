#ifndef DEBUGRENDERMANAGER_H
#define DEBUGRENDERMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CDebugRendeerManager final : public CEngine
{
	DECLARE_SINGLETON(CDebugRendeerManager)
	typedef std::vector<SHARED(CBoxComponent)> _BOXCOMPONENTS;
	typedef std::vector<SHARED(CSphereComponent)> _SPHERECOMPONENTS;
	typedef std::vector<SHARED(CLineComponent)> _LINECOMPONENTS;
	typedef std::vector<SHARED(CTriangleComponent)> _TRIANGLECOMPONENTS;
private:
	_BOXCOMPONENTS		m_boxRenderList;
	_SPHERECOMPONENTS		m_sphereRenderList;
	_LINECOMPONENTS		m_lineRenderList;
	_TRIANGLECOMPONENTS		m_triangleRenderList;
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
		 
	_uint BoxRender();
	_uint SphereRender();
	_uint LineRedner();
	_uint TriangleRendeer();

	_uint AddToBoxRenderList(SHARED(CBoxComponent) pGC);
	_uint AddToSphereRenderList(SHARED(CSphereComponent) pGC);
	_uint AddToLineRenderList(SHARED(CLineComponent) pGC);
	_uint AddToTriangleRenderList(SHARED(CTriangleComponent) pGC);
};
END
#endif