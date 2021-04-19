#include "stdafx.h"
#include "..\Header\PlayerIdle.h"
#include "Player.h"

CPlayerIdle::CPlayerIdle(CPlayer* player)
{
	m_player = player;
}

CPlayerIdle::~CPlayerIdle()
{
}

void CPlayerIdle::Start()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(1);
}

void CPlayerIdle::End()
{
}

_uint CPlayerIdle::FixedUpdate()
{
	return _uint();
}

_uint CPlayerIdle::Update()
{
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_A) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_S) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		m_player->ChangeFSM(CPlayer::STATE::MOVE);
	}

	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		m_player->ChangeFSM(CPlayer::STATE::ATTACK);
	}

	return _uint();
}

_uint CPlayerIdle::LateUpdate()
{
	return _uint();
}

void CPlayerIdle::OnDestroy(void)
{
}



