#include "EngineStdafx.h"
#include "AnimMeshRenderComponent.h"
#include "DeviceManager.h"
#include "AnimMeshRenderManager.h"
#include "SceneManager.h"
#include "Scene.h"

USING(Engine)
CAnimMeshRenderComponent::CAnimMeshRenderComponent(void)  
{
}

CAnimMeshRenderComponent::~CAnimMeshRenderComponent(void)
{
}

SHARED(CComponent) CAnimMeshRenderComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CAnimMeshRenderComponent) pClone(new CAnimMeshRenderComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetRenderID(m_renderID);

	pClone->SetLoader(m_pLoader);
	pClone->SetRootFrame(m_pRootFrame);
	pClone->SetAnimCtrl(m_pAniCtrl);
	pClone->SetMeshContainers(m_vMeshContainers);

	return pClone;
}
void CAnimMeshRenderComponent::Awake(void)
{
	__super::Awake();
}

void CAnimMeshRenderComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	Set_AnimationSet(0);

}

_uint CAnimMeshRenderComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CAnimMeshRenderComponent::Update(SHARED(CComponent) spThis /* Shared pointer of current component*/)
{
	Play_Animation(deltaTime);

	return _uint();
}

_uint CAnimMeshRenderComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CAnimMeshRenderManager::GetInstance()->
		AddToRenderList(m_renderID, std::dynamic_pointer_cast<CAnimMeshRenderComponent>(spThis));

	return NO_EVENT;
}

_uint CAnimMeshRenderComponent::PreRender(void)
{
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	return NO_EVENT;
}

_uint CAnimMeshRenderComponent::Render(void)
{
	for (auto& iter : m_vMeshContainers)
	{
		D3DXMESHCONTAINER_DERIVED*		pMeshContainer = iter;

		for (_uint i = 0; i < pMeshContainer->iNumBones; ++i)
		{
			pMeshContainer->pRenderingMatrices[i] = pMeshContainer->pOffsetMatrices[i] * (*pMeshContainer->ppCombinedTransformationMatrices[i]);
		}

		void*		pSrcVertices = nullptr;
		void*		pDestVertices = nullptr;

		pMeshContainer->pOriginalMesh->LockVertexBuffer(0, &pSrcVertices);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVertices);

		// 소프트웨어 스키닝을 수행해주는 함수,동시에 스키닝 뿐 아니라 애니메이션 변경 시, 뼈대들과 정점 정보들의 변경을 수행
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->pRenderingMatrices,
			NULL,			// 모든 뼈들의 역행렬을 구해야함, 안 넣어줘도 됨.
			pSrcVertices,	// 변하지 않는 정점 정보
			pDestVertices);	// 변환된 정점 정보

		for (_ulong i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			GET_DEVICE->SetTexture(0, pMeshContainer->ppTexture[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		pMeshContainer->pOriginalMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}

	return S_OK;
}

_uint CAnimMeshRenderComponent::PostRender(void)
{
	return _uint();
}

void CAnimMeshRenderComponent::OnDestroy(void)
{
}

void CAnimMeshRenderComponent::OnEnable(void)
{
	__super::OnEnable();
}

void CAnimMeshRenderComponent::Set_AnimationSet(const _uint & iIndex)
{
	if (nullptr == m_pAniCtrl)
		return;

	m_pAniCtrl->Set_AnimationSet(iIndex);
}

void CAnimMeshRenderComponent::Play_Animation(const _double & fTimeDelta)
{
	if (nullptr == m_pAniCtrl)
		return;

	m_pAniCtrl->Play_Animation(fTimeDelta);

	matrix4x4 matTemp;
	Update_FrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
}

void CAnimMeshRenderComponent::MeshInput(_wcharT * path, _wcharT * fileName)
{
	lstrcpy(m_path, path);
	lstrcpy(m_fileName, fileName);

	_wcharT	fullPath[MAX_PATH] = L"";

	lstrcpy(fullPath, m_path);
	lstrcat(fullPath, m_fileName);

	m_pLoader = CHierarchyLoader::Create(m_path);

	LPD3DXANIMATIONCONTROLLER		pAniCtrl = nullptr;

	if (FAILED(D3DXLoadMeshHierarchyFromX(
		fullPath,
		D3DXMESH_MANAGED,
		CDeviceManager::GetInstance()->GetDevice(),
		m_pLoader,
		nullptr,
		&m_pRootFrame,
		&pAniCtrl)))
		return;

	m_pAniCtrl = CAniCtrl::Create(pAniCtrl);

	SafeRelease(pAniCtrl);

	matrix4x4		MatrixTemp;
	Update_CombinedTransformationMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, *D3DXMatrixIdentity(&MatrixTemp));

	Setup_BoneCombinedTransformationMatrixPointer((D3DXFRAME_DERIVED*)m_pRootFrame);
}

