#include "stdafx.h"
#include "Monster.h"
#include "SoldierSpearMove.h"
#include "MonsterInfo.h"



CSoldierSpearMove::CSoldierSpearMove(CMonster* monster)
{
	m_monster = monster;
}

CSoldierSpearMove::~CSoldierSpearMove()
{
}

void CSoldierSpearMove::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(16);
}

void CSoldierSpearMove::End()
{
}

_uint CSoldierSpearMove::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSoldierSpearMove::Update()
{
	
	return NO_EVENT;
}

_uint CSoldierSpearMove::LateUpdate()
{

	return NO_EVENT;
}

void CSoldierSpearMove::OnDestroy(void)
{
}



