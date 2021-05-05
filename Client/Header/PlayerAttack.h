#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerAttack :
	public FSM
{
private:
	Engine::CCollider* collision;
	_bool init;
	_int m_attackAnimNumber;
	_bool m_nextAttack;
public:
	CPlayerAttack(CPlayer* player);
	virtual ~CPlayerAttack();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void GroundAttack();
	void JumpAttack();
};

