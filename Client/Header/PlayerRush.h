#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerRush :
	public FSM
{
private:
	Engine::CCollider* collision;
public:
	CPlayerRush(CPlayer* player);
	virtual ~CPlayerRush();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void Move();
};

