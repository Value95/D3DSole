#include "EngineStdafx.h"
#include "LineComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "UIManager.h"
#include "MeshStore.h"

#include "SceneManager.h"

USING(Engine)
CLineComponent::CLineComponent()  
{
}


CLineComponent::~CLineComponent(void)
{
}

SHARED(CComponent) CLineComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CLineComponent) pClone(new CLineComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetTextureKey(m_textureKey);
	pClone->SetTexData(m_pTexData);

	return pClone;
}

void CLineComponent::Awake(void)
{
	__super::Awake();
}


void CLineComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	//���� ������Ʈ�� Static Scene�� ������Ʈ��?
	_bool		isStatic = m_pOwner->GetIsStatic();

	std::wstring layerKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if ((m_pTexData = CTextureStore::GetInstance()->GetTextureData(m_textureKey)) == nullptr)
		m_pTexData = CTextureStore::GetInstance()->GetTextureData(L"None");

	m_meshDate = CMeshStore::GetInstance()->GetMeshData(L"Cube");

	DateInit();
}

_uint CLineComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CLineComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CLineComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CLineComponent::PreRender(void)
{
	// ������ ����
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");

	//��ǥ����
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	return _uint();
}

_uint CLineComponent::Render(void)
{
	return _uint();
}

_uint CLineComponent::PostRender(void)
{
	return _uint();
}

void CLineComponent::OnDestroy(void)
{
}

void CLineComponent::OnEnable(void)
{
}

void CLineComponent::OnDisable(void)
{
}

void CLineComponent::DateInit()
{
	// FVF�� �����Ͽ� ������ �������� ������ �����ϰ� ����� ������ ������ �޸��Ҵ�
	/*GET_DEVICE->CreateVertexBuffer(4 * sizeof(_CustomVertex), 0, customFVF, D3DPOOL_MANAGED, &m_meshDate.vertexBuffer, NULL);

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

	GET_DEVICE->CreateIndexBuffer(2 * sizeof(vector3), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_meshDate.indexBuffer, NULL);

	vector3* pIndices = nullptr;

	m_meshDate.indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	m_meshDate.faceCount = 2;

	pIndices[0] = vector3(0, 1, 2);
	pIndices[1] = vector3(0, 2, 3);

	m_meshDate.indexBuffer->Unlock();*/

}
