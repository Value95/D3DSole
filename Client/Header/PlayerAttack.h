#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerAttack :
	public FSM
{
private:
	CPlayer* m_player;
	Engine::CCollider* collision;
	_bool init;
public:
	CPlayerAttack(CPlayer* player);
	virtual ~CPlayerAttack();

	// FSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

