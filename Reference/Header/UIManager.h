#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CUIManager final : public CEngine
{
	DECLARE_SINGLETON(CUIManager)
private:
	typedef std::vector<std::vector<SHARED(CUIComponent)>> _UICOMPONENTS;
	typedef std::vector<SHARED(CWorldUIComponent)> _WORLDUICOMPONENTS;

	_UICOMPONENTS m_uiRenderList;
	_WORLDUICOMPONENTS m_worldUiRenderList;
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
		 
	_uint AddToRenderList(_uint sortingLayer, SHARED(CUIComponent) pGC);
	_uint AddToWorldUIRenderList(SHARED(CWorldUIComponent) pGC);
};
END
#endif