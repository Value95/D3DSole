#include "stdafx.h"
#include "..\Header\PlayerMove.h"
#include "PlayerInfo.h"

CPlayerMove::CPlayerMove(CPlayer* player)
{
	m_player = player;
	m_rotation = 0;
	cameraY = 0;
	m_moveCheckDir = 0.8f;

	m_dashCehckTime = 0.2f;
	m_dashCehckTimer = fullTime;

	m_deshOn = false;
}

CPlayerMove::~CPlayerMove()
{
}

void CPlayerMove::Start()
{
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);

	if(!Desh())
		WW = false, AA = false, SS = false, DD = false;
	else
		m_player->GetAnim()->GetAnimCtrl()->SetSpeed(3.0f);


	m_speed = 0;
	W = false, A = false, S = false, D = false;
}

// Start에서 bool값키기 이동끝나고 다음 이동들어올때 특정 bool이켜져있따면 대쉬
void CPlayerMove::End()
{
	m_deshOn = false;
	m_dashCehckTimer = fullTime;
}

_uint CPlayerMove::FixedUpdate()
{

	return NO_EVENT;
}

_uint CPlayerMove::Update()
{
	if (DeshActivation()) return NO_EVENT;

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
	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 99)
		return false;

	m_speed = m_player->GetPlayerInfo()->GetSpeed();

	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		m_speed *= 0.6f;

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Forward)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Forward * deltaTime * m_speed);
		W = true;
		WW = true, AA = false, SS = false, DD = false;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Back)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Back * deltaTime * m_speed);
		S = true;
		WW = false, AA = false, SS = true, DD = false;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Left)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Left * deltaTime * m_speed);
		A = true;
		WW = false, AA = true, SS = false, DD = false;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Right)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Right * deltaTime * m_speed);
		D = true;
		WW = false, AA = false, SS = false, DD = true;
	}

	Rotation();

	if (W || A || S || D) // 이동했을 경우
	{
		if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() != 108 &&
			m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		{
			m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(108);
		}

		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
		m_player->GetOwner()->SetRotationY(m_rotation - 180 + cameraY);
	}
	else if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() != 99 &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() != 101) // 이동하지 않았고 점프하지 않았을경우
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		return true;
	}

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
		WW = false, AA = false, SS = false, DD = false;
		return true;
	}
	return false;
}

bool CPlayerMove::DeshAttack()
{
	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		m_player->ChangeFSM(CPlayer::STATE::DESHATTACK);
		WW = false, AA = false, SS = false, DD = false;
		return true;
	}
	return false;
}

bool CPlayerMove::Jump()
{
	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() &&
		m_player->GetAnim()->GetAnimValue() != 101)
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(100);
	}

	if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() && Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE)) // 점프시작애니
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(101);

		vector3 translate = vector3(0, 1, 0);

		if (W || A || S || D)
			translate.z = -0.3f;

		m_player->GetOwner()->OutTranslate(translate);
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->AddForce(translate * m_player->GetPlayerInfo()->GetJumpPower());

		return false;
	}

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 101 &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd()) // 점프중 애니
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(100);
		return false;
	}

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 100 &&
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck()) // 점프 끝 애니
	{
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(99);
		return false;
	}

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimValue() == 99 &&
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		WW = false, AA = false, SS = false, DD = false;
		return true;
	}
}

bool CPlayerMove::Desh()
{
	_float T = fullTime - m_dashCehckTimer;
	if (T > m_dashCehckTime)
		return false;

	if (WW && Engine::CInputManager::GetInstance()->KeyPress(KEY_W))
	{
		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
		m_player->GetOwner()->SetRotationY(180 + cameraY);

		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(105);
		m_deshOn = true;
		return true;
	}
	else if (SS && Engine::CInputManager::GetInstance()->KeyPress(KEY_S))
	{
		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
		m_player->GetOwner()->SetRotationY(180 + cameraY);

		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(104);
		m_deshOn = true;
		return true;
	}
	else if (AA && Engine::CInputManager::GetInstance()->KeyPress(KEY_A))
	{
		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
		m_player->GetOwner()->SetRotationY(180 + cameraY);

		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(102);
		m_deshOn = true;
		return true;
	}
	else if (DD && Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
		m_player->GetOwner()->SetRotationY(180 + cameraY);

		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(103);
		m_deshOn = true;
		return true;
	}
	return false;
}

bool CPlayerMove::DeshActivation()
{
	if (m_deshOn)
	{
		if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
		{
			WW = false, AA = false, SS = false, DD = false;
			m_player->ChangeFSM(CPlayer::STATE::IDLE);
		}

		if (DeshAttack()) return true;

		if (WW && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Forward)))
		{
			m_player->GetOwner()->Translate(vector3Back * deltaTime * m_player->GetPlayerInfo()->GetDeshSpeed());
		}
		else if (SS && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Back)))
		{
			m_player->GetOwner()->Translate(vector3Forward * deltaTime * m_player->GetPlayerInfo()->GetDeshSpeed());
		}
		else if (AA && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Left)))
		{
			m_player->GetOwner()->Translate(vector3Right * deltaTime * m_player->GetPlayerInfo()->GetDeshSpeed());
		}
		else if (DD && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Right)))
		{
			m_player->GetOwner()->Translate(vector3Left * deltaTime * m_player->GetPlayerInfo()->GetDeshSpeed());
		}

		return true;
	}

	return false;
}

bool CPlayerMove::MoveCheck(vector3 dir)
{
	vector3 orgine = m_player->GetOwner()->GetPosition();
	Engine::CGameObject* obj = Engine::CRaycast::BoxRayCast(orgine, dir, m_moveCheckDir, L"Collider");
	if (obj != nullptr)
	{
		return false;
	}
	return true;
}
