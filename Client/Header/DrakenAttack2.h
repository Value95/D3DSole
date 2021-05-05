#pragma once
#include "FSM.h"
class CMonster;
class CDrakenAttack2 :
	public FSM
{
private:
	CMonster* m_monster;
	Engine::CCollider* collision;
	_bool init;
	_bool m_attack[2];
public:
	CDrakenAttack2(CMonster* monster);
	virtual ~CDrakenAttack2();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

