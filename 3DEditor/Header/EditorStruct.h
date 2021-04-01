#ifndef EDITORSTRUCT_H
#define EDITORSTRUCT_H

typedef struct tagCubeMap
{
	vector3 vPos;
	vector3 vSize;
	BYTE byOption;
}CUBEMAP;

typedef struct tagCollider
{
	tagCollider()
	{
		colliderType = L"Default";
		offset = vector3Zero;
		boxsize = vector3One;
		radius = 0.5f;
	}

	std::wstring colliderType;
	vector3 offset;
	vector3 boxsize;
	_float radius;
}ColliderData;

typedef struct tagPrefab
{
	_bool enable;
	std::wstring name;
	std::wstring layerKey;
	std::wstring objectKey;
	std::wstring messKey;
	std::wstring textureKey;
	vector3 rotation;
	vector3 scale;
	tagCollider* collider;
}PrefabData;

typedef struct tagTriangle
{
	vector3 point[3];
}Triangle;

#endif