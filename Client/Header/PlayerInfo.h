#pragma once
class CPlayerInfo
{
protected:
	GETTOR_SETTOR(_int, m_hp, 0, HP)
	GETTOR_SETTOR(_float, m_rotationSpeed, 20, RotationSpeed)
	GETTOR_SETTOR(_float, m_jumpPower, 5, JumpPower)
	GETTOR_SETTOR(_float, m_speed, 200, Speed)
	GETTOR_SETTOR(_float, m_mouseSensitivity, 5, MouseSensitivity);
	GETTOR_SETTOR(_int, m_damage, 5, Damage);
public:
	CPlayerInfo::CPlayerInfo()
	{
	}


	CPlayerInfo::~CPlayerInfo()
	{
	}
};

