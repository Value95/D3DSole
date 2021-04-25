#include "stdafx.h"
#include "PlayerWapon.h"


CPlayerWapon::CPlayerWapon()
{
}


CPlayerWapon::~CPlayerWapon()
{
}

std::shared_ptr<Engine::CComponent> CPlayerWapon::MakeClone(Engine::CGameObject *pObject)
{
	SHARED(CPlayerWapon) pClone(new CPlayerWapon);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CPlayerWapon::Awake(void)
{
	__super::Awake();

}

void CPlayerWapon::Start(SHARED(CComponent) spSelf)
{
	__super::Start(spSelf);

	SHARED(Engine::CAnimMeshRenderComponent) playerMeshCom = Engine::GET_CUR_SCENE->FindObjectByName(L"Player")->GetComponent<Engine::CAnimMeshRenderComponent>();

	const Engine::D3DXFRAME_DERIVED* pFrame = playerMeshCom->Get_FrameByName("L_Hand");

	m_parentBoneMatrix = &pFrame->CombinedTransformationMatrix;

	m_playerObj = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");

	m_parentWorldMatrix = m_playerObj->GetWorldMatrixPoint();
}

_uint CPlayerWapon::FixedUpdate(SHARED(CComponent) spSelf)
{
	GetOwner()->SetPosition(m_playerObj->GetPosition());
	GetOwner()->SetWorldMatrix(*m_parentBoneMatrix * *m_parentWorldMatrix);

	return _uint();
}

_uint CPlayerWapon::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CPlayerWapon::LateUpdate(SHARED(CComponent) spThis)
{


	return _uint();
}

void CPlayerWapon::OnDestroy(void)
{
}

void CPlayerWapon::OnEnable(void)
{
}

void CPlayerWapon::OnDisable(void)
{
}
