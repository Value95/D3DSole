#pragma once
#include "MonsterFSM.h"
class CMonster;
class CDrakenUI;
class CDrakenMaintenance :
	public MonsterFSM
{
private:
	CDrakenUI* m_drakenUI;
	// ���� ü�� ������Ʈ
public:
	CDrakenMaintenance(CMonster* monster);
	virtual ~CDrakenMaintenance();
public:
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void PatternTimer();
	void ChangePattern();
};

