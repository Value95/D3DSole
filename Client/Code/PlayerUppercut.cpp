#include "stdafx.h"
#include "PlayerUppercut.h"
#include "PlayerInfo.h"

#include "MonsterInfo.h"

CPlayerUppercut::CPlayerUppercut(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1, 3, 1), vector3(0, 1.8, -0.7));
}

CPlayerUppercut::~CPlayerUppercut()
{
}

void CPlayerUppercut::Start()
{
	m_player->SetWaponPosNumber(1);
	m_upInit = false;
	init = true;

	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(2.0f);
	m_player->GetAnim()->Set_AnimationSet(1);
	
	m_player->SetUppercutCount(m_player->GetUppercutCount() + 1);
}

void CPlayerUppercut::End()
{
	m_player->SetWaponPosNumber(0);
}

_uint CPlayerUppercut::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
		{
			for (auto& object : col)
			{
				m_player->Attack(object, m_player->GetPlayerInfo()->GetDamageA());
			}
		}
		init = true;
	}
	return NO_EVENT;
}

_uint CPlayerUppercut::Update()
{
	if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
	}

	if (!m_upInit && m_player->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.5416666f)
	{
		m_upInit = true;
		init = false;
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetForce(vector3Up * 5);
	}

	return NO_EVENT;
}

_uint CPlayerUppercut::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerUppercut::OnDestroy(void)
{
}
