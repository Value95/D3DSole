#include "stdafx.h"
#include "ColliderManager.h"

CColliderManager* CColliderManager::m_instance = nullptr;

void CColliderManager::OnDestroy()
{
	for (auto& iter : m_colliderData)
	{
		delete(iter);
	}

	m_colliderData.clear();
}

void CColliderManager::DataDelete(int value)
{
	m_colliderData.erase(m_colliderData.begin() + value);
}
