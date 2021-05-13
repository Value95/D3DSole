#include "stdafx.h"
#include "SanwaMoneyDeath.h"
#include "Monster.h"
#include "MonsterInfo.h"

CSanwaMoneyDeath::CSanwaMoneyDeath(CMonster* monster)
{
	m_monster = monster;
}

CSanwaMoneyDeath::~CSanwaMoneyDeath()
{
}

void CSanwaMoneyDeath::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(4);
}

void CSanwaMoneyDeath::End()
{
}

_uint CSanwaMoneyDeath::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSanwaMoneyDeath::Update()
{
	if (m_monster->GetAnim()->GetAnimValue() == 4 && m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_monster->GetAnim()->Set_AnimationSet(3);
	}

	return NO_EVENT;
}

_uint CSanwaMoneyDeath::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyDeath::OnDestroy(void)
{
}



