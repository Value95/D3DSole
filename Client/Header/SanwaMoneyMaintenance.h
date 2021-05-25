#pragma once
#include "MonsterFSM.h"
class CMonster;
class CSanwaMoneyUI;
class CSanwaMoneyMaintenance :
	public MonsterFSM
{
private:
	_bool m_halfHealthCheck;
	CSanwaMoneyUI* m_sanwaMouneyUI;

	_bool m_debug;
public:
	CSanwaMoneyMaintenance(CMonster* monster);
	virtual ~CSanwaMoneyMaintenance();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void Death();
	void PatternTimer();
	void ChangePattern();

	void HalfHealth();
	void Debug();
};

