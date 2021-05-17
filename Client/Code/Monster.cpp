#include "stdafx.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "MonsterFSM.h"

#include "PlayerInfo.h"

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
	m_rigidBody = GetOwner()->GetComponent<Engine::CRigidBodyComponent>();
	m_monsterState = 0;



	m_monsterFSM[0]->SetMonster(this);
	m_monsterFSM[0]->Start();
	m_monsterMaintenanceFSM->Start();
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

void CMonster::AddFSM(MonsterFSM * fsm, _int fsmNumber)
{
	m_monsterFSM[fsmNumber] = fsm;
	m_monsterFSM.emplace_back(nullptr);
}

void CMonster::Attack(_float damage)
{
	m_playerCom->GetPlayerInfo()->DownHP(damage);
}

_bool CMonster::Collision(Engine::CCollider * collision, Engine::CGameObject* object)
{
	std::vector<Engine::CGameObject*> col;
	if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, object, col))
	{
		for (auto& object : col)
		{
			if (object->GetName() == L"Player")
			{
				return true;
			}
		}
	}
	return false;
}

_bool CMonster::MoveCheck(vector3 dir, _float moveCheckDir)
{
	vector3 orgine = GetOwner()->GetPosition();
	orgine.y += 0.9;
	Engine::CGameObject* obj = Engine::CRaycast::BoxRayCast(orgine, dir, moveCheckDir);

	if (obj != nullptr)
	{
		return false;
	}
	return true;
}

void CMonster::HitEffect()
{
	//std::cout << "HitEffect" << endl;
}

