#include "stdafx.h"
#include "DrakenHit.h"
#include "Monster.h"
#include "MonsterInfo.h"

CDrakenHit::CDrakenHit(CMonster* monster)
{
	m_monster = monster;
}

CDrakenHit::~CDrakenHit()
{
}

void CDrakenHit::Start()
{
}

void CDrakenHit::End()
{
}

_uint CDrakenHit::FixedUpdate()
{
	return NO_EVENT;
}

_uint CDrakenHit::Update()
{


	return NO_EVENT;
}

_uint CDrakenHit::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenHit::OnDestroy(void)
{
}



