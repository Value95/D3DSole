#ifndef WORLDUICOMPONENT_H
#define WORLDUICOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CWorldUIComponent final : public CComponent
{
private:
	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // �̹����� �ҷ��� Ű��
	GETTOR_SETTOR(SHARED(_TexData), m_pTexData, nullptr, TexData) // �̹����� ������ ����
	GETTOR_SETTOR(CShader*, m_shader,{}, Shader)

	_MeshData m_meshDate; // ���ؽ� ,�ε��� ���۸������ϱ� ���� ����
public:
	explicit CWorldUIComponent(void);
	virtual ~CWorldUIComponent(void);

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

#endif // !WORLDUICOMPONENT_H
