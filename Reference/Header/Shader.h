#ifndef SHADER_H
#define SHADER_H

BEGIN(Engine)
class ENGINE_DLL CShader
{
protected:
	GETTOR_SETTOR(CGameObject*, m_gameobject, {}, GameObject);
	GETTOR_SETTOR(std::wstring, m_shaderKey, {}, ShaderKey);
	GETTOR_SETTOR(LPD3DXEFFECT, m_effectShader, {}, EffectShader);	// 쉐이더를 적용하기 각종 멤버함수를 지닌 컴객체
	LPD3DXBUFFER m_pErrMsg;	// void*형의 에러 메세지에 따른 문자열을 저장하기 위한 버퍼

	GETTOR_SETTOR(_uint, m_passNumber, 0, PassNumber);
	GETTOR_SETTOR(_uint, m_passMaxNumber, 0, PassMaxNumber);
public:
	explicit CShader(void);
	virtual	~CShader(void);

public:
	virtual void State() PURE;
	virtual void Update() PURE;
	virtual void PreRender() PURE;
	virtual void Render() PURE;

	void ShaderReady();
	void ShaderEnd();
};
END

#endif // !SHADER_H

