#ifndef ANIMCOMPONENT_H
#define ANIMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CAnimComponent final : public CComponent
{
private:

public:
	explicit CAnimComponent(void);
	virtual	~CAnimComponent(void);
public:
	SHARED(CComponent) MakeClone(CGameObject* pObject) override;

	void Awake(void) override;
	void Start(SHARED(CComponent) spSelf) override;

	_uint FixedUpdate(SHARED(CComponent) spSelf) override;
	_uint Update(SHARED(CComponent) spThis) override;
	_uint LateUpdate(SHARED(CComponent) spThis) override;

	void OnDestroy(void) override;
		 
	void OnEnable(void) override;
	void OnDisable(void) override;
};
END

#endif // !ANIMCOMPONENT_H
