#include "stdafx.h"
#include "ScarecrowIdle.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "PlayerInfo.h"
#include "ScarecrowMaintenance.h"

CScarecrowIdle::CScarecrowIdle(CMonster* monster)
{
	m_monster = monster;
}

CScarecrowIdle::~CScarecrowIdle()
{
}

void CScarecrowIdle::Start()
{
	if (!m_init)
	{
		m_init = true;

		m_monster->GetMonsterInfo()->SetHP(1000);
		m_monster->GetMonsterInfo()->SetMaxHP(1000);
		m_pastHP = m_monster->GetMonsterInfo()->GetHP();
		m_monster->SetMonsterMaintenanceFSM(new CScarecrowMaintenance(m_monster));
		m_resetTimeMax = 5;
		m_resetTime = m_resetTimeMax;
	}
}

void CScarecrowIdle::End()
{
}

_uint CScarecrowIdle::FixedUpdate()
{
	return NO_EVENT;
}

_uint CScarecrowIdle::Update()
{


	return NO_EVENT;
}

_uint CScarecrowIdle::LateUpdate()
{
	if (m_pastHP == m_monster->GetMonsterInfo()->GetHP())
	{
		m_resetTime -= deltaTime;

		if (m_resetTime <= 0)
		{
			m_monster->GetMonsterInfo()->SetHP(m_monster->GetMonsterInfo()->GetMaxHP());
		}
	}
	else
	{
		m_resetTime = m_resetTimeMax;
	}

	if (m_monster->GetHitCheck())
	{
		m_monster->SetHitCheck(false);
		m_pastHP = m_monster->GetMonsterInfo()->GetHP();
		m_monster->GetPlayerCom()->GetPlayerInfo()->SetGold(m_monster->GetPlayerCom()->GetPlayerInfo()->GetGold() + 100);
	}

	return NO_EVENT;
}

void CScarecrowIdle::OnDestroy(void)
{
}



