#include "EngineStdafx.h"
#include "TriangleComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "DebugRendeerManager.h"
#include "MeshStore.h"

#include "SceneManager.h"

USING(Engine)
CTriangleComponent::CTriangleComponent()  
{
}


CTriangleComponent::~CTriangleComponent(void)
{
}

SHARED(CComponent) CTriangleComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CTriangleComponent) pClone(new CTriangleComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CTriangleComponent::Awake(void)
{
	__super::Awake();
}


void CTriangleComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	DateInit();
}

_uint CTriangleComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CTriangleComponent::Update(SHARED(CComponent) spThis)
{

	return NO_EVENT;
}

_uint CTriangleComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CDebugRendeerManager::GetInstance()->AddToTriangleRenderList(dynamic_pointer_cast<CTriangleComponent>(spThis));

	return NO_EVENT;
}

_uint CTriangleComponent::PreRender(void)
{
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");


	GET_DEVICE->SetStreamSource(0, m_meshDate.vertexBuffer, 0, m_meshDate.vertexSize);
	GET_DEVICE->SetFVF(m_meshDate.FVF);
	GET_DEVICE->SetIndices(m_meshDate.indexBuffer);

	//좌표셋팅
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_MAIN_CAM->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());

	return _uint();
}

_uint CTriangleComponent::Render(void)
{

	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshDate.vertexCount, 0, m_meshDate.faceCount);


	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());


	return _uint();
}

_uint CTriangleComponent::PostRender(void)
{

	return _uint();
}

void CTriangleComponent::OnDestroy(void)
{
}

void CTriangleComponent::OnEnable(void)
{
}

void CTriangleComponent::OnDisable(void)
{
}

void CTriangleComponent::DateInit()
{
	m_meshDate.FVF = customFVF;
	m_meshDate.vertexSize = sizeof(_CustomVertex);
	m_meshDate.vertexNumInFace = 3;
	// FVF를 지정하여 보관할 데이터의 형식을 지정하고 사용자 정점을 보관할 메모리할당
	GET_DEVICE->CreateVertexBuffer(4 * sizeof(_CustomVertex), 0, m_meshDate.FVF, D3DPOOL_MANAGED, &m_meshDate.vertexBuffer, NULL);

	_CustomVertex* pVertices = nullptr;

	m_meshDate.vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	m_meshDate.vertexCount = 4;

	pVertices[0].position = vector3(-0.5f, 0.5f, 0);
	pVertices[0].uv = vector2(0, 0);

	pVertices[1].position = vector3(0.5f, 0.5f, 0);
	pVertices[1].uv = vector2(1, 0);

	pVertices[2].position = vector3(0.5f, -0.5f, 0);
	pVertices[2].uv = vector2(1, 1);

	pVertices[3].position = vector3(-0.5f, -0.5f, 0);
	pVertices[3].uv = vector2(0, 1);

	pVertices[0].normal = vector3Back;
	pVertices[1].normal = vector3Back;
	pVertices[2].normal = vector3Back;
	pVertices[3].normal = vector3Back;

	m_meshDate.vertexBuffer->Unlock();

	GET_DEVICE->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_meshDate.indexBuffer, NULL);
	m_meshDate.indexSize = sizeof(WORD);
	WORD* pIndices = nullptr;

	m_meshDate.indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	m_meshDate.faceCount = 2;

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;
	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;

	m_meshDate.indexBuffer->Unlock();

}
