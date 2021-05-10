#include "stdafx.h"
#include "Monster.h"
#include "SoldierSpearMaintenance.h"
#include "MonsterInfo.h"



CSoldierSpearMaintenance::CSoldierSpearMaintenance(CMonster* monster)
{
	m_monster = monster;
}

CSoldierSpearMaintenance::~CSoldierSpearMaintenance()
{
}

void CSoldierSpearMaintenance::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(16);
}

void CSoldierSpearMaintenance::End()
{
}

_uint CSoldierSpearMaintenance::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSoldierSpearMaintenance::Update()
{
	
	return NO_EVENT;
}

_uint CSoldierSpearMaintenance::LateUpdate()
{

	return NO_EVENT;
}

void CSoldierSpearMaintenance::OnDestroy(void)
{
}



