#include "stdafx.h"
#include "NavMeshManager.h"

CNavMeshManager* CNavMeshManager::m_instance = nullptr;

void CNavMeshManager::OnDestroy()
{

}

_uint CNavMeshManager::PreRender(void)
{
	int  triangleSize = m_triangle.size() - 1;

	if (triangleSize == 0)
		return NO_EVENT;

	DataInit();

	Engine::GET_DEVICE->SetStreamSource(0, m_meshDate.vertexBuffer, 0, m_meshDate.vertexSize);
	Engine::GET_DEVICE->SetFVF(m_meshDate.FVF);
	Engine::GET_DEVICE->SetIndices(m_meshDate.indexBuffer);

	//좌표셋팅
	matrix4x4 worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

	Engine::GET_DEVICE->SetTransform(D3DTS_WORLD, &worldMatrix);
	Engine::GET_DEVICE->SetTransform(D3DTS_VIEW, &Engine::GET_MAIN_CAM->GetViewMatrix());
	Engine::GET_DEVICE->SetTransform(D3DTS_PROJECTION, &Engine::GET_MAIN_CAM->GetProjMatrix());

	return NO_EVENT;
}

_uint CNavMeshManager::Render(void)
{
	int  triangleSize = m_triangle.size() - 1;

	if (triangleSize == 0)
		return NO_EVENT;

	Engine::GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshDate.vertexCount, 0, m_meshDate.faceCount);

	return NO_EVENT;
}

_uint CNavMeshManager::PostRender(void)
{
	int  triangleSize = m_triangle.size() - 1;

	if (triangleSize == 0)
		return NO_EVENT;

	return NO_EVENT;
}

void CNavMeshManager::DataInit()
{
	int  triangleSize = m_triangle.size() - 1;

	m_meshDate.FVF = Engine::customFVF;
	m_meshDate.vertexSize = sizeof(Engine::_CustomVertex);
	m_meshDate.vertexNumInFace = 3;
	m_meshDate.vertexCount = triangleSize * 3;
	// FVF를 지정하여 보관할 데이터의 형식을 지정하고 사용자 정점을 보관할 메모리할당
	Engine::GET_DEVICE->CreateVertexBuffer(m_meshDate.vertexCount * sizeof(Engine::_CustomVertex), 0, m_meshDate.FVF, D3DPOOL_MANAGED, &m_meshDate.vertexBuffer, NULL);

	Engine::_CustomVertex* pVertices = nullptr;

	m_meshDate.vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	int count = 0;
	for (int i = 0; i <triangleSize; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pVertices[count].position = *m_triangle[i].point[j];
			pVertices[count].uv = vector2(0, 0);
			pVertices[count].normal = vector3Back;

			count++;
		}
	}
	m_meshDate.vertexBuffer->Unlock();

	Engine::GET_DEVICE->CreateIndexBuffer((triangleSize * 3) * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_meshDate.indexBuffer, NULL);
	m_meshDate.indexSize = sizeof(WORD);
	WORD* pIndices = nullptr;

	m_meshDate.indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	m_meshDate.faceCount = triangleSize;

	count = 0;
	for (int i = 0; i < triangleSize; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pIndices[count] = count;
			count++;
		}
	}

	m_meshDate.indexBuffer->Unlock();
}

void CNavMeshManager::ObjectCreate()
{
	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		return;
	}

	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		vector3 hitPoint;
		SHARED(Engine::CGameObject) pObj;
		if ((m_createCount == 0 || m_createCount == 1) && m_object.size() >= 2)
		{
			hitPoint = Engine::GET_MAIN_CAM->GetOwner()->GetPosition();

			for (auto& iter = m_object.begin(); iter != m_object.end(); iter++)
			{
				vector3 targetPosition = iter->get()->GetPosition();
				if (Engine::Distance(hitPoint, targetPosition) <= 2)
				{
					pObj = *iter;
					break;
				}
			}
		}
		else
		{
			hitPoint = Engine::GET_MAIN_CAM->GetOwner()->GetPosition();

			_bool enable = true;;
			std::wstring name = L"NavMesh";
			vector3 rotation = vector3Zero;
			vector3 scale = vector3One;

			pObj = Engine::ADD_CLONE(L"NavMesh", L"NavMesh", true);
			pObj->SetIsEnabled(enable);
			pObj->SetName(name);

			pObj->SetPosition(hitPoint);

			pObj->SetRotation(rotation);
			pObj->SetScale(scale);

			m_object.emplace_back(pObj);

			CInspectorView* inspectorView = dynamic_cast<CInspectorView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_rightSplitter.GetPane(0, 0));
			inspectorView->SetData(pObj.get());
		}

		m_triangle[m_triangleCount].point[m_createCount] = &pObj->GetPosition();
		
		m_createCount++;

		if (m_createCount == 3)
		{
			TriangleClockWise(m_triangle[m_triangleCount]);

			m_createCount = 0;
			m_triangleCount++;
			m_triangle.emplace_back(Engine::Triangle());
		}
	}

}

