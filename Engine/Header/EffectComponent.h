#ifndef EFFECTCOMPONENT_H
#define EFFECTCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CEffectComponent final : public CComponent
{
private:
	std::wstring m_textureKey; // 이미지를 불러올 키값
	GETTOR_SETTOR(_int, m_effectCount, 0, EffectCount)
	GETTOR_SETTOR(std::vector<SHARED(_TexData)>, m_texData, {}, TexData) // 이미지를 저장할 변수

	GETTOR_SETTOR(CShader*, m_shader, {}, Shader)

	_MeshData m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수
	_int m_effectCurCount;
	_int m_effectSpeed;
public:
	explicit						CEffectComponent	(void);
	virtual						   ~CEffectComponent	(void);

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

	void Reset(std::wstring textureKey, _int effectCount);
private:
	void DateInit();
};
END

#endif // !TEXTURECOMPONENT_H
