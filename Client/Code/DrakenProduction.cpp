#include "stdafx.h"
#include "DrakenProduction.h"
#include "Monster.h"
#include "MonsterInfo.h"

#include "Player.h"
#include "CameraMove.h"

CDrakenProduction::CDrakenProduction(CMonster* monster)
{
	m_monster = monster;
	m_player = Engine::GET_CUR_SCENE->FindObjectByName(L"Player")->GetComponent<CPlayer>();
	m_cameraMove = Engine::GET_MAIN_CAM->GetOwner()->GetComponent<CCameraMove>();
}

CDrakenProduction::~CDrakenProduction()
{
}

void CDrakenProduction::Start()
{
	m_player->IdleLookState();
	m_cameraMove->SetIsEnabled(false);

	m_monster->GetAnim()->GetAnimCtrl()->SetSpeed(1.0f);
	m_monster->GetAnim()->Set_AnimationSet(2);
}

void CDrakenProduction::End()
{
	m_player->IdleLookEnd();
	m_cameraMove->SetIsEnabled(true);
}
// 2 -> 1 -> 14 -> 16 연출때의 모습
_uint CDrakenProduction::FixedUpdate()
{
	return NO_EVENT;
}

_uint CDrakenProduction::Update()
{
	if (m_monster->GetAnim()->GetAnimCtrl()->Is_AnimationSetEnd())
	{
		switch (m_monster->GetAnim()->GetAnimValue())
		{
		case 2:
			m_monster->GetAnim()->Set_AnimationSet(1);
			break;
		case 1:
			m_monster->GetAnim()->Set_AnimationSet(14);
			break;
		case 14:
			m_monster->ChangeFSM(CMonster::DRAKEN_STATE::IDLE);
		}
	}

	return NO_EVENT;
}

_uint CDrakenProduction::LateUpdate()
{

	return NO_EVENT;
}

void CDrakenProduction::OnDestroy(void)
{
}



