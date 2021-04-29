#include "EngineStdafx.h"
#include "ShaderStore.h"
#include "DeviceManager.h"

#include <fstream>
#include <algorithm>
#include <filesystem>

USING(Engine)
IMPLEMENT_SINGLETON(CShaderStore)

void CShaderStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CShaderStore::ParsingMesh, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Shader";
}

void CShaderStore::Start(void)
{
	__super::Start();
}

void CShaderStore::OnDestroy(void)
{
	m_StaticShaderData.clear();
}

void CShaderStore::ClearCurResource(void)
{
	m_mCurSceneShaderData.clear();
}

LPD3DXEFFECT* CShaderStore::GetShaderData(std::wstring meshKey)
{
	auto iter_find_static = m_StaticShaderData.find(meshKey);
	if (iter_find_static != m_StaticShaderData.end())
		return iter_find_static->second;

	auto iter_find_cur = m_StaticShaderData.find(meshKey);
	if (iter_find_cur != m_StaticShaderData.end())
		return iter_find_cur->second;

	return nullptr;
}

void CShaderStore::InitShaderForScene(std::wstring curScene)
{
	InitResource(m_resourcePath + L"\\" + curScene);
}

void CShaderStore::InitResource(std::wstring sourcePath)
{
	__super::InitResource(sourcePath);
}

void CShaderStore::ParsingMesh(std::wstring filePath, std::wstring fileName)
{
	LPD3DXEFFECT* effectShader = new LPD3DXEFFECT;
	
	/*_wcharT* path = (_wcharT*)filePath.c_str();
	//_wcharT* file = (_wcharT*)fileName.c_str();

	lstrcat(path, L"\\");
	lstrcat(path, (_wcharT*)fileName.c_str());*/

	D3DXCreateEffectFromFile(GET_DEVICE,
		L"..\\..\\Resource\\Shader\\Static\\Shader_Sample.hpp",
		NULL,
		NULL,
		D3DXSHADER_DEBUG, NULL,
		effectShader,
		nullptr);

	if(m_isStatic)
		m_StaticShaderData[fileName] = effectShader;
	else
		m_mCurSceneShaderData[fileName] = effectShader;
	
}