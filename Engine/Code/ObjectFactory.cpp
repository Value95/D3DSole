#include "EngineStdafx.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CObjectFactory)

void CObjectFactory::Awake(void)
{
	__super::Awake();
}

void CObjectFactory::Start(void)
{
}

void CObjectFactory::OnDestroy(void)
{
	m_mCurPrototypes.clear();
	m_mStaticPrototypes.clear();
}

void CObjectFactory::OnEnable(void)
{
}

void CObjectFactory::OnDisable(void)
{
}

HRESULT CObjectFactory::AddPrototype(SHARED(CGameObject) pPrototype)
{
	if (pPrototype == nullptr)
		return E_FAIL;

	_PROTOTYPES* pCurPrototypes = nullptr;

	if (pPrototype->GetIsStatic())
		pCurPrototypes = &m_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;

	auto& it = pCurPrototypes->find(pPrototype->GetObjectKey());
	if (it == pCurPrototypes->end())
		(*pCurPrototypes)[pPrototype->GetObjectKey()] = pPrototype;

	return S_OK;
}

SHARED(CGameObject) CObjectFactory::AddClone(const std::wstring & layerKey,
											 const std::wstring & objectKey,
											 _bool isStatic)
{
	_PROTOTYPES* pCurPrototypes = nullptr;

	if (isStatic)
		pCurPrototypes = &m_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;


	auto iter_find_prototype = pCurPrototypes->find(objectKey);
	if (pCurPrototypes->end() == iter_find_prototype)
	{
		MSG_BOX(__FILE__, (objectKey + L" is not found in AddClone").c_str());
		return nullptr;
	}

	SHARED(CGameObject) pClone = iter_find_prototype->second->MakeClone();
	if (pClone == nullptr)
	{
		MSG_BOX(__FILE__, (objectKey + L" failed to make clone in AddClone").c_str());
		return nullptr;
	}
	
	auto iter_find_layer = GET_CUR_SCENE->GetLayers().find(layerKey);
	if (iter_find_layer == GET_CUR_SCENE->GetLayers().end())
	{
		MSG_BOX(__FILE__, (objectKey + L" failed to find layer in AddClone").c_str());
		return nullptr;
	}
	GET_CUR_SCENE->GetLayers()[layerKey]->GetGameObjects().push_back(pClone);
	GET_CUR_SCENE->AddObjectCount(1);
	return pClone;
}

SHARED(CGameObject) CObjectFactory::AddClone(const std::wstring & layerKey, const std::wstring & objectKey, SHARED(CScene) scene, _bool isStatic)
{
	_PROTOTYPES* pCurPrototypes = nullptr;

	if (isStatic)
		pCurPrototypes = &m_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;


	auto iter_find_prototype = pCurPrototypes->find(objectKey);
	if (pCurPrototypes->end() == iter_find_prototype)
	{
		MSG_BOX(__FILE__, (objectKey + L" is not found in AddClone").c_str());
		return nullptr;
	}

	SHARED(CGameObject) pClone = iter_find_prototype->second->MakeClone();
	if (pClone == nullptr)
	{
		MSG_BOX(__FILE__, (objectKey + L" failed to make clone in AddClone").c_str());
		return nullptr;
	}

	auto iter_find_layer = scene->GetLayers().find(layerKey);
	if (iter_find_layer == scene->GetLayers().end())
	{
		MSG_BOX(__FILE__, (objectKey + L" failed to find layer in AddClone").c_str());
		return nullptr;
	}
	scene->GetLayers()[layerKey]->GetGameObjects().push_back(pClone);
	scene->AddObjectCount(1);
	return pClone;
}

void CObjectFactory::ClearCurPrototype(void)
{
	for (auto& prototype : m_mCurPrototypes)
	{
		prototype.second.reset();
	}
	m_mCurPrototypes.clear();
}
