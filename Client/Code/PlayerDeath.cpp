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
	m_player->GetAnim()->Set_AnimationSet(3);
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
	if (m_player->GetAnim()->GetAnimValue() == 3 && m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->GetAnim()->Set_AnimationSet(2);
	}

	return NO_EVENT;
}

_uint CPlayerDeath::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerDeath::OnDestroy(void)
{
}
