#ifndef ENGINESTRUCTURE_H
#define ENGINESTRUCTURE_H


namespace Engine
{
	 
	typedef struct _VTXCUBE
	{
		vector3	position;
		vector3	uv;
	}TexCube;
	const _uint texCubeFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	typedef struct INDEX16
	{
		unsigned short _0;
		unsigned short _1;
		unsigned short _2;

	}INDEX16;

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

	typedef struct _MeshComData
	{
		_MeshComData()
		{
			name = L"";
			adjacency = nullptr;
			materials = nullptr;
			materialsCount = 0;
			mesh = nullptr;
		}

		void AddTexture(LPDIRECT3DDEVICE9 device, const _wcharT * textureFilePath)
		{
			/*IDirect3DBaseTexture9*	Ttexture = nullptr;
			if (FAILED(D3DXCreateTextureFromFile(device, textureFilePath, (LPDIRECT3DTEXTURE9*)&Ttexture)))
				return;
			texture.emplace_back(Ttexture);*/
		}

		std::wstring name;
		LPD3DXBUFFER adjacency = nullptr;
		LPD3DXBUFFER materials = nullptr;
		_ulong materialsCount = 0;
		LPD3DXMESH mesh = nullptr;

		std::vector<IDirect3DBaseTexture9*> texture;
		D3DXIMAGE_INFO imageInfo;
	}MeshComData;

	typedef struct tagD3DXFrame_Derived : public D3DXFRAME
	{
		D3DXMATRIX		CombinedTransformationMatrix;
	}D3DXFRAME_DERIVED;

	typedef struct tagD3DXMeshContainer_Derived : public D3DXMESHCONTAINER
	{
		class CTexture*		pMeshTexture;

		unsigned int		iNumBones;	// 메쉬가 지닌 모든 뼈의 개수를 보관

		LPDIRECT3DTEXTURE9*		ppTexture;

		// 최초 로드 시점의 상태를 가지고 있는 메쉬 객체(불변)
		LPD3DXMESH		pOriginalMesh;

		// 애니메이션 정보를 포함한 최초의 행렬 상태 
		D3DXMATRIX*		pOffsetMatrices;

		// 뼈 구조체가 갖고 있는 CombinedTransformationMatrix의 주소값들을 보관하는 포인터
		D3DXMATRIX**	ppCombinedTransformationMatrices;

		// 최종적으로 출력을 위한 행렬의 상태
		D3DXMATRIX*		pRenderingMatrices;

	}D3DXMESHCONTAINER_DERIVED;

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
}

#endif // !ENGINESTRUCTURE_H

