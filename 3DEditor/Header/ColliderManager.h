#pragma once
#include "Scene.h"

class CColliderManager final
{
	SMART_DELETER_REGISTER
public:
	static CColliderManager* m_instance;
	static CColliderManager* CColliderManager::GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new CColliderManager;
		return m_instance;
	}

	static void CColliderManager::DestroyInstance(void)
	{
		if (m_instance != nullptr)
		{
			m_instance->OnDestroy();
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:
	std::vector<PrefabData> m_prefabData;

private:
	void OnDestroy();
public:

};

