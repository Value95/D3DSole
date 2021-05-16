#include "EngineStdafx.h"
#include "Raycast.h"
#include "WndApp.h"
#include "GameObject.h"
#include "Layer.h"
#include "SceneManager.h"

USING(Engine)

CRaycast::CRaycast()
{
}

CRaycast::~CRaycast()
{
}

// 원점(origin) , 방향(direction) , 거리(maxDistance) , 레이어(layerKey) , 히트지점(outHit)
CGameObject * CRaycast::MeshRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey, vector3& outHit)
{
	BOOL hit;
	DWORD dwfaceIndex;
	_float u, v, dist;
	HRESULT hr;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerKey].get();

	vector3 Torigin;
	vector3 Tdirection;

	CGameObject* gameObject = nullptr;
	_float minDist = 999999;
	for (auto& object : pLayer->GetGameObjects())
	{
		SHARED(Engine::CMeshComponent) meshCom = object->GetComponent<Engine::CMeshComponent>();

		if (!meshCom->GetMeshData())
			continue;

		// 월드 -> 로컬
		matrix4x4 matWorld = object->GetWorldMatrix();
		D3DXMatrixInverse(&matWorld, NULL, &matWorld);

		D3DXVec3TransformCoord(&Torigin, &origin, &matWorld);
		D3DXVec3TransformNormal(&Tdirection, &direction, &matWorld);

		hr = D3DXIntersect(meshCom->GetMeshData()->mesh,
			&Torigin,
			&Tdirection,
			&hit,
			&dwfaceIndex,
			&u, &v, &dist, nullptr, nullptr);

		if (hit == true && maxDistance >= dist)
		{
			outHit = vector3(origin + (dist * direction)); // 맞은위치 충돌위치를
			if (EPSILON > outHit.x && -EPSILON < outHit.x)
				outHit.x = 0.f;
			if (EPSILON > outHit.y && -EPSILON < outHit.y)
				outHit.y = 0.f;
			if (EPSILON > outHit.z && -EPSILON < outHit.z)
				outHit.z = 0.f;

			if (dist <= minDist)
			{
				minDist = dist;
				gameObject = object.get();
			}
		}
	}
	return gameObject;
}

CGameObject * CRaycast::MeshRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey)
{
	BOOL hit;
	DWORD dwfaceIndex;
	_float u, v, dist;
	HRESULT hr;


	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerKey].get();

	vector3 Torigin;
	vector3 Tdirection;

	CGameObject* gameObject = nullptr;
	_float minDist = 999999;
	for (auto& object : pLayer->GetGameObjects())
	{
		SHARED(Engine::CMeshComponent) meshCom = object->GetComponent<Engine::CMeshComponent>();

		if (!meshCom->GetMeshData())
			continue;

		// 월드 -> 로컬
		matrix4x4 matWorld = object->GetWorldMatrix();
		D3DXMatrixInverse(&matWorld, NULL, &matWorld);

		D3DXVec3TransformCoord(&Torigin, &origin, &matWorld);
		D3DXVec3TransformNormal(&Tdirection, &direction, &matWorld);

		hr = D3DXIntersect(meshCom->GetMeshData()->mesh, // 해당 매쉬
			&Torigin, // 시작위치
			&Tdirection, // 방향
			&hit, // 충돌지점 넘겨받음 out
			&dwfaceIndex, // 매쉬에서 충돌된 인덱스번호 out
			&u, &v, &dist, nullptr, nullptr); // dist는 거리 out

		if (hit == true && maxDistance >= dist)
		{
			vector3 outHit = vector3(Torigin + (dist * Tdirection)); // 맞은위치 충돌위치를
			if (EPSILON > outHit.x && -EPSILON < outHit.x)
				outHit.x = 0.f;
			if (EPSILON > outHit.y && -EPSILON < outHit.y)
				outHit.y = 0.f;
			if (EPSILON > outHit.z && -EPSILON < outHit.z)
				outHit.z = 0.f;

			if (dist <= minDist)
			{
				minDist = dist;
				gameObject = object.get();
			}			
		}
	}
	return gameObject;
}

