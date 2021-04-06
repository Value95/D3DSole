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
	Engine::_MeshData m_meshDate; // ���ؽ� ,�ε��� ���۸������ϱ� ���� ����
	std::vector<SHARED(Engine::CGameObject)> m_object; // ������Ʈ�� �����Һ���
	std::vector<Engine::Triangle> m_triangle; // �ﰢ���� �����Һ���

	_int m_createCount = 0;
	_int m_triangleCount = 0;
private:
	void OnDestroy();
public:
	// �ﰢ���� �׷��� �Լ�
	_uint PreRender();
	_uint Render();
	_uint PostRender();
	void DataInit();

	void ObjectCreate();
	void ObjectDelete(SHARED(Engine::CGameObject) obj);
	void TriangleDelete(SHARED(Engine::CGameObject) obj);
	Engine::CGameObject* ObjectPicking();
	void TriangleClockWise(Engine::Triangle& triangle);

public:
	std::vector<SHARED(Engine::CGameObject)> GetGameObject() { return m_object; }
	void SetGameObject(SHARED(Engine::CGameObject) object) { m_object.emplace_back(object); }

	std::vector<Engine::Triangle> GetTriangle() { return m_triangle; }
	void SetTriangle(Engine::Triangle triangle) { m_triangle.emplace_back(triangle); }

	_int* GetCreateCount() { return &m_createCount; }

	_int* GetTriangleCount() { return &m_triangleCount; }
};

