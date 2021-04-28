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
	//m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(54);

	m_speed = 0;
	W = false, A = false, S = false, D = false;
}

void CPlayerMove::End()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(53);
	W = false, A = false, S = false, D = false;
}

_uint CPlayerMove::FixedUpdate()
{

	return NO_EVENT;
}

_uint CPlayerMove::Update()
{
	W = false, A = false, S = false, D = false;

	if (Jump()) return NO_EVENT;
	if (Move())  return NO_EVENT;
	if (Attack()) return NO_EVENT;
	
	return NO_EVENT;
}

_uint CPlayerMove::LateUpdate()
{

	return NO_EVENT;
}

void CPlayerMove::OnDestroy(void)
{
}

bool CPlayerMove::Move()
{
	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 49)
		return false;

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

	Rotation();

	if (W || A || S || D) // 이동했을 경우
	{
		if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() != 54 &&
			m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		{
			m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(54);
		}

		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
	}
	else if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() != 49 &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() != 51) // 이동하지 않았고 점프하지 않았을경우
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		return true;
	}

	m_player->GetOwner()->SetRotationY(m_rotation - 180 + cameraY);
	return false;
}

void CPlayerMove::Rotation()
{
	if (W)
	{
		if (A)
		{
			m_rotation = 315;
		}
		else if (D)
		{
			m_rotation = 45;
		}
		else
		{
			m_rotation = 0;
		}
	}
	else if (S)
	{
		if (A)
		{
			m_rotation = 225;
		}
		else if (D)
		{
			m_rotation = 125;
		}
		else
		{
			m_rotation = 180;
		}
	}
	else if (A)
	{
		m_rotation = 270;
	}
	else if (D)
	{
		m_rotation = 90;
	}
}

bool CPlayerMove::Attack()
{
	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		m_player->ChangeFSM(CPlayer::STATE::ATTACK);
		return true;
	}
	return false;
}

bool CPlayerMove::Jump()
{
	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(50);
	}

	if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() && Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE)) // 점프시작애니
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(51);

		vector3 translate = vector3(0, 1, 0);

		if (W || A || S || D)
			translate.z = -0.3f;

		m_player->GetOwner()->OutTranslate(translate);
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->AddForce(translate * m_player->GetPlayerInfo()->GetJumpPower());

		return false;
	}

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 51 &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd()) // 점프중 애니
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(50);
		return false;
	}

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 50 &&
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck()) // 점프 끝 애니
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(49);
		return false;
	}

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 49 &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		return true;
	}
}
