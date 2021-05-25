	#include "stdafx.h"
#include "PlayerUppercut.h"
#include "PlayerInfo.h"

#include "MonsterInfo.h"

CPlayerUppercut::CPlayerUppercut(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(0.6, 1.6, 4), vector3(0, 0.9, -2));	
	m_moveCheckDir = 1.0f;
}

CPlayerUppercut::~CPlayerUppercut()
{
}

void CPlayerUppercut::Start()
{
	m_player->SetWaponPosNumber(1);
	m_upInit = false;
	init = true;

	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(2.0f);
	m_player->GetAnim()->Set_AnimationSet(1);
	
	m_player->SetUppercutCount(m_player->GetUppercutCount() + 1);
}

void CPlayerUppercut::End()
{
	Engine::CSoundManager::GetInstance()->StopSound(Engine::CHANNELID::ATTACK);
}

_uint CPlayerUppercut::FixedUpdate()
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
		init = true;
	}
	return NO_EVENT;
}

_uint CPlayerUppercut::Update()
{
	Move();

	if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
		return NO_EVENT;
	}

	if (!m_upInit && m_player->GetAnim()->GetAnimCtrl()->CurentTime() >= 0.5416666f)
	{
		m_upInit = true;
		init = false;
		m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->SetForce(vector3Up * 5);
	}

	return NO_EVENT;
}

_uint CPlayerUppercut::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerUppercut::OnDestroy(void)
{
}

bool CPlayerUppercut::Move()
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
