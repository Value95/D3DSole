#include "stdafx.h"
#include "..\Header\PlayerDeath.h"


CPlayerDeath::CPlayerDeath(CPlayer* player)
{
	m_player = player;
}

CPlayerDeath::~CPlayerDeath()
{
}

void CPlayerDeath::Start()
{
}

void CPlayerDeath::End()
{
}

_uint CPlayerDeath::FixedUpdate()
{
	return NO_EVENT;
}

_uint CPlayerDeath::Update()
{
	return NO_EVENT;
}

_uint CPlayerDeath::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerDeath::OnDestroy(void)
{
}
