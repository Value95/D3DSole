#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerInteraction :
	public FSM
{
private:
	Engine::CCollider* collision;

public:
	CPlayerInteraction(CPlayer* player);
	virtual ~CPlayerInteraction();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void Interaction(std::wstring objectKey);
};

