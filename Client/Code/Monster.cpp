#include "stdafx.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "FSM.h"

#include "PlayerInfo.h"
#include "DrakenIdle.h"

CMonster::CMonster()
{
}

CMonster::~CMonster(void)
{
	OnDestroy();
}

SHARED(Engine::CComponent) CMonster::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CMonster) pClone(new CMonster);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetMonsterFSM(m_monsterFSM);
	pClone->SetMonsterMaintenanceFSM(m_monsterMaintenanceFSM);

	pClone->SetMonsterInfo(m_monsterInfo);

	return pClone;
}

void CMonster::Awake(void)
{
	__super::Awake();
	if(m_monsterInfo == nullptr)
		m_monsterInfo = new CMonsterInfo();

}

void CMonster::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_player = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");
	m_playerCom = m_player->GetComponent<CPlayer>();
	m_anim = GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>();

	static_cast<CDrakenIdle*>(m_monsterFSM[0])->SetMonster(this);

	m_monsterFSM[0]->Start();


	m_hitCheck = false;
}

_uint CMonster::FixedUpdate(SHARED(CComponent) spThis)
{
	m_monsterFSM[m_monsterState]->FixedUpdate();
	m_monsterMaintenanceFSM->FixedUpdate();

	return NO_EVENT;
}

_uint CMonster::Update(SHARED(CComponent) spThis)
{
	m_monsterFSM[m_monsterState]->Update();
	m_monsterMaintenanceFSM->Update();

	return NO_EVENT;
}

_uint CMonster::LateUpdate(SHARED(CComponent) spThis)
{
	m_monsterFSM[m_monsterState]->LateUpdate();
	m_monsterMaintenanceFSM->LateUpdate();

	m_hitCheck = true;
	return NO_EVENT;
}

void CMonster::OnDestroy(void)
{
	if (!m_monsterFSM.empty())
	{
		/*for (int i = 0; i < m_monsterFSM.size(); i++)
		{
			SAFE_DELETE(m_monsterFSM[i]);
		}*/
	}
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
	m_hitCheck = true;
	m_monsterInfo->AddHp(-damage);
	HitEffect();
}

void CMonster::AddFSM(FSM * fsm)
{
	m_monsterFSM.emplace_back(fsm);
}

void CMonster::Attack(_float damage)
{
	m_playerCom->GetPlayerInfo()->DownHP(damage);
}

void CMonster::HitEffect()
{
	//std::cout << "HitEffect" << endl;
}

