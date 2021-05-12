#include "stdafx.h"
#include "..\Header\PlayerAttack.h"
#include "PlayerInfo.h"

#include "MonsterInfo.h"

CPlayerAttack::CPlayerAttack(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1, 4, 3), vector3(0, 0.9, -1));
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

	init = false;
	
	if (m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
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
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1);
	m_player->SetWaponPosNumber(0);

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
				init = true;
			}
		}
	}

	return NO_EVENT;
}

_uint CPlayerAttack::Update()
{
	if (m_player->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		if (Engine::CInputManager::GetInstance()->KeyPress(KEY_LBUTTON))
		{
			init = false;
		}
		else
		{
			m_player->ChangeFSM(CPlayer::STATE::IDLE);
		}
	}

	Move();

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

		if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Forward)))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
			m_player->GetOwner()->Translate(vector3Forward * deltaTime * m_speed);
		}
		else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Back)))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
			m_player->GetOwner()->Translate(vector3Back * deltaTime * m_speed);
		}

		if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Left)))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
			m_player->GetOwner()->Translate(vector3Left * deltaTime * m_speed);
		}
		else if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D) && MoveCheck(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3Right)))
		{
			m_player->GetOwner()->SetRotationY(Engine::GET_MAIN_CAM->GetOwner()->GetRotation().y);
			m_player->GetOwner()->Translate(vector3Right * deltaTime * m_speed);
		}

	}

	return false;

}

bool CPlayerAttack::MoveCheck(vector3 dir)
{
	vector3 orgine = m_player->GetOwner()->GetPosition();
	orgine.y += 0.9;
	Engine::CGameObject* obj = Engine::CRaycast::BoxRayCast(orgine, dir, 0.8, L"Collider");

	if (obj == nullptr)
		obj = Engine::CRaycast::BoxRayCast(orgine, dir, 0.8, L"Map");

	if (obj != nullptr)
	{
		return false;
	}
	return true;

}
