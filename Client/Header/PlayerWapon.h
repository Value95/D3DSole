#ifndef PLAYERWAPON_H
#define PLAYERWAPON_H

class CPlayer;
class CPlayerWapon  final : public Engine::CComponent
{
private:
	 vector<const matrix4x4*> m_parentBoneMatrix;
	const matrix4x4* m_parentWorldMatrix = nullptr;

	SHARED(Engine::CGameObject)	m_playerObj;
	SHARED(CPlayer)	m_playerCom;
public:
	explicit CPlayerWapon();
	virtual ~CPlayerWapon();

public:
	virtual std::shared_ptr<Engine::CComponent> MakeClone(Engine::CGameObject *pObject);

	void Awake(void) override;
	void Start(SHARED(CComponent) spSelf) override;

	_uint FixedUpdate(SHARED(CComponent) spSelf) override;
	_uint Update(SHARED(CComponent) spThis) override;
	_uint LateUpdate(SHARED(CComponent) spThis) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

private:
	void Wapon0();
	void Wapon1();
};

#endif // !PLAYERWAPON_H