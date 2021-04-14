#include "EngineStdafx.h"
#include "Component.h"
#include "GameObject.h"

USING(Engine)
CComponent::CComponent()
{
}

CComponent::~CComponent(void)
{
}

void CComponent::Awake(void)
{
	if (!m_isEnabled)
		return;

	m_isAwaked = true;
	m_name = GetCurClassName(this);
}

void CComponent::Start(SHARED(CComponent) spThis)
{
	if (!m_isEnabled)
		return;

	m_isStarted = true;
}

_uint CComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CComponent::OnDestroy(void)
{
}

void CComponent::OnEnable(void)
{
}

void CComponent::OnDisable(void)
{
}