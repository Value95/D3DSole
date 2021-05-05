#pragma once
#include "FSM.h"
class CMonster;
class CDrakenAttack1 :
	public FSM
{
private:
	CMonster* m_monster;
	Engine::CCollider* collision;
	_bool init;
	_bool m_attack;
public:
	CDrakenAttack1(CMonster* monster);
	virtual ~CDrakenAttack1();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

