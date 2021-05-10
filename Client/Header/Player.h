#ifndef PLAYER_H
#define PLAYER_H

class FSM;
class CPlayerInfo;
class CPlayerHP;
class CPlayer final : public Engine::CComponent
{
public:	enum STATE {IDLE, MOVE, ATTACK, DEATH, DESHATTACK, HIT, DEBUGMODE, ATTACK2, STATEEND};

private:
	FSM* m_playerFSM[STATE::STATEEND];
	GETTOR(STATE, m_playerState, STATE::IDLE, PlayerState);
	GETTOR_SETTOR(CPlayerInfo*, m_playerInfo, {}, PlayerInfo);
	GETTOR_SETTOR(_bool, m_idleLook, {}, IdleLook);

	GETTOR_SETTOR(SHARED(Engine::CAnimMeshRenderComponent), m_anim, nullptr, Anim);
	CPlayerHP* m_playerHP;
public:
	explicit CPlayer(void);
	virtual	 ~CPlayer(void);

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

	void ChangeFSM(STATE state);
	void Attack(Engine::CGameObject* gameObject, _float damage);
	void UpAttack(Engine::CGameObject* gameObject, _float force);
	void Hit(_int damage, _int hitType);
	void IdleLookState();
	void IdleLookEnd();
private:
	void FSMCreate();
};

#endif // !PLAYER_H
