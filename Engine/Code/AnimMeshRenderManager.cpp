#include "EngineStdafx.h"
#include "AnimMeshRenderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DeviceManager.h"
#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CAnimMeshRenderManager)

void CAnimMeshRenderManager::Awake(void)
{
	__super::Awake();
}

void CAnimMeshRenderManager::Start(void)
{
}

_uint CAnimMeshRenderManager::FixedUpdate(void)
{
	return NO_EVENT;
}

_uint CAnimMeshRenderManager::Update(void)
{
	return NO_EVENT;
}

_uint CAnimMeshRenderManager::LateUpdate(void)
{
	for (int i = 0; i < (_int)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& it = m_animRenderList[i].begin(); it != m_animRenderList[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
				it = m_animRenderList[i].erase(it);
			else
				++it;
		}
	}

	return NO_EVENT;
}

_uint CAnimMeshRenderManager::PreRender(void)
{
	GET_DEVICE->BeginScene();
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	return NO_EVENT;
}

_uint CAnimMeshRenderManager::Render(void)
{
	_uint event = NO_EVENT;

	event = AnimMeshRender();
	event = EffectMeshRender();

	return event;
}

_uint CAnimMeshRenderManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	return NO_EVENT;
}

void CAnimMeshRenderManager::OnDestroy(void)
{
	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
		m_animRenderList[i].clear();
}

void CAnimMeshRenderManager::OnEnable(void)
{
}

void CAnimMeshRenderManager::OnDisable(void)
{
}

_uint CAnimMeshRenderManager::AddToRenderList(ERenderID renderID, SHARED(CAnimMeshRenderComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	if (ERenderID::NumOfRenderID <= renderID)
		return OUT_OF_RANGE;

	m_animRenderList[(_uint)renderID].emplace_back(pGC);

	return NO_EVENT;
}

_uint CAnimMeshRenderManager::AddToEffectRenderList(SHARED(CEffectComponent) effectComPonent)
{
	if (effectComPonent == nullptr)
		return NULL_PARAMETER;

	m_effectRenderList.emplace_back(effectComPonent);
	return _uint();
}

_uint CAnimMeshRenderManager::AnimMeshRender()
{
	_uint event = NO_EVENT;

	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& pGC : m_animRenderList[i])
		{
			if (pGC->GetOwner() != nullptr)
			{
				//if (GET_MAIN_CAM->IsInFrustum(pGC->GetOwner()->GetPosition()))
				{
					if (event = pGC->PreRender()) return event;
					if (event = pGC->Render()) return event;
					if (event = pGC->PostRender()) return event;
				}
			}

			pGC.reset();
		}
		m_animRenderList[i].clear();
	}
	return event;
}

_uint CAnimMeshRenderManager::EffectMeshRender()
{
	_uint event = NO_EVENT;

	GET_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); // 알파모드 시작
	GET_DEVICE->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	GET_DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행

	for (auto& pGC : m_effectRenderList)
	{
		if (pGC->GetOwner() != nullptr)
		{
			if (GET_MAIN_CAM->IsInFrustum(pGC->GetOwner()->GetPosition()))
			{
				if (event = pGC->PreRender()) return event;
				if (event = pGC->Render()) return event;
				if (event = pGC->PostRender()) return event;
			}
		}

		pGC.reset();
	}
	m_effectRenderList.clear();

	GET_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); // 알파모드 헤제

	return event;
}
