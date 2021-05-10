#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSoldierSpearDeath :
	public MonsterFSM
{
private:
	_bool m_init = false;

public:
	CSoldierSpearDeath(CMonster* monster);
	virtual ~CSoldierSpearDeath();
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
};

