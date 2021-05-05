#include "stdafx.h"
#include "Monster.h"
#include "MonsterInfo.h"

#include "DrakenIdle.h"
#include "DrakenMaintenance.h"
#include "DrakenMove.h"
#include "DrakenAttack1.h"
#include "DrakenAttack2.h"
#include "DrakenHit.h"
#include "DrakenDeath.h"

CDrakenIdle::CDrakenIdle(CMonster* monster)
{
	m_monster = monster;
}

CDrakenIdle::~CDrakenIdle()
{
}

void CDrakenIdle::Start()
{
	if (!m_init)
	{
		m_init = true;
		m_monster->GetOwner()->GetComponent<Engine::CColliderComponent>()->SetIsTrigger(false);

		m_monster->GetMonsterFSM().reserve(CMonster::DRAKEN_STATE::STATEEND);
		m_monster->GetMonsterInfo()->SetHP(1000);
		m_monster->GetMonsterInfo()->SetMaxHP(1000);
		m_monster->GetMonsterInfo()->SetSpeed(4);
		m_monster->GetMonsterInfo()->AddPatternTime(7);
		m_monster->GetMonsterInfo()->AddPatternTime(10);
		m_monster->GetMonsterInfo()->AddDamager(10);
		m_monster->GetMonsterInfo()->AddDamager(15);

		m_monster->SetMonsterMaintenanceFSM(new CDrakenMaintenance(m_monster));
		m_monster->AddFSM(new CDrakenMove(m_monster));
		m_monster->AddFSM(new CDrakenAttack1(m_monster));
		m_monster->AddFSM(new CDrakenAttack2(m_monster));
		m_monster->AddFSM(new CDrakenHit(m_monster));
		m_monster->AddFSM(new CDrakenDeath(m_monster));
	}

	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(16);
}
// 2 -> 1 -> 14 -> 16 연출때의 모습
void CDrakenIdle::End()
{
}

_uint CDrakenIdle::FixedUpdate()
{
	return NO_EVENT;
}

_uint CDrakenIdle::Update()
{
	m_monster->GetOwner()->LookAt(m_monster->GetPlayer()->GetPosition());
	m_monster->GetOwner()->AddRotationY(180);

	if (Engine::Distance(m_monster->GetOwner()->GetPosition(), m_monster->GetPlayer()->GetPosition()) > 6.0f)
	{
		m_monster->ChangeFSM(CMonster::DRAKEN_STATE::MOVE);
	}


	return NO_EVENT;
}

_uint CDrakenIdle::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenIdle::OnDestroy(void)
{
}



