#include "stdafx.h"
#include "ShaderMesh.h"
#include "ShaderStore.h"

CShaderMesh::CShaderMesh()
{
}

CShaderMesh::~CShaderMesh()
{
}

void CShaderMesh::State()
{
	m_effectShader = *Engine::CShaderStore::GetInstance()->GetShaderData(L"Shader_Sample.hpp");
}

void CShaderMesh::Update()
{
}

void CShaderMesh::PreRender()
{
	//m_effectShader->SetMatrix("g_matWorld", &m_gameobject->GetWorldMatrix());
	m_effectShader->SetMatrix("g_matView", &Engine::GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	m_effectShader->SetMatrix("g_matProj", &Engine::GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());
}

void CShaderMesh::Render()
{

}
