#include "EngineStdafx.h"
#include "HierarchyLoader.h"
#include "DeviceManager.h"

USING(Engine)

Engine::CHierarchyLoader::CHierarchyLoader()
{
}

CHierarchyLoader::CHierarchyLoader(const _wcharT * pPath)
{
	m_filePath = pPath;
}

Engine::CHierarchyLoader::~CHierarchyLoader(void)
{

}

STDMETHODIMP Engine::CHierarchyLoader::CreateFrame(THIS_ LPCSTR Name,
												LPD3DXFRAME *ppNewFrame)
{
	D3DXFRAME_DERIVED*		pFrame = new D3DXFRAME_DERIVED;
	ZeroMemory(pFrame, sizeof(D3DXFRAME_DERIVED));

	Allocate_Name(&pFrame->Name, Name);

	pFrame->CombinedTransformationMatrix = *D3DXMatrixIdentity(&pFrame->TransformationMatrix);

	*ppNewFrame = pFrame;

	return S_OK;
}

STDMETHODIMP Engine::CHierarchyLoader::CreateMeshContainer(THIS_ LPCSTR Name, // 메시의 이름
	CONST D3DXMESHDATA *pMeshData,  // 메시 데이터 구조체 (유니온으로되어있다.)
	CONST D3DXMATERIAL *pMaterials,  // 메시의 메터리얼 정보 구조체의 포인터
	CONST D3DXEFFECTINSTANCE *pEffectInstances, // EffectInstance 구조체의 포인터
	DWORD NumMaterials, // 메터리얼 갯수
	CONST DWORD *pAdjacency, // 인접정보를 갖고 있는 DWORD형의 삼각형 하나당 3개의 배열의 포인터
	LPD3DXSKININFO pSkinInfo, // 스킨 정보를 가지고있는 ID3DXKININFO인터페이스의 포인터 (인터페이스이다) 단순하게 스킨정보를 가지고있는 녀석 해당정보를 함수로 여람하고 조작할수있다.
	LPD3DXMESHCONTAINER *ppNewMeshContainer) // 링크드 리스트
{
	D3DXMESHCONTAINER_DERIVED*		pMeshContainer = new D3DXMESHCONTAINER_DERIVED;

	Allocate_Name(&pMeshContainer->Name, Name);

	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH	pMesh = pMeshData->pMesh;

	_ulong	dwNumFaces = pMesh->GetNumFaces();

	_ulong	dwFVF = pMesh->GetFVF();

	// 메쉬의 노말 정보가 없는 경우 코드로 삽입
	if (!(dwFVF & D3DFVF_NORMAL))
	{
		pMeshData->pMesh->CloneMeshFVF(
			pMeshData->pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			GET_DEVICE,
			&pMeshContainer->MeshData.pMesh);

		D3DXComputeNormals(pMeshContainer->MeshData.pMesh, pMeshContainer->pAdjacency);
	}
	else
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF, GET_DEVICE, &pMeshContainer->MeshData.pMesh);
	}

	pMeshContainer->NumMaterials = (NumMaterials == 0 ? 1 : NumMaterials);

	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

	pMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	if (0 != NumMaterials)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

		for (_ulong i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			_wcharT		szFullPath[256] = L"";
			_wcharT		szFileName[256] = L"";

			lstrcpy(szFullPath, m_filePath);

			MultiByteToWideChar(CP_ACP,
				0,
				pMeshContainer->pMaterials[i].pTextureFilename,
				strlen(pMeshContainer->pMaterials[i].pTextureFilename),
				szFileName,
				256);

			lstrcat(szFullPath, szFileName);

			if (FAILED(D3DXCreateTextureFromFile(GET_DEVICE, szFullPath, &pMeshContainer->ppTexture[i])))
				return E_FAIL;
		}
	}
	else
	{
		pMeshContainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Power = 0.f;

		pMeshContainer->ppTexture[0] = nullptr;
	}

	if (nullptr == pSkinInfo)
		return S_OK;

	pMeshContainer->pSkinInfo = pSkinInfo;
	pMeshContainer->pSkinInfo->AddRef();


	pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(), dwFVF, GET_DEVICE, &pMeshContainer->pOriginalMesh);

	// 메쉬 컨테이너에 영향을 미치는 뼈의 개수를 반환
	pMeshContainer->iNumBones = pMeshContainer->pSkinInfo->GetNumBones();

	pMeshContainer->pOffsetMatrices = new matrix4x4[pMeshContainer->iNumBones];
	ZeroMemory(pMeshContainer->pOffsetMatrices, sizeof(matrix4x4) * pMeshContainer->iNumBones);

	pMeshContainer->ppCombinedTransformationMatrices = new matrix4x4*[pMeshContainer->iNumBones];
	ZeroMemory(pMeshContainer->ppCombinedTransformationMatrices, sizeof(matrix4x4*) * pMeshContainer->iNumBones);

	pMeshContainer->pRenderingMatrices = new matrix4x4[pMeshContainer->iNumBones];
	ZeroMemory(pMeshContainer->pRenderingMatrices, sizeof(matrix4x4) * pMeshContainer->iNumBones);

	for (_ulong i = 0; i < pMeshContainer->iNumBones; ++i)
		pMeshContainer->pOffsetMatrices[i] = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	*ppNewMeshContainer = pMeshContainer;

	return S_OK;
}

STDMETHODIMP Engine::CHierarchyLoader::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	SafeDeleteArray(pFrameToFree->Name);

	if (nullptr != pFrameToFree->pMeshContainer)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	if (nullptr != pFrameToFree->pFrameSibling)
		DestroyFrame(pFrameToFree->pFrameSibling);

	if (nullptr != pFrameToFree->pFrameFirstChild)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	SafeDelete(pFrameToFree);

	return S_OK;
}

STDMETHODIMP Engine::CHierarchyLoader::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	D3DXMESHCONTAINER_DERIVED*	pDerivedMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerToFree;

	for (_ulong i = 0; i < pDerivedMeshContainer->NumMaterials; ++i)
		SafeRelease(pDerivedMeshContainer->ppTexture[i]);

	SafeDeleteArray(pDerivedMeshContainer->ppTexture);

	SafeDeleteArray(pDerivedMeshContainer->pMaterials);
	SafeDeleteArray(pDerivedMeshContainer->pAdjacency);

	SafeRelease(pDerivedMeshContainer->MeshData.pMesh);
	SafeRelease(pDerivedMeshContainer->pOriginalMesh);
	SafeRelease(pDerivedMeshContainer->pSkinInfo);

	SafeDeleteArray(pDerivedMeshContainer->Name);

	SafeDelete(pDerivedMeshContainer);

	return S_OK;
}

CHierarchyLoader * CHierarchyLoader::Create(const _wcharT * filePath)
{
	CHierarchyLoader* pInstance = new CHierarchyLoader(filePath);

	if (FAILED(pInstance->Start(filePath)))
		SafeRelease(pInstance);

	return pInstance;
}

HRESULT CHierarchyLoader::Start(const _wcharT * filePath)
{
	m_filePath = filePath;

	return S_OK;
}

void CHierarchyLoader::Allocate_Name(char** ppSour, const char * pDest)
{
	if (nullptr == pDest)
		return;

	_uint		iLength = strlen(pDest);

	*ppSour = new char[iLength + 1];

	strcpy_s(*ppSour, iLength + 1, pDest);
}

void CHierarchyLoader::OnDestroy()
{
}

