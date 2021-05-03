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


	return NO_EVENT;
}

_uint CDrakenDeath::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenDeath::OnDestroy(void)
{
}



