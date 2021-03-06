#pragma once
#include "MonsterFSM.h"
class CMonster;
class CScarecrowIdle :
	public MonsterFSM
{
private:
	_bool m_init = false;

	_float m_resetTime;
	_float m_resetTimeMax;

	_float m_pastHP;
public:
	CScarecrowIdle(CMonster* monster);
	virtual ~CScarecrowIdle();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

