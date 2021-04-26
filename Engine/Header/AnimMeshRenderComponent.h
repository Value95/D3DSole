#ifndef ANIMMESHRENDERCOMPONENT_H
#define ANIMMESHRENDERCOMPONENT_H

#include "HierarchyLoader.h"
#include "AniCtrl.h"

BEGIN(Engine)
class CMeshComponent;
class ENGINE_DLL CAnimMeshRenderComponent final : public CComponent
{
protected:
	GETTOR_SETTOR(CHierarchyLoader*, m_pLoader, nullptr, Loader);
	GETTOR_SETTOR(D3DXFRAME*, m_pRootFrame, nullptr, RootFrame);
	GETTOR_SETTOR(CAniCtrl*, m_pAniCtrl, {}, AnimCtrl);

	GETTOR_SETTOR(std::vector<D3DXMESHCONTAINER_DERIVED*>, m_vMeshContainers, {}, MeshContainers);

	 _wcharT	m_path[MAX_PATH];
	 _wcharT	m_fileName[MAX_PATH];
	GETTOR_SETTOR(ERenderID,m_renderID,		ERenderID::Base,	RenderID)

	GETTOR_SETTOR(_int, m_animValue, 0, AnimValue)

public:
	explicit CAnimMeshRenderComponent(void);
	~CAnimMeshRenderComponent(void);
public:
	SHARED(CComponent) MakeClone(CGameObject* pObject)	override;

	void Awake(void) override;
	void Start(SHARED(CComponent) spThis) override;

	_uint FixedUpdate(SHARED(CComponent) spThis) override;
	_uint Update(SHARED(CComponent) spThis) override;
	_uint LateUpdate(SHARED(CComponent) spThis) override;
		  
	_uint PreRender(void);
	_uint Render(void);
	_uint PostRender(void);	

	void OnDestroy(void) override;
		 
	void OnDisable(void) override;
	void OnEnable(void) override;

public:
	const D3DXFRAME_DERIVED* Get_FrameByName(const char* frameName);

	void Set_AnimationSet(const _uint& iIndex);
	void Play_Animation(const _double& fTimeDelta);

	void MeshInput(_wcharT* path, _wcharT* fileName);
private:
	HRESULT Update_CombinedTransformationMatrices(D3DXFRAME_DERIVED* pFrame, matrix4x4 ParentMatrix);
	HRESULT Setup_BoneCombinedTransformationMatrixPointer(D3DXFRAME_DERIVED* pFrame);

	void Update_FrameMatrices(D3DXFRAME_DERIVED* pFrame, const matrix4x4* pParentMatrix);
	void Set_FrameMatrixPointer(D3DXFRAME_DERIVED* pFrame);

};
END
#endif // !ANIMMESHRENDERCOMPONENT_H
