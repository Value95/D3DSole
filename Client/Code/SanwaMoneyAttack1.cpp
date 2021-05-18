#include "stdafx.h"
#include "SanwaMoneyAttack1.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "PlayerInfo.h"

CSanwaMoneyAttack1::CSanwaMoneyAttack1(CMonster* monster)
{
	m_monster = monster;
	collision = Engine::CBoxCollider::Create(vector3(3, 3, 3), vector3(0, 2, -4));
}

CSanwaMoneyAttack1::~CSanwaMoneyAttack1()
{
}

void CSanwaMoneyAttack1::Start()
{
	init = true;
	m_attack = true;
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(2.0f);
	m_monster->GetAnim()->Set_AnimationSet(8);
}

void CSanwaMoneyAttack1::End()
{
	m_monster->GetRigidBody()->SetVelocity(vector3Zero);
}

_uint CSanwaMoneyAttack1::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_monster->GetOwner(), col))
		{
			for (auto& object : col)
			{
				if (object->GetName() == L"Player")
				{
					m_monster->GetPlayerCom()->Hit(m_monster->GetPlayerCom()->GetPlayerInfo()->GetHpMax(), 0);
					init = true;
				}
			}
		}
	}
	
	return NO_EVENT;
}

_uint CSanwaMoneyAttack1::Update()
{
	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_IDLE);
		return NO_EVENT;
	}

	if (m_attack && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.53636f)
	{
		init = false;
		m_attack = false;
		m_monster->GetOwner()->LookAtX(m_monster->GetPlayer()->GetPosition());
		m_monster->GetOwner()->AddRotationY(180);
		
	}

	if (!m_attack && !init && m_monster->MoveCheck(vector3Forward, 2.8f))
	{
		Move();
	}

	if (!m_attack && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.72f)
	{
		init = true;
	}
	
	return NO_EVENT;
}

_uint CSanwaMoneyAttack1::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyAttack1::OnDestroy(void)
{
}

void CSanwaMoneyAttack1::Move()
{
	m_monster->GetOwner()->Translate(vector3Back * deltaTime * 1000);
}
