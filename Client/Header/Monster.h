#ifndef MONSTER_H
#define MONSTER_H

class CMonsterInfo;
class CMonster final : public Engine::CComponent
{
private:
	GETTOR_SETTOR(vector<FSM*>, m_monsterFSM, {}, MonsterFSM);
	GETTOR(_int, m_monsterState, 0, MonsterState);
	GETTOR_SETTOR(CMonsterInfo*, m_monsterInfo, {}, MonsterInfo);
	SHARED(Engine::CGameObject) m_player;

public:
	explicit CMonster(void);
	virtual	 ~CMonster(void);

public:
	SHARED(Engine::CComponent) MakeClone(Engine::CGameObject* pObject) override;

	void Awake(void) override;
	void Start(SHARED(CComponent) spSelf) override;

	_uint FixedUpdate(SHARED(CComponent) spSelf) override;
	_uint Update(SHARED(CComponent) spThis) override;
	_uint LateUpdate(SHARED(CComponent) spThis) override;
		  
	void OnDestroy(void) override;
		 
	void OnEnable(void) override;
	void OnDisable(void) override;

	void ChangeFSM(_int state);

	template <typename FSMType>
	void AddFSM(void)
	{
		FSMType* fsm = new FSMType(this);
		m_monsterFSM.emplace_back(fsm);
		m_monsterFSM[0]->Start();
	}

	void Hit(_int damage);
private:
	void HitEffect();

};

#endif // !MONSTER_H
