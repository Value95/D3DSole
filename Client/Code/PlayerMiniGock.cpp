#include "stdafx.h"
#include "PlayerMiniGock.h"
#include "Player.h"

CPlayerMiniGock::CPlayerMiniGock()
{
}


CPlayerMiniGock::~CPlayerMiniGock()
{
}

std::shared_ptr<Engine::CComponent> CPlayerMiniGock::MakeClone(Engine::CGameObject *pObject)
{
	SHARED(CPlayerMiniGock) pClone(new CPlayerMiniGock);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CPlayerMiniGock::Awake(void)
{
	__super::Awake();

}

void CPlayerMiniGock::Start(SHARED(CComponent) spSelf)
{
	__super::Start(spSelf);

	m_playerObj = Engine::GET_CUR_SCENE->FindObjectByName(L"Player");
	SHARED(Engine::CAnimMeshRenderComponent) playerMeshCom = m_playerObj->GetComponent<Engine::CAnimMeshRenderComponent>();
	m_playerCom = m_playerObj->GetComponent<CPlayer>();

	const Engine::D3DXFRAME_DERIVED* pFrame = playerMeshCom->Get_FrameByName("Finger_L");
	m_parentBoneMatrix =&pFrame->CombinedTransformationMatrix;

	m_parentWorldMatrix = m_playerObj->GetWorldMatrixPoint();
}

_uint CPlayerMiniGock::FixedUpdate(SHARED(CComponent) spSelf)
{

	return NO_EVENT;
}

_uint CPlayerMiniGock::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CPlayerMiniGock::LateUpdate(SHARED(CComponent) spThis)
{
	GetOwner()->SetPosition(m_playerObj->GetPosition());
	matrix4x4 bone = *m_parentBoneMatrix * *m_parentWorldMatrix;

	matrix4x4 world = GetOwner()->GetWorldMatrix();
	world._41 = 0;
	world._42 = 0;
	world._43 = 0;

	GetOwner()->SetWorldMatrix(world * bone);

	return NO_EVENT;
}

void CPlayerMiniGock::OnDestroy(void)
{
}

void CPlayerMiniGock::OnEnable(void)
{
}

void CPlayerMiniGock::OnDisable(void)
{
}