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
	return _uint();
}

_uint CPlayerDeath::Update()
{
	return _uint();
}

_uint CPlayerDeath::LateUpdate()
{
	return _uint();
}

void CPlayerDeath::OnDestroy(void)
{
}
