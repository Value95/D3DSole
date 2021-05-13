#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSanwaMoneyHalfHealth :
	public MonsterFSM
{
private:

public:
	CSanwaMoneyHalfHealth(CMonster* monster);
	virtual ~CSanwaMoneyHalfHealth();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void Move();
};

