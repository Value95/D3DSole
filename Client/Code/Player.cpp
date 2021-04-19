#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"

#include "FSM.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"
#include "PlayerDeath.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer(void)
{
}

SHARED(Engine::CComponent) CPlayer::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CPlayer) pClone(new CPlayer);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CPlayer::Awake(void)
{
	__super::Awake();
	state = new CPlayerState();
}


void CPlayer::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	FSMCreate();
}

_uint CPlayer::FixedUpdate(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->FixedUpdate();
	return NO_EVENT;
}

_uint CPlayer::Update(SHARED(CComponent) spThis)
{

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	{
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationY(5);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraY(Engine::GET_MAIN_CAM->GetOwner()->GetCameraY() + 5);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_E))
	{
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationY(-5);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraY(Engine::GET_MAIN_CAM->GetOwner()->GetCameraY() - 5);
	}


	m_playerFSM[m_playerState]->Update();

	return NO_EVENT;
}

_uint CPlayer::LateUpdate(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->LateUpdate();

	return NO_EVENT;
}

void CPlayer::OnDestroy(void)
{
}

void CPlayer::OnEnable(void)
{
}

void CPlayer::OnDisable(void)
{
}

void CPlayer::ChangeFSM(STATE state)
{
	m_playerFSM[m_playerState]->End();
	m_playerState = state;
	m_playerFSM[m_playerState]->Start();
}

void CPlayer::FSMCreate()
{
	m_playerFSM[STATE::IDLE] = new CPlayerIdle(this);
	m_playerFSM[STATE::IDLE]->Start();

	m_playerFSM[STATE::MOVE] = new CPlayerMove(this);
	m_playerFSM[STATE::ATTACK] = new CPlayerAttack(this);
	m_playerFSM[STATE::DEATH] = new CPlayerDeath(this);
}