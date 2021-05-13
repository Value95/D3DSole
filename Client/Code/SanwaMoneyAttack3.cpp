#include "stdafx.h"
#include "SanwaMoneyAttack3.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "PlayerInfo.h"

CSanwaMoneyAttack3::CSanwaMoneyAttack3(CMonster* monster)
{
	m_monster = monster;
	collision = Engine::CBoxCollider::Create(vector3(6, 4.5f, 6), vector3(0, 2, -0.5f));
}

CSanwaMoneyAttack3::~CSanwaMoneyAttack3()
{
}

void CSanwaMoneyAttack3::Start()
{
	init = true;
	m_attack = true;
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(3.0f);
	m_monster->GetAnim()->Set_AnimationSet(5);
}

void CSanwaMoneyAttack3::End()
{
	m_monster->GetRigidBody()->SetVelocity(vector3Zero);
}

_uint CSanwaMoneyAttack3::FixedUpdate()
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
					m_monster->GetPlayerCom()->Hit(m_monster->GetMonsterInfo()->GetDamage()[0], 0);
					cout << "플레이어 체력 : " << m_monster->GetPlayerCom()->GetPlayerInfo()->GetHP() << endl;
					init = true;
				}
			}
		}
	}
	
	return NO_EVENT;
}

_uint CSanwaMoneyAttack3::Update()
{
	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_IDLE);
		return NO_EVENT;
	}

	if (m_attack && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.38f)
	{
		init = false;
		m_attack = false;
		m_monster->GetOwner()->LookAtX(m_monster->GetPlayer()->GetPosition());
		m_monster->GetOwner()->AddRotationY(180);
	}

	if (!m_attack && !init)
	{
		Move();
	}

	if (!m_attack && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.93f)
	{
		init = true;
	}

	return NO_EVENT;
}

_uint CSanwaMoneyAttack3::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyAttack3::OnDestroy(void)
{
}

void CSanwaMoneyAttack3::Move()
{
	m_monster->GetOwner()->Translate(vector3Back * deltaTime * 800);
}



