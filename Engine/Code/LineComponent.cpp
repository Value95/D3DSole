#include "EngineStdafx.h"
#include "LineComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "DebugRendeerManager.h"

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

	return pClone;
}

void CLineComponent::Awake(void)
{
	__super::Awake();
}


void CLineComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	
	m_linePos[0] = GetOwner()->GetPosition();

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
	CDebugRendeerManager::GetInstance()->AddToLineRenderList(dynamic_pointer_cast<CLineComponent>(spThis));

	return NO_EVENT;
}

_uint CLineComponent::PreRender(void)
{
	// 데이터 셋팅
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");

	//좌표셋팅
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	return _uint();
}

_uint CLineComponent::Render(void)
{
	ID3DXLine* line;
	D3DXCreateLine(GET_DEVICE, &line);		
	line->SetWidth(1);
	line->SetAntialias(true);
	line->Begin();
	line->DrawTransform(m_linePos, 2, &(GetOwner()->GetWorldMatrix() * GET_CUR_SCENE->GetMainCamera()->GetViewMatrix() * GET_CUR_SCENE->GetMainCamera()->GetProjMatrix()), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	line->End();
	line->Release();	

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

void CLineComponent::EndLinePosition(vector3 endLine)
{
	m_linePos[1] = endLine;
}

void CLineComponent::DateInit()
{
	// FVF를 지정하여 보관할 데이터의 형식을 지정하고 사용자 정점을 보관할 메모리할당
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
