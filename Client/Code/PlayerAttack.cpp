#include "stdafx.h"
#include "..\Header\PlayerAttack.h"
#include "PlayerInfo.h"

#include "MonsterInfo.h"

CPlayerAttack::CPlayerAttack(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3(0,0,-2));
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Start()
{
	init = false;
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(10);

	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(34);

	/*if(m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(45);
	else
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(45);*/
}

void CPlayerAttack::End()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(1);
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
				Attack(object);
			}
		}
	}
	return NO_EVENT;
}

_uint CPlayerAttack::Update()
{

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
	}

	return NO_EVENT;
}

_uint CPlayerAttack::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerAttack::OnDestroy(void)
{
}

void CPlayerAttack::Attack(Engine::CGameObject* gameObject)
{
	if (gameObject->GetLayerKey() == L"Monster")
	{
		gameObject->GetComponent<CMonster>()->Hit(m_player->GetPlayerInfo()->GetDamage());
		cout << "몬스터 체력 : " << gameObject->GetComponent<CMonster>()->GetMonsterInfo()->GetHP() << endl;
		init = false;
	}
	else if (gameObject->GetName() == L"Boss")
	{

	}
}
