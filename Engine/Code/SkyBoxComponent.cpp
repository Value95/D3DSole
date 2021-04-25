#include "EngineStdafx.h"
#include "SkyBoxComponent.h"
#include "DeviceManager.h"
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextureStore.h"

USING(Engine)
CSkyBoxComponent::CSkyBoxComponent()  
{
}


CSkyBoxComponent::~CSkyBoxComponent(void)
{
}

SHARED(CComponent) CSkyBoxComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CSkyBoxComponent) pClone(new CSkyBoxComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetTextureKey(m_textureKey);
	pClone->SetTexData(m_pTexData);

	return pClone;
}

void CSkyBoxComponent::Awake(void)
{
	__super::Awake();


}

void CSkyBoxComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	std::wstring layerKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if ((m_pTexData = CTextureStore::GetInstance()->GetTextureData(m_textureKey)) == nullptr)
		m_pTexData = CTextureStore::GetInstance()->GetTextureData(L"Error");

	DateInit();
}

_uint CSkyBoxComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CSkyBoxComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CSkyBoxComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CGraphicsManager::GetInstance()->AddToSkyBox(std::dynamic_pointer_cast<CSkyBoxComponent>(spThis));
	//GetOwner()->SetPosition(GET_MAIN_CAM->GetOwner()->GetPosition());
	GetOwner()->AddPositionY(3);
	return NO_EVENT;
}

_uint CSkyBoxComponent::PreRender(void)
{
	
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");

	if (m_pTexData != nullptr)
		GET_DEVICE->SetTexture(0, m_pTexData->pTexture);
	else
		GET_DEVICE->SetTexture(0, nullptr);

	//좌표셋팅
	matrix4x4 identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	//GET_DEVICE->SetTransform(D3DTS_VIEW, &identityMatrix);
	//GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetOrthoMatrix());

	GET_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return _uint();
}

_uint CSkyBoxComponent::Render(void)
{
	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshDate.vertexCount, 0, m_meshDate.faceCount);

	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());


	return _uint();
}

_uint CSkyBoxComponent::PostRender(void)
{
	GET_DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GET_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return _uint();
}

void CSkyBoxComponent::OnDestroy(void)
{
}

void CSkyBoxComponent::OnEnable(void)
{
}

void CSkyBoxComponent::OnDisable(void)
{
}

void CSkyBoxComponent::DateInit()
{
	m_meshDate.FVF = texCubeFVF;
	m_meshDate.vertexSize = sizeof(_VTXCUBE);
	m_meshDate.vertexNumInFace = 3;
	// FVF를 지정하여 보관할 데이터의 형식을 지정하고 사용자 정점을 보관할 메모리할당
	GET_DEVICE->CreateVertexBuffer(8 * sizeof(_VTXCUBE), 0, m_meshDate.FVF, D3DPOOL_MANAGED, &m_meshDate.vertexBuffer, NULL);

	TexCube* pVertices = nullptr;

	m_meshDate.vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	m_meshDate.vertexCount = 8;

	// 앞면
	pVertices[0].position = vector3(-0.5f, 0.5f, -0.5f);
	pVertices[0].uv = pVertices[0].position;

	pVertices[1].position = vector3(0.5f, 0.5f, -0.5f);
	pVertices[1].uv = pVertices[1].position;

	pVertices[2].position = vector3(0.5f, -0.5f, -0.5f);
	pVertices[2].uv = pVertices[2].position;

	pVertices[3].position = vector3(-0.5f, -0.5f, -0.5f);
	pVertices[3].uv = pVertices[3].position;

	// 뒷면
	pVertices[4].position = vector3(-0.5f, 0.5f, 0.5f);
	pVertices[4].uv = pVertices[4].position;

	pVertices[5].position = vector3(0.5f, 0.5f, 0.5f);
	pVertices[5].uv = pVertices[5].position;

	pVertices[6].position = vector3(0.5f, -0.5f, 0.5f);
	pVertices[6].uv = pVertices[6].position;

	pVertices[7].position = vector3(-0.5f, -0.5f, 0.5f);
	pVertices[7].uv = pVertices[7].position;

	m_meshDate.vertexBuffer->Unlock();

	GET_DEVICE->CreateIndexBuffer(6 * sizeof(INDEX16), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_meshDate.indexBuffer, NULL);
	m_meshDate.indexSize = sizeof(INDEX16);
	INDEX16* pIndices = nullptr;

	m_meshDate.indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	m_meshDate.faceCount = 2;

	// X+
	pIndices[0]._0 = 1;
	pIndices[0]._1 = 5;
	pIndices[0]._2 = 6;

	pIndices[1]._0 = 1;
	pIndices[1]._1 = 6;
	pIndices[1]._2 = 2;

	// X-
	pIndices[2]._0 = 4;
	pIndices[2]._1 = 0;
	pIndices[2]._2 = 3;

	pIndices[3]._0 = 4;
	pIndices[3]._1 = 3;
	pIndices[3]._2 = 7;

	// y+
	pIndices[4]._0 = 4;
	pIndices[4]._1 = 5;
	pIndices[4]._2 = 1;

	pIndices[5]._0 = 4;
	pIndices[5]._1 = 1;
	pIndices[5]._2 = 0;

	// y-
	pIndices[6]._0 = 3;
	pIndices[6]._1 = 2;
	pIndices[6]._2 = 6;

	pIndices[7]._0 = 3;
	pIndices[7]._1 = 6;
	pIndices[7]._2 = 7;

	// z+
	pIndices[8]._0 = 7;
	pIndices[8]._1 = 6;
	pIndices[8]._2 = 5;

	pIndices[9]._0 = 7;
	pIndices[9]._1 = 5;
	pIndices[9]._2 = 4;

	// z-
	pIndices[10]._0 = 0;
	pIndices[10]._1 = 1;
	pIndices[10]._2 = 2;

	pIndices[11]._0 = 0;
	pIndices[11]._1 = 2;
	pIndices[11]._2 = 3;

	m_meshDate.indexBuffer->Unlock();

}

