#include "EngineStdafx.h"
#include "HierarchyLoader.h"

USING(Engine)

Engine::CHierarchyLoader::CHierarchyLoader()
{
}

Engine::CHierarchyLoader::~CHierarchyLoader(void)
{

}
/*
���ο� ���� ������ִ��Լ�
���ڷ� �̸����ް� ������ ����ü ���� ���� �����͸� �޾Ƽ� ���� �޸𸮸� �Ҵ���ؼ�
�������� �������ְ� �����͸� �������ش�.
�׸��� �� �����Ӿȿ� �ִ� ���� �������� �ʱ�ȭ �����ش�.
*/
STDMETHODIMP Engine::CHierarchyLoader::CreateFrame(THIS_ LPCSTR Name,
												LPD3DXFRAME *ppNewFrame)
{
	return S_OK;
}

/*

*/
STDMETHODIMP Engine::CHierarchyLoader::CreateMeshContainer(THIS_ LPCSTR Name, // �޽��� �̸�
	CONST D3DXMESHDATA *pMeshData,  // �޽� ������ ����ü (���Ͽ����εǾ��ִ�.)
	CONST D3DXMATERIAL *pMaterials,  // �޽��� ���͸��� ���� ����ü�� ������
	CONST D3DXEFFECTINSTANCE *pEffectInstances, // EffectInstance ����ü�� ������
	DWORD NumMaterials, // ���͸��� ����
	CONST DWORD *pAdjacency, // ���������� ���� �ִ� DWORD���� �ﰢ�� �ϳ��� 3���� �迭�� ������
	LPD3DXSKININFO pSkinInfo, // ��Ų ������ �������ִ� ID3DXKININFO�������̽��� ������ (�������̽��̴�) �ܼ��ϰ� ��Ų������ �������ִ� �༮ �ش������� �Լ��� �����ϰ� �����Ҽ��ִ�.
	LPD3DXMESHCONTAINER *ppNewMeshContainer) // ��ũ�� ����Ʈ
{
	return S_OK;
}

STDMETHODIMP Engine::CHierarchyLoader::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	return S_OK;
}

STDMETHODIMP Engine::CHierarchyLoader::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{

	return S_OK;
}

