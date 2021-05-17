#ifndef SKYBOXCOMPONENT_H
#define SKYBOXCOMPONENT_H

BEGIN(Engine)
class CShader;
class ENGINE_DLL CSkyBoxComponent final : public CComponent
{
private:
	GETTOR_SETTOR(CShader*, m_shader,{}, Shader)

	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // �̹����� �ҷ��� Ű��
	GETTOR_SETTOR(IDirect3DBaseTexture9*, m_pTexData, nullptr, TexData) // �̹����� ������ ����

	_MeshData m_meshDate; // ���ؽ� ,�ε��� ���۸������ϱ� ���� ����

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
