#pragma once
#include "Shader.h"
class CShaderSkyBox :
	public Engine::CShader
{
public:
	CShaderSkyBox();
	virtual ~CShaderSkyBox();


	// CShader을(를) 통해 상속됨
	virtual Engine::CShader* Create() override;
	virtual void State() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

};

