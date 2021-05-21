#include "stdafx.h"
#include "CameraShake.h"

CCameraShake::CCameraShake()
{
}

CCameraShake::~CCameraShake(void)
{
	OnDestroy();
}

SHARED(Engine::CComponent) CCameraShake::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CCameraShake) pClone(new CCameraShake);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);


	return pClone;
}

void CCameraShake::Awake(void)
{
	__super::Awake();

}

void CCameraShake::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CCameraShake::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CCameraShake::Update(SHARED(CComponent) spThis)
{
	CameraShake();

	return NO_EVENT;
}

_uint CCameraShake::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CCameraShake::OnDestroy(void)
{
}

void CCameraShake::OnEnable(void)
{

}

void CCameraShake::OnDisable(void)
{
}

void CCameraShake::CameraShakeActivation(_float activationTime, _int aMount)
{
	GetOwner()->SetCameraDirPos(m_oldPosition);

	m_oldPosition = GetOwner()->GetCameraDirPos();
	m_activationTime = activationTime;
	m_aMount = aMount;
}

void CCameraShake::CameraShake()
{
	if (m_activationTime > 0)
	{
		m_activationTime = Engine::MathfMax(m_activationTime - deltaTime, 0);

		_float x = (rand() % (m_aMount * 2)) - m_aMount;
		x /= 10;
		_float y = (rand() % (m_aMount * 2)) - m_aMount;
		y /= 10;

		vector3 aMount = m_oldPosition + vector3(x, y, 0);
		GetOwner()->SetCameraDirPos(aMount);
	}
}