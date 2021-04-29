#ifndef SHADER_H
#define SHADER_H

BEGIN(Engine)
class ENGINE_DLL CShader
{
private:
	GETTOR_SETTOR(std::wstring, m_shaderKey, {}, ShaderKey);
	GETTOR_SETTOR(LPD3DXEFFECT, m_effectShader, {}, EffectShader);	// ���̴��� �����ϱ� ���� ����Լ��� ���� �İ�ü
	LPD3DXBUFFER m_pErrMsg;	// void*���� ���� �޼����� ���� ���ڿ��� �����ϱ� ���� ����

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
