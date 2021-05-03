#include "stdafx.h"
#include "DrakenMove.h"
#include "Monster.h"
#include "MonsterInfo.h"

CDrakenMove::CDrakenMove(CMonster* monster)
{
	m_monster = monster;
}

CDrakenMove::~CDrakenMove()
{
}

void CDrakenMove::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(15);
}

void CDrakenMove::End()
{
}

_uint CDrakenMove::FixedUpdate()
{
	return NO_EVENT;
}

_uint CDrakenMove::Update()
{
	Move();

	return NO_EVENT;
}

_uint CDrakenMove::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenMove::OnDestroy(void)
{
}

void CDrakenMove::Move()
{
	if (Engine::Distance(m_monster->GetOwner()->GetPosition(), m_monster->GetPlayer()->GetPosition()) >= 5.5f)
	{
		m_monster->GetOwner()->LookAt(m_monster->GetPlayer()->GetPosition());
		m_monster->GetOwner()->AddRotationY(180);
		m_monster->GetOwner()->Translate(vector3Back * m_monster->GetMonsterInfo()->GetSpeed());
	}
}



