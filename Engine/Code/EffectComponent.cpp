#include "EngineStdafx.h"
#include "EffectComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "TextureStore.h"
#include "AnimMeshRenderManager.h"
#include "ShaderStore.h"

#include "SceneManager.h"

USING(Engine)
CEffectComponent::CEffectComponent()  
{
}


CEffectComponent::~CEffectComponent(void)
{
}

SHARED(CComponent) CEffectComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CEffectComponent) pClone(new CEffectComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetEffectCount(m_effectCount);
	pClone->SetTexData(m_texData);

	return pClone;
}

void CEffectComponent::Awake(void)
{
	__super::Awake();
}


void CEffectComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	std::wstring layerKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	m_effectCurCount = 0;

	for (int i = 0; i < m_effectCount; i++)
	{
		std::wstring textureKey = m_textureKey + to_wstring(i);
		m_texData.emplace_back(CTextureStore::GetInstance()->GetTextureData(textureKey));
		if (m_texData[i] == nullptr)
			m_texData[i] = CTextureStore::GetInstance()->GetTextureData(L"Error");
	}

	if (m_shader)
		m_shader->SetEffectShader(*CShaderStore::GetInstance()->GetShaderData(m_shader->GetShaderKey()));

	DateInit();
}

_uint CEffectComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	matrix4x4 matWorld, matView, matBill;

	matWorld = GetOwner()->GetWorldMatrix();
	GET_DEVICE->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;
	D3DXMatrixInverse(&matBill, NULL, &matBill);

	// 주의!! 월 = matBill * (스 * 자 * 이) 이기 때문에...
	GetOwner()->SetWorldMatrix(matBill * matWorld);

	return NO_EVENT;
}

_uint CEffectComponent::Update(SHARED(CComponent) spThis)
{
	if (m_effectSpeed <= 0)
	{
		m_effectCurCount++;
		if (m_effectCurCount == m_effectCount)
		{
			m_effectCurCount = 0;
		}
	}

	m_effectSpeed -= deltaTime;
	return NO_EVENT;
}

_uint CEffectComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CAnimMeshRenderManager::GetInstance()->AddToEffectRenderList(std::dynamic_pointer_cast<CEffectComponent>(spThis));

	return NO_EVENT;
}

_uint CEffectComponent::PreRender(void)
{
	// 데이터 셋팅
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");


	GET_DEVICE->SetStreamSource(0, m_meshDate.vertexBuffer, 0, m_meshDate.vertexSize);
	GET_DEVICE->SetFVF(m_meshDate.FVF);
	GET_DEVICE->SetIndices(m_meshDate.indexBuffer);

	if (m_texData[m_effectCurCount] != nullptr)
		GET_DEVICE->SetTexture(0, m_texData[m_effectCurCount]->pTexture);
	else
		GET_DEVICE->SetTexture(0, nullptr);


	//좌표셋팅
	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	if (m_shader)
	{
		m_shader->GetEffectShader()->SetMatrix("g_matWorld", &GetOwner()->GetWorldMatrix());
		m_shader->GetEffectShader()->SetMatrix("g_matView", &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
		m_shader->GetEffectShader()->SetMatrix("g_matProj", &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

		m_shader->GetEffectShader()->SetTexture("g_BaseTexture", m_texData[m_effectCurCount]->pTexture);

		m_shader->ShaderReady();
	}

	return _uint();
}

_uint CEffectComponent::Render(void)
{
	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshDate.vertexCount, 0, m_meshDate.faceCount);

	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());
	return _uint();
}

_uint CEffectComponent::PostRender(void)
{
	if (m_shader)
		m_shader->ShaderEnd();

	return _uint();
}

void CEffectComponent::OnDestroy(void)
{
}

void CEffectComponent::OnEnable(void)
{
}

void CEffectComponent::OnDisable(void)
{
}

void CEffectComponent::Reset(std::wstring textureKey, _int effectCount)
{
	m_textureKey = textureKey;
	m_effectCount = effectCount;
}

void CEffectComponent::DateInit()
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