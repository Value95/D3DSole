#ifndef TRIANGLECOMPONENT_H
#define TRIANGLECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTriangleComponent final : public CComponent
{
private:
	_MeshData m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수
	vector3 m_position[3];
public:
	explicit CTriangleComponent(void);
	virtual	~CTriangleComponent(void);

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
