#pragma once
#include "Scene.h"

class CNavMeshManager final
{
	SMART_DELETER_REGISTER
public:
	static CNavMeshManager* m_instance;
	static CNavMeshManager* CNavMeshManager::GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new CNavMeshManager;
		return m_instance;
	}

	static void CNavMeshManager::DestroyInstance(void)
	{
		if (m_instance != nullptr)
		{
			m_instance->OnDestroy();
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:
	// 오브젝트를 저장할변수
	std::vector<SHARED(Engine::CGameObject)> m_object;
	// 삼각형을 저장할변수
	std::vector<Triangle> m_triangle;
private:
	void OnDestroy();
public:
	// 삼각형을 그려줄 함수
	void TriangleRender();
};

