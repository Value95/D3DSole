#pragma once
#include "FSM.h"
class CMonster;
class CDrakenUI;
class CDrakenMaintenance :
	public FSM
{
private:
	CMonster* m_monster;
	CDrakenUI* m_drakenUI;
	// 몬스터 체력 컴포넌트
public:
	CDrakenMaintenance(CMonster* monster);
	virtual ~CDrakenMaintenance();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void PatternTimer();
	void ChangePattern();
};

