#ifndef PLAYERMINIGOCK_H
#define PLAYERMINIGOCK_H

class CPlayer;
class CPlayerMiniGock  final : public Engine::CComponent
{
private:
	 const matrix4x4* m_parentBoneMatrix;
	const matrix4x4* m_parentWorldMatrix = nullptr;

	SHARED(Engine::CGameObject)	m_playerObj;
	SHARED(CPlayer)	m_playerCom;
public:
	explicit CPlayerMiniGock();
	virtual ~CPlayerMiniGock();

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

};

#endif // !PLAYERMINIGOCK_H