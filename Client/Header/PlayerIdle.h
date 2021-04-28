#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerIdle :
	public FSM
{
private:
	CPlayer* m_player;

	_int T;
public:
	CPlayerIdle(CPlayer* player);
	virtual ~CPlayerIdle();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

