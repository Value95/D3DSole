#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSanwaMoneyIdle :
	public MonsterFSM
{
private:
	_bool m_init = false;
	_int m_animCount;

public:
	CSanwaMoneyIdle(CMonster* monster);
	virtual ~CSanwaMoneyIdle();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

	void SetMonster(CMonster* monster)
	{
		m_monster = monster;
	}

private:
	void ReSet();
};

