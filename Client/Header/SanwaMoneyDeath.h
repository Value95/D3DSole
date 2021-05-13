#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSanwaMoneyDeath :
	public MonsterFSM
{
private:

public:
	CSanwaMoneyDeath(CMonster* monster);
	virtual ~CSanwaMoneyDeath();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

