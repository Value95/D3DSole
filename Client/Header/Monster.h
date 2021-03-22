#ifndef MONSTER_H
#define MONSTER_H

class CMonster final : public Engine::CComponent
{
private:
	SHARED(Engine::CGameObject) player;
public:
	explicit CMonster(void);
	virtual	 ~CMonster(void);

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

#endif // !TEXTURECOMPONENT_H
