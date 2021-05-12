#include "stdafx.h"
#include "PlayerMove.h"
#include "PlayerInfo.h"

CPlayerMove::CPlayerMove(CPlayer* player)
{
	m_player = player;
	m_rotation = 0;
	cameraY = 0;
	m_moveCheckDir = 0.8f;

}

CPlayerMove::~CPlayerMove()
{
}

void CPlayerMove::Start()
{
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);

	m_speed = 0;
	W = false, A = false, S = false, D = false;
}

// Start에서 bool값키기 이동끝나고 다음 이동들어올때 특정 bool이켜져있따면 대쉬
void CPlayerMove::End()
{
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
	if (Roll()) return NO_EVENT;
	if (MiniPickaxe()) return NO_EVENT;

	m_player->UpperCutCountReset();

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
	m_speed = m_player->GetPlayerInfo()->GetSpeed();

	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		m_speed *= 0.6f;

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Forward)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Forward * deltaTime * m_speed);
		W = true;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Back)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Back * deltaTime * m_speed);
		S = true;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Left)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Left * deltaTime * m_speed);
		A = true;
	}
	else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Right)))
	{
		m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
		m_player->GetOwner()->Translate(vector3Right * deltaTime * m_speed);
		D = true;
	}

	Rotation();

	if (W || A || S || D) // 이동했을 경우
	{
		if (m_player->GetAnim()->GetAnimValue() != 2 &&
			m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		{
			m_player->GetAnim()->Set_AnimationSet(2);
		}

		cameraY = Engine::GET_MAIN_CAM->GetOwner()->GetCameraY();
		m_player->GetOwner()->SetRotationY(m_rotation - 180 + cameraY);
	}
	else if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck()) // 이동하지 않았고 점프하지 않았을경우
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
		return true;
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_RBUTTON))
	{
		if (m_player->GetUppercutCount() != m_player->GetUppercutMaxCount())
			m_player->ChangeFSM(CPlayer::STATE::UPPERCUT);
	}

	return false;
}

bool CPlayerMove::Jump()
{
	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() &&
		m_player->GetAnim()->GetAnimValue() != 5)
	{
		m_player->GetAnim()->Set_AnimationSet(6);
	}

	if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck() && Engine::CInputManager::GetInstance()->KeyPress(KEY_SPACE)) // 점프시작애니
	{
		m_player->GetAnim()->Set_AnimationSet(5);

		vector3 translate = vector3(0, 1, 0);

		if (W || A || S || D)
			translate.z = -0.3f;

		m_player->GetOwner()->OutTranslate(translate);
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->AddForce(translate * m_player->GetPlayerInfo()->GetJumpPower());

		return false;
	}

	if (m_player->GetAnim()->GetAnimValue() == 5 &&
		m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd()) // 점프중 애니
	{
		m_player->GetAnim()->Set_AnimationSet(6);
		return false;
	}

	if (m_player->GetAnim()->GetAnimValue() == 6 &&
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck()) // 점프 끝 애니
	{
		m_player->GetAnim()->Set_AnimationSet(7);
		return false;
	}

	if (m_player->GetAnim()->GetAnimValue() == 7 &&
		m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		return true;
	}

	return false;
}

bool CPlayerMove::Roll()
{
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_SHIFT))
	{
		m_player->ChangeFSM(CPlayer::STATE::ROLL);
		return true;
	}
	return false;
}

bool CPlayerMove::MoveCheck(vector3 dir)
{
	vector3 orgine = m_player->GetOwner()->GetPosition();
	orgine.y += 0.9;
	Engine::CGameObject* obj = Engine::CRaycast::BoxRayCast(orgine, dir, m_moveCheckDir, L"Collider");

	if(obj == nullptr)
		obj = Engine::CRaycast::BoxRayCast(orgine, dir, m_moveCheckDir, L"Map");

	if (obj != nullptr)
	{
		return false;
	}
	return true;
}

bool CPlayerMove::MiniPickaxe()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F))
	{
		m_player->ChangeFSM(CPlayer::STATE::MINIPICKAXE);
		return true;
	}
	return false;
}
