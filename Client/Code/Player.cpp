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
#include "PlayerDeshAttack.h"
#include "PlayerHit.h"

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
	m_playerHP = new CPlayerHP(&m_playerInfo->GetHP(), &m_playerInfo->GetHpMax());
	m_anim = GetOwner()->GetComponent<Engine::CAnimMeshRenderComponent>();
	FSMCreate();
}

_uint CPlayer::FixedUpdate(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->FixedUpdate();

	return NO_EVENT;
}

_uint CPlayer::Update(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->Update();
	m_playerHP->Update();

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_Q))
	{
		Hit(50, 0);
	}

	return NO_EVENT;
}

_uint CPlayer::LateUpdate(SHARED(CComponent) spThis)
{
	m_playerFSM[m_playerState]->LateUpdate();

	return NO_EVENT;
}

void CPlayer::OnDestroy(void)
{
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
	m_playerState = state;
	m_playerFSM[m_playerState]->Start();
}

void CPlayer::Attack(Engine::CGameObject* gameObject)
{
	if (gameObject->GetLayerKey() == L"Monster")
	{
		_float aa = GetPlayerInfo()->GetDamage();
		gameObject->GetComponent<CMonster>()->Hit(GetPlayerInfo()->GetDamage());
		cout << "몬스터 체력 : " << gameObject->GetComponent<CMonster>()->GetMonsterInfo()->GetHP() << endl;
	}
	else if (gameObject->GetName() == L"Boss")
	{

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

	ChangeFSM(STATE::HIT);
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

void CPlayer::FSMCreate()
{
	m_playerFSM[STATE::IDLE] = new CPlayerIdle(this);
	m_playerFSM[STATE::IDLE]->Start();

	m_playerFSM[STATE::MOVE] = new CPlayerMove(this);
	m_playerFSM[STATE::ATTACK] = new CPlayerAttack(this);
	m_playerFSM[STATE::DESHATTACK] = new CPlayerDeshAttack(this);
	m_playerFSM[STATE::HIT] = new CPlayerHit(this);
	m_playerFSM[STATE::DEATH] = new CPlayerDeath(this);
}
