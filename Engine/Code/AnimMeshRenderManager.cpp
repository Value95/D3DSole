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
		for (auto& it = m_vRenderList[i].begin(); it != m_vRenderList[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
				it = m_vRenderList[i].erase(it);
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

	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
	{
		if ((_uint)ERenderID::WireFrame == i)
		{
			GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{
			GET_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		for (auto& pGC : m_vRenderList[i])
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
		m_vRenderList[i].clear();
	}

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
		m_vRenderList[i].clear();
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

	m_vRenderList[(_uint)renderID].push_back(pGC);

	return NO_EVENT;
}

