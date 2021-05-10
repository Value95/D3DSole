#include "stdafx.h"
#include "Monster.h"
#include "SoldierSpearHit.h"
#include "MonsterInfo.h"



CSoldierSpearHit::CSoldierSpearHit(CMonster* monster)
{
	m_monster = monster;
}

CSoldierSpearHit::~CSoldierSpearHit()
{
}

void CSoldierSpearHit::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(16);
}

void CSoldierSpearHit::End()
{
}

_uint CSoldierSpearHit::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSoldierSpearHit::Update()
{
	
	return NO_EVENT;
}

_uint CSoldierSpearHit::LateUpdate()
{

	return NO_EVENT;
}

void CSoldierSpearHit::OnDestroy(void)
{
}



