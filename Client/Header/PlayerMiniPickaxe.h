#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerMiniPickaxe :
	public FSM
{
private:
	Engine::CCollider* collision;
	_bool init;
	SHARED(Engine::CGameObject) m_miniGock;
public:
	CPlayerMiniPickaxe(CPlayer* player);
	virtual ~CPlayerMiniPickaxe();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

