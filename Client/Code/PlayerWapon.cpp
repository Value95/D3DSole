#include "stdafx.h"
#include "PlayerWapon.h"
#include "Player.h"

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

	m_playerObj = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");
	SHARED(Engine::CAnimMeshRenderComponent) playerMeshCom = m_playerObj->GetComponent<Engine::CAnimMeshRenderComponent>();
	m_playerCom = m_playerObj->GetComponent<CPlayer>();

	const Engine::D3DXFRAME_DERIVED* pFrame1 = playerMeshCom->Get_FrameByName("Hip");
	m_parentBoneMatrix.emplace_back(&pFrame1->CombinedTransformationMatrix);

	const Engine::D3DXFRAME_DERIVED* pFrame2 = playerMeshCom->Get_FrameByName("Finger_L");
	m_parentBoneMatrix.emplace_back(&pFrame2->CombinedTransformationMatrix);

	m_parentWorldMatrix = m_playerObj->GetWorldMatrixPoint();
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
	switch (m_playerCom->GetWaponPosNumber())
	{
	case 0:
		Wapon0();
		break;
	case 1:
		Wapon1();
		break;
	}

	
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

void CPlayerWapon::Wapon0()
{
	GetOwner()->SetPosition(m_playerObj->GetPosition());
	matrix4x4 bone = *m_parentBoneMatrix[0] * *m_parentWorldMatrix;

	matrix4x4 world = GetOwner()->GetWorldMatrix();
	world._41 = -10.0f;
	world._42 = 0.0f;
	world._43 = -12.0f;

	GetOwner()->SetRotation(vector3(-90, 45, 0));

	// 위치 vector3(-10, 0, -12)
	// 회전 vector3(-90, 45, 0)

	// 위치 vector3(-4.313, 28.600, 20.1628)
	// 회전 vector3(325, 175, 364)

	GetOwner()->SetWorldMatrix(world * bone);
}

void CPlayerWapon::Wapon1()
{
	GetOwner()->SetPosition(m_playerObj->GetPosition());
	matrix4x4 bone = *m_parentBoneMatrix[1] * *m_parentWorldMatrix;

	matrix4x4 world = GetOwner()->GetWorldMatrix();
	world._41 = -4.313f;
	world._42 = 28.600f;
	world._43 = 20.1628f;

	GetOwner()->SetRotation(vector3(325, 175, 364));

	// 위치 vector3(-4.313, 28.600, 20.1628)
	// 회전 vector3(325, 175, 364)

	GetOwner()->SetWorldMatrix(world * bone);
}

