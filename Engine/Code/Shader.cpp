#include "EngineStdafx.h"
#include "Shader.h"

USING(Engine)
CShader::CShader()
{
}

CShader::~CShader(void)
{
}

CShader* CShader::Create(std::wstring shaderKey)
{
	CShader* T = new CShader();
	T->SetShaderKey(shaderKey);

	return T;
}

void CShader::ShaderReady()
{
	_uint	iMaxPass = 0;

	m_effectShader->Begin(&iMaxPass, 0);	// 1���� : ���� ���̴� ������ ���� �ִ� �н��� ����, 2���� : �����ϴ� ����� ���� ����, default 0
	m_effectShader->BeginPass(0);
}

void CShader::ShaderEnd()
{
	
	m_effectShader->EndPass();
	m_effectShader->End();
}
