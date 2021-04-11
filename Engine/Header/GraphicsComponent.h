#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

BEGIN(Engine)
class CMeshComponent;
class ENGINE_DLL CGraphicsComponent final : public CComponent
{
protected:
	GETTOR(SHARED(CMeshComponent),m_mesh,nullptr,Mesh)

	GETTOR_SETTOR(ERenderID,m_renderID,		ERenderID::Base,	RenderID)

public:
	explicit CGraphicsComponent(void);
	~CGraphicsComponent(void);
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
#endif // !GRAPHICSCOMPONENT_H
