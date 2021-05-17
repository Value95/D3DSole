#include "stdafx.h"
#include "..\Header\PlayerAttack.h"
#include "PlayerInfo.h"

#include "MonsterInfo.h"

CPlayerAttack::CPlayerAttack(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1.2, 3, 6), vector3(0, 0.9, -3));
	m_moveCheckDir = 1.0f;
}

CPlayerAttack::~CPlayerAttack()
{
	OnDestroy();
}

void CPlayerAttack::Start()
{
	m_player->SetWaponPosNumber(1);
	m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
	m_player->GetOwner()->AddRotationY(-180);

	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(m_player->GetPlayerInfo()->GetAttackSpeed());

	Engine::GET_MAIN_CAM->GetOwner()->GetComponent<CCameraShake>()->CameraShakeActivation(0.1f, 1);

	init = true;
	m_attack = true;
	
	if (m_player->GetRigidBody()->GetGroundCheck())
	{
		m_player->GetAnim()->Set_AnimationSet(13);
	}
	else
	{
		m_player->GetAnim()->Set_AnimationSet(15);
	}
}

void CPlayerAttack::End()
{
	init = false;
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1);
}

_uint CPlayerAttack::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
		{
			for (auto& object : col)
			{
				m_player->Attack(object, m_player->GetPlayerInfo()->GetDamageA());
			}
		}
	}
	init = true;
	return NO_EVENT;
}

_uint CPlayerAttack::Update()
{
	Move();

	if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		if (Engine::CInputManager::GetInstance()->KeyPress(KEY_LBUTTON))
		{
			m_player->GetAnim()->GetAnimCtrl()->SetPeriod(m_player->GetAnim()->GetAnimCtrl()->GetPeriod() + m_player->GetAnim()->GetAnimCtrl()->GetSavePeriod());
			m_player->ChangeFSM(CPlayer::ATTACK);
		}
		else
		{
			m_player->ChangeFSM(CPlayer::STATE::IDLE);
		}
		return NO_EVENT;
	}

	if (m_attack && m_player->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.7f)
	{
		m_attack = false;
		init = false;
	}


	return NO_EVENT;
}

_uint CPlayerAttack::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerAttack::OnDestroy(void)
{
	SAFE_DELETE(collision);

}

bool CPlayerAttack::Move()
{
	

	if (!m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
	{
		_float m_speed = m_player->GetPlayerInfo()->GetSpeed() * 0.6f;

		if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) && 
			m_player->MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Forward), m_moveCheckDir))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y + 180);
			m_player->GetOwner()->Translate(vector3Back * deltaTime * m_speed);
		}
		else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S) &&
			m_player->MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Back), m_moveCheckDir))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y + 180);
			m_player->GetOwner()->Translate(vector3Forward * deltaTime * m_speed);
		}

		if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A) &&
			m_player->MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Left), m_moveCheckDir))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y + 180);
			m_player->GetOwner()->Translate(vector3Right * deltaTime * m_speed);
		}
		else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D) &&
			m_player->MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Right), m_moveCheckDir))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y + 180);
			m_player->GetOwner()->Translate(vector3Left * deltaTime * m_speed);
		}

	}

	return false;
}