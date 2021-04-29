#ifndef SHADER_H
#define SHADER_H

BEGIN(Engine)
class ENGINE_DLL CShader
{
private:
	GETTOR_SETTOR(std::wstring, m_shaderKey, {}, ShaderKey);
	GETTOR_SETTOR(LPD3DXEFFECT, m_effectShader, {}, EffectShader);	// 쉐이더를 적용하기 각종 멤버함수를 지닌 컴객체
	LPD3DXBUFFER m_pErrMsg;	// void*형의 에러 메세지에 따른 문자열을 저장하기 위한 버퍼

public:
	explicit CShader(void);
	virtual	~CShader(void);

public:
	static CShader* Create(std::wstring shaderKey);
	void ShaderReady();
	void ShaderEnd();
};
END

#endif // !SHADER_H
