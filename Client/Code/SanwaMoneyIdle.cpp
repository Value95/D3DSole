#include "stdafx.h"
#include "Monster.h"
#include "MonsterInfo.h"

#include "SanwaMoneyIdle.h"
#include "SanwaMoneyMaintenance.h"
#include "SanwaMoneyMove.h"
#include "SanwaMoneyAttack1.h"
#include "SanwaMoneyAttack2.h"
#include "SanwaMoneyAttack3.h"
#include "SanwaMoneyAttack4.h"
#include "SanwaMoneyDeath.h"
#include "SanwaMoneyHalfHealth.h"

CSanwaMoneyIdle::CSanwaMoneyIdle(CMonster* monster)
{
	m_monster = monster;
}

CSanwaMoneyIdle::~CSanwaMoneyIdle()
{
}

void CSanwaMoneyIdle::Start()
{
	if (!m_init)
	{
		ReSet();
	}

	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(1);

}

void CSanwaMoneyIdle::End()
{
}

_uint CSanwaMoneyIdle::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSanwaMoneyIdle::Update()
{
	if (Engine::Distance(m_monster->GetOwner()->GetPosition(), m_monster->GetPlayer()->GetPosition()) >= 8.0f)
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_MOVE);
		return NO_EVENT;
	}
	MoveCheck();
	m_monster->GetOwner()->LookAtX(m_monster->GetPlayer()->GetPosition());
	m_monster->GetOwner()->AddRotationY(180);

	return NO_EVENT;
}

_uint CSanwaMoneyIdle::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyIdle::OnDestroy(void)
{
}

void CSanwaMoneyIdle::ReSet()
{
	m_init = true;
	m_monster->GetOwner()->GetComponent<Engine::CColliderComponent>()->SetIsTrigger(false);

	m_monster->GetMonsterFSM().reserve(CMonster::SM_STATE::SM_STATEEND);
	m_monster->GetMonsterInfo()->SetHP(1000);
	m_monster->GetMonsterInfo()->SetMaxHP(1000);
	m_monster->GetMonsterInfo()->SetSpeed(1);

	m_monster->GetMonsterInfo()->AddPatternTime(7);
	m_monster->GetMonsterInfo()->AddDamager(10);

	m_monster->GetMonsterInfo()->AddPatternTime(10);
	m_monster->GetMonsterInfo()->AddDamager(15);


	m_monster->SetMonsterMaintenanceFSM(new CSanwaMoneyMaintenance(m_monster));
	m_monster->AddFSM(new CSanwaMoneyMove(m_monster), CMonster::SM_STATE::SM_MOVE);
	m_monster->AddFSM(new CSanwaMoneyAttack1(m_monster), CMonster::SM_STATE::SM_ATTACK1);
	m_monster->AddFSM(new CSanwaMoneyAttack2(m_monster), CMonster::SM_STATE::SM_ATTACK2);
	m_monster->AddFSM(new CSanwaMoneyAttack3(m_monster), CMonster::SM_STATE::SM_ATTACK3);
	m_monster->AddFSM(new CSanwaMoneyAttack4(m_monster), CMonster::SM_STATE::SM_ATTACK4);
	m_monster->AddFSM(new CSanwaMoneyHalfHealth(m_monster), CMonster::SM_STATE::SM_HALFHEALTH);
	m_monster->AddFSM(new CSanwaMoneyDeath(m_monster), CMonster::SM_STATE::SM_DEATH);
}

void CSanwaMoneyIdle::MoveCheck()
{
	if (m_monster->Collision(m_monster->GetOwner()->GetComponent<Engine::CColliderComponent>()->GetColliders()[0], m_monster->GetOwner()))
	{
		vector3 dir = m_monster->GetPlayer()->GetPosition() - m_monster->GetOwner()->GetPosition();
		D3DXVec3Normalize(&dir, &dir);
		dir.y = 0;
		m_monster->GetPlayer()->AddPosition(dir * m_monster->GetMonsterInfo()->GetSpeed() * deltaTime * 10);
	}
}	



