#include "stdafx.h"
#include "ShaderMesh.h"
#include "ShaderStore.h"

CShaderMesh::CShaderMesh()
{
}

CShaderMesh::~CShaderMesh()
{
}

Engine::CShader* CShaderMesh::Create()
{
	Engine::CShader* T = new CShaderMesh();
	return T;
}

void CShaderMesh::State()
{
	m_effectShader = *Engine::CShaderStore::GetInstance()->GetShaderData(L"Shader_Mesh.hpp");
	m_light = Engine::GET_CUR_SCENE->FindObjectByName(L"DirectionalLight")->GetComponent<Engine::CDirectionalLightComponent>();
}

void CShaderMesh::Update()
{
}

void CShaderMesh::PreRender()
{
	m_effectShader->SetVector("g_vLightDir", &D3DXVECTOR4(m_light->GetLight().Direction,0));
	m_effectShader->SetVector("g_vCamPos", &D3DXVECTOR4(Engine::GET_MAIN_CAM->GetOwner()->GetPosition(),0));
	m_effectShader->SetVector("g_vLightDiffuse", (D3DXVECTOR4*)&m_light->GetLight().Diffuse);
	m_effectShader->SetVector("g_vLightAmbient", (D3DXVECTOR4*)&m_light->GetLight().Ambient);
	m_effectShader->SetVector("g_vMtrlDiffuse", (D3DXVECTOR4*)&m_light->GetLight().Diffuse);
	m_effectShader->SetVector("g_vMtrlSpecular", (D3DXVECTOR4*)&m_light->GetLight().Specular);
	m_effectShader->SetVector("g_vMtrlAmbient", (D3DXVECTOR4*)&m_light->GetLight().Ambient);
	m_effectShader->SetFloat("g_fPower", 10.0f);
	m_effectShader->SetFloat("g_fDetail", 20.0f);

	m_effectShader->SetMatrix("g_matWorld", &m_gameobject->GetWorldMatrix());
	m_effectShader->SetMatrix("g_matView", &Engine::GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	m_effectShader->SetMatrix("g_matProj", &Engine::GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

}

void CShaderMesh::Render()
{

}
