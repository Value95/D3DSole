#include "EngineStdafx.h"
#include "GameObject.h"
#include "Layer.h"
#include "ObjectFactory.h"
USING(Engine)

CGameObject::CGameObject(void)
{
}

CGameObject::CGameObject(const CGameObject & other)
	: m_isClone(true)
{
}

CGameObject::~CGameObject(void)
{
	OnDestroy();
}

SHARED(CGameObject) CGameObject::Create(std::wstring layerKey, 
										std::wstring objectKey, 
										_bool isStatic)
{
	SHARED(CGameObject) pGameObject(new CGameObject, SmartDeleter<CGameObject>);
	pGameObject->SetLayerKey(layerKey);
	pGameObject->SetObjectKey(objectKey);
	pGameObject->SetIsStatic(isStatic);
	pGameObject->Awake();

	return pGameObject;
}


SHARED(CGameObject) CGameObject::MakeClone(void)
{
	SHARED(CGameObject) pGameObject(Create(m_layerKey, m_objectKey, m_isStatic));
	pGameObject->SetIsClone(true);
	pGameObject->SetName(m_name);
	pGameObject->SetPosition(m_position);
	pGameObject->SetRotation(m_rotation);
	pGameObject->SetScale(m_scale);
	pGameObject->SetIsEnabled(m_isEnabled);
	pGameObject->Awake();

	for (auto& component : m_mComponents)
	{
		pGameObject->AddComponentToClone(component.second, component.first);
	}

	return pGameObject;
}



void CGameObject::Awake(void)
{
	m_isAwaked = true;
}

void CGameObject::Start(void)
{
	m_isStarted = true;
}

_uint CGameObject::FixedUpdate(void)
{
	_uint event = NO_EVENT;

	if (!m_isEnabled)
		return event;

	TransformUpdate();

	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false || component.second->GetIsEnabled() == false)
			continue;

		if (component.second->GetIsStarted() && component.second->GetIsAwaked())
		{
			if (event = component.second->FixedUpdate(component.second))
				return event;
		}
	}

	return event;
}

_uint CGameObject::Update(void)
{
	_uint event = NO_EVENT;

	for (auto& component : m_mComponents)
	{
		if (m_mComponents.empty())
			continue;

		if (component.second->GetIsStarted() == false)
			component.second->Start(component.second);

		if (component.second->GetIsEnabled() == false)
			continue;

		if (event = component.second->Update(component.second))
			return event;
	}
	
	return event;
}

_uint CGameObject::LateUpdate(void)
{
	_uint event = NO_EVENT;

	if (!m_isEnabled)
		return event;

	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false || component.second->GetIsEnabled() == false)
			continue;

		if (event = component.second->LateUpdate(component.second))
			return event;
	}



	return event;
}


void CGameObject::OnDestroy(void)
{
	for (auto& component : m_mComponents)
		component.second->SetOwner(nullptr);

	m_mComponents.clear();
}

void CGameObject::OnEnable(void)
{
	for (auto& component : m_mComponents)
	{
		component.second->OnEnable();
	}
}


void CGameObject::OnDisable(void)
{
	for (auto& component : m_mComponents)
	{
		component.second->OnDisable();
	}
}