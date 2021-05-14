#ifndef BOXCOMPONENT_H
#define BOXCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CBoxComponent final : public CComponent
{
private:
	_MeshData m_meshDate;
	LPD3DXMESH m_mesh;

	GETTOR_SETTOR(vector3, m_size, vector3Zero, Size);
	GETTOR_SETTOR(vector3, m_offSet, vector3Zero, OffSet);
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
