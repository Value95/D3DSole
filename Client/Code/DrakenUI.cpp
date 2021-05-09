#include "stdafx.h"
#include "..\Header\DrakenUI.h"

CDrakenUI::CDrakenUI(CMonster* monster)
{
	m_monster = monster;
}

CDrakenUI::~CDrakenUI()
{
}

void CDrakenUI::Start()
{
	m_hpUIPos = vector3(0, 7.5, 0);
	m_hpUI[0] = Engine::CObjectFactory::GetInstance()->AddClone(L"UI", L"WorldUI", true);
	m_hpUI[0]->SetPosition(vector3(0, 0, 0));
	m_hpUI[0]->SetScale(vector3(5, 2, 0));
	m_hpUI[0]->GetComponent<Engine::CWorldUIComponent>()->SetTextureKey(L"Hp_Back0");

	m_hpUI[1] = Engine::CObjectFactory::GetInstance()->AddClone(L"UI", L"WorldUI", true);
	m_hpUI[1]->SetPosition(vector3(0, 0, 0));
	m_hpUI[1]->SetScale(vector3(3.4125, 2, 0));
	m_hpUI[1]->GetComponent<Engine::CWorldUIComponent>()->SetTextureKey(L"Hp_Gauge2");
}

void CDrakenUI::OnDestory()
{
}

void CDrakenUI::SetMonsterHP(_int* hp, _int* hpMax)
{
	m_hpUiScaleX = m_hpUI[1]->GetScale().x;
	m_hp = hp;
	m_curHp = *m_hp;
	m_hpMax = hpMax;
	m_downSpeed = 100;
}

void CDrakenUI::Update()
{
	m_hpUI[0]->LookAtX(m_monster->GetPlayer()->GetPosition());
	m_hpUI[1]->LookAtX(m_monster->GetPlayer()->GetPosition());

	m_hpUI[0]->SetPosition(m_monster->GetOwner()->GetPosition() + m_hpUIPos);
	//m_hpUI[0]->SetRotation(m_monster->GetOwner()->GetRotation());
	m_hpUI[1]->SetPosition(m_monster->GetOwner()->GetPosition() + m_hpUIPos);
	//m_hpUI[1]->SetRotation(m_monster->GetOwner()->GetRotation());

	if (m_curHp == 0)
	{
		m_hpUI[1]->AddPositionX(m_hpUiScaleX * 0.5f);
		m_hpUI[1]->SetScaleX(0);
	}
	else
	{
		_float a = (float)m_curHp / (float)*m_hpMax; // 깍인 체력의 비율
		_float b = m_hpUiScaleX * a;
		_float c = m_hpUiScaleX - b; // UI가 줄여야되는 스케일

		m_hpUI[1]->AddPosition(m_hpUI[1]->ReturnTranslate(vector3Right * (-c * 0.5f)));
		m_hpUI[1]->SetScaleX(b);
	}

	m_curHp = Engine::MathfMax(m_curHp - deltaTime * m_downSpeed, *m_hp);

}
