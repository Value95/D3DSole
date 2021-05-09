#pragma once
#include "MonsterFSM.h"

class CCameraMove;
class CMonster;
class CDrakenProduction :
	public MonsterFSM
{
private:
	SHARED(CPlayer) m_player;
	SHARED(CCameraMove) m_cameraMove;
public:
	CDrakenProduction(CMonster* monster);
	virtual ~CDrakenProduction();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;
};

