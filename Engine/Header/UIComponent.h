#ifndef UICOMPONENT_H
#define UICOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CUIComponent final : public CComponent
{
private:

	GETTOR_SETTOR(_uint, m_sortingLayer, 0, SortingLayer) // UI�� �׷����� ���� (���ڰ� �������� �����׷���)

	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // �̹����� �ҷ��� Ű��
	GETTOR_SETTOR(SHARED(_TexData), m_pTexData, nullptr, TexData) // �̹����� ������ ����

	vector2 m_xUV; // xUV���� ������ ����
	vector2 m_yUV; // xUV���� ������ ����

	_MeshData m_meshDate; // ���ؽ� ,�ε��� ���۸������ϱ� ���� ����
public:
	explicit						CUIComponent	(void);
	virtual						   ~CUIComponent	(void);

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

	void SetXUV(vector2 value);
	void SetYUV(vector2 value);
private:
	void DateInit();
	void UVSetting();
};
END

#endif // !TEXTURECOMPONENT_H
