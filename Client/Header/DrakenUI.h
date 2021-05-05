#pragma once
class CDrakenUI
{
	// HP
	CMonster* m_monster;
	vector3 m_hpUIPos;
	SHARED(Engine::CGameObject) m_hpUI[2];

	_int* m_hp;
	_float m_curHp;
	_int* m_hpMax;
	_float m_hpUiScaleX;
	vector3 m_oldPos;
	_float m_downSpeed;
public:
	CDrakenUI(CMonster* monster);
	~CDrakenUI();

	void Start();

	void Update();
	void OnDestory();

	void  SetMonsterHP(_int* hp, _int* hpMax);

};

