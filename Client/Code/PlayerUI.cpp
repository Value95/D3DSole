#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"
#include "PlayerInfo.h"


CPlayerUI::CPlayerUI(CPlayerInfo * playerInfo)
{
	m_playerInfo = playerInfo;
	Engine::CFontManager::GetInstance()->AddText(L"PlayerHP", L"HP : 000", vector3(-70, 35, 0), D3DXCOLOR(1, 1, 1, 1));
	Engine::CFontManager::GetInstance()->AddText(L"PlayerGold", L"Gold : 000", vector3(-70, 55, 0), D3DXCOLOR(1, 1, 1, 1));
}

CPlayerUI::~CPlayerUI()
{
}

void CPlayerUI::Update()
{
	Engine::CFontManager::GetInstance()->RewriteText(L"PlayerHP", L"HP : " + to_wstring(m_playerInfo->GetHP()));
	Engine::CFontManager::GetInstance()->RewriteText(L"PlayerGold", L"Gold : " + to_wstring(m_playerInfo->GetGold()));
}
