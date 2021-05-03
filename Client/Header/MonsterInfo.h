#pragma once
class CMonsterInfo
{
protected:
	GETTOR_SETTOR(_int, m_hp, 0, HP)
	GETTOR_SETTOR(_int, m_maxHp, 0, MaxHP)
	GETTOR_SETTOR(_float, m_speed, 0, Speed)
	GETTOR_SETTOR(vector<_float>, m_damage, {}, Damage)
	GETTOR_SETTOR(vector<_float>, m_patternTime, {}, PatternTime)
	GETTOR_SETTOR(vector<_float>, m_patternTimeMax, {}, PatternTimeMax)
public:
	CMonsterInfo::CMonsterInfo()	{	}
	CMonsterInfo::~CMonsterInfo()	{	}

	void AddHp(_int hp) { m_hp += hp; }
	void AddDamager(_float damage) { m_damage.emplace_back(damage); }
	void AddPatternTime(_float time) 
	{
		m_patternTime.emplace_back(time); 
		m_patternTimeMax.emplace_back(time);
	}
};

