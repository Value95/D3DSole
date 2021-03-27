#ifndef ENGINEMATRIXFUNCTION_H
#define ENGINEMATRIXFUNCTION_H

namespace Engine
{
	/*
	
	// 로컬스페이스 -> 월드스페이스 -> 뷰스페이스  -> 투영        -> 뷰포트
	// Local space  -> World space  -> View space  -> projection  -> Viewport

	void LocalToWorld(vector3& position) // 로컬 -> 월드
	{

	}

	void LocalToView(vector3& position) //로컬 -> 뷰
	{

	}

	void LocalToProjection(vector3& position) // 로컬 -> 투영
	{

	}

	void LocalToViewport(vector3& position) // 로컬 -> 뷰포트
	{

	}

	void WorldToLocal(vector3& position, matrix4x4 world) // 월드 -> 로컬
	{
	D3DXMatrixInverse(&world, NULL, &world);
	D3DXVec3TransformCoord(&position, &position, &world);
	}

	void WordlToView(vector3& position) // 월드 -> 뷰
	{

	}

	void WorldToProjection(vector3& position) // 월드 -> 투영
	{

	}

	void WorldToViewport(vector3& position) // 월드 -> 뷰포트
	{

	}

	void ViewToLocal(vector3& position) // 뷰 -> 로컬
	{

	}

	void ViewToWorld(vector3& position, LPDIRECT3DDEVICE9 device) // 뷰 -> 월드
	{
	matrix4x4		matView;
	device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformNormal(&position, &position, &matView);
	}

	void ViewToProjection(vector3& position) // 뷰 -> 투영
	{

	}

	void ViewToViewport(vector3& position) // 뷰 -> 뷰포트
	{

	}

	void ProjectionToLocal(vector3& position) // 투영 -> 로컬
	{

	}

	void ProjectionToWorld(vector3& position) // 투영 -> 월드
	{

	}

	void ProjectionToView(vector3& position, LPDIRECT3DDEVICE9 device) // 투영 -> 뷰
	{
	matrix4x4		matProj;
	device->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&position, &position, &matProj);
	}

	void ProjectionToViewport(vector3& position) // 투영 -> 뷰포트
	{

	}

	void ViewportToLocal(vector3& position) // 뷰포트 -> 로컬
	{

	}

	void ViewportToWorld(vector3& position) // 뷰포트 -> 월드
	{

	}

	void ViewportToView(vector3& position) // 뷰포트 -> 뷰
	{

	}

	void ViewportToProject(vector3& position, LPDIRECT3DDEVICE9 device) // 뷰포트 -> 투영
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

// 뷰포트 -> 투영
vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
vMousePos.y = ptMouse.y / (ViewPort.Height * -0.5f) + 1.f;
vMousePos.z = 0.f;

// 투영 -> 뷰스페이스

_matrix		matProj;
m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
D3DXMatrixInverse(&matProj, NULL, &matProj);
D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

// 뷰스페이스 -> 월드

_vec3	vRayPos, vRayDir;

vRayPos = _vec3(0.f, 0.f, 0.f);
vRayDir = vMousePos - vRayPos;

_matrix		matView;
m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
D3DXMatrixInverse(&matView, NULL, &matView);

D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

// 월드 -> 로컬

_matrix matWorld;
pTerrainTransCom->Get_WorldMatrix(&matWorld);
D3DXMatrixInverse(&matWorld, NULL, &matWorld);

D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

*/

