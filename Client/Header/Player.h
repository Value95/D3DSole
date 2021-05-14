#ifndef PLAYER_H
#define PLAYER_H

class FSM;
class CPlayerInfo;
class CPlayerHP;
class CPlayerDushUI;
class CPlayerUI;
class CPlayer final : public Engine::CComponent
{
public:	enum STATE {IDLE, MOVE, ATTACK, DEATH, HIT, DEBUGMODE, UPPERCUT, ROLL, MINIPICKAXE, RUSH, INTERACTION, STATEEND};

private:
	FSM* m_playerFSM[STATE::STATEEND];
	GETTOR(STATE, m_playerState, STATE::IDLE, PlayerState);
	GETTOR(STATE, m_playerOldState, STATE::IDLE, PlayerOldState);
	GETTOR_SETTOR(CPlayerInfo*, m_playerInfo, {}, PlayerInfo);

	GETTOR_SETTOR(SHARED(Engine::CAnimMeshRenderComponent), m_anim, nullptr, Anim);
	GETTOR_SETTOR(SHARED(Engine::CRigidBodyComponent), m_rigidbody, nullptr, RigidBody);
	CPlayerHP* m_playerHP;
	CPlayerDushUI* m_playerDushUI;
	CPlayerUI* m_playerUI;

	GETTOR_SETTOR(_int, m_uppercutCount, 0, UppercutCount);
	GETTOR(_int, m_uppercutMaxCount, 3, UppercutMaxCount);
	GETTOR_SETTOR(_int, m_waponPosNumber, 0, WaponPosNumber);

	GETTOR_SETTOR(_bool, m_idleLook, {}, IdleLook);

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
	void Hit(_int damage, _int hitType);
	void IdleLookState();
	void IdleLookEnd();
	void UpperCutCountReset();
	bool MoveCheck(vector3 dir, _float moveCheckDir);

private:
	void FSMCreate();
};

#endif // !PLAYER_H
