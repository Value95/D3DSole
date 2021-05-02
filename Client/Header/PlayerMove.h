#pragma once
#include "FSM.h"
class CPlayer;
class CPlayerMove :
	public FSM
{
private:
	CPlayer* m_player;
	_float m_rotation;

	_float m_speed;
	_float cameraY;

	_float m_moveCheckDir;

	_float m_dashCehckTime;
	_float m_dashCehckTimer;
	_bool m_deshOn;
	_bool W, A, S, D;
	_bool WW, AA, SS, DD;

public:
	CPlayerMove(CPlayer* player);
	virtual ~CPlayerMove();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	bool Move();
	void Rotation();
	bool Attack();
	bool DeshAttack();
	bool Jump();
	bool Desh();
	bool DeshActivation();

	bool MoveCheck(vector3 dir);
};

