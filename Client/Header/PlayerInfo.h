#pragma once
class CPlayerInfo
{
protected:
	GETTOR_SETTOR(_int, m_hp, 200, HP)
	GETTOR_SETTOR(_int, m_hpMax, 200, HpMax)
	GETTOR_SETTOR(_float, m_rotationSpeed, 20, RotationSpeed)
	GETTOR_SETTOR(_float, m_jumpPower, 5, JumpPower)
	GETTOR_SETTOR(_float, m_speed, 200, Speed)
	GETTOR_SETTOR(_float, m_deshSpeed, 300, DeshSpeed)
	GETTOR_SETTOR(_float, m_mouseSensitivity, 5, MouseSensitivity);
	GETTOR_SETTOR(_int, m_damage, 300, Damage);
public:
	CPlayerInfo::CPlayerInfo()
	{
	}
	CPlayerInfo::~CPlayerInfo()
	{
	}

	void DownHP(_float damage)
	{
		m_hp = Engine::MathfMax(m_hp - damage, 0);
	}
};

