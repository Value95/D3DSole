#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerDeshAttack :
	public FSM
{
private:
	CPlayer* m_player;
	Engine::CCollider* collision;

	_bool init;
	_int m_attackAnimNumber;

	_bool m_attack[2];
public:
	CPlayerDeshAttack(CPlayer* player);
	virtual ~CPlayerDeshAttack();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

