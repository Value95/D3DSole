#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

BEGIN(Engine)
class ENGINE_DLL CParticleSystem final : public CComponent
{

	struct particleObj
{
	void Push(std::shared_ptr<CGameObject> obj, float time)
	{
		object = obj;
		lifeTime = time;
	}

	std::shared_ptr<CGameObject> object;
	float lifeTime;
};

protected:
	std::vector<SHARED(CGameObject)> m_offObject;
	std::vector<particleObj> m_onObject;

	GETTOR_SETTOR(std::wstring, m_particleKey, {}, ParticleKey)
	GETTOR_SETTOR(_float, m_lifeTime, 0, LifeTime)
	GETTOR_SETTOR(_int, m_enableCount, 0, EnableCout) // 한번 돌때 나올 오브젝트의 갯수

	_int m_curCount = 0;
public:
	explicit CParticleSystem(void);
	virtual	~CParticleSystem(void);
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

	void Init(std::wstring keyValue, _float lifeTime, _int enableCount);
	void play();

private:
	void DeathObject();
};
END

#endif // !PARTICLESYSTEM_H

