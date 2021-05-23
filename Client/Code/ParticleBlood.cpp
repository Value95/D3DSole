#include "stdafx.h"
#include "ParticleBlood.h"

CParticleBlood::CParticleBlood()
{
}

CParticleBlood::~CParticleBlood(void)
{
	OnDestroy();
}

SHARED(Engine::CComponent) CParticleBlood::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CParticleBlood) pClone(new CParticleBlood);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);
	pClone->SetForce(m_force);

	return pClone;
}

void CParticleBlood::Awake(void)
{
	__super::Awake();
}

void CParticleBlood::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CParticleBlood::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CParticleBlood::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CParticleBlood::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CParticleBlood::OnDestroy(void)
{
}

void CParticleBlood::OnEnable(void)
{
	vector3 force = vector3(m_force.x - (rand() % (int)(m_force.x * 2)), rand() % (int)m_force.y, m_force.z - (rand() % (int)(m_force.z * 2)));
	GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetVelocity(vector3Zero);
	GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->AddForce(force);
}

void CParticleBlood::OnDisable(void)
{
}