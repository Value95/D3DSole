#ifndef ENGINEMATRIXFUNCTION_H
#define ENGINEMATRIXFUNCTION_H

namespace Engine
{
	/*
	
	// ���ý����̽� -> ���彺���̽� -> �佺���̽�  -> ����        -> ����Ʈ
	// Local space  -> World space  -> View space  -> projection  -> Viewport

	void LocalToWorld(vector3& position) // ���� -> ����
	{

	}

	void LocalToView(vector3& position) //���� -> ��
	{

	}

	void LocalToProjection(vector3& position) // ���� -> ����
	{

	}

	void LocalToViewport(vector3& position) // ���� -> ����Ʈ
	{

	}

	void WorldToLocal(vector3& position, matrix4x4 world) // ���� -> ����
	{
	D3DXMatrixInverse(&world, NULL, &world);
	D3DXVec3TransformCoord(&position, &position, &world);
	}

	void WordlToView(vector3& position) // ���� -> ��
	{

	}

	void WorldToProjection(vector3& position) // ���� -> ����
	{

	}

	void WorldToViewport(vector3& position) // ���� -> ����Ʈ
	{

	}

	void ViewToLocal(vector3& position) // �� -> ����
	{

	}

	void ViewToWorld(vector3& position, LPDIRECT3DDEVICE9 device) // �� -> ����
	{
	matrix4x4		matView;
	device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformNormal(&position, &position, &matView);
	}

	void ViewToProjection(vector3& position) // �� -> ����
	{

	}

	void ViewToViewport(vector3& position) // �� -> ����Ʈ
	{

	}

	void ProjectionToLocal(vector3& position) // ���� -> ����
	{

	}

	void ProjectionToWorld(vector3& position) // ���� -> ����
	{

	}

	void ProjectionToView(vector3& position, LPDIRECT3DDEVICE9 device) // ���� -> ��
	{
	matrix4x4		matProj;
	device->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&position, &position, &matProj);
	}

	void ProjectionToViewport(vector3& position) // ���� -> ����Ʈ
	{

	}

	void ViewportToLocal(vector3& position) // ����Ʈ -> ����
	{

	}

	void ViewportToWorld(vector3& position) // ����Ʈ -> ����
	{

	}

	void ViewportToView(vector3& position) // ����Ʈ -> ��
	{

	}

	void ViewportToProject(vector3& position, LPDIRECT3DDEVICE9 device) // ����Ʈ -> ����
	{
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	device->GetViewport(&ViewPort);

	position.x = position.x / (ViewPort.Width * 0.5f);
	position.y = position.y / (ViewPort.Height * -0.5f);
	position.z = 0.f;
	}
	
	*/
}



#endif // !ENGINEMATRIXFUNCTION_H



/*

// ����Ʈ -> ����
vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
vMousePos.y = ptMouse.y / (ViewPort.Height * -0.5f) + 1.f;
vMousePos.z = 0.f;

// ���� -> �佺���̽�

_matrix		matProj;
m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
D3DXMatrixInverse(&matProj, NULL, &matProj);
D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

// �佺���̽� -> ����

_vec3	vRayPos, vRayDir;

vRayPos = _vec3(0.f, 0.f, 0.f);
vRayDir = vMousePos - vRayPos;

_matrix		matView;
m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
D3DXMatrixInverse(&matView, NULL, &matView);

D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

// ���� -> ����

_matrix matWorld;
pTerrainTransCom->Get_WorldMatrix(&matWorld);
D3DXMatrixInverse(&matWorld, NULL, &matWorld);

D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

*/

