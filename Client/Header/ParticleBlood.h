#ifndef PARTICLEBLOOD_H
#define PARTICLEBLOOD_H

class CParticleBlood final : public Engine::CComponent
{
private:
	// 퍼질각도
	GETTOR_SETTOR(vector3, m_force, vector3Zero, Force);
	vector3 m_forceMin;
public:
	explicit CParticleBlood(void);
	virtual	 ~CParticleBlood(void);

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

private:

};

#endif // !PARTICLEBLOOD_H
