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

	//T = 4;
	//m_player->GetAnim()->Set_AnimationSet(T);

	if (m_player->GetAnim()->GetAnimValue() != 53)
		m_player->GetAnim()->Set_AnimationSet(55);
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
	/*if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd() && T <= 50)
	{
		T--;
		cout << T << endl;
		if (T == 32	)
			T = 55;
		m_player->GetAnim()->Set_AnimationSet(T);
	}*/

	if (m_player->GetAnim()->GetAnimValue() == 53 && m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->GetAnim()->Set_AnimationSet(55);
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
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(50);
	}

		

	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
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



