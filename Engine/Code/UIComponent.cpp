#include "EngineStdafx.h"
#include "UIComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "UIManager.h"
#include "TextureStore.h"
#include "ShaderStore.h"

#include "SceneManager.h"

USING(Engine)
CUIComponent::CUIComponent()  
{
}


CUIComponent::~CUIComponent(void)
{
}

SHARED(CComponent) CUIComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CUIComponent) pClone(new CUIComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetTextureKey(m_textureKey);
	pClone->SetTexData(m_pTexData);

	return pClone;
}

void CUIComponent::Awake(void)
{
	__super::Awake();
	m_xUV = vector2(0, 1.0f);
	m_yUV = vector2(0, 1.0f);
}


void CUIComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	std::wstring layerKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if ((m_pTexData = CTextureStore::GetInstance()->GetTextureData(m_textureKey)) == nullptr)
		m_pTexData = CTextureStore::GetInstance()->GetTextureData(L"Error");

	if (m_shader)
		m_shader->SetEffectShader(*CShaderStore::GetInstance()->GetShaderData(m_shader->GetShaderKey()));

	DateInit();
}

_uint CUIComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CUIComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CUIComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CUIManager::GetInstance()->AddToRenderList(m_sortingLayer, std::static_pointer_cast<CUIComponent>(spThis));

	return NO_EVENT;
}

_uint CUIComponent::PreRender(void)
{
	// 데이터 셋팅
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");


	GET_DEVICE->SetStreamSource(0, m_meshDate.vertexBuffer, 0, m_meshDate.vertexSize);
	GET_DEVICE->SetFVF(m_meshDate.FVF);
	GET_DEVICE->SetIndices(m_meshDate.indexBuffer);

	if (m_pTexData != nullptr)
		GET_DEVICE->SetTexture(0, m_pTexData->pTexture);
	else
		GET_DEVICE->SetTexture(0, nullptr);

	//좌표셋팅
	matrix4x4 identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &identityMatrix);
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetOrthoMatrix());

	if (m_shader)
	{
		m_shader->GetEffectShader()->SetMatrix("g_matWorld", &GetOwner()->GetWorldMatrix());
		m_shader->GetEffectShader()->SetMatrix("g_matView", &identityMatrix);
		m_shader->GetEffectShader()->SetMatrix("g_matProj", &GET_CUR_SCENE->GetMainCamera()->GetOrthoMatrix());

		m_shader->GetEffectShader()->SetTexture("g_BaseTexture", m_pTexData->pTexture);

		m_shader->ShaderReady();
	}

	GET_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	GET_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); // 알파모드 시작
	GET_DEVICE->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	GET_DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행

	return _uint();
}

_uint CUIComponent::Render(void)
{
	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshDate.vertexCount, 0, m_meshDate.faceCount);
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	return _uint();
}

_uint CUIComponent::PostRender(void)
{
	if (m_shader)
		m_shader->ShaderEnd();

	GET_DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); // 알파모드 헤제


	return _uint();
}

void CUIComponent::OnDestroy(void)
{
}

void CUIComponent::OnEnable(void)
{
}

void CUIComponent::OnDisable(void)
{
}

void CUIComponent::SetXUV(vector2 value)
{
	m_xUV = value;
	UVSetting();
}

void CUIComponent::SetYUV(vector2 value)
{
	m_yUV = value;
	UVSetting();
}

void CUIComponent::DateInit()
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
	pVertices[0].uv = vector2(m_xUV.x, m_yUV.x);

	pVertices[1].position = vector3(0.5f, 0.5f, 0);
	pVertices[1].uv = vector2(m_xUV.y, m_yUV.x);

	pVertices[2].position = vector3(0.5f, -0.5f, 0);
	pVertices[2].uv = vector2(m_xUV.y, m_yUV.y);

	pVertices[3].position = vector3(-0.5f, -0.5f, 0);
	pVertices[3].uv = vector2(m_xUV.x, m_yUV.y);
		
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

void CUIComponent::UVSetting()
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
	pVertices[0].uv = vector2(m_xUV.x, m_yUV.x);

	pVertices[1].position = vector3(0.5f, 0.5f, 0);
	pVertices[1].uv = vector2(m_xUV.y, m_yUV.x);

	pVertices[2].position = vector3(0.5f, -0.5f, 0);
	pVertices[2].uv = vector2(m_xUV.y, m_yUV.y);

	pVertices[3].position = vector3(-0.5f, -0.5f, 0);
	pVertices[3].uv = vector2(m_xUV.x, m_yUV.y);

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
