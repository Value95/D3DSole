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
		{
			m_instance = new CNavMeshManager;
			m_instance->m_triangle.emplace_back(Engine::Triangle());
		}
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
	Engine::_MeshData m_meshDate; // 버텍스 ,인덱스 버퍼를저장하기 위한 변수
	std::vector<SHARED(Engine::CGameObject)> m_object; // 오브젝트를 저장할변수
	std::vector<Engine::Triangle> m_triangle; // 삼각형을 저장할변수

	_int m_createCount = 0;
	_int m_triangleCount = 0;
private:
	void OnDestroy();
public:
	// 삼각형을 그려줄 함수
	_uint PreRender();
	_uint Render();
	_uint PostRender();
	void DataInit();

	void ObjectCreate();
	void ObjectDelete(SHARED(Engine::CGameObject) obj);
	void TriangleDelete(SHARED(Engine::CGameObject) obj);
	Engine::CGameObject* ObjectPicking();
	void TriangleClockWise(Engine::Triangle& triangle);
};

