#include "EngineStdafx.h"
#include "ParticleSystem.h"
#include "ObjectFactory.h"

USING(Engine)
CParticleSystem::CParticleSystem()
{
}

CParticleSystem::~CParticleSystem(void)
{
}

SHARED(CComponent) CParticleSystem::MakeClone(CGameObject * pObject)
{
	SHARED(CParticleSystem) pClone(new CParticleSystem);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);
	pClone->SetIsAwaked(m_isAwaked);
	pClone->SetParticleKey(m_particleKey);
	pClone->SetLifeTime(m_lifeTime);
	pClone->SetEnableCout(m_enableCount);
	pClone->SetSpawnPosition(m_spawnPosition);
	return pClone;
}

void CParticleSystem::Awake()
{
	__super::Awake();
}

void CParticleSystem::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	for (int i = 0; i < m_enableCount * 5; i++)
	{
		m_offObject.emplace_back(CObjectFactory::GetInstance()->AddClone(L"Particle", m_particleKey, true));
	}
}

_uint CParticleSystem::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CParticleSystem::Update(SHARED(CComponent) spThis)
{
	DeathObject();

	return _uint();
}

_uint CParticleSystem::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CParticleSystem::OnDestroy(void)
{
}

void CParticleSystem::OnEnable(void)
{
}

void CParticleSystem::OnDisable(void)
{
}

void CParticleSystem::Init(std::wstring keyValue, _float lifeTime, _int enableCount, vector3 spawnPosition)
{
	m_lifeTime = lifeTime;
	m_enableCount = enableCount;
	m_spawnPosition = spawnPosition;
	m_particleKey = keyValue;
}

void CParticleSystem::play()
{
	// 오브젝트 활성화
	for (int i = 0; i < m_enableCount; i++)
	{
		if (m_offObject.size() <= m_enableCount * 4)
		{
			m_offObject.insert(m_offObject.begin(), CObjectFactory::GetInstance()->AddClone(L"Particle", m_particleKey, true));
		}

		particleObj obj;
		obj.Push(m_offObject.back(), m_lifeTime);
		obj.object->SetPosition(GetOwner()->GetPosition() + m_spawnPosition);
		obj.object->SetIsEnabled(true);
		m_offObject.pop_back();
		m_onObject.emplace_back(obj);
		m_curCount++;
	}
}

void CParticleSystem::DeathObject()
{
	int index = 0;
	for (auto iter = m_onObject.begin(); iter != m_onObject.end(); iter++ , index++)
	{
		if ((*iter).lifeTime <= 0)
		{
			iter->object->SetIsEnabled(false);
			m_offObject.emplace_back(iter->object);
			m_onObject.erase(iter);
			iter = m_onObject.begin();
			m_curCount--;

			if (m_onObject.empty())
				return;
		}
		else
		{
			(*iter).lifeTime -= deltaTime;
		}
	}
}
