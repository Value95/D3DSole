#include "stdafx.h"
#include "SanwaMoneyMove.h"
#include "Monster.h"
#include "MonsterInfo.h"

CSanwaMoneyMove::CSanwaMoneyMove(CMonster* monster)
{
	m_monster = monster;
}

CSanwaMoneyMove::~CSanwaMoneyMove()
{
}

void CSanwaMoneyMove::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(0);
}

void CSanwaMoneyMove::End()
{
}

_uint CSanwaMoneyMove::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSanwaMoneyMove::Update()
{
	Move();

	return NO_EVENT;
}

_uint CSanwaMoneyMove::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyMove::OnDestroy(void)
{
}

void CSanwaMoneyMove::Move()
{
	if (Engine::Distance(m_monster->GetOwner()->GetPosition(), m_monster->GetPlayer()->GetPosition()) >= 7.5f)
	{
		m_monster->GetOwner()->LookAtX(m_monster->GetPlayer()->GetPosition());
		m_monster->GetOwner()->AddRotationY(180);
		m_monster->GetOwner()->Translate(vector3Back * m_monster->GetMonsterInfo()->GetSpeed());

		MoveCheck();
	}
	else
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_IDLE);
	}
}

void CSanwaMoneyMove::MoveCheck()
{
	if (m_monster->Collision(m_monster->GetOwner()->GetComponent<Engine::CColliderComponent>()->GetColliders()[0], m_monster->GetOwner()))
	{
		m_monster->GetPlayer()->Translate(vector3Forward * m_monster->GetMonsterInfo()->GetSpeed() * 2);
	}
}



