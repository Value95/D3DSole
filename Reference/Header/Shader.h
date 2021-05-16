#ifndef SHADER_H
#define SHADER_H

BEGIN(Engine)
class ENGINE_DLL CShader
{
protected:
	GETTOR_SETTOR(CGameObject*, m_gameobject, {}, GameObject);
	GETTOR_SETTOR(std::wstring, m_shaderKey, {}, ShaderKey);
	GETTOR_SETTOR(LPD3DXEFFECT, m_effectShader, {}, EffectShader);	// ���̴��� �����ϱ� ���� ����Լ��� ���� �İ�ü
	LPD3DXBUFFER m_pErrMsg;	// void*���� ���� �޼����� ���� ���ڿ��� �����ϱ� ���� ����

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

