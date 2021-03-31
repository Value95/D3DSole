#include "EngineStdafx.h"
#include "DebugRendeerManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDebugRendeerManager)

void CDebugRendeerManager::Awake(void)
{
	__super::Awake();
}

void CDebugRendeerManager::Start(void)
{

}

_uint CDebugRendeerManager::FixedUpdate(void)
{
	return NO_EVENT;
}

_uint CDebugRendeerManager::Update(void)
{
	return NO_EVENT;
}

_uint CDebugRendeerManager::LateUpdate(void)
{
	return NO_EVENT;
}

_uint CDebugRendeerManager::PreRender(void)
{
	// UI를 렌더할 준비
	GET_DEVICE->BeginScene();

	return NO_EVENT;
}

_uint CDebugRendeerManager::Render(void)
{
	_uint event = NO_EVENT;

	event = BoxRender();
	event = SphereRender();
	event = LineRedner();
	event = TriangleRendeer();

	return event;
}

_uint CDebugRendeerManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	return NO_EVENT;
}

void CDebugRendeerManager::OnDestroy(void)
{
}

void CDebugRendeerManager::OnEnable(void)
{
}

void CDebugRendeerManager::OnDisable(void)
{
}

_uint CDebugRendeerManager::BoxRender()
{
	_uint event = NO_EVENT;

	for (auto& pGC : m_boxRenderList)
	{
		if (pGC->GetOwner() != nullptr)
		{
			if (event = pGC->PreRender()) return event;
			if (event = pGC->Render()) return event;
			if (event = pGC->PostRender()) return event;
		}
		pGC.reset();
	}
	m_boxRenderList.clear();
}

_uint CDebugRendeerManager::SphereRender()
{
	_uint event = NO_EVENT;

	for (auto& pGC : m_sphereRenderList)
	{
		if (pGC->GetOwner() != nullptr)
		{
			if (event = pGC->PreRender()) return event;
			if (event = pGC->Render()) return event;
			if (event = pGC->PostRender()) return event;
		}
		pGC.reset();
	}
	m_sphereRenderList.clear();
}

_uint CDebugRendeerManager::LineRedner()
{
	_uint event = NO_EVENT;

	for (auto& pGC : m_lineRenderList)
	{
		if (pGC->GetOwner() != nullptr)
		{
			if (event = pGC->PreRender()) return event;
			if (event = pGC->Render()) return event;
			if (event = pGC->PostRender()) return event;
		}
		pGC.reset();
	}
	m_lineRenderList.clear();
}

_uint CDebugRendeerManager::TriangleRendeer()
{
	_uint event = NO_EVENT;

	for (auto& pGC : m_triangleRenderList)
	{
		if (pGC->GetOwner() != nullptr)
		{
			if (event = pGC->PreRender()) return event;
			if (event = pGC->Render()) return event;
			if (event = pGC->PostRender()) return event;
		}
		pGC.reset();
	}
	m_triangleRenderList.clear();
}

_uint CDebugRendeerManager::AddToBoxRenderList(SHARED(CBoxComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	m_boxRenderList.emplace_back(pGC);
	return NO_EVENT;
}

_uint CDebugRendeerManager::AddToSphereRenderList(SHARED(CSphereComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	m_sphereRenderList.emplace_back(pGC);
	return NO_EVENT;
}

_uint CDebugRendeerManager::AddToLineRenderList(SHARED(CLineComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	m_lineRenderList.emplace_back(pGC);
	return NO_EVENT;
}

_uint CDebugRendeerManager::AddToTriangleRenderList(SHARED(CTriangleComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	m_triangleRenderList.emplace_back(pGC);
	return NO_EVENT;
}

