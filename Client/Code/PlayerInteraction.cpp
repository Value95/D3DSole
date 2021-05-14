#include "stdafx.h"
#include "PlayerInteraction.h"

#include "TitleScene.h"

CPlayerInteraction::CPlayerInteraction(CPlayer* player)
{
	m_player = player;
	collision = Engine::CBoxCollider::Create(vector3(0.6, 3, 6), vector3(0, 0.9, -3));
}

CPlayerInteraction::~CPlayerInteraction()
{
}

void CPlayerInteraction::Start()
{
	m_player->SetWaponPosNumber(0);
}

void CPlayerInteraction::End()
{
}

_uint CPlayerInteraction::FixedUpdate()
{
	std::vector<Engine::CGameObject*> col;
	if (Engine::CColliderManager::GetInstance()->OnColliderEnter(collision, m_player->GetOwner(), col))
	{
		for (auto& object : col)
		{
			if (object->GetLayerKey() == L"Interaction")
			{
				Interaction(object->GetObjectKey());
			}
		}
	}
	return NO_EVENT;
}

_uint CPlayerInteraction::Update()
{
	
	m_player->ChangeFSM(CPlayer::STATE::IDLE);
	return NO_EVENT;
}

_uint CPlayerInteraction::LateUpdate()
{
	return NO_EVENT;
}

void CPlayerInteraction::OnDestroy(void)
{
}

void CPlayerInteraction::Interaction(std::wstring objectKeys)
{
	Engine::CSceneManager::GetInstance()->SceneChange(CTitleScene::Create());

}

// �浹�Ѵ����� �ش� ������Ʈ�� �������� �Ǵ�
// �׿��´� �Լ��� ����

// NPC�� UI������
// UI�� NPC������ 
// ���������?