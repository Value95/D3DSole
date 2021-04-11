#include "EngineStdafx.h"
#include "MeshStore.h"
#include "DeviceManager.h"

#include <fstream>
#include <algorithm>
#include <filesystem>

USING(Engine)
IMPLEMENT_SINGLETON(CMeshStore)

void CMeshStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CMeshStore::ParsingMesh, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Mesh";
}

void CMeshStore::Start(void)
{
	__super::Start();
}

void CMeshStore::OnDestroy(void)
{
	m_mStaticMeshData.clear();
	m_mCurSceneMeshData.clear();
}

void CMeshStore::ClearCurResource(void)
{
	m_mCurSceneMeshData.clear();
}

SHARED(MeshComData) CMeshStore::GetMeshData(std::wstring meshKey)
{
	auto iter_find_static = m_mStaticMeshData.find(meshKey);
	if (iter_find_static != m_mStaticMeshData.end())
		return iter_find_static->second;

	auto iter_find_cur = m_mCurSceneMeshData.find(meshKey);
	if (iter_find_cur != m_mCurSceneMeshData.end())
		return iter_find_cur->second;

	return nullptr;
}

void CMeshStore::InitMeshForScene(std::wstring curScene)
{
	InitResource(m_resourcePath + L"\\" + curScene);
}

void CMeshStore::InitResource(std::wstring sourcePath)
{
	__super::InitResource(sourcePath);
}

void CMeshStore::ParsingMesh(std::wstring filePath, std::wstring fileName)
{
	string temp;
	temp = temp.assign(fileName.begin(), fileName.end());
	if (GetExt(temp) != "X")
		return;

	SHARED(MeshComData) TmeshComData(new MeshComData);
	TmeshComData->name = fileName;

	_wcharT	fullPath[MAX_PATH] = L"";// 경로가 저장된다.

	lstrcpy(fullPath, filePath.c_str());
	lstrcat(fullPath, L"//");
	lstrcat(fullPath, fileName.c_str());

	
	D3DXLoadMeshFromX(fullPath, D3DXMESH_MANAGED, GET_DEVICE, &TmeshComData->adjacency, &TmeshComData->materials, nullptr, &TmeshComData->materialsCount, &TmeshComData->mesh);

	// D3DXMATERIAL
	for (_ulong i = 0; i < TmeshComData->materialsCount; ++i)
	{
		D3DXMATERIAL*	pMaterials = (D3DXMATERIAL*)TmeshComData->materials->GetBufferPointer();

		lstrcpy(fullPath, filePath.c_str());
		lstrcat(fullPath, L"//");

		_wcharT	textureName[MAX_PATH] = L"";

		MultiByteToWideChar(CP_ACP, 0, pMaterials[i].pTextureFilename, strlen(pMaterials[i].pTextureFilename), textureName, MAX_PATH);

		lstrcat(fullPath, textureName);

		IDirect3DBaseTexture9*	Ttexture = nullptr;
		if (FAILED(D3DXCreateTextureFromFile(GET_DEVICE, fullPath, (LPDIRECT3DTEXTURE9*)&Ttexture)))
			return;
		TmeshComData->texture.emplace_back(Ttexture);

		//TmeshComData->AddTexture(GET_DEVICE, fullPath);
	}

	m_mStaticMeshData[fileName] = TmeshComData;
	
}