#include "stdafx.h"
#include "Monster.h"
#include "SceneManager.h"
#include "Scene.h"
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

	//player = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");
}

_uint CMonster::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CMonster::Update(SHARED(CComponent) spThis)
{
	// GetOwner()->Lerp(player->GetPosition(), 1.0f);
	// GetOwner()->LookAt(player->GetPosition());
	return NO_EVENT;
}

_uint CMonster::LateUpdate(SHARED(CComponent) spThis)
{
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
