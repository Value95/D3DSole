#ifndef SKYBOXCOMPONENT_H
#define SKYBOXCOMPONENT_H

BEGIN(Engine)
class CShader;
class ENGINE_DLL CSkyBoxComponent final : public CComponent
{
private:
	GETTOR_SETTOR(CShader*, m_shader,{}, Shader)

	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // 이미지를 불러올 키값
	GETTOR_SETTOR(IDirect3DBaseTexture9*, m_pTexData, nullptr, TexData) // 이미지를 저장할 변수

	_MeshData m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수

public:
	explicit CSkyBoxComponent(void);
	virtual	~CSkyBoxComponent(void);

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

#endif // !SKYBOXCOMPONENT_H
