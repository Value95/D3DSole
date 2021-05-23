#pragma once
#include "Shader.h"
class CShaderMesh :
	public Engine::CShader
{
	SHARED(Engine::CDirectionalLightComponent) m_light;
public:
	CShaderMesh();
	virtual ~CShaderMesh();

	virtual Engine::CShader* Create();
	virtual void State();
	virtual void Update();
	virtual void PreRender();
	virtual void Render();

};

