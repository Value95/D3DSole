#include "stdafx.h"
#include "DrakenAttack1.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "PlayerInfo.h"

CDrakenAttack1::CDrakenAttack1(CMonster* monster)
{
	m_monster = monster;
	collision = Engine::CBoxCollider::Create(vector3(4, 8, 7), vector3(0, 3.6f, -3));
}

CDrakenAttack1::~CDrakenAttack1()
{
}

void CDrakenAttack1::Start()
{
	init = true;
	m_attack = true;
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(4);
}

void CDrakenAttack1::End()
{
}

_uint CDrakenAttack1::FixedUpdate()
{
	if (!init && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.7f && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() <= 0.75f)
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
					
				}
			}
		}
	}
	init = true;
	return NO_EVENT;
}

_uint CDrakenAttack1::Update()
{
	vector3 createPos = m_monster->GetOwner()->ReturnPosTranslate(vector3(0, 3.6f, -3));

	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		if (m_monster->GetAnim()->GetAnimValue() == 3)
		{
			m_monster->ChangeFSM(CMonster::DRAKEN_STATE::MOVE);
			return NO_EVENT;
		}

		m_monster->GetAnim()->Set_AnimationSet(3);
	}

	if (m_attack && m_monster->GetAnim()->GetAnimValue() == 4 && m_monster->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.5f)
	{
		init = false;
		m_attack = false;
	}


	return NO_EVENT;
}

_uint CDrakenAttack1::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenAttack1::OnDestroy(void)
{
}



