#pragma once
#include "MonsterFSM.h"
class CMonster;
class CDrakenDeath :
	public MonsterFSM
{
private:

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

