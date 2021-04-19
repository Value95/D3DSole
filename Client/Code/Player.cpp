#include "stdafx.h"
#include "Player.h"
#include "PlayerInfo.h"
#include "SceneManager.h"

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
	m_playerInfo = new CPlayerInfo();

	RECT rect;

	GetClientRect(Engine::CWndApp::GetInstance()->GetHWnd(), &rect);

	POINT p1, p2;
	p1.x = rect.left;
	p1.y = rect.top;
	p2.x = rect.right;
	p2.y = rect.bottom;

	ClientToScreen(Engine::CWndApp::GetInstance()->GetHWnd(), &p1);
	ClientToScreen(Engine::CWndApp::GetInstance()->GetHWnd(), &p2);

	rect.left = p1.x;
	rect.top = p1.y;
	rect.right = p2.x;
	rect.bottom = p2.y;

	m_centerPt.x = (p1.x + p2.x) / 2;
	m_centerPt.y = (p1.y + p2.y) / 2;
	SetCursorPos(m_centerPt.x, m_centerPt.y);
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
	Sight();
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

void CPlayer::Sight()
{
	POINT curPt;
	GetCursorPos(&curPt);
	SetCursorPos(m_centerPt.x, m_centerPt.y);

	// 카메라 회전
	if (curPt.y < m_centerPt.y) // mouse up look
	{
		_float angleY = deltaTime * (abs(curPt.y - m_centerPt.y) * m_playerInfo->GetMouseSensitivity());
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationX(-1 * angleY);
	}

	if (curPt.y > m_centerPt.y) // mouse down look
	{
		_float angleY = deltaTime * (abs(curPt.y - m_centerPt.y) * m_playerInfo->GetMouseSensitivity());
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationX(angleY);
	}

	if (curPt.x < m_centerPt.x) // mouse left look
	{
		_float angleX = (deltaTime * (abs(curPt.x - m_centerPt.x) * m_playerInfo->GetMouseSensitivity())) * -1;
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationY(angleX);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraY(Engine::GET_MAIN_CAM->GetOwner()->GetCameraY() + angleX);
	}

	if (curPt.x > m_centerPt.x) // mouse right look
	{
		_float angleX = deltaTime * (abs(curPt.x - m_centerPt.x) * m_playerInfo->GetMouseSensitivity());
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationY(angleX);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraY(Engine::GET_MAIN_CAM->GetOwner()->GetCameraY() + angleX);
	}

}
