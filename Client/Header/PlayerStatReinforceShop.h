#pragma once
#include "FSM.h"
class CPlayer;
class CCameraMove;
class CPlayerStatReinforceShop :
	public FSM
{
private:
	vector<Engine::CGameObject*> m_objectVector;
	SHARED(CCameraMove) m_cameraMove;

	_int m_shopValue;
public:
	CPlayerStatReinforceShop(CPlayer* player);
	virtual ~CPlayerStatReinforceShop();

	// FSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;

	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void Health();
	void HealthFont();

	void Force();
	void ForceFont();

	void Strength();
	void StrengthFont();
	
};

