#include "stdafx.h"
#include "..\Header\PlayerAttack.h"
#include "PlayerInfo.h"

#include "MonsterInfo.h"

CPlayerAttack::CPlayerAttack(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1, 4, 3), vector3(0, 0.9,-1));
}

CPlayerAttack::~CPlayerAttack()
{
	OnDestroy();
}

void CPlayerAttack::Start()
{
	m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
	m_player->GetOwner()->AddRotationY(-180);

	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(1);

	init = false;
	
	m_nextAttack = false;

	if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
	{
		m_attackAnimNumber = 90;
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(m_attackAnimNumber);
	}
	else
	{
		m_attackAnimNumber = 15;
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(m_attackAnimNumber);
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->TranslateForce((vector3Up + vector3Back) * 3);
	}
}

void CPlayerAttack::End()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(1);
}

_uint CPlayerAttack::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
		{
			for (auto& object : col)
			{
				m_player->Attack(object);
				init = true;
			}
		}
	}
	return NO_EVENT;
}

_uint CPlayerAttack::Update()
{
	if (Engine::IMKEY_DOWN(KEY_LBUTTON))
	{
		m_nextAttack = true;
	}

	if(m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		GroundAttack();
	else
		JumpAttack();


	return NO_EVENT;
}

_uint CPlayerAttack::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerAttack::OnDestroy(void)
{
	SAFE_DELETE(collision);

}

void CPlayerAttack::GroundAttack()
{
	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		if (!m_nextAttack || m_attackAnimNumber == 83)
		{
			m_player->ChangeFSM(CPlayer::STATE::IDLE);
		}
		else if (m_nextAttack)
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
			m_player->GetOwner()->AddRotationY(-180);

			m_nextAttack = false;

			if (m_attackAnimNumber <= 84)
				m_attackAnimNumber--;
			else
			{
				m_attackAnimNumber -= 2;
				m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->TranslateForce(vector3Back * 3);
			}

			init = false;
			m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(m_attackAnimNumber);
		}
	}

}

void CPlayerAttack::JumpAttack()
{
	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
	}
}
