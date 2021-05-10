#include "stdafx.h"
#include "Monster.h"
#include "MonsterInfo.h"

#include "SoldierSpearMaintenance.h"
#include "SoldierSpearIdle.h"
#include "SoldierSpearMove.h"
#include "SoldierSpearAttack1.h"
#include "SoldierSpearHit.h"
#include "SoldierSpearDeath.h"

CSoldierSpearIdle::CSoldierSpearIdle(CMonster* monster)
{
	m_monster = monster;
}

CSoldierSpearIdle::~CSoldierSpearIdle()
{
}

void CSoldierSpearIdle::Start()
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

		m_monster->SetMonsterMaintenanceFSM(new CSoldierSpearMaintenance(m_monster));
		m_monster->AddFSM(new CSoldierSpearMove(m_monster));
		m_monster->AddFSM(new CSoldierSpearAttack1(m_monster));
		m_monster->AddFSM(new CSoldierSpearHit(m_monster));
		m_monster->AddFSM(new CSoldierSpearDeath(m_monster));

		m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
		m_monster->GetAnim()->Set_AnimationSet(16);

		return;
	}

	m_animCount = 0;
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(m_animCount);
}

void CSoldierSpearIdle::End()
{
}

_uint CSoldierSpearIdle::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSoldierSpearIdle::Update()
{
	m_monster->GetOwner()->LookAtX(m_monster->GetPlayer()->GetPosition());
	m_monster->GetOwner()->AddRotationY(180);

	return NO_EVENT;
}

_uint CSoldierSpearIdle::LateUpdate()
{

	return NO_EVENT;
}

void CSoldierSpearIdle::OnDestroy(void)
{
}



