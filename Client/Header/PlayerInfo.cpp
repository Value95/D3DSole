#include "stdafx.h"
#include "PlayerInfo.h"
#include "DataStore.h"

void CPlayerInfo::Start()
{
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_hp", m_hp);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_hpMax", m_hpMax);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_attackSpeed", m_attackSpeed);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_rotationSpeed", m_rotationSpeed);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_jumpPower", m_jumpPower);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_speed", m_speed);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_speedRush", m_speedRush);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_roolSpeed", m_roolSpeed);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_dushGauge", m_dushGauge);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageA", m_damageA);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageB", m_damageB);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageC", m_damageC);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageD", m_damageD);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageRush", m_damageRush);
	Engine::GET_VALUE(true, L"Player", L"PlayerInfo", L"m_gold", m_gold);
}

void CPlayerInfo::End()
{
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_hp", to_wstring(m_hp));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_hpMax", to_wstring(m_hpMax));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_attackSpeed", to_wstring(m_attackSpeed));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_rotationSpeed", to_wstring(m_rotationSpeed));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_jumpPower", to_wstring(m_jumpPower));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_speed", to_wstring(m_speed));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_speedRush", to_wstring(m_speedRush));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_roolSpeed", to_wstring(m_roolSpeed));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_dushGauge", to_wstring(m_dushGauge));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageA", to_wstring(m_damageA));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageB", to_wstring(m_damageB));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageC", to_wstring(m_damageC));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageD", to_wstring(m_damageD));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_damageRush", to_wstring(m_damageRush));
	Engine::SET_VALUE(true, L"Player", L"PlayerInfo", L"m_gold", to_wstring(m_gold));
}

