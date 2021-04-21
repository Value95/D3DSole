#include "stdafx.h"
#include "Monster.h"
#include "MonsterInfo.h"

#include "FSM.h"

CMonster::CMonster()
{
}


CMonster::~CMonster(void)
{
}

SHARED(Engine::CComponent) CMonster::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CMonster) pClone(new CMonster);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);


	return pClone;
}

void CMonster::Awake(void)
{
	__super::Awake();
}


void CMonster::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_monsterInfo = new CMonsterInfo();
	m_player = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");
}

_uint CMonster::FixedUpdate(SHARED(CComponent) spThis)
{
	m_monsterFSM[m_monsterState]->FixedUpdate();
	return NO_EVENT;
}

_uint CMonster::Update(SHARED(CComponent) spThis)
{
	m_monsterFSM[m_monsterState]->Update();
	return NO_EVENT;
}

_uint CMonster::LateUpdate(SHARED(CComponent) spThis)
{
	m_monsterFSM[m_monsterState]->LateUpdate();
	return NO_EVENT;
}

void CMonster::OnDestroy(void)
{
}

void CMonster::OnEnable(void)
{
}

void CMonster::OnDisable(void)
{
}

void CMonster::ChangeFSM(_int state)
{
	m_monsterFSM[m_monsterState]->End();
	m_monsterState = state;
	m_monsterFSM[m_monsterState]->Start();
}

void CMonster::Hit(_int damage)
{
	m_monsterInfo->AddHp(damage);
	HitEffect();
}

void CMonster::HitEffect()
{
	std::cout << "HitEffect" << endl;
}
