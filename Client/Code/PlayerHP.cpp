#include "stdafx.h"
#include "..\Header\PlayerHP.h"


CPlayerHP::CPlayerHP()
{
}

CPlayerHP::CPlayerHP(_int* hp, _int* hpMax)
{
	m_playerHpUi = Engine::GET_CUR_SCENE->FindObjectByName(L"PlayerHP");
	m_hpUiScaleX = m_playerHpUi->GetScale().x;
	m_hp = hp;
	m_curHp = *m_hp;
	m_hpMax = hpMax;
	m_oldPos = m_playerHpUi->GetPosition();
	m_downSpeed = 100;
}

CPlayerHP::~CPlayerHP()
{
}

void CPlayerHP::Update()
{
	if (m_curHp != *m_hp)
	{
		if (m_curHp == 0)
		{
			m_playerHpUi->AddPositionX(m_hpUiScaleX * 0.5f);
			m_playerHpUi->SetScaleX(0);
		}
		else if (m_curHp < *m_hp)
		{
			_float a = (float)m_curHp / (float)*m_hpMax; // 깍인 체력의 비율
			_float b = m_hpUiScaleX * a;
			_float c = m_hpUiScaleX - b; // UI가 줄여야되는 스케일

			m_playerHpUi->SetPositionX(m_oldPos.x - (c * 0.5f));
			m_playerHpUi->SetScaleX(b);

			m_curHp = Engine::MathfMin(m_curHp + deltaTime * m_downSpeed, *m_hp);

		}
		else if(m_curHp > *m_hp)
		{
			_float a = (float)m_curHp / (float)*m_hpMax; // 깍인 체력의 비율
			_float b = m_hpUiScaleX * a;
			_float c = m_hpUiScaleX - b; // UI가 줄여야되는 스케일

			m_playerHpUi->SetPositionX(m_oldPos.x - (c * 0.5f));
			m_playerHpUi->SetScaleX(b);

			m_curHp = Engine::MathfMax(m_curHp - deltaTime * m_downSpeed, *m_hp);
		}

	}

}

void CPlayerHP::Hit(_float damage)
{
}
