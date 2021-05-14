#pragma once
class CPlayerUI
{
private:
	CPlayerInfo* m_playerInfo;
public:
	CPlayerUI(CPlayerInfo* playerInfo);
	~CPlayerUI();

	void Update();
};