void CNavMeshManager::ObjectDelete(SHARED(Engine::CGameObject) obj)
{
	// 오브젝트 만드는게 1,2단계라면 삭제안됨
	// 3단게까지 정상적으로 삼각형 만들어지고 삭제가능
	// 
	for (auto& iter = m_object.begin(); iter != m_object.end(); iter++)
	{
		if (iter->get()->GetPosition() == obj.get()->GetPosition())
		{
			m_object.erase(iter);
			break;
		}
	}

	TriangleDelete(obj);
}

void CNavMeshManager::TriangleDelete(SHARED(Engine::CGameObject) obj)
{
	bool init = false;
	for (auto& iter = m_triangle.begin(); iter != m_triangle.end(); )
	{
		for (int i = 0; i < 3; i++)
		{
			if (iter->point[i] == &obj->GetPosition())
			{
				iter = m_triangle.erase(iter);
				m_triangleCount--;
				init = true;
				break;
			}
		}
		if(!init)
			iter++;
		init = false;
	}
}

Engine::CGameObject* CNavMeshManager::ObjectPicking()
{
	if (Engine::IMKEY_DOWN(KEY_LBUTTON))
	{
		POINT point;
		GetCursorPos(&point);
		vector3		origin;

		if (point.x >= 1056 || point.y >= 648)
			return nullptr;

		// 마우스좌표(뷰포트) -> (월드행렬)로변환
		D3DVIEWPORT9		ViewPort;
		ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

		Engine::GET_DEVICE->GetViewport(&ViewPort);

		origin.x = point.x / (1056 * 0.5f) - 1.f;
		origin.y = point.y / (648 * -0.5f) + 1.f;
		origin.z = 0.f;

		// 투영 -> 뷰스페이스

		matrix4x4 matProj;
		Engine::GET_DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
		D3DXMatrixInverse(&matProj, NULL, &matProj);
		D3DXVec3TransformCoord(&origin, &origin, &matProj);

		// 뷰스페이스 -> 월드

		vector3	rayDir, rayPos;

		rayPos = vector3(0.0f, 0.0f, 0.0f);
		rayDir = origin - rayPos;

		matrix4x4		matView;
		Engine::GET_DEVICE->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matView, NULL, &matView);

		D3DXVec3TransformCoord(&rayPos, &rayPos, &matView);
		D3DXVec3TransformNormal(&rayDir, &rayDir, &matView);

		Engine::CGameObject* obj = Engine::CRaycast::RayCast(rayPos, rayDir, 1000, L"NavMesh");
		if (obj != nullptr)
		{
			CInspectorView* inspectorView = dynamic_cast<CInspectorView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_rightSplitter.GetPane(0, 0));
			inspectorView->SetData(obj);
			return obj;
		}
	}
}

void CNavMeshManager::TriangleClockWise(Engine::Triangle& triangle)
{
	vector3* onePoint = new vector3(-99999, 0, 0);
	vector3* twoPoint = new vector3(-99999, 0, 0);
	vector3* therePoint = new vector3(-99999, 0, 0);

	vector3* deletePoint[3];
	deletePoint[0] = onePoint;
	deletePoint[1] = twoPoint;
	deletePoint[2] = therePoint;

	for (int i = 0; i < 3; i++)
	{
		if (onePoint->x <= triangle.point[i]->x)
		{
			therePoint = twoPoint;
			twoPoint = onePoint;
			onePoint = triangle.point[i];
		}
		else if (twoPoint->x <= triangle.point[i]->x)
		{
			therePoint = twoPoint;
			twoPoint = triangle.point[i];
		}
		else
		{
			therePoint = triangle.point[i];
		}
	}

	if (therePoint->z < twoPoint->z)
	{
		vector3* T = twoPoint;
		twoPoint = therePoint;
		therePoint = T;
	}

	triangle.point[0] = onePoint;
	triangle.point[1] = twoPoint;
	triangle.point[2] = therePoint;
	
	delete(deletePoint[0]);
	delete(deletePoint[1]);
	delete(deletePoint[2]);
}

