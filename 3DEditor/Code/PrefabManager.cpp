#include "stdafx.h"
#include "PrefabManager.h"

CPrefabManager* CPrefabManager::m_instance = nullptr;

void CPrefabManager::OnDestroy()
{
}

void CPrefabManager::DataInit(bool enable, std::wstring name, std::wstring layerKey, std::wstring objectKey, std::wstring messKey, std::wstring textureKey, vector3 rotation, vector3 scale)
{
	PrefabData TprefabData;
	TprefabData.enable = enable;
	TprefabData.name = name;
	TprefabData.layerKey = layerKey;
	TprefabData.objectKey = objectKey;
	TprefabData.messKey = messKey;
	TprefabData.textureKey = textureKey;
	TprefabData.rotation = rotation;
	TprefabData.scale = scale;

	m_prefabData.emplace_back(TprefabData);
}

void CPrefabManager::DataDelete(int value)
{
	m_prefabData.erase(m_prefabData.begin() + value);
}
