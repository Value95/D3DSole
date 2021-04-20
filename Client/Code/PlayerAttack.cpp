#include "stdafx.h"
#include "..\Header\PlayerAttack.h"


CPlayerAttack::CPlayerAttack(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3(0,0,-3));
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Start()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(10);

	if(m_player->GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(10);
	else
		m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(7);
}

void CPlayerAttack::End()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(1);
}

_uint CPlayerAttack::FixedUpdate()
{
	// 충돌판정
	std::vector<Engine::CGameObject*> col;
	if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision ,m_player->GetOwner(), col))
	{
		for (auto& object : col)
		{

			if (object->GetLayerKey() == L"Monster")
			{
				wcout << object->GetName().c_str() << endl;
			//	std::cout << "몬스터 충돌" << endl;
			}
		}
	}

	return _uint();
}

_uint CPlayerAttack::Update()
{

	if (m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_player->ChangeFSM(CPlayer::STATE::IDLE);
	}

	return _uint();
}

_uint CPlayerAttack::LateUpdate()
{
	return _uint();
}

void CPlayerAttack::OnDestroy(void)
{
}
