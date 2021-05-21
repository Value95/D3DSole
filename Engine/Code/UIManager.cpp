#include "EngineStdafx.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CUIManager)

void CUIManager::Awake(void)
{
	__super::Awake();
}

void CUIManager::Start(void)
{
	m_uiRenderList.resize(10);
}

_uint CUIManager::FixedUpdate(void)
{
	return NO_EVENT;
}

_uint CUIManager::Update(void)
{
	return NO_EVENT;
}

_uint CUIManager::LateUpdate(void)
{
	return NO_EVENT;
}

_uint CUIManager::PreRender(void)
{
	GET_DEVICE->BeginScene();

	return NO_EVENT;
}

_uint CUIManager::Render(void)
{
	_uint event = NO_EVENT;
	for (_uint i = 0; i < m_uiRenderList.size(); ++i)
	{
		for (auto& pGC : m_uiRenderList[i])
		{
			if (pGC->GetOwner() != nullptr)
			{
				if (event = pGC->PreRender()) return event;
				if (event = pGC->Render()) return event;
				if (event = pGC->PostRender()) return event;
			}

			pGC.reset();
		}

		m_uiRenderList[i].clear();
	}

	for (auto& pGC : m_worldUiRenderList)
	{
		if (pGC->GetOwner() != nullptr)
		{
			if (event = pGC->PreRender()) return event;
			if (event = pGC->Render()) return event;
			if (event = pGC->PostRender()) return event;
		}

		pGC.reset();
	}


	m_worldUiRenderList.clear();

	return event;
}

_uint CUIManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);

	return NO_EVENT;
}

void CUIManager::OnDestroy(void)
{
	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
		m_uiRenderList[i].clear();

	m_worldUiRenderList.clear();
}

void CUIManager::OnEnable(void)
{
}

void CUIManager::OnDisable(void)
{
}

_uint CUIManager::AddToRenderList(_uint sortingLayer, SHARED(CUIComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	m_uiRenderList.at(sortingLayer).emplace_back(pGC);

	return NO_EVENT;
}

_uint CUIManager::AddToWorldUIRenderList(SHARED(CWorldUIComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	m_worldUiRenderList.emplace_back(pGC);

	return NO_EVENT;

}

