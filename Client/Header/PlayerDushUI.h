#pragma once
class CPlayerDushUI
{
private:
	GETTOR_SETTOR(SHARED(Engine::CGameObject), m_object, {}, Obejct)
	_float* m_value;
	_float m_ValueUiScaleY;
	vector3 m_oldPos;
public:
	CPlayerDushUI();
	CPlayerDushUI(_float* value);
	~CPlayerDushUI();
	
	void Update();
	void Hit(_float damage);
};

