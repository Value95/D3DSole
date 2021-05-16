#pragma once
#include "Shader.h"
class CShaderMesh :
	public Engine::CShader
{
public:
	CShaderMesh();
	virtual ~CShaderMesh();

	virtual void State();
	virtual void Update();
	virtual void PreRender();
	virtual void Render();

};