CGameObject * CRaycast::BoxRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey, vector3 & outHit)
{
	// 콜라이더랑 충돌하는 RayCast가필요하다.	

	_float t = FLT_MAX;
	CGameObject* pGameObject = nullptr;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerKey].get();

	for (auto& object : pLayer->GetGameObjects())
	{
		if (object->GetPosition() == origin)
			continue;

		_float tMin = 0;
		_float tMax = maxDistance;

		vector3 minPos = (object->GetScale()* 0.5f) * -1;
		vector3 maxPos = (object->GetScale()* 0.5f);

		object->OutTranslate(minPos);
		object->OutTranslate(maxPos);

		minPos.x = minPos.x / object->GetScale().x;
		minPos.y = minPos.y / object->GetScale().y;
		minPos.z = minPos.z / object->GetScale().z;

		maxPos.x = maxPos.x / object->GetScale().x;
		maxPos.y = maxPos.y / object->GetScale().y;
		maxPos.z = maxPos.z / object->GetScale().z;

		D3DXVec3TransformCoord(&minPos, &minPos, &object->GetWorldMatrix());
		D3DXVec3TransformCoord(&maxPos, &maxPos, &object->GetWorldMatrix());

		// 문제는 오브젝트의크기
		// 플레이어의 0.001과 돌의 1은 같은 크기이다. 근데 이것을 월드로보면 플레이어는 돌에 100배작다.

		for (int i = 0; i < 3; ++i)
		{
			if (minPos[i] > maxPos[i])
			{
				_float temp = minPos[i];
				minPos[i] = maxPos[i];
				maxPos[i] = temp;
			}
		}

		if (!RayIntersectCheck(direction.x, origin.x, minPos.x, maxPos.x, tMin, tMax))
			continue;
		if (!RayIntersectCheck(direction.y, origin.y, minPos.y, maxPos.y, tMin, tMax))
			continue;
		if (!RayIntersectCheck(direction.z, origin.z, minPos.z, maxPos.z, tMin, tMax))
			continue;

		if (tMin < t)
		{
			t = tMin;
			pGameObject = object.get();
		}
	}

	return pGameObject;
}

CGameObject* CRaycast::BoxRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey)
{
	_float t = FLT_MAX;
	CGameObject* pGameObject = nullptr;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerKey].get();

	if(pLayer == nullptr)
		return pGameObject;

	for (auto& object : pLayer->GetGameObjects())
	{
		if (object->GetPosition() == origin)
			continue;

		if (object->GetComponent<Engine::CColliderComponent>() == nullptr)
			continue;

		if (object->GetComponent<Engine::CColliderComponent>()->GetColliders()[0] == nullptr)
			continue;
		

		_float tMin = 0;
		_float tMax = maxDistance;

		CCollider* collider = object->GetComponent<Engine::CColliderComponent>()->GetColliders()[0];

		vector3 minPos;
		vector3 maxPos;

		if (collider->GetColliderType() == (int)EColliderType::Box)
		{
			CBoxCollider* boxCollider = static_cast<Engine::CBoxCollider*>(collider);
			minPos = ((boxCollider->GetBoxSize() * 0.5f) * -1) + (boxCollider->GetOffset());
			maxPos = (boxCollider->GetBoxSize() * 0.5f) + (boxCollider->GetOffset());
		}
		else if (collider->GetColliderType() == (int)EColliderType::Sphere)
		{
			collider = dynamic_cast<Engine::CSphereCollider*>(collider);
		}

		object->OutTranslate(minPos);
		object->OutTranslate(maxPos);

		minPos.x = minPos.x / object->GetScale().x;
		minPos.y = minPos.y / object->GetScale().y;
		minPos.z = minPos.z / object->GetScale().z;

		maxPos.x = maxPos.x / object->GetScale().x;
		maxPos.y = maxPos.y / object->GetScale().y;
		maxPos.z = maxPos.z / object->GetScale().z;

		matrix4x4 rotation;
		D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(object->GetRotation().y), D3DXToRadian(object->GetRotation().x), D3DXToRadian(object->GetRotation().z));

		D3DXVec3TransformNormal(&minPos, &minPos, &rotation);
		D3DXVec3Normalize(&minPos, &minPos);

		D3DXVec3TransformNormal(&maxPos, &maxPos, &rotation);
		D3DXVec3Normalize(&maxPos, &maxPos);

		D3DXVec3TransformCoord(&minPos, &minPos, &object->GetWorldMatrix());
		D3DXVec3TransformCoord(&maxPos, &maxPos, &object->GetWorldMatrix());

		

		// 문제는 오브젝트의크기
		// 플레이어의 0.001과 돌의 1은 같은 크기이다. 근데 이것을 월드로보면 플레이어는 돌에 100배작다.

		for (int i = 0; i < 3; ++i)
		{
			if (minPos[i] > maxPos[i])
			{
				_float temp = minPos[i];
				minPos[i] = maxPos[i];
				maxPos[i] = temp;
			}
		}

		// D3DXIntersectTri

		if (!RayIntersectCheck(direction.x, origin.x, minPos.x, maxPos.x, tMin, tMax))
			continue;
		if (!RayIntersectCheck(direction.y, origin.y, minPos.y, maxPos.y, tMin, tMax))
			continue;
		if (!RayIntersectCheck(direction.z, origin.z, minPos.z, maxPos.z, tMin, tMax))
			continue;

		if (tMin < t)
		{
			t = tMin;
			pGameObject = object.get();
		}
	}

	return pGameObject;
}

