#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSanwaMoneyAttack2 :
	public MonsterFSM
{
private:
	Engine::CCollider* collision;
	_bool init;
	_bool m_attack;
public:
	CSanwaMoneyAttack2(CMonster* monster);
	virtual ~CSanwaMoneyAttack2();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

