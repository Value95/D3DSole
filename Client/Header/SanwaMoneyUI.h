#pragma once
class CSanwaMoneyUI
{
	// HP
	CMonster* m_monster;
	vector3 m_hpUIPos;
	SHARED(Engine::CGameObject) m_hpUI;

	_int* m_hp;
	_float m_curHp;
	_int* m_hpMax;
	_float m_hpUiScaleX;
	vector3 m_oldPos;
	_float m_downSpeed;
public:
	CSanwaMoneyUI(CMonster* monster);
	~CSanwaMoneyUI();

	void Start();

	void Update();
	void OnDestory();

	void DateInput(_int* hp, _int* hpMax);
};

