#include "stdafx.h"
#include "PlayerHit.h"


CPlayerHit::CPlayerHit(CPlayer* player)
{
	m_player = player;
}

CPlayerHit::~CPlayerHit()
{
}

void CPlayerHit::Start()
{
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_player->GetAnim()->Set_AnimationSet(9);
}

void CPlayerHit::End()
{
}

_uint CPlayerHit::FixedUpdate()
{
	return NO_EVENT;
}

_uint CPlayerHit::Update()
{
	if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
	}

	return NO_EVENT;
}

_uint CPlayerHit::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerHit::OnDestroy(void)
{
}
