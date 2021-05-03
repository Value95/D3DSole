#include "stdafx.h"
#include "DrakenMaintenance.h"
#include "Monster.h"
#include "MonsterInfo.h"

CDrakenMaintenance::CDrakenMaintenance(CMonster* monster)
{
	m_monster = monster;
}

CDrakenMaintenance::~CDrakenMaintenance()
{
}

void CDrakenMaintenance::Start()
{
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
	PatternTimer();
	ChangePattern();
	return NO_EVENT;
}

_uint CDrakenMaintenance::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenMaintenance::OnDestroy(void)
{
}

void CDrakenMaintenance::PatternTimer()
{
	if (m_monster->GetMonsterState() == CMonster::DRAKEN_STATE::MOVE)
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
		//m_monster->ChangeFSM(CMonster::DRAKEN_STATE::ATTACK2);
		m_monster->GetMonsterInfo()->GetPatternTime()[1] = m_monster->GetMonsterInfo()->GetPatternTimeMax()[1];
	}
}



