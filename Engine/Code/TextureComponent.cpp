#include "EngineStdafx.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TextureStore.h"
#include "DataStore.h"

USING(Engine)
CTextureComponent::CTextureComponent()  
{
}


CTextureComponent::~CTextureComponent(void)
{
}

SHARED(CComponent) CTextureComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CTextureComponent) pClone(new CTextureComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetTextureKey(m_textureKey);
	pClone->SetTexData(m_pTexData);

	return pClone;
}

void CTextureComponent::Awake(void)
{
	__super::Awake();
}


void CTextureComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	//현재 오브젝트가 Static Scene의 오브젝트냐?
	_bool		isStatic	= m_pOwner->GetIsStatic();

	//현재 오브젝트의 Layer / Object 키 값
	std::wstring layerKey	= m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if (m_textureKey == L"")
	{
		m_textureKey = L"Error";
	}

	m_pTexData = CTextureStore::GetInstance()->GetTextureData(m_textureKey);
}

_uint CTextureComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CTextureComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CTextureComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}



void CTextureComponent::OnDestroy(void)
{
}

void CTextureComponent::OnEnable(void)
{
}

void CTextureComponent::OnDisable(void)
{
}
