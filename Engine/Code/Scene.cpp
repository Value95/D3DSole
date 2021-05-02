#include "EngineStdafx.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "ObjectFactory.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "ShaderStore.h"


USING(Engine)
CScene::CScene(void)
{
}
CScene::~CScene(void)
{
}

void CScene::Awake(void)
{
	if (!m_isAwaked)
	{
		m_isAwaked = true;
		m_name = GetCurClassName(this);
		CDataStore::GetInstance()->InitDataForScene(m_name);
		CMeshStore::GetInstance()->InitMeshForScene(m_name);
		CTextureStore::GetInstance()->InitTextureForScene(m_name);
		CShaderStore::GetInstance()->InitShaderForScene(m_name);
	}
}

void CScene::Start(void)
{
	for (auto& layer : m_mLayers)
	{
		if (m_mLayers.empty())
			return;

		layer.second->Start();
	}
}

_uint CScene::FixedUpdate(void)
{
	_uint event = 0;

	for (auto& layer : m_mLayers)
	{
		if (event = layer.second->FixedUpdate())
			return event;
	}
	return event;
}

_uint CScene::Update(void)
{
	_uint event = 0;	

	if (m_mLayers.empty())
		return event;

	for (auto& layer : m_mLayers)
	{
		if (event = layer.second->Update())
			return event;
	}
	return event;
}

_uint CScene::LateUpdate(void)
{
	_uint event = 0;

	for (auto& layer : m_mLayers)
	{
		if (event = layer.second->LateUpdate())
			return event;
	}
	return event;
}

void CScene::OnDestroy(void)
{
	m_mLayers.clear();
}

void CScene::OnEnable(void)
{
}

void CScene::OnDisable(void)
{
}

SHARED(CGameObject) CScene::FindObjectByName(std::wstring name)
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetName() == name)
				return gameObject;
		}
	}
	return nullptr;
}

SHARED(CGameObject) CScene::FindObjectWithKey(std::wstring objectKey)
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				return gameObject;
		}
	}
	return nullptr;
}

SHARED(CGameObject) CScene::FindObjectPosition(vector3 position)
{
	for (auto& layer : m_mLayers)
	{
		if (layer.first == L"Camera" || layer.first == L"Debug")
			continue;

		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetPosition() == position)
				return gameObject;
		}
	}
	return nullptr;
}

SHARED(CGameObject) CScene::FindObjectPoint(CGameObject* object)
{
	for (auto& layer : m_mLayers)
	{
		if (layer.first == L"Camera" || layer.first == L"Debug")
			continue;

		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject.get() == object)
				return gameObject;
		}
	}
	return nullptr;
}

void CScene::AllDelete()
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetLayerKey() == L"Camera")
				continue;

			gameObject->SetIsNeedToBeDeleted(true);
		}
	}
}

_uint CScene::FindObjectsWithKey(std::wstring objectKey, std::vector<SHARED(CGameObject)>& gameObjects)
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				gameObjects.push_back(gameObject);
		}
	}
	return gameObjects.size();
}

void CScene::LoadObject(std::wstring path)
{
	std::wstring fullPath = L"../../Data/";
	fullPath += path;
	fullPath += L".dat";

	CString wstrFilePath = fullPath.c_str();

	HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwByte = 0;
	DWORD dwStringSize = 0;

	// 오브젝트------------------------------------------------------------------------------------

	_int objectCount = 0;
	ReadFile(hFile, &objectCount, sizeof(_int), &dwByte, nullptr);

	for (int i = 0; i < objectCount; i++)
	{
		std::wstring strName = LoadWstring(&hFile, &dwByte); // 이름

		std::wstring layerKey = LoadWstring(&hFile, &dwByte); // 레이어

		std::wstring objectKey = LoadWstring(&hFile, &dwByte); // 오브젝트

		SHARED(CGameObject) obj = ADD_CLONE(layerKey, objectKey, true);
		obj->SetName(strName);

		if (obj->GetComponent<Engine::CUIComponent>())
		{
			obj->GetComponent<Engine::CUIComponent>()->SetTextureKey(LoadWstring(&hFile, &dwByte));
		}
		else if (obj->GetComponent<Engine::CMeshComponent>())
		{
			obj->GetComponent<Engine::CMeshComponent>()->SetMeshKey(LoadWstring(&hFile, &dwByte));
		}
		else
			LoadWstring(&hFile, &dwByte);

		ReadFile(hFile, &obj->GetIsEnabled(), sizeof(bool), &dwByte, nullptr);
		ReadFile(hFile, &obj->GetPosition(), sizeof(vector3), &dwByte, nullptr);
		ReadFile(hFile, &obj->GetRotation(), sizeof(vector3), &dwByte, nullptr);
		ReadFile(hFile, &obj->GetScale(), sizeof(vector3), &dwByte, nullptr);

		ColliderData* colliderData = new ColliderData();

		ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr); // 이름
		TCHAR* colliderType = new TCHAR[dwStringSize];
		ReadFile(hFile, colliderType, dwStringSize, &dwByte, nullptr);

		colliderData->colliderType = colliderType;
		ReadFile(hFile, &colliderData->offset, sizeof(vector3), &dwByte, nullptr);
		ReadFile(hFile, &colliderData->boxsize, sizeof(vector3), &dwByte, nullptr);
		ReadFile(hFile, &colliderData->radius, sizeof(_float), &dwByte, nullptr);


		if (colliderData->colliderType == L"BOX")
		{
			obj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(colliderData->boxsize, colliderData->offset));
		}
		else if (colliderData->colliderType == L"SPHERE")
		{
			obj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CSphereCollider::Create(colliderData->radius));
		}
	}

	CloseHandle(hFile);
}

void CScene::AddLayer(std::wstring layerName)
{
	m_mLayers[layerName] = CLayer::Create(layerName);
}

std::wstring CScene::LoadWstring(HANDLE * file, DWORD * dwByte)
{
	DWORD dwStringSize = 0;

	ReadFile(*file, &dwStringSize, sizeof(DWORD), dwByte, nullptr); // 이름
	TCHAR* strName = new TCHAR[dwStringSize];
	ReadFile(*file, strName, dwStringSize, dwByte, nullptr);
	wstring returnstring = strName;
	delete[](strName);
	strName = nullptr;
	return returnstring;
}

