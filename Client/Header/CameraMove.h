#ifndef CAMERAMOVE_H
#define CAMERAMOVE_H

class CCameraMove final : public Engine::CComponent
{
private:
	GETTOR_SETTOR(POINT, m_centerPt, {}, CenterPt);

public:
	explicit CCameraMove(void);
	virtual	 ~CCameraMove(void);

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
	void Sight();
	void CameraCrush();
};

#endif // !CAMERAMOVE_H
