#ifndef LINECOMPONENT_H
#define LINECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CLineComponent final : public CComponent
{
private:
	vector3 m_linePos[2];

public:
	explicit						CLineComponent	(void);
	virtual						   ~CLineComponent	(void);

public:
	SHARED(CComponent)	MakeClone			(CGameObject* pObject) override;

	void Awake(void) override;
	void Start(SHARED(CComponent) spSelf) override;

	_uint FixedUpdate(SHARED(CComponent) spSelf) override;
	_uint Update(SHARED(CComponent) spThis) override;
	_uint LateUpdate(SHARED(CComponent) spThis) override;
		  
	_uint PreRender(void);
	_uint Render(void);
	_uint PostRender(void);

	void OnDestroy(void) override;
		 
	void OnEnable(void) override;
	void OnDisable(void) override;

	void EndLinePosition(vector3 endLine);
private:
	void DateInit();

};
END

#endif // !TEXTURECOMPONENT_H
