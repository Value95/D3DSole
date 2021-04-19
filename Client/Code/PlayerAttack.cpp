#include "stdafx.h"
#include "..\Header\PlayerAttack.h"


CPlayerAttack::CPlayerAttack(CPlayer* player)
{
	m_player = player;
	Engine::CCollider* box = Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3(0,0,0));
	m_player->GetOwner()->GetComponent<Engine::CColliderComponent>()->AddCollider(box);
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Start()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(10);
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->Set_AnimationSet(10);
}

void CPlayerAttack::End()
{
	m_player->GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>()->GetAnimCtrl()->SetSpeed(1);
}

_uint CPlayerAttack::FixedUpdate()
{
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
