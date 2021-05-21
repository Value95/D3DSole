#include "stdafx.h"
#include "SanwaMoneyHalfHealth.h"
#include "Monster.h"
#include "MonsterInfo.h"

CSanwaMoneyHalfHealth::CSanwaMoneyHalfHealth(CMonster* monster)
{
	m_monster = monster;
}

CSanwaMoneyHalfHealth::~CSanwaMoneyHalfHealth()
{
}

void CSanwaMoneyHalfHealth::Start()
{
	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(2);
	Engine::CSoundManager::GetInstance()->StartSound(L"Boss_Skill_Roar_01.wav", Engine::CHANNELID::ROAR);
}

void CSanwaMoneyHalfHealth::End()
{
	Engine::CSoundManager::GetInstance()->StopSound(Engine::CHANNELID::ROAR);

}

_uint CSanwaMoneyHalfHealth::FixedUpdate()
{
	return NO_EVENT;
}

_uint CSanwaMoneyHalfHealth::Update()
{
	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		m_monster->ChangeFSM(CMonster::SM_STATE::SM_IDLE);
	}

	Move();

	return NO_EVENT;
}

_uint CSanwaMoneyHalfHealth::LateUpdate()
{

	return NO_EVENT;
}

void CSanwaMoneyHalfHealth::OnDestroy(void)
{
}

void CSanwaMoneyHalfHealth::Move()
{
	m_monster->GetOwner()->Translate(vector3Forward * m_monster->GetMonsterInfo()->GetSpeed() * 2);
}



