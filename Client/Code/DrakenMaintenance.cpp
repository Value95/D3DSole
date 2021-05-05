#include "stdafx.h"
#include "DrakenMaintenance.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "DrakenUI.h"

CDrakenMaintenance::CDrakenMaintenance(CMonster* monster)
{
	m_monster = monster;
}

CDrakenMaintenance::~CDrakenMaintenance()
{
}

void CDrakenMaintenance::Start()
{
	// 컴포넌트 생성
	m_drakenUI = new CDrakenUI(m_monster);
	m_drakenUI->Start();
	m_drakenUI->SetMonsterHP(&m_monster->GetMonsterInfo()->GetHP(), &m_monster->GetMonsterInfo()->GetMaxHP());
}

void CDrakenMaintenance::End()
{
}

_uint CDrakenMaintenance::FixedUpdate()
{
	return NO_EVENT;
}

_uint CDrakenMaintenance::Update()
{
	if (m_monster->GetMonsterInfo()->GetHP() <= 0 && m_monster->GetMonsterState() != CMonster::DRAKEN_STATE::DEATH)
	{
		m_monster->ChangeFSM(CMonster::DRAKEN_STATE::DEATH);
	}

	if (m_monster->GetMonsterState() != CMonster::DRAKEN_STATE::DEATH)
	{
		PatternTimer();
		ChangePattern();
	}

	m_drakenUI->Update();

	return NO_EVENT;
}

_uint CDrakenMaintenance::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenMaintenance::OnDestroy(void)
{
	m_drakenUI->OnDestory();
}

void CDrakenMaintenance::PatternTimer()
{
	if (m_monster->GetMonsterState() == CMonster::DRAKEN_STATE::MOVE || m_monster->GetMonsterState() == CMonster::DRAKEN_STATE::IDLE)
	{
		m_monster->GetMonsterInfo()->GetPatternTime()[0] -= deltaTime;
		m_monster->GetMonsterInfo()->GetPatternTime()[1] -= deltaTime;
	}
}

void CDrakenMaintenance::ChangePattern()
{
	if (m_monster->GetMonsterInfo()->GetPatternTime()[0] <= 0)
	{
		m_monster->ChangeFSM(CMonster::DRAKEN_STATE::ATTACK1);
		m_monster->GetMonsterInfo()->GetPatternTime()[0] = m_monster->GetMonsterInfo()->GetPatternTimeMax()[0];
	}
	else if (m_monster->GetMonsterInfo()->GetPatternTime()[1] <= 0)
	{
		m_monster->ChangeFSM(CMonster::DRAKEN_STATE::ATTACK2);
		m_monster->GetMonsterInfo()->GetPatternTime()[1] = m_monster->GetMonsterInfo()->GetPatternTimeMax()[1];
	}
}



