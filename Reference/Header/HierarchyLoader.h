#ifndef HierarchyLoader_h__
#define HierarchyLoader_h__

BEGIN(Engine)

class ENGINE_DLL CHierarchyLoader : public ID3DXAllocateHierarchy
{
private:
	const _wcharT*		m_filePath;

private:
	explicit CHierarchyLoader();
	explicit CHierarchyLoader(const _wcharT* pPath);
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

	static CHierarchyLoader* Create(const _wcharT* filePath);
private:
	HRESULT Start(const _wcharT* filePath);
	void Allocate_Name(char** ppSour, const char* pDest);
	void OnDestroy();
};
END
#endif // HierarchyLoader_h__

/*
�ִϸ��̼��� �����ϴ� Ŭ����
���������� �������� ���� ���ؽ����� �����Ҽ��ְ� �����͸� �����ϴ³�
*/