HRESULT CAnimMeshRenderComponent::Update_CombinedTransformationMatrices(D3DXFRAME_DERIVED * pFrame, matrix4x4 ParentMatrix)
{
	// 나의 변환 * 부모뼈의 변환
	pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix * ParentMatrix;

	if (pFrame->pFrameFirstChild)
		Update_CombinedTransformationMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild, pFrame->CombinedTransformationMatrix);

	if (pFrame->pFrameSibling)
		Update_CombinedTransformationMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameSibling, ParentMatrix);

	return S_OK;
}

HRESULT CAnimMeshRenderComponent::Setup_BoneCombinedTransformationMatrixPointer(D3DXFRAME_DERIVED * pFrame)
{
	if (nullptr != pFrame->pMeshContainer)
	{
		D3DXMESHCONTAINER_DERIVED*	pMeshContainerDerived = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;

		for (_uint i = 0; i < pMeshContainerDerived->iNumBones; ++i)
		{
			const char* pBoneName = pMeshContainerDerived->pSkinInfo->GetBoneName(i);

			D3DXFRAME_DERIVED*	pFrameDerived = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, pBoneName);

			pMeshContainerDerived->ppCombinedTransformationMatrices[i] = &pFrameDerived->CombinedTransformationMatrix;
		}

		m_vMeshContainers.push_back(pMeshContainerDerived);
	}

	if (pFrame->pFrameFirstChild)
		Setup_BoneCombinedTransformationMatrixPointer((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		Setup_BoneCombinedTransformationMatrixPointer((D3DXFRAME_DERIVED*)pFrame->pFrameSibling);

	return S_OK;
}

void CAnimMeshRenderComponent::Update_FrameMatrices(D3DXFRAME_DERIVED * pFrame, const matrix4x4 * pParentMatrix)
{
	if (nullptr == pFrame)
		return;

	pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix * (*pParentMatrix);

	if (nullptr != pFrame->pFrameSibling)
		Update_FrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameSibling, pParentMatrix);

	if (nullptr != pFrame->pFrameFirstChild)
		Update_FrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
}

void CAnimMeshRenderComponent::Set_FrameMatrixPointer(D3DXFRAME_DERIVED * pFrame)
{
	if (nullptr != pFrame->pMeshContainer)
	{
		D3DXMESHCONTAINER_DERIVED*	pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;

		for (_uint i = 0; i < pMeshContainer->iNumBones; ++i)
		{
			const char*			pBoneName = pMeshContainer->pSkinInfo->GetBoneName(i);
			D3DXFRAME_DERIVED*	pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, pBoneName);

			pMeshContainer->ppCombinedTransformationMatrices[i] = &pFrame->CombinedTransformationMatrix;
		}

		m_vMeshContainers.push_back(pMeshContainer);
	}

	if (nullptr != pFrame->pFrameSibling)
		Set_FrameMatrixPointer((D3DXFRAME_DERIVED*)pFrame->pFrameSibling);

	if (nullptr != pFrame->pFrameFirstChild)
		Set_FrameMatrixPointer((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild);
}

void CAnimMeshRenderComponent::OnDisable(void)
{
}