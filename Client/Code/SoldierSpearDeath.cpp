#include "stdafx.h"
#include "Monster.h"
#include "SoldierSpearDeath.h"
#include "MonsterInfo.h"



CSoldierSpearDeath::CSoldierSpearDeath(CMonster* monster)
{
	m_monster = monster;
}

CSoldierSpearDeath::~CSoldierSpearDeath()
{
}

void CSoldierSpearDeath::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(16);
}

void CSoldierSpearDeath::End()
{
}

_uint CSoldierSpearDeath::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSoldierSpearDeath::Update()
{
	
	return NO_EVENT;
}

_uint CSoldierSpearDeath::LateUpdate()
{

	return NO_EVENT;
}

void CSoldierSpearDeath::OnDestroy(void)
{
}



