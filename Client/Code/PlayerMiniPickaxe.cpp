#include "stdafx.h"
#include "PlayerMiniPickaxe.h"
#include "PlayerInfo.h"

CPlayerMiniPickaxe::CPlayerMiniPickaxe(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1, 4, 3), vector3(0, 0.9, -1));
	m_miniGock = Engine::GET_CUR_SCENE->FindObjectByName(L"MiniGock");
}

CPlayerMiniPickaxe::~CPlayerMiniPickaxe()
{
}

void CPlayerMiniPickaxe::Start()
{
	init = false;
}

void CPlayerMiniPickaxe::End()
{
	m_miniGock->SetIsEnabled(false);
	m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetGravity(-9.807f);
}

_uint CPlayerMiniPickaxe::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
		{
			for (auto& object : col)
			{
				init = true;
				m_miniGock->SetIsEnabled(true);
				m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetVelocity(vector3Zero);
				m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetGravity(-0.5f);
				m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
				m_player->GetAnim()->Set_AnimationSet(14);
			}
		}
	}

	if (!init)
	{
		m_player->ChangeFSM(m_player->GetPlayerOldState());
	}
	return NO_EVENT;
}

_uint CPlayerMiniPickaxe::Update()
{
	if (Engine::CInputManager::GetInstance()->KeyUp(KEY_F))
	{
		m_player->ChangeFSM(CPlayer::STATE::MOVE);
		return true;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE))
	{
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetForce(vector3Up * m_player->GetPlayerInfo()->GetJumpPower());
		m_player->GetAnim()->Set_AnimationSet(6);
		m_player->ChangeFSM(CPlayer::STATE::MOVE);
	}

	
	return NO_EVENT;
}

_uint CPlayerMiniPickaxe::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerMiniPickaxe::OnDestroy(void)
{
}
