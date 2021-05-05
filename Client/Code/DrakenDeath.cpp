#include "stdafx.h"
#include "DrakenDeath.h"
#include "Monster.h"
#include "MonsterInfo.h"

CDrakenDeath::CDrakenDeath(CMonster* monster)
{
	m_monster = monster;
}

CDrakenDeath::~CDrakenDeath()
{
}

void CDrakenDeath::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(13);
}

void CDrakenDeath::End()
{
}

_uint CDrakenDeath::FixedUpdate()
{
	return NO_EVENT;
}

_uint CDrakenDeath::Update()
{
	if (m_monster->GetAnim()->GetAnimValue() == 13 && m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_monster->GetAnim()->Set_AnimationSet(0);
	}

	return NO_EVENT;
}

_uint CDrakenDeath::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenDeath::OnDestroy(void)
{
}



