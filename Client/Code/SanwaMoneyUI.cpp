#include "stdafx.h"
#include "SanwaMoneyUI.h"

CSanwaMoneyUI::CSanwaMoneyUI(CMonster* monster)
{
	m_monster = monster;
}

CSanwaMoneyUI::~CSanwaMoneyUI()
{

}

void CSanwaMoneyUI::Start()
{
	m_hpUI = Engine::GET_CUR_SCENE->FindObjectByName(L"Boss_HP");
	m_hpUI->GetComponent<Engine::CUIComponent>()->SetSortingLayer(1);
	m_hpUI->SetIsEnabled(true);
}

void CSanwaMoneyUI::OnDestory()
{

}

void CSanwaMoneyUI::DateInput(_int * hp, _int * hpMax)
{
	m_hpUiScaleX = m_hpUI->GetScale().x;
	m_hp = hp;
	m_curHp = *m_hp;
	m_hpMax = hpMax;
	m_oldPos = m_hpUI->GetPosition();
	m_downSpeed = 100;
}

void CSanwaMoneyUI::Update()
{
	if (m_curHp != *m_hp)
	{
		if (m_curHp == 0)
		{
			m_hpUI->AddPositionX(m_hpUiScaleX * 0.5f);
			m_hpUI->SetScaleX(0);
		}
		else
		{
			_float a = (float)m_curHp / (float)*m_hpMax; // 깍인 체력의 비율
			_float b = m_hpUiScaleX * a;
			_float c = m_hpUiScaleX - b; // UI가 줄여야되는 스케일

			m_hpUI->SetPositionX(m_oldPos.x - (c * 0.5f));
			m_hpUI->SetScaleX(b);
		}

		m_curHp = Engine::MathfMax(m_curHp - deltaTime * m_downSpeed, *m_hp);
	}
}
