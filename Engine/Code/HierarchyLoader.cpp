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
새로운 뼈를 만들어주는함수
인자로 이름을받고 프레임 구조체 형의 더블 포인터를 받아서 새로 메모리를 할당당해서
프레임을 생성해주고 포인터를 연결해준다.
그리고 그 프레임안에 있는 각종 값을들을 초기화 시켜준다.
*/
STDMETHODIMP Engine::CHierarchyLoader::CreateFrame(THIS_ LPCSTR Name,
												LPD3DXFRAME *ppNewFrame)
{
	return S_OK;
}

/*

*/
STDMETHODIMP Engine::CHierarchyLoader::CreateMeshContainer(THIS_ LPCSTR Name, // 메시의 이름
	CONST D3DXMESHDATA *pMeshData,  // 메시 데이터 구조체 (유니온으로되어있다.)
	CONST D3DXMATERIAL *pMaterials,  // 메시의 메터리얼 정보 구조체의 포인터
	CONST D3DXEFFECTINSTANCE *pEffectInstances, // EffectInstance 구조체의 포인터
	DWORD NumMaterials, // 메터리얼 갯수
	CONST DWORD *pAdjacency, // 인접정보를 갖고 있는 DWORD형의 삼각형 하나당 3개의 배열의 포인터
	LPD3DXSKININFO pSkinInfo, // 스킨 정보를 가지고있는 ID3DXKININFO인터페이스의 포인터 (인터페이스이다) 단순하게 스킨정보를 가지고있는 녀석 해당정보를 함수로 여람하고 조작할수있다.
	LPD3DXMESHCONTAINER *ppNewMeshContainer) // 링크드 리스트
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

