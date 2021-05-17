#ifndef CAMERASHAKE_H
#define CAMERASHAKE_H

class CCameraShake final : public Engine::CComponent
{
private:
	_float m_speed = 500;
	_float m_activationTime = 0;
	_int m_aMount = 0;
	vector3 m_oldPosition = vector3(0, 3, -8);
public:
	explicit CCameraShake(void);
	virtual	 ~CCameraShake(void);

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

	void CameraShakeActivation(_float activationTime, _int aMount);
private:
	void CameraShake();
};

#endif // !CAMERASHAKE_H
