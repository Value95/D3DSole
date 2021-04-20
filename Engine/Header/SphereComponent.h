#ifndef SPHERECOMPONENT_H
#define SPHERECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CSphereComponent final : public CComponent
{
private:
	_MeshData m_meshDate; // ���ؽ� ,�ε��� ���۸������ϱ� ���� ����
	LPD3DXMESH m_mesh;

	GETTOR_SETTOR(_float, radus, 0.5f, Radus);
public:
	explicit CSphereComponent(void);
	virtual ~CSphereComponent(void);

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

};
END

#endif // !TEXTURECOMPONENT_H
