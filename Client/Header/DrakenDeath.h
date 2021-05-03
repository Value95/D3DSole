#pragma once
#include "FSM.h"
class CMonster;
class CDrakenDeath :
	public FSM
{
private:
	CMonster* m_monster;

public:
	CDrakenDeath(CMonster* monster);
	virtual ~CDrakenDeath();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

