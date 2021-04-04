#ifndef ENGINESTRUCTURE_H
#define ENGINESTRUCTURE_H


namespace Engine
{
	typedef struct _CustomVertex
	{
		vector3	position;
		vector3 normal;
		vector2	uv;
	}CUSTOM_VERTEX;
	const _uint customFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL;

	typedef struct _MeshData
	{
		std::wstring name;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		_uint vertexCount;
		_uint vertexSize;
		_uint faceCount; //== PolygonCount == triangleCount
		_uint FVF;
		_uint vertexNumInFace;

		LPDIRECT3DINDEXBUFFER9 indexBuffer;
		D3DFORMAT indexFormat;
		_uint indexSize;
	}MESH_DATA;

	typedef struct _TexData
	{
		std::wstring name;
		LPDIRECT3DTEXTURE9 pTexture;
		D3DXIMAGE_INFO imageInfo;
	}TEXTURE_DATA;

	typedef struct _BOOL3
	{
		_BOOL3(bool x, bool y, bool z)
		{
			x = x;
			y = y;
			z = z;
		}

		bool x;
		bool y;
		bool z;
	}BOOL3;

	typedef struct _Face
	{
		_uint vertexIndex[3];
		_uint uvIndex[3];
		_uint normIndex[3];
	}FACE;

	typedef struct _Text
	{
		std::wstring	m_message;
		D3DXVECTOR3		m_position;
		D3DXCOLOR		m_color;
		bool			m_isVisible;
	}TEXT;

	typedef struct _tagUnitInfo
	{
		std::wstring wsObjectKey;
		vector3 vPos;
		vector3 vRot;
		vector3 vScale;
	}UNITINFO;

	typedef struct tagTriangle
	{
		vector3* point[3];
	}Triangle;
}

#endif // !ENGINESTRUCTURE_H

