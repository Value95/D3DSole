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
	W = false, A = false, S = false, D = false;
}

void CPlayerMove::End()
{
	W = false, A = false, S = false, D = false;
}

_uint CPlayerMove::FixedUpdate()
{

	return _uint();
}

_uint CPlayerMove::Update()
{
	W = false, A = false, S = false, D = false;

	Move();
	Jump();
	Attack();
	
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
	// 나의 회전값빼기 - 상대의값이 = 양수라면
	// 음수라면 
	if (W)
	{
		if (A)
		{
			if(m_rotation - 315 >= 0) // 양수 시계
				m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 315);
			else if(m_rotation - 315 < 0) // 음수 반시계
				m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 315);
		}
		else if (D)
		{
			if (m_rotation <= 45)
			{
				m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 45);
			}
			else if (m_rotation > 45)
			{
				// 최단경로가 반시계인지 시계인지판단
				// 반시계이면 -
				// 시계이면 +
				// 다만 315 -> 45가되기위해서는 시계이나 +하면 절대 될수가없다.

				m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 45);
			}
		}
		else
		{
			if (m_rotation <= 0)
				m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 0);
			else if (m_rotation > 0)
				m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 0);
		}
	}
	else if (S)
	{
		if (A)
		{
			if (m_rotation <= 225)
				m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 225);
			else if (m_rotation > 225)
				m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 225);
		}
		else if (D)
		{
			if (m_rotation <= 125)
				m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 125);
			else if (m_rotation > 125)
				m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 125);
		}
		else
		{
			if (m_rotation <= 180)
				m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 180);
			else if (m_rotation > 180)
				m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 180);
		}
	}
	else if (A)
	{
		if (m_rotation <= 270)
			m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 270);
		else if (m_rotation > 270)
			m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 270);
	}
	else if (D)
	{
		if (m_rotation <= 90)
			m_rotation = Engine::MathfMin(m_rotation + (m_player->GetPlayerInfo()->GetRotationSpeed()), 90);
		else if (m_rotation > 90)
			m_rotation = Engine::MathfMax(m_rotation - (m_player->GetPlayerInfo()->GetRotationSpeed()), 90);
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

		if (W || A || S || D)
 			translate.z = -0.3f;

		m_player->GetOwner()->OutTranslate(translate);
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->AddForce(translate * m_player->GetPlayerInfo()->GetJumpPower());
	}
}
