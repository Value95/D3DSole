#ifndef DRAKENWAPON_H
#define DRAKENWAPON_H

class CDrakenWapon  final : public Engine::CComponent
{
private:
	const matrix4x4* m_parentBoneMatrix = nullptr;
	const matrix4x4* m_parentWorldMatrix = nullptr;

	SHARED(Engine::CGameObject)	m_drakenObj;
public:
	explicit CDrakenWapon();
	virtual ~CDrakenWapon();

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

#endif // !DRAKENWAPON_H