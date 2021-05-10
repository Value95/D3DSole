#include "stdafx.h"
#include "PlayerAttack2.h"
#include "PlayerInfo.h"


CPlayerAttack2::CPlayerAttack2(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(4, 4, 4), vector3(0, 0, 0));

}

CPlayerAttack2::~CPlayerAttack2()
{
}

void CPlayerAttack2::Start()
{
	m_attackAnimCount = 0;
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(3.0f);
	m_player->GetAnim()->Set_AnimationSet(54);
	m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->TranslateForce(vector3Up * 8);
}

void CPlayerAttack2::End()
{
}

_uint CPlayerAttack2::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
		{
			for (auto& object : col)
			{
				m_player->Attack(object, m_player->GetPlayerInfo()->GetDamageD());
				m_player->UpAttack(object,0.8f);
			}
		}
		init = true;
	}

	return NO_EVENT;
}

_uint CPlayerAttack2::Update()
{
	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_attackAnimCount++;
		if (m_attackAnimCount == 10)
		{
			m_player->ChangeFSM(CPlayer::STATE::IDLE);
			return NO_EVENT;
		}
		else
		{
			m_player->GetAnim()->Set_AnimationSet(54);
			init = false;
		}
	}

	return NO_EVENT;
}

_uint CPlayerAttack2::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerAttack2::OnDestroy(void)
{
}
