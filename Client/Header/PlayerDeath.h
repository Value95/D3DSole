#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerDeath :
	public FSM
{
private:

public:
	CPlayerDeath(CPlayer* player);
	virtual ~CPlayerDeath();

	// FSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

