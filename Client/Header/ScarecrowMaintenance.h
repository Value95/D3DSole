#pragma once
#include "MonsterFSM.h"
class CMonster;
class CScarecrowMaintenance :
	public MonsterFSM
{
private:

public:
	CScarecrowMaintenance(CMonster* monster);
	virtual ~CScarecrowMaintenance();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

