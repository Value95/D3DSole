#include "stdafx.h"
#include "PlayerDeshAttack.h"


CPlayerDeshAttack::CPlayerDeshAttack(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(3, 3, 3), vector3(0, 0, -2));
}

CPlayerDeshAttack::~CPlayerDeshAttack()
{
}

void CPlayerDeshAttack::Start()
{
	init = true;
	m_attackAnimNumber = 44;
	
	memset(m_attack, true, sizeof(m_attack));

	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(1);
	m_player->GetAnim()->Set_AnimationSet(m_attackAnimNumber);
}

void CPlayerDeshAttack::End()
{
}

_uint CPlayerDeshAttack::FixedUpdate()
{
	if (!init)
	{
		std::vector<Engine::CGameObject*> col;
		if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
		{
			for (auto& object : col)
			{
				m_player->Attack(object);
				cout << "АјАн" << endl;
				init = true;
			}
		}
	}
	return NO_EVENT;
}

_uint CPlayerDeshAttack::Update()
{
	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
	}

	if (m_attack[0] && m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->CurentTime() >= 0.1)
	{
		m_attack[0] = false;
		init = false;
	}
	if (m_attack[1] && m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->CurentTime() >= 0.5)
	{
		m_attack[1] = false;
		init = false;
	}
	

	return NO_EVENT;
}

_uint CPlayerDeshAttack::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerDeshAttack::OnDestroy(void)
{
}
