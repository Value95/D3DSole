#pragma once
class CPlayerHP
{
private:
	GETTOR_SETTOR(SHARED(Engine::CGameObject), m_playerHpUi, {}, PlayerHpUi)
	_int* m_hp;
	_float m_curHp;
	_int* m_hpMax;
	_float m_hpUiScaleX;
	vector3 m_oldPos;
	_float m_downSpeed;
public:
	CPlayerHP();
	CPlayerHP(_int* hp, _int* hpMax);
	~CPlayerHP();
	
	void Update();
	void Hit(_float damage);
};

