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
	static CGameObject* MeshRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey, vector3& outHit);
	static CGameObject* MeshRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey);
	static CGameObject* BoxRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey, vector3& outHit);
	static CGameObject* BoxRayCast(vector3 origin, vector3 direction, _float maxDistance, std::wstring layerKey);
	static CGameObject* BoxRayCast(vector3 origin, vector3 direction, _float maxDistance, CGameObject* originObject = nullptr);
	static vector<CGameObject*> UIRayCast(std::wstring layerKey);
	// ��� ������Ʈ�� ���忡������


private:
	static _bool RayIntersectCheck	(_float rayAxisDir, _float rayAxisStart,
							_float aabbAxisMin, _float aabbAxisMax,
							_float& tMin, _float& tMax);

};
END

#endif