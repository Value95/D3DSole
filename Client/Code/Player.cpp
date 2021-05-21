#include "stdafx.h"
#include "Player.h"
#include "PlayerInfo.h"
#include "PlayerHP.h"
#include "MonsterInfo.h"

#include "FSM.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"
#include "PlayerDeath.h"
#include "PlayerHit.h"
#include "PlayerDebug.h"
#include "PlayerUppercut.h"
#include "PlayerRoll.h"
#include "PlayerMiniPickaxe.h"
#include "PlayerRush.h"
#include "PlayerInteraction.h"
#include "PlayerUI.h"
#include "PlayerDushUI.h"
#include "PlayerStatReinforceShop.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer(void)
{
	OnDestroy();
}

SHARED(Engine::CComponent) CPlayer::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CPlayer) pClone(new CPlayer);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);
	pClone->SetPlayerInfo(m_playerInfo);

	return pClone;
}

void CPlayer::Awake(void)
{
	__super::Awake();
	m_playerInfo = new CPlayerInfo();
}


void CPlayer::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_playerInfo->Start();
	m_playerHP = new CPlayerHP(&m_playerInfo->GetHP(), &m_playerInfo->GetHpMax());
	m_playerDushUI = new CPlayerDushUI(&m_playerInfo->GetDushGague());
	m_playerUI = new CPlayerUI(m_playerInfo);
	m_anim = GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>();
	m_rigidbody = GetOwner()->GetComponent<Engine::CRigidBodyComponent>();
	FSMCreate();
}

_uint CPlayer::FixedUpdate(SHARED(CComponent) spThis)
{
	return m_playerFSM[m_playerState]->FixedUpdate();
}

_uint CPlayer::Update(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->Update();
	m_playerHP->Update();
	m_playerUI->Update();
	m_playerDushUI->Update();
	m_playerInfo->AddDushGague(deltaTime * 100);

	if(m_playerState != STATE::DEATH)
		m_playerInfo->NaturalRecovery();

	return NO_EVENT;
}

_uint CPlayer::LateUpdate(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->LateUpdate();

	m_playerInfo->End();

	return NO_EVENT;
}

void CPlayer::OnDestroy(void)
{
	m_playerInfo->End();

	/*if (m_playerFSM != nullptr)
	{
		for (int i = 0; i < STATE::STATEEND; i++)
		{
			SAFE_DELETE(m_playerFSM[i]);
		}
	}*/
}

void CPlayer::OnEnable(void)
{
}

void CPlayer::OnDisable(void)
{
}

void CPlayer::ChangeFSM(STATE state)
{
	m_playerFSM[m_playerState]->End();
	m_playerOldState = m_playerState;
	m_playerState = state;
	m_playerFSM[m_playerState]->Start();
}

void CPlayer::Attack(Engine::CGameObject* gameObject, _float damage)
{
	if (gameObject->GetLayerKey() == L"Monster")
	{
		gameObject->GetComponent<CMonster>()->Hit(damage);
		gameObject->GetComponent<Engine::CParticleSystem>()->play();
	}
	else if (gameObject->GetLayerKey() == L"Boss")
	{
		gameObject->GetComponent<CMonster>()->Hit(damage);
	}
}

void CPlayer::Hit(_int damage, _int hitType)
{
	m_playerInfo->DownHP(damage);


	if (m_playerInfo->GetHP() <= 0)
	{
		ChangeFSM(STATE::DEATH);
		return;
	}

	switch (hitType)
	{
	case 0:
		break;
	case 1:
		m_playerInfo->DownHP(damage);
		ChangeFSM(STATE::HIT);
		break;
	default:
		break;
	}


	return;
}

void CPlayer::IdleLookState()
{
	m_idleLook = true;
	ChangeFSM(STATE::IDLE);
}

void CPlayer::IdleLookEnd()
{
	m_idleLook = false;
}

void CPlayer::UpperCutCountReset()
{
	if (GetOwner()->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
	{
		m_uppercutCount = 0;
	}
}

bool CPlayer::MoveCheck(vector3 dir, _float moveCheckDir)
{
	vector3 orgine = GetOwner()->GetPosition();
	orgine.y += 0.9;
	Engine::CGameObject* obj = Engine::CRaycast::BoxRayCast(orgine, dir, moveCheckDir, GetOwner());

	if (obj != nullptr && obj->GetComponent<Engine::CColliderComponent>()->GetIsTrigger() == true)
	{
		return false;
	}

	return true;
}

void CPlayer::FSMCreate()
{
	m_playerFSM[STATE::IDLE] = new CPlayerIdle(this);
	m_playerFSM[STATE::MOVE] = new CPlayerMove(this);
	m_playerFSM[STATE::ATTACK] = new CPlayerAttack(this);
	m_playerFSM[STATE::HIT] = new CPlayerHit(this);
	m_playerFSM[STATE::DEATH] = new CPlayerDeath(this);
	m_playerFSM[STATE::DEBUGMODE] = new CPlayerDebug(this);
	m_playerFSM[STATE::UPPERCUT] = new CPlayerUppercut(this);
	m_playerFSM[STATE::ROLL] = new CPlayerRoll(this);
	m_playerFSM[STATE::MINIPICKAXE] = new CPlayerMiniPickaxe(this);
	m_playerFSM[STATE::RUSH] = new CPlayerRush(this);
	m_playerFSM[STATE::INTERACTION] = new CPlayerInteraction(this);
	m_playerFSM[STATE::STATREINFORCESHOP] = new CPlayerStatReinforceShop(this);

	m_playerFSM[STATE::IDLE]->Start();
}
