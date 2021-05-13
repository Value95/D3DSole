#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSanwaMoneyMove :
	public MonsterFSM
{
private:

public:
	CSanwaMoneyMove(CMonster* monster);
	virtual ~CSanwaMoneyMove();
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

