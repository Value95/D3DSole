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

	/// ???? ????
	D3DXVECTOR3 vecDir;									/// ???⼺ ????(directional light)?? ???? ???? ????
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));			/// ????ü?? 0???? ??????.
	m_light.Type = D3DLIGHT_DIRECTIONAL;			/// ?????? ????(?? ????,???⼺ ????,????Ʈ????Ʈ)
	m_light.Diffuse.r = 1.0f;							/// ?????? ?????? ????
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_lightDir = D3DXVECTOR3(D3DXToRadian(GetOwner()->GetRotation().x), D3DXToRadian(GetOwner()->GetRotation().y), D3DXToRadian(GetOwner()->GetRotation().z));

	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &m_lightDir);	/// ?????? ?????? ???????ͷ? ??????.
	m_light.Range = 1000.0f;									/// ?????? ?ٴٸ??? ?ִ? ?ִ??Ÿ?
	GET_DEVICE->SetLight(0, &m_light);							/// ?????̽??? 0?? ???? ??ġ
	GET_DEVICE->LightEnable(0, TRUE);							/// 0?? ?????? ?Ҵ?
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);			/// ?????????? ?Ҵ?

	GET_DEVICE->SetRenderState(D3DRS_AMBIENT, 0x00202020);		/// ȯ?汤??(ambient light)?? ?? ????
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