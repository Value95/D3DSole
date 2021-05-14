#pragma once
class CPlayerInfo
{
protected:
	GETTOR_SETTOR(_int, m_hp, 200, HP)
	GETTOR_SETTOR(_int, m_hpMax, 200, HpMax)
	GETTOR_SETTOR(_int, m_attackSpeed, 3, AttackSpeed)
	GETTOR_SETTOR(_float, m_rotationSpeed, 20, RotationSpeed)
	GETTOR_SETTOR(_float, m_jumpPower, 5, JumpPower)
	GETTOR_SETTOR(_float, m_speed, 200, Speed)
	GETTOR_SETTOR(_float, m_speedRush, 1000, SpeedRush)
	GETTOR_SETTOR(_float, m_roolSpeed, 500, RollSpeed)
	GETTOR_SETTOR(_float, m_mouseSensitivity, 5, MouseSensitivity);
	GETTOR_SETTOR(_int, m_damageA, 100, DamageA);
	GETTOR_SETTOR(_int, m_damageB, 100, DamageB);
	GETTOR_SETTOR(_int, m_damageC, 100, DamageC);
	GETTOR_SETTOR(_int, m_damageD, 10, DamageD);
	GETTOR_SETTOR(_int, m_damageRush, 50, DamageRush);

	GETTOR_SETTOR(_int, m_gold, 50, Gold);
public:
	CPlayerInfo::CPlayerInfo(){}
	CPlayerInfo::~CPlayerInfo(){}

	void DownHP(_float damage)
	{
		m_hp = Engine::MathfMax(m_hp - damage, 0);
	}
};

