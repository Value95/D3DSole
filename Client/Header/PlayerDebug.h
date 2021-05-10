#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerDebug :
	public FSM
{
private:
	_int m_animCount;
public:
	CPlayerDebug(CPlayer* player);
	virtual ~CPlayerDebug();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

