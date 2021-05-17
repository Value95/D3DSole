#include "EngineStdafx.h"
#include "DirectionalLightComponent.h"
#include "DeviceManager.h"

USING(Engine)

CDirectionalLightComponent::CDirectionalLightComponent(void)
{
}

CDirectionalLightComponent::~CDirectionalLightComponent(void)
{
}

SHARED(CComponent) CDirectionalLightComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CDirectionalLightComponent) pClone(new CDirectionalLightComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);
	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CDirectionalLightComponent::Awake(void)
{
	__super::Awake();
}

void CDirectionalLightComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

}

_uint CDirectionalLightComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CDirectionalLightComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CDirectionalLightComponent::LateUpdate(SHARED(CComponent) spSelf)
{
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	GET_DEVICE->SetMaterial(&mtrl);

	/// 광원 설정
	D3DXVECTOR3 vecDir;									/// 방향성 광원(directional light)이 향할 빛의 방향
	D3DLIGHT9 light;									/// 광원 구조체
	ZeroMemory(&light, sizeof(D3DLIGHT9));			/// 구조체를 0으로 지운다.
	light.Type = D3DLIGHT_DIRECTIONAL;			/// 광원의 종류(점 광원,방향성 광원,스포트라이트)
	light.Diffuse.r = 1.0f;							/// 광원의 색깔과 밝기
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(GetOwner()->GetRotation().x, GetOwner()->GetRotation().y, GetOwner()->GetRotation().z);

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	/// 광원의 방향을 단위벡터로 만든다.
	light.Range = 10000.0f;									/// 광원이 다다를수 있는 최대거리
	GET_DEVICE->SetLight(0, &light);							/// 디바이스에 0번 광원 설치
	GET_DEVICE->LightEnable(0, TRUE);							/// 0번 광원을 켠다
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);			/// 광원설정을 켠다

	GET_DEVICE->SetRenderState(D3DRS_AMBIENT, 0x00202020);		/// 환경광원(ambient light)의 값 설정
	return _uint();
}

void CDirectionalLightComponent::OnDestroy(void)
{

}

void CDirectionalLightComponent::OnEnable(void)
{
}

void CDirectionalLightComponent::OnDisable(void)
{
}