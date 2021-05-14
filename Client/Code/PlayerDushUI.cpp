#include "stdafx.h"
#include "PlayerDushUI.h"


CPlayerDushUI::CPlayerDushUI()
{
}

CPlayerDushUI::CPlayerDushUI(_float* value)
{
	m_object = Engine::GET_CUR_SCENE->FindObjectByName(L"PlayerDush_UI");
	m_ValueUiScaleY = m_object->GetScale().y;
	m_value = value;
	m_oldPos = m_object->GetPosition();
}

CPlayerDushUI::~CPlayerDushUI()
{
}

void CPlayerDushUI::Update()
{
	if (m_value == 0)
	{
		m_object->AddPositionY(m_ValueUiScaleY * 0.5f);
		m_object->SetScaleY(0);
	}
	else
	{
		_float a = *m_value / 100; // 깍인 체력의 비율
		_float b = m_ValueUiScaleY * a;
		_float c = m_ValueUiScaleY - b; // UI가 줄여야되는 스케일

		m_object->SetPositionY(m_oldPos.y - (c * 0.5f));
		m_object->SetScaleY(b);
	}
}

void CPlayerDushUI::Hit(_float damage)
{
}
