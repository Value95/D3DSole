#include "stdafx.h"
#include "PlayerRoll.h"
#include "PlayerInfo.h"

CPlayerRoll::CPlayerRoll(CPlayer* player)
{
	m_player = player;
}

CPlayerRoll::~CPlayerRoll()
{
}

void CPlayerRoll::Start()
{
	m_player->GetPlayerInfo()->SetDushGague(0);
	m_player->SetWaponPosNumber(0);
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_player->GetAnim()->Set_AnimationSet(4);
}

void CPlayerRoll::End()
{
}

_uint CPlayerRoll::FixedUpdate()
{
	return NO_EVENT;
}

_uint CPlayerRoll::Update()
{
	if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		return NO_EVENT;
	}

	if (m_player->GetAnim()->GetAnimCtrl()->CurentTime() <= 0.869565f && m_player->MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Forward), 1.2f))
		m_player->GetOwner()->Translate(vector3Back * deltaTime * m_player->GetPlayerInfo()->GetRollSpeed());

	return NO_EVENT;
}

_uint CPlayerRoll::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerRoll::OnDestroy(void)
{
}
