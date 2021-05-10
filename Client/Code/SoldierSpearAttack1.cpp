#include "stdafx.h"
#include "Monster.h"
#include "SoldierSpearAttack1.h"
#include "MonsterInfo.h"



CSoldierSpearAttack1::CSoldierSpearAttack1(CMonster* monster)
{
	m_monster = monster;
}

CSoldierSpearAttack1::~CSoldierSpearAttack1()
{
}

void CSoldierSpearAttack1::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(16);
}

void CSoldierSpearAttack1::End()
{
}

_uint CSoldierSpearAttack1::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSoldierSpearAttack1::Update()
{
	
	return NO_EVENT;
}

_uint CSoldierSpearAttack1::LateUpdate()
{

	return NO_EVENT;
}

void CSoldierSpearAttack1::OnDestroy(void)
{
}



