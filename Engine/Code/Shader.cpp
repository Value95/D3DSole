#include "EngineStdafx.h"
#include "Shader.h"
#include "ShaderStore.h"

USING(Engine)
CShader::CShader()
{
}

CShader::~CShader(void)
{
}

void CShader::ShaderReady()
{
	m_passMaxNumber = 0;
	m_effectShader->Begin(&m_passMaxNumber, 0);	// 1인자 : 현재 쉐이더 파일이 지닌 최대 패스의 개수, 2인자 : 시작하는 방식을 묻는 인자, default 0
	m_effectShader->BeginPass(m_passNumber);
}

void CShader::ShaderEnd()
{
	m_effectShader->EndPass();
	m_effectShader->End();
}
