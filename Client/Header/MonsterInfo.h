#pragma once
class CMonsterInfo
{
protected:
	GETTOR_SETTOR(_int, m_hp, 0, HP)
	GETTOR_SETTOR(_int, m_maxHp, 0, MaxHP)
	GETTOR_SETTOR(_float, m_speed, 0, Speed)
	GETTOR_SETTOR(vector<_float>, m_damage, {}, Damage)

public:
	CMonsterInfo::CMonsterInfo()	{	}
	CMonsterInfo::~CMonsterInfo()	{	}

	void AddHp(_int hp) { m_hp += hp; }

};

