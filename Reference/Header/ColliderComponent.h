#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H


BEGIN(Engine)
class CCollider;
class ENGINE_DLL CColliderComponent final : public CComponent
{
public:
	explicit CColliderComponent(void);
	~CColliderComponent(void);
public:
	virtual SHARED(CComponent) MakeClone(CGameObject* pObject) override;

	virtual void Awake();
	virtual void Start(SHARED(CComponent) spThis) override;

	virtual _uint FixedUpdate(SHARED(CComponent) spThis) override;
	virtual _uint Update(SHARED(CComponent) spThis) override;
	virtual _uint LateUpdate(SHARED(CComponent) spThis) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;

	CColliderComponent* AddCollider(CCollider* collider);

protected:
	GETTOR_SETTOR(std::vector<CCollider*>, m_vColliders,{}, Colliders)
};
END

#endif // COLLIDERCOMPONENT_H