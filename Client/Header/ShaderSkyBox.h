#pragma once
#include "Shader.h"
class CShaderSkyBox :
	public Engine::CShader
{
public:
	CShaderSkyBox();
	virtual ~CShaderSkyBox();


	// CShader��(��) ���� ��ӵ�
	virtual Engine::CShader* Create() override;
	virtual void State() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

};

