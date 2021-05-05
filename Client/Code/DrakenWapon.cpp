#include "stdafx.h"
#include "DrakenWapon.h"


CDrakenWapon::CDrakenWapon()
{
}


CDrakenWapon::~CDrakenWapon()
{
}

std::shared_ptr<Engine::CComponent> CDrakenWapon::MakeClone(Engine::CGameObject *pObject)
{
	SHARED(CDrakenWapon) pClone(new CDrakenWapon);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CDrakenWapon::Awake(void)
{
	__super::Awake();

}

void CDrakenWapon::Start(SHARED(CComponent) spSelf)
{
	__super::Start(spSelf);

	m_drakenObj = Engine::GET_CUR_SCENE->FindObjectByName(L"Draken");
	SHARED(Engine::CAnimMeshRenderComponent) drakenMeshCom = m_drakenObj->GetComponent<Engine::CAnimMeshRenderComponent>();

	const Engine::D3DXFRAME_DERIVED* pFrame = drakenMeshCom->Get_FrameByName("R_Hand");

	m_parentBoneMatrix = &pFrame->CombinedTransformationMatrix;


	m_parentWorldMatrix = m_drakenObj->GetWorldMatrixPoint();
}

_uint CDrakenWapon::FixedUpdate(SHARED(CComponent) spSelf)
{

	return NO_EVENT;
}

_uint CDrakenWapon::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CDrakenWapon::LateUpdate(SHARED(CComponent) spThis)
{
	GetOwner()->SetPosition(m_drakenObj->GetPosition());
	matrix4x4 bone = *m_parentBoneMatrix * *m_parentWorldMatrix;

	matrix4x4 world = GetOwner()->GetWorldMatrix();
	world._41 = -30;
	world._42 = 1;
	world._43 = 1;

	GetOwner()->SetWorldMatrix(world * bone);

	return NO_EVENT;
}

void CDrakenWapon::OnDestroy(void)
{
}

void CDrakenWapon::OnEnable(void)
{
}

void CDrakenWapon::OnDisable(void)
{
}
