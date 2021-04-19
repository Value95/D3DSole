#include "stdafx.h"
#include "..\Header\PlayerMove.h"


CPlayerMove::CPlayerMove(CPlayer* player)
{
	m_player = player;
	m_rotation = 0;
	m_rotationSpeed = 50;
	cameraY = 0;
}

CPlayerMove::~CPlayerMove()
{
}

void CPlayerMove::Start()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(0);
}

void CPlayerMove::End()
{
}

_uint CPlayerMove::FixedUpdate()
{

	return _uint();
}

_uint CPlayerMove::Update()
{
	Attack();
	Move();
	
	return _uint();
}

_uint CPlayerMove::LateUpdate()
{

	return _uint();
}

void CPlayerMove::OnDestroy(void)
{
}

void CPlayerMove::Move()
{
	bool W = false, A = false, S = false, D = false;

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Forward * deltaTime * 50);
		W = true;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Back * deltaTime * 50);
		S = true;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Left * deltaTime * 50);
		A = true;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Right * deltaTime * 50);
		D = true;
	}

	if (W)
	{ // -45 , 45
		if (A)
			m_rotation = Engine::MathfMax(m_rotation - (m_rotationSpeed), -45);
		else if (D)
			m_rotation = Engine::MathfMin(m_rotation + (m_rotationSpeed), 45);
		else if (W)
			m_rotation = Engine::MathfMin(m_rotation + (m_rotationSpeed), 0);
	}
	else if (S)
	{ // -225 , -135 , -180
		if (A)
			m_rotation = Engine::MathfMax(m_rotation - (m_rotationSpeed), -135);
		else if (D)
			m_rotation = Engine::MathfMax(m_rotation - (m_rotationSpeed), -225);
		else if (S)
			m_rotation = Engine::MathfMax(m_rotation - (m_rotationSpeed), -180);
	}
	else if (D)
	{ // 90
		m_rotation = Engine::MathfMin(m_rotation + (m_rotationSpeed ), 90);
	}
	else if (A)
	{ // -90
		m_rotation = Engine::MathfMax(m_rotation - (m_rotationSpeed), -90);
	}


	if (W || A || S || D)
		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
	else
		m_player->ChangeFSM(CPlayer::STATE::IDLE);

	m_player->GetOwner()->SetRotationY(m_rotation - 180 + cameraY);
}

void CPlayerMove::Attack()
{
	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		m_player->ChangeFSM(CPlayer::STATE::ATTACK);
	}
}
