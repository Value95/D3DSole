#include "stdafx.h"
#include "SanwaMoneyAttack2.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "PlayerInfo.h"

CSanwaMoneyAttack2::CSanwaMoneyAttack2(CMonster* monster)
{
	m_monster = monster;
	collision = Engine::CBoxCollider::Create(vector3(3, 3, 3), vector3(0, 2, -6));
}

CSanwaMoneyAttack2::~CSanwaMoneyAttack2()
{
}

void CSanwaMoneyAttack2::Start()
{
	init = true;
	m_attack = true;

	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(2.0f);
	m_monster->GetAnim()->Set_AnimationSet(9);
}

void CSanwaMoneyAttack2::End()
{
}

_uint CSanwaMoneyAttack2::FixedUpdate()
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
					m_monster->GetPlayerCom()->Hit(m_monster->GetMonsterInfo()->GetDamage()[0], 1);
					cout << "플레이어 체력 : " << m_monster->GetPlayerCom()->GetPlayerInfo()->GetHP() << endl;
				}
			}
		}
	}
	init = true;
	return NO_EVENT;
}

_uint CSanwaMoneyAttack2::Update()
{
	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_IDLE);
		return NO_EVENT;
	}

	if (m_attack && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.6f)
	{
		init = false;
		m_attack = false;
	}

	return NO_EVENT;
}

_uint CSanwaMoneyAttack2::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyAttack2::OnDestroy(void)
{
}



