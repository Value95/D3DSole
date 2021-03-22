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
	m_vRenderList.resize(100);
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

	GET_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);


	GET_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); // 알파모드 시작
	GET_DEVICE->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	GET_DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행
	return NO_EVENT;
}

_uint CUIManager::Render(void)
{
	_uint event = NO_EVENT;
	for (_uint i = 0; i < m_vRenderList.size(); ++i)
	{
		for (auto& pGC : m_vRenderList[i])
		{
			if (pGC->GetOwner() != nullptr)
			{
				if (event = pGC->PreRender()) return event;
				if (event = pGC->Render()) return event;
				if (event = pGC->PostRender()) return event;
			}

			pGC.reset();
		}

		m_vRenderList[i].clear();
	}

	return event;
}

_uint CUIManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); // 알파모드 헤제
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);

	return NO_EVENT;
}

void CUIManager::OnDestroy(void)
{
	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
		m_vRenderList[i].clear();
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

	m_vRenderList.at(sortingLayer).emplace_back(pGC);

	return NO_EVENT;
}

