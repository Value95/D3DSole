#pragma once
#include "FSM.h"
class CMonster;
class CDrakenIdle :
	public FSM
{
private:
	CMonster* m_monster;
	_bool m_init = false;

public:
	CDrakenIdle(CMonster* monster);
	virtual ~CDrakenIdle();
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

