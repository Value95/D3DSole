#include "stdafx.h"
#include "PlayerStatReinforceShop.h"
#include "CameraMove.h"
#include "PlayerInfo.h"

CPlayerStatReinforceShop::CPlayerStatReinforceShop(CPlayer* player)
{
	m_player = player;
	m_objectVector.emplace_back(Engine::GET_CUR_SCENE->FindObjectByName(L"StatReinforceShop_UI").get());
	m_objectVector.emplace_back(Engine::GET_CUR_SCENE->FindObjectByName(L"StatReinforceShop_End_UI").get());
	m_objectVector.emplace_back(Engine::GET_CUR_SCENE->FindObjectByName(L"StatReinforceShop_Health_UI").get());
	m_objectVector.emplace_back(Engine::GET_CUR_SCENE->FindObjectByName(L"StatReinforceShop_Force_UI").get());
	m_objectVector.emplace_back(Engine::GET_CUR_SCENE->FindObjectByName(L"StatReinforceShop_Strength_UI").get());

	m_cameraMove = Engine::GET_MAIN_CAM->GetOwner()->GetComponent<CCameraMove>();
	m_shopValue = 0;

	//Engine::CFontManager::GetInstance()->AddText(L"PlayerHP", L"HP : 000", vector3(-70, 35, 0), D3DXCOLOR(1, 1, 1, 1));
	//Engine::CFontManager::GetInstance()->AddText(L"PlayerGold", L"Gold : 000", vector3(-70, 55, 0), D3DXCOLOR(1, 1, 1, 1));

}

CPlayerStatReinforceShop::~CPlayerStatReinforceShop()
{
}

void CPlayerStatReinforceShop::Start()
{
	m_player->SetWaponPosNumber(0);
	m_player->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_player->GetAnim()->Set_AnimationSet(8);
	m_cameraMove->SetIsEnabled(false);
	ShowCursor(true);
	for (auto iter : m_objectVector)
	{
		iter->SetIsEnabled(true);
	}
}

void CPlayerStatReinforceShop::End()
{
	m_cameraMove->SetIsEnabled(true);
	ShowCursor(false);
	for (auto iter : m_objectVector)
	{
		iter->SetIsEnabled(false);
	}
}

_uint CPlayerStatReinforceShop::FixedUpdate()
{
	return NO_EVENT;
}

_uint CPlayerStatReinforceShop::Update()
{
	vector<Engine::CGameObject*> obj = Engine::CRaycast::UIRayCast(L"UI");

	for (auto iter : obj)
	{
		if (iter->GetName() == L"StatReinforceShop_Health_UI")
		{
			m_shopValue = 0;
		}
		else if (iter->GetName() == L"StatReinforceShop_Force_UI")
		{
			m_shopValue = 1;
		}
		else if (iter->GetName() == L"StatReinforceShop_Strength_UI")
		{
			m_shopValue = 2;
		}
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_LBUTTON))
	{
		for (auto iter : obj)
		{
			if (iter->GetName() == L"StatReinforceShop_End_UI")
			{
				m_player->ChangeFSM(CPlayer::STATE::IDLE);
			}
			else if (iter->GetName() == L"StatReinforceShop_Health_UI")
			{
				Health();
			}
			else if (iter->GetName() == L"StatReinforceShop_Force_UI")
			{
				Force();
			}
			else if (iter->GetName() == L"StatReinforceShop_Strength_UI")
			{
				Strength();
			}
		}
	}

	switch (m_shopValue)
	{
	case 0:
		HealthFont();
		break;
	case 1:
		ForceFont();
		break;
	case 2:
		StrengthFont();
		break;

	}

	return NO_EVENT;
}

_uint CPlayerStatReinforceShop::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerStatReinforceShop::OnDestroy(void)
{
}

void CPlayerStatReinforceShop::Health()
{
	if (m_player->GetPlayerInfo()->GetHP() > 1000)
		return;

	if (m_player->GetPlayerInfo()->GetGold() >= (m_player->GetPlayerInfo()->GetHP() * 5))
	{
		m_player->GetPlayerInfo()->SetGold(m_player->GetPlayerInfo()->GetGold() - (m_player->GetPlayerInfo()->GetHP() * 5));
		m_player->GetPlayerInfo()->SetHpMax(m_player->GetPlayerInfo()->GetHpMax() + 200);
		m_player->GetPlayerInfo()->SetHP(m_player->GetPlayerInfo()->GetHP() + 200);
	}
}

void CPlayerStatReinforceShop::HealthFont()
{
}

void CPlayerStatReinforceShop::Force()
{
	if (m_player->GetPlayerInfo()->GetAttackSpeed() > 10)
		return;

	if (m_player->GetPlayerInfo()->GetGold() >= (m_player->GetPlayerInfo()->GetAttackSpeed() * 500))
	{
		m_player->GetPlayerInfo()->SetGold(m_player->GetPlayerInfo()->GetGold() - (m_player->GetPlayerInfo()->GetAttackSpeed() * 500));
		m_player->GetPlayerInfo()->SetAttackSpeed(m_player->GetPlayerInfo()->GetAttackSpeed() + 1);
	}
}

void CPlayerStatReinforceShop::ForceFont()
{
}

void CPlayerStatReinforceShop::Strength()
{
}

void CPlayerStatReinforceShop::StrengthFont()
{
}

// 마우스를 가져가면 그에맞는 설명으로변경
// 클릭하면 구매된다.

// 플레이어의 데이터정보를 변경하자.
// 그리고 플레이어 인풋도 start해서 데이터값 받아오자