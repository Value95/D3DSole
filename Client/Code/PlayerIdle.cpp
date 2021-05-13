#include "stdafx.h"
#include "PlayerIdle.h"
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
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_player->GetAnim()->Set_AnimationSet(8);

	//m_player->ChangeFSM(CPlayer::STATE::DEBUGMODE);
}

void CPlayerIdle::End()
{
}

_uint CPlayerIdle::FixedUpdate()
{
	if(m_player->GetIdleLook())
		return NO_EVENT;


	return NO_EVENT;
}

_uint CPlayerIdle::Update()
{
	if (m_player->GetIdleLook())
	{
		if (m_player->GetAnim()->GetAnimValue() != 8)
		{
			m_player->GetAnim()->Set_AnimationSet(8);
		}

		return NO_EVENT;
	}
	
	if (Move()) return NO_EVENT;
	if (Attack()) return NO_EVENT;
	if (Rush()) return NO_EVENT;

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F))
	{
		m_player->ChangeFSM(CPlayer::STATE::MINIPICKAXE);
		return true;
	}

	m_player->UpperCutCountReset();

	return NO_EVENT;
}

_uint CPlayerIdle::LateUpdate()
{
	if (m_player->GetIdleLook())
		return NO_EVENT;

	return NO_EVENT;
}

void CPlayerIdle::OnDestroy(void)
{
}

_bool CPlayerIdle::Move()
{
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_A) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_S) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_D) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE))
	{
		m_player->ChangeFSM(CPlayer::STATE::MOVE);
		return true;
	}
	return false;
}

_bool CPlayerIdle::Attack()
{
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_LBUTTON))
	{
		m_player->ChangeFSM(CPlayer::STATE::ATTACK);
		return true;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_RBUTTON))
	{
		if(m_player->GetUppercutCount() != m_player->GetUppercutMaxCount())
			m_player->ChangeFSM(CPlayer::STATE::UPPERCUT);
		return true;
	}
	return false;
}

_bool CPlayerIdle::Roll()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_SHIFT))
	{
		m_player->ChangeFSM(CPlayer::STATE::ROLL);
		return true;
	}
	return false;
}

_bool CPlayerIdle::Rush()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_CTRL))
	{
		m_player->ChangeFSM(CPlayer::STATE::RUSH);
		return true;
	}
	return false;
}



