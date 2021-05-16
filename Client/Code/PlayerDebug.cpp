#include "stdafx.h"
#include "PlayerDebug.h"


CPlayerDebug::CPlayerDebug(CPlayer* player)
{
	m_player = player;
}

CPlayerDebug::~CPlayerDebug()
{
}

void CPlayerDebug::Start()
{
	m_player->SetWaponPosNumber(0);
	m_animCount = 0;
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_player->GetAnim()->Set_AnimationSet(m_animCount);
}

void CPlayerDebug::End()
{
}

_uint CPlayerDebug::FixedUpdate()
{
	return NO_EVENT;
}

_uint CPlayerDebug::Update()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_LBUTTON))
	{
		m_animCount++;
		m_player->GetAnim()->Set_AnimationSet(m_animCount);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_RBUTTON))
	{
		m_animCount--;
		m_player->GetAnim()->Set_AnimationSet(m_animCount);
		cout << m_animCount << endl;
	}

	return NO_EVENT;
}

_uint CPlayerDebug::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerDebug::OnDestroy(void)
{
}
