#include "stdafx.h"
#include "ShaderSkyBox.h"
#include "ShaderStore.h"

CShaderSkyBox::CShaderSkyBox()
{
}


CShaderSkyBox::~CShaderSkyBox()
{
}

Engine::CShader* CShaderSkyBox::Create()
{
	Engine::CShader* T = new CShaderSkyBox();
	return T;
}

void CShaderSkyBox::State()
{
	m_effectShader = *Engine::CShaderStore::GetInstance()->GetShaderData(L"Shader_SkyBox.hpp");
}

void CShaderSkyBox::Update()
{
}

void CShaderSkyBox::PreRender()
{

	m_effectShader->SetMatrix("g_matWorld", &m_gameobject->GetWorldMatrix());
	m_effectShader->SetMatrix("g_matView", &Engine::GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	m_effectShader->SetMatrix("g_matProj", &Engine::GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	m_effectShader->SetTexture("g_BaseTexture", m_gameobject->GetComponent<Engine::CStaticMeshRenderComponent>()->GetMesh()->GetMeshData()->texture[0]);
}

void CShaderSkyBox::Render()
{
}