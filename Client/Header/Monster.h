#ifndef MONSTER_H
#define MONSTER_H

class MonsterFSM;
class CMonsterInfo;
class CMonster final : public Engine::CComponent
{
public:	enum DRAKEN_STATE { IDLE, MOVE, ATTACK1, ATTACK2, PRODUCTION, DEATH, STATEEND };
public:	enum SOLDIERSPEAR_STATE { SOLDIERSPEARIDLE, SOLDIERSPEARMOVE, SOLDIERSPEARATTACK1, SOLDIERSPEARHIT, SOLDIERSPEARDEATH, SOLDIERSPEARSTATEEND };

private:
	GETTOR_SETTOR(vector<MonsterFSM*>, m_monsterFSM, {}, MonsterFSM);
	GETTOR_SETTOR(MonsterFSM*, m_monsterMaintenanceFSM, {}, MonsterMaintenanceFSM);
	GETTOR(_int, m_monsterState, 0, MonsterState);
	GETTOR_SETTOR(CMonsterInfo*, m_monsterInfo, {}, MonsterInfo);
	GETTOR(SHARED(Engine::CGameObject), m_player, {}, Player);
	GETTOR(SHARED(CPlayer), m_playerCom, {}, PlayerCom);

	GETTOR(_bool, m_hitCheck, 0, HitCheck);

	GETTOR_SETTOR(SHARED(Engine::CAnimMeshRenderComponent), m_anim, nullptr, Anim);

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

	void Hit(_int damage);
	void AddFSM(MonsterFSM* fsm);
	void Attack(_float damage);

	template <typename FSMType>
	void AddFSM(void)
	{
		m_monsterState = 0;
		FSMType* fsm = new FSMType(this);
		m_monsterFSM.emplace_back(fsm);
	}

private:
	void HitEffect();
};

#endif // !MONSTER_H
