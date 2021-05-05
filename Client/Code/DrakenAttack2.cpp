#include "stdafx.h"
#include "DrakenAttack2.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "PlayerInfo.h"

CDrakenAttack2::CDrakenAttack2(CMonster* monster)
{
	m_monster = monster;
	collision = Engine::CBoxCollider::Create(vector3(4, 8, 7), vector3(0, 3.6f, -3));
}

CDrakenAttack2::~CDrakenAttack2()
{
}

void CDrakenAttack2::Start()
{
	init = true;
	memset(m_attack, true, sizeof(m_attack));

	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(6);
}

void CDrakenAttack2::End()
{
}

_uint CDrakenAttack2::FixedUpdate()
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
					m_monster->GetPlayerCom()->Hit(m_monster->GetMonsterInfo()->GetDamage()[1], 1);
					cout << "플레이어 체력 : " << m_monster->GetPlayerCom()->GetPlayerInfo()->GetHP() << endl;
				}
			}
		}
	}
	init = true;
	return NO_EVENT;
}

_uint CDrakenAttack2::Update()
{
	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		if (m_monster->GetAnim()->GetAnimValue() == 5)
		{
			m_monster->ChangeFSM(CMonster::DRAKEN_STATE::MOVE);
			return NO_EVENT;
		}

		m_monster->GetAnim()->Set_AnimationSet(5);
	}

	if (m_monster->GetAnim()->GetAnimValue() == 6)
	{
		if (m_attack[0] && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.35f)
		{
			m_attack[0] = false;
			init = false;
		}
		if (m_attack[1] && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.75f)
		{
			m_attack[1] = false;
			init = false;
		}
	}

	return NO_EVENT;
}

_uint CDrakenAttack2::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenAttack2::OnDestroy(void)
{
}



