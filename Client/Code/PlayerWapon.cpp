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

	const Engine::D3DXFRAME_DERIVED* pFrame = playerMeshCom->Get_FrameByName("R_FINGER11");

	m_parentBoneMatrix = &pFrame->CombinedTransformationMatrix;

	m_playerObj = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");

	m_parentWorldMatrix = m_playerObj->GetWorldMatrixPoint();

	vector3 a = GetOwner()->GetRotation();
}

_uint CPlayerWapon::FixedUpdate(SHARED(CComponent) spSelf)
{

	return NO_EVENT;
}

_uint CPlayerWapon::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CPlayerWapon::LateUpdate(SHARED(CComponent) spThis)
{
	GetOwner()->SetPosition(m_playerObj->GetPosition());
	matrix4x4 bone = *m_parentBoneMatrix * *m_parentWorldMatrix;

	matrix4x4 world = GetOwner()->GetWorldMatrix();
	world._41 = 1;
	world._42 = 1;
	world._43 = 1;

	GetOwner()->SetWorldMatrix(world * bone);

	return NO_EVENT;
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
