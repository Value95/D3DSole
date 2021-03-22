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

// 원점(origin) , 방향(direction) , 거리(maxDistance) , 레이어(layerKey)
CGameObject * CRaycast::RayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey)
{
	_float t = FLT_MAX;
	CGameObject* pGameObject = nullptr;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerKey].get();

	for (auto& object : pLayer->GetGameObjects())
	{
		if (object->GetPosition() == origin)
			continue;

		_float tMin = 0;
		_float tMax = maxDistance;

		// 36 ~ 57행 설명좀
		vector3 minPos = vector3(-0.5f, -0.5f, -0.5f);
		vector3 maxPos = vector3(0.5f, 0.5f, 0.5f);

		D3DXVec3TransformCoord(&minPos, &minPos, &object->GetWorldMatrix());
		D3DXVec3TransformCoord(&maxPos, &maxPos, &object->GetWorldMatrix());
		
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