CGameObject* CRaycast::BoxRayCast(vector3 origin, vector3 direction, _float maxDistance, CGameObject* originObject)
{
	_float t = FLT_MAX;
	CGameObject* pGameObject = nullptr;

	for (auto pLayer = GET_CUR_SCENE->GetLayers().begin(); pLayer != GET_CUR_SCENE->GetLayers().end(); pLayer++)
	{

		if (pLayer->second == nullptr)
			continue;

		for (auto& object : pLayer->second->GetGameObjects())
		{
			if (originObject == object.get())
				continue;

			if (object->GetComponent<Engine::CColliderComponent>() == nullptr)
				continue;

			if (object->GetComponent<Engine::CColliderComponent>()->GetColliders()[0] == nullptr)
				continue;


			_float tMin = 0;
			_float tMax = maxDistance;

			CCollider* collider = object->GetComponent<Engine::CColliderComponent>()->GetColliders()[0];

			vector3 minPos;
			vector3 maxPos;

			if (collider->GetColliderType() == (int)EColliderType::Box)
			{
				CBoxCollider* boxCollider = static_cast<Engine::CBoxCollider*>(collider);
				minPos = ((boxCollider->GetBoxSize() * 0.5f) * -1);
				maxPos = (boxCollider->GetBoxSize() * 0.5f);

				object->OutTranslate(minPos);
				object->OutTranslate(maxPos);

				minPos.x = minPos.x / object->GetScale().x;
				minPos.y = minPos.y / object->GetScale().y;
				minPos.z = minPos.z / object->GetScale().z;

				maxPos.x = maxPos.x / object->GetScale().x;
				maxPos.y = maxPos.y / object->GetScale().y;
				maxPos.z = maxPos.z / object->GetScale().z;

				D3DXVec3TransformCoord(&minPos, &minPos, &object->GetWorldMatrix());
				D3DXVec3TransformCoord(&maxPos, &maxPos, &object->GetWorldMatrix());

				minPos += (boxCollider->GetOffset());
				maxPos += (boxCollider->GetOffset());
			}
			else if (collider->GetColliderType() == (int)EColliderType::Sphere)
			{
				collider = dynamic_cast<Engine::CSphereCollider*>(collider);
			}



			// 문제는 오브젝트의크기
			// 플레이어의 0.001과 돌의 1은 같은 크기이다. 근데 이것을 월드로보면 플레이어는 돌에 100배작다.

			for (int i = 0; i < 3; ++i)
			{
				if (minPos[i] > maxPos[i])
				{
					_float temp = minPos[i];
					minPos[i] = maxPos[i];
					maxPos[i] = temp;
				}
			}

			// D3DXIntersectTri

			if (!RayIntersectCheck(direction.x, origin.x, minPos.x, maxPos.x, tMin, tMax))
				continue;
			if (!RayIntersectCheck(direction.y, origin.y, minPos.y, maxPos.y, tMin, tMax))
				continue;
			if (!RayIntersectCheck(direction.z, origin.z, minPos.z, maxPos.z, tMin, tMax))
				continue;

			if (tMin < t)
			{
				t = tMin;
				pGameObject = object.get();
			}
		}
	}

	return pGameObject;
}

vector<CGameObject*> CRaycast::UIRayCast(std::wstring layerKey)
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(CWndApp::GetInstance()->GetHWnd(), &point);

	point.x -= CWndApp::GetInstance()->GetWndWidth() *0.5f;
	point.y -= CWndApp::GetInstance()->GetWndHeight() *0.5f;

	cout << point.x << endl;
	cout << point.y << endl << endl;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerKey].get();

	vector<CGameObject*> returnObject;

	for (auto& object : pLayer->GetGameObjects())
	{
		float distanceX = fabs(fabs(object->GetPosition().x) - fabs(point.x));
		float radCX = object->GetScale().x * 0.5f;

		float distanceY = fabs(fabs(object->GetPosition().y) - fabs(point.y));
		float radCY = object->GetScale().y * 0.5f;

		if (distanceX <= radCX && distanceY <= radCY)
		{
			returnObject.emplace_back(object.get());
		}

	}

	return returnObject;
}

_bool CRaycast::RayIntersectCheck(_float rayAxisDir, _float rayAxisStart,
	_float aabbAxisMin, _float aabbAxisMax,
	_float& tMin, _float& tMax)
{
	if (abs(rayAxisDir) < EPSILON)
	{
		//no hit if origin not within axis
		if (rayAxisStart < aabbAxisMin || rayAxisStart > aabbAxisMax)
			return false;
	}
	else
	{
		//compute intersection t value of near and far plane of axis
		float ood = 1.f / rayAxisDir;
		float t1 = (aabbAxisMin - rayAxisStart) * ood;
		float t2 = (aabbAxisMax - rayAxisStart) * ood;
		//make t1 be intersection with near plane, t2 with far
		if (t1 > t2)
		{
			_float temp = t1;
			t1 = t2;
			t2 = temp;
		}

		//compute intersection on axis 
		if (t1 > tMin)
			tMin = t1;
		if (t2 < tMax)
			tMax = t2;

		//Exit with no collision as soon as intersection becomes empty
		if (tMin > tMax)
			return false;
	}


	return true;
}

