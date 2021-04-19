#include "stdafx.h"
#include "..\Header\PlayerMove.h"
#include "PlayerInfo.h"

CPlayerMove::CPlayerMove(CPlayer* player)
{
	m_player = player;
	m_rotation = 0;
	cameraY = 0;
}

CPlayerMove::~CPlayerMove()
{
}

void CPlayerMove::Start()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(0);
	m_speed = 0;
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
	Jump();
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
	m_speed = m_player->GetPlayerInfo()->GetSpeed();

	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		m_speed *= 0.6f;

	bool W = false, A = false, S = false, D = false;

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Forward * deltaTime * m_speed);
		W = true;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Back * deltaTime * m_speed);
		S = true;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Left * deltaTime * m_speed);
		A = true;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Right * deltaTime * m_speed);
		D = true;
	}

	if (W)
	{ // -45 , 45
		if (A)
			m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), -45);
		else if (D)
			m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 45);
		else if (W)
			m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 0);
	}
	else if (S)
	{ // -225 , -135 , -180
		if (A)
			m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), -135);
		else if (D)
			m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), -225);
		else if (S)
			m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), -180);
	}
	else if (D)
	{ // 90
		m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 90);
	}
	else if (A)
	{ // -90
		m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), -90);
	}


	if (W || A || S || D)
		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
	else if(m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
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

void CPlayerMove::Jump()
{
	if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() && Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE))
	{
		vector3 translate = vector3(0, 1, 0);

		if (m_speed != 0)
			translate.z = -0.8f;

		m_player->GetOwner()->OutTranslate(translate);
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->AddForce(translate * m_player->GetPlayerInfo()->GetJumpPower());
	}
}
