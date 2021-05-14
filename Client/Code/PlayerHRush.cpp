#include "stdafx.h"
#include "PlayerRush.h"
#include "PlayerInfo.h"

CPlayerRush::CPlayerRush(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(0.6, 1.6, 2), vector3(0, 0.9, -1));
}

CPlayerRush::~CPlayerRush()
{
}

void CPlayerRush::Start()
{
	m_player->SetWaponPosNumber(0);
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_player->GetAnim()->Set_AnimationSet(3);
	m_player->GetRigidBody()->SetVelocity(vector3Zero);
}

void CPlayerRush::End()
{
}

_uint CPlayerRush::FixedUpdate()
{
	std::vector<Engine::CGameObject*> col;
	if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
	{
		for (auto& object : col)
		{
			m_player->Attack(object, m_player->GetPlayerInfo()->GetDamageRush());
			m_player->Hit(m_player->GetPlayerInfo()->GetDamageRush(), 0);
			m_player->GetOwner()->Translate(vector3Forward * deltaTime * (m_player->GetPlayerInfo()->GetSpeedRush() *2));
			m_player->GetRigidBody()->TranslateForce((vector3Forward + vector3Up) * 4);
			m_player->ChangeFSM(CPlayer::STATE::IDLE);
		}
	}

	return NO_EVENT;
}

_uint CPlayerRush::Update()
{
	Move();

	return NO_EVENT;
}

_uint CPlayerRush::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerRush::OnDestroy(void)
{
}

void CPlayerRush::Move()
{
	m_player->GetOwner()->Translate(vector3Back * deltaTime * m_player->GetPlayerInfo()->GetSpeedRush());
}
