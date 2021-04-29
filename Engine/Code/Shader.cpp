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

	m_effectShader->Begin(&iMaxPass, 0);	// 1인자 : 현재 쉐이더 파일이 지닌 최대 패스의 개수, 2인자 : 시작하는 방식을 묻는 인자, default 0
	m_effectShader->BeginPass(0);
}

void CShader::ShaderEnd()
{
	
	m_effectShader->EndPass();
	m_effectShader->End();
}
