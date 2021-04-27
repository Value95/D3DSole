#ifndef UICOMPONENT_H
#define UICOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CUIComponent final : public CComponent
{
private:

	GETTOR_SETTOR(_uint, m_sortingLayer, 0, SortingLayer) // UI의 그려지는 순서 (숫자가 작을수록 빨리그려짐)

	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey) // 이미지를 불러올 키값
	GETTOR_SETTOR(SHARED(_TexData), m_pTexData, nullptr, TexData) // 이미지를 저장할 변수

	vector2 m_xUV; // xUV값을 저장할 변수
	vector2 m_yUV; // xUV값을 저장할 변수

	_MeshData m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수
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
