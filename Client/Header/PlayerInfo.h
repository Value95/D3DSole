#pragma once
class CPlayerInfo
{
protected:
	GETTOR_SETTOR(_int, m_hp, 0, HP)
	GETTOR_SETTOR(_int, m_hpMax, 0, HpMax)
	GETTOR_SETTOR(_int, m_attackSpeed, 0, AttackSpeed)
	GETTOR_SETTOR(_float, m_rotationSpeed, 0, RotationSpeed)
	GETTOR_SETTOR(_float, m_jumpPower, 0, JumpPower)
	GETTOR_SETTOR(_float, m_speed, 0, Speed)
	GETTOR_SETTOR(_float, m_speedRush, 0, SpeedRush)
	GETTOR_SETTOR(_float, m_roolSpeed, 0, RollSpeed)
	GETTOR_SETTOR(_float, m_dushGauge, 0, DushGague)
	GETTOR_SETTOR(_float, m_mouseSensitivity, 0, MouseSensitivity);
	GETTOR_SETTOR(_int, m_damageA, 0, DamageA);
	GETTOR_SETTOR(_int, m_damageB, 0, DamageB);
	GETTOR_SETTOR(_int, m_damageC, 0, DamageC);
	GETTOR_SETTOR(_int, m_damageD, 0, DamageD);
	GETTOR_SETTOR(_int, m_damageRush, 0, DamageRush);

	GETTOR_SETTOR(_int, m_gold, 0, Gold);
public:
	CPlayerInfo::CPlayerInfo(){}
	CPlayerInfo::~CPlayerInfo(){}
	void Start();
	void End();

	void DownHP(_float damage)
	{
		m_hp = Engine::MathfMax(m_hp - damage, 0);
	}

	void AddDushGague(_int value)
	{
		m_dushGauge = Engine::MathfMin(m_dushGauge + value, 100);
	}
};

