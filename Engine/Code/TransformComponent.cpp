#include "EngineStdafx.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "DataStore.h"

USING(Engine)
CTransformComponent::CTransformComponent(void)  
{
}

CTransformComponent::~CTransformComponent(void)
{
}

void CTransformComponent::TransformUpdate()
{
	UpdateWorldmMatrix();
}
// 자신의 회전축을 기준으로 이동한다.
void CTransformComponent::Translate(vector3 translation)
{	
	matrix4x4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	m_position += translation * deltaTime;
}
vector3 CTransformComponent::ReturnTranslate(vector3 translation)
{
	matrix4x4 rotate;
	
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	return m_position + translation;
}
// 타겟까지 일정한 속도로 이동한다.
void CTransformComponent::MoveTowards(vector3 targetPosition, _float speed)
{

}
// 타겟까지 선형보간하여 이동한다.
void CTransformComponent::Lerp(vector3 targetPosition, _float speed)
{
	vector3 dir = targetPosition - m_position;
	D3DXVec3Normalize(&dir, &dir);
	
	if (Engine::Distance(targetPosition, m_position) >= 0.01f)
	{
		m_position += dir * speed * deltaTime;
	}
	else
	{
		m_position = targetPosition;
	}

}
// 타겟을 바라보게 회전해준다.
void CTransformComponent::LookAt(vector3 target, vector3 worldUp)
{
	matrix4x4 matrix;
	vector3 axis, dir;
	_float angle, dot;

	// Y의대한 회전
	/*
	{
		dir = m_position - target;

		D3DXVec3Normalize(&dir, &dir);

		D3DXVec3Cross(&axis, &vector3Forward, &dir);
		dot = D3DXVec3Dot(&vector3Forward, &dir);
		angle = acos(dot);
		angle = D3DXToDegree(angle);

		m_rotation.y = angle;
	}

	// X의대한 회전
	{
		dir = m_position - target;

		D3DXVec3Normalize(&dir, &dir);

		D3DXVec3Cross(&axis, &vector3Up, &dir);
		dot = D3DXVec3Dot(&vector3Up, &dir);
		angle = asin(dot);
		angle = D3DXToDegree(angle);

		m_rotation.x = angle;
	}
	//*/

	//*
	dir = m_position - target;
	D3DXVec3Normalize(&dir, &dir);
	D3DXVec3Cross(&axis, &vector3Forward, &dir);
	D3DXVec3Normalize(&axis, &axis);

	dot = D3DXVec3Dot(&vector3Forward, &dir);

	angle = acos(dot);
	
	quaternion qu;
	D3DXQuaternionRotationAxis(&qu, &dir, angle);
	qu.y = D3DXToDegree(qu.y) * 2;
	qu.x = D3DXToDegree(qu.x) * 2;
	if (dot <= 0)
	{
		qu.x = 90 + abs(qu.x - 90);
	//	qu.y = 90 + abs(qu.y + 90);
	}

	cout << qu.y << endl;

	m_rotation.x = qu.y;
	m_rotation.y = qu.x;
	//*/
}

void CTransformComponent::UpdateWorldmMatrix(void)
{
	matrix4x4 rotateX, rotateY, rotateZ, scale, translation;

	D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(m_rotation.z));
    D3DXMatrixRotationY(&rotateY, D3DXToRadian(m_rotation.y));
    D3DXMatrixRotationX(&rotateX, D3DXToRadian(m_rotation.x));
    
    D3DXMatrixScaling(&scale, m_scale.x, 
                               m_scale.y,
                               m_scale.z);
    
    D3DXMatrixTranslation(&translation, m_position.x, 
                                          m_position.y,
                                          m_position.z);

	m_worldMat = scale * rotateX * rotateY * rotateZ * translation;
}
