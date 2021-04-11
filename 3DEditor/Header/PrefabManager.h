#pragma once
#include "Scene.h"

class CPrefabManager final
{
	SMART_DELETER_REGISTER
public:
	static CPrefabManager* m_instance;
	static CPrefabManager* CPrefabManager::GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new CPrefabManager;
		return m_instance;
	}

	static void CPrefabManager::DestroyInstance(void)
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
	std::vector<PrefabData> GetPrefabData() { return m_prefabData; }

	void DataInit(
		bool enable,
		std::wstring name,
		std::wstring layerKey,
		std::wstring objectKey,
		std::wstring messKey,
		std::wstring textureKey,
		vector3 rotation,
		vector3 scale,
		ColliderData* collider
	);

	void DataInit(
		bool enable,
		std::wstring name,
		std::wstring layerKey,
		std::wstring objectKey,
		std::wstring messKey,
		vector3 rotation,
		vector3 scale,
		ColliderData* collider
	);

	void DataDelete(int value);
};

