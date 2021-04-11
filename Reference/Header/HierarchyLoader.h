#ifndef HierarchyLoader_h__
#define HierarchyLoader_h__

BEGIN(Engine)

class ENGINE_DLL CHierarchyLoader : public ID3DXAllocateHierarchy
{
private:

private:
	explicit CHierarchyLoader();
	virtual  ~CHierarchyLoader();

public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
		
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name,
									CONST D3DXMESHDATA *pMeshData,
									CONST D3DXMATERIAL *pMaterials,
									CONST D3DXEFFECTINSTANCE *pEffectInstances,
									DWORD NumMaterials,
									CONST DWORD *pAdjacency,
									LPD3DXSKININFO pSkinInfo,
									LPD3DXMESHCONTAINER *ppNewMeshContainer);
	
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

private:

};


END
#endif // HierarchyLoader_h__

/*
애니메이션을 셋팅하는 클래스
본의정보를 가져오고 본의 버텍스등의 접근할수있게 데이터를 저장하는놈
*/