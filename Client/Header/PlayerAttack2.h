#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerAttack2 :
	public FSM
{
private:
	Engine::CCollider* collision;
	_bool init;

	_int m_attackAnimCount;

public:
	CPlayerAttack2(CPlayer* player);
	virtual ~CPlayerAttack2();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

