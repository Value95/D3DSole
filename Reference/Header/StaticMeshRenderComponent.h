#ifndef STATICMESHRENDERCOMPONENT_H
#define STATICMESHRENDERCOMPONENT_H

BEGIN(Engine)
class CMeshComponent;
class CShader;
class ENGINE_DLL CStaticMeshRenderComponent final : public CComponent
{
protected:
	GETTOR_SETTOR(CShader*, m_shader,{}, Shader)
	GETTOR(SHARED(CMeshComponent),m_mesh,nullptr,Mesh)
	GETTOR_SETTOR(ERenderID, m_renderID,	ERenderID::Base, RenderID)

	_bool m_fixedCheck;
public:
	explicit CStaticMeshRenderComponent(void);
	~CStaticMeshRenderComponent(void);
public:
	SHARED(CComponent) MakeClone(CGameObject* pObject)	override;

	void Awake(void) override;
	void Start(SHARED(CComponent) spThis) override;

	_uint FixedUpdate(SHARED(CComponent) spThis) override;
	_uint Update(SHARED(CComponent) spThis) override;
	_uint LateUpdate(SHARED(CComponent) spThis) override;
		  
	_uint PreRender(void);
	_uint Render(void);
	_uint PostRender(void);	

	void OnDestroy(void) override;
		 
	void OnDisable(void) override;
	void OnEnable(void) override;
};
END
#endif // !STATICMESHRENDERCOMPONENT_H
