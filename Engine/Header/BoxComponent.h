#ifndef BOXCOMPONENT_H
#define BOXCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CBoxComponent final : public CComponent
{
private:
	_MeshData m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수
	LPD3DXMESH m_mesh;

public:
	explicit CBoxComponent(void);
	virtual	 ~CBoxComponent(void);

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

private:
	void DateInit();

};
END

#endif // !TEXTURECOMPONENT_H
