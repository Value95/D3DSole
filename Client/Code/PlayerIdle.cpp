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
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);

	if (m_player->GetAnim()->GetAnimValue() == 9)
		m_player->GetAnim()->Set_AnimationSet(37);
	else
		m_player->GetAnim()->Set_AnimationSet(110);
}

void CPlayerIdle::End()
{
}

_uint CPlayerIdle::FixedUpdate()
{
	return NO_EVENT;
}

_uint CPlayerIdle::Update()
{
	if (m_player->GetAnim()->GetAnimValue() == 37 && m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->GetAnim()->Set_AnimationSet(110);
	}


	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_A) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_S) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_D) ||
		Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE))
	{
		m_player->ChangeFSM(CPlayer::STATE::MOVE);
	}

	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
	{
		m_player->ChangeFSM(CPlayer::STATE::MOVE);
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(100);
	}

	if (Engine::IMKEY_DOWN(KEY_LBUTTON))
	{
		m_player->ChangeFSM(CPlayer::STATE::ATTACK);
	}

	return NO_EVENT;
}

_uint CPlayerIdle::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerIdle::OnDestroy(void)
{
}



