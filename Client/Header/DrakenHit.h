#pragma once
#include "MonsterFSM.h"
class CMonster;
class CDrakenHit :
	public MonsterFSM
{
private:

public:
	CDrakenHit(CMonster* monster);
	virtual ~CDrakenHit();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

