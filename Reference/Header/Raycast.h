#ifndef RAYCAST_H
#define RAYCAST_H

#include "Engine.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CRaycast final : public CEngine
{
private:
	CRaycast();
	~CRaycast();
public:
	static CGameObject* RayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey, vector3& outHit);
private:
	static _bool RayIntersectCheck	(_float rayAxisDir, _float rayAxisStart,
							_float aabbAxisMin, _float aabbAxisMax,
							_float& tMin, _float& tMax);

};
END

#endif