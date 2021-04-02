#include "stdafx.h"
#include "NavMeshManager.h"

CNavMeshManager* CNavMeshManager::m_instance = nullptr;

void CNavMeshManager::OnDestroy()
{
}

void CNavMeshManager::TriangleRender()
{
}

void CNavMeshManager::ObjectCreate()
{
	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		return;
	}

	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		_bool enable = true;;
		std::wstring name = L"NavMesh";
		vector3 rotation = vector3Zero;
		vector3 scale = vector3One;


		// 오브젝트 생성--------------------------------------------------
		SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(L"NavMesh", L"NavMesh", true);
		pObj->AddComponent<Engine::CSphereComponent>();
		pObj->SetIsEnabled(enable);
		pObj->SetName(name);

		pObj->SetPosition(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3(0, 0, 5)));
		pObj->SetRotation(rotation);
		pObj->SetScale(scale);

		CInspectorView* inspectorView = dynamic_cast<CInspectorView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_rightSplitter.GetPane(0, 0));
		inspectorView->SetData(pObj.get());
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

