#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer(void)
{
}

SHARED(Engine::CComponent) CPlayer::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CPlayer) pClone(new CPlayer);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);


	return pClone;
}

void CPlayer::Awake(void)
{
	__super::Awake();
}


void CPlayer::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CPlayer::FixedUpdate(SHARED(CComponent) spThis)
{

	return NO_EVENT;
}

_uint CPlayer::Update(SHARED(CComponent) spThis)
{
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W))
	{
		GetOwner()->Translate(vector3Forward * deltaTime * 50);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S))
	{
		GetOwner()->Translate(vector3Back * deltaTime * 50);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A))
	{
		GetOwner()->Translate(vector3Left * deltaTime * 50);
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		GetOwner()->Translate(vector3Right * deltaTime * 50);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_1))
	{
		GetOwner()->AddRotationX(5 * deltaTime * 50);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_2))
	{
		GetOwner()->AddRotationY(5 * deltaTime * 50);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_3))
	{
		GetOwner()->AddRotationZ(5 * deltaTime * 50);
	}
	return NO_EVENT;
}

_uint CPlayer::LateUpdate(SHARED(CComponent) spThis)
{

	return NO_EVENT;
}

void CPlayer::OnDestroy(void)
{
}

void CPlayer::OnEnable(void)
{
	std::cout << "Player OnEnable" << endl;
}

void CPlayer::OnDisable(void)
{
	std::cout << "Player OnDisable" << endl;
}
