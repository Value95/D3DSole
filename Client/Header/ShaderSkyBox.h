#pragma once
#include "Shader.h"
class CShaderSkyBox :
	public Engine::CShader
{
public:
	CShaderSkyBox();
	virtual ~CShaderSkyBox();

	virtual void State();
	virtual void Update();
	virtual void PreRender();

};

