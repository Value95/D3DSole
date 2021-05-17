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
	m_effectShader->Begin(&m_passMaxNumber, 0);	// 1���� : ���� ���̴� ������ ���� �ִ� �н��� ����, 2���� : �����ϴ� ����� ���� ����, default 0
	m_effectShader->BeginPass(m_passNumber);
}

void CShader::ShaderEnd()
{
	m_effectShader->EndPass();
	m_effectShader->End();
}
