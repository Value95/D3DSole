#include "stdafx.h"
#include "SanwaMoneyMaintenance.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "SanwaMoneyUI.h"

CSanwaMoneyMaintenance::CSanwaMoneyMaintenance(CMonster* monster)
{
	m_monster = monster;
	m_sanwaMouneyUI = new CSanwaMoneyUI(m_monster);
}

CSanwaMoneyMaintenance::~CSanwaMoneyMaintenance()
{
}

void CSanwaMoneyMaintenance::Start()
{
	m_halfHealthCheck = true;
	m_sanwaMouneyUI->Start();
	m_sanwaMouneyUI->DateInput(&m_monster->GetMonsterInfo()->GetHP(), &m_monster->GetMonsterInfo()->GetMaxHP());
}

void CSanwaMoneyMaintenance::End()
{
}

_uint CSanwaMoneyMaintenance::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSanwaMoneyMaintenance::Update()
{
	Death();

	HalfHealth();
	m_sanwaMouneyUI->Update();

	/*if (m_monster->GetMonsterState() != CMonster::SM_STATE::SM_DEATH)
	{
		PatternTimer();
		ChangePattern();
	}*/

	Debug();

	return NO_EVENT;
}

_uint CSanwaMoneyMaintenance::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyMaintenance::OnDestroy(void)
{
}

void CSanwaMoneyMaintenance::Death()
{
	if (m_monster->GetMonsterInfo()->GetHP() <= 0 && m_monster->GetMonsterState() != CMonster::SM_STATE::SM_DEATH)
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_DEATH);
	}
}

void CSanwaMoneyMaintenance::PatternTimer()
{
	if (m_monster->GetMonsterState() == CMonster::SM_STATE::SM_MOVE || m_monster->GetMonsterState() == CMonster::SM_STATE::SM_IDLE)
	{
		m_monster->GetMonsterInfo()->GetPatternTime()[0] -= deltaTime;
		//m_monster->GetMonsterInfo()->GetPatternTime()[1] -= deltaTime;
	}
}

void CSanwaMoneyMaintenance::ChangePattern()
{
	if (m_monster->GetMonsterInfo()->GetPatternTime()[0] <= 0)
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_ATTACK1);
		m_monster->GetMonsterInfo()->GetPatternTime()[0] = m_monster->GetMonsterInfo()->GetPatternTimeMax()[0];
	}
	else if (m_monster->GetMonsterInfo()->GetPatternTime()[1] <= 0)
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_ATTACK2);
		m_monster->GetMonsterInfo()->GetPatternTime()[1] = m_monster->GetMonsterInfo()->GetPatternTimeMax()[1];
	}
}

void CSanwaMoneyMaintenance::HalfHealth()
{
	if (m_halfHealthCheck && m_monster->GetMonsterInfo()->GetHP() <= m_monster->GetMonsterInfo()->GetMaxHP() * 0.5f)
	{
		m_halfHealthCheck = false;
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_HALFHEALTH);
	}
}

void CSanwaMoneyMaintenance::Debug()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_ATTACK1);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_ATTACK2);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_ATTACK3);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_4))
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_HALFHEALTH);
	}
}



