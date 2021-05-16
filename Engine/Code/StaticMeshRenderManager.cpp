#include "EngineStdafx.h"
#include "StaticMeshRenderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DeviceManager.h"
#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CStaticMeshRenderManager)

void CStaticMeshRenderManager::Awake(void)
{
	__super::Awake();
}

void CStaticMeshRenderManager::Start(void)
{
}

_uint CStaticMeshRenderManager::FixedUpdate(void)
{
	return NO_EVENT;
}

_uint CStaticMeshRenderManager::Update(void)
{
	GET_DEVICE->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 225),
		1.f, 0);

	return NO_EVENT;
}

_uint CStaticMeshRenderManager::LateUpdate(void)
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

_uint CStaticMeshRenderManager::PreRender(void)
{
	GET_DEVICE->BeginScene();
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	
	return NO_EVENT;
}

_uint CStaticMeshRenderManager::Render(void)
{
	_uint event = NO_EVENT;

	if (m_skyBox != nullptr)
	{
		if (event = m_skyBox->PreRender()) return event;
		if (event = m_skyBox->Render()) return event;
		if (event = m_skyBox->PostRender()) return event;
	}

	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& pGC : m_vRenderList[i])
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
		m_vRenderList[i].clear();
	}

	return event;
}

_uint CStaticMeshRenderManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);
	return NO_EVENT;
}

void CStaticMeshRenderManager::OnDestroy(void)
{
	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
		m_vRenderList[i].clear();
}

void CStaticMeshRenderManager::OnEnable(void)
{
}

void CStaticMeshRenderManager::OnDisable(void)
{
}

_uint CStaticMeshRenderManager::AddToRenderList(ERenderID renderID, SHARED(CStaticMeshRenderComponent) pGC)
{
	if (pGC == nullptr)
		return NULL_PARAMETER;

	if (ERenderID::NumOfRenderID <= renderID)
		return OUT_OF_RANGE;

	m_vRenderList[(_uint)renderID].push_back(pGC);

	return NO_EVENT;
}

_uint CStaticMeshRenderManager::AddToSkyBox(SHARED(CSkyBoxComponent) skyBox)
{
	m_skyBox = skyBox;

	return NO_EVENT;
}