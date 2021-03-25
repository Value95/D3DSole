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
	speed *= deltaTime;
	vector3 a = targetPosition - m_position;
	float magnitude = D3DXVec3Length(&a);
	if (magnitude <= speed || magnitude == 0.0f)
	{
		m_position = targetPosition;
		return;
	}
	m_position = m_position + a / magnitude * speed;
}
// 타겟까지 선형보간하여 이동한다.
void CTransformComponent::Lerp(vector3 targetPosition, _float speed)
{
	/*
	float lerp(float p1, float p2, float d1)
	{
		return (1-d1)*p1 + d1*p2;
	}
	*/

	vector3 dir = targetPosition - m_position;
	D3DXVec3Normalize(&dir, &dir);

	float distance = Engine::Distance(targetPosition, m_position);

	if (distance >= 0.01f)
	{
		float a = MathfMin(speed * deltaTime, 1);
		m_position += dir * a;
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
	//*
	{
		dir = m_position - target;

		D3DXVec3Normalize(&dir, &dir);

		D3DXVec3Cross(&axis, &vector3Forward, &dir);
		dot = D3DXVec3Dot(&vector3Forward, &dir);
		angle = acos(dot);


		if (dir.y <= 0)
		{
			angle = angle + (abs(angle - 3.14f) * 2);
		}

		angle = D3DXToDegree(angle);
		m_rotation.x = angle;
	}
	//*/

	// X의대한 회전
	/*
	{
		dir = m_position - target;

		D3DXVec3Normalize(&dir, &dir);

		D3DXVec3Cross(&axis, &vector3Up, &dir);
		dot = D3DXVec3Dot(&vector3Up, &dir);
		angle = acos(dot);


		if (dir.x >= 0)
		{
			angle = angle + (abs(angle - 3.14f) * 2);
		}

		angle = D3DXToDegree(angle);
		m_rotation.y = angle;
	}
	//*/

	//*
	dir = target - m_position;

	D3DXVec3Normalize(&dir, &dir);
	D3DXVec3Cross(&axis, &vector3Up, &dir);
	D3DXVec3Normalize(&axis, &axis);

	dot = D3DXVec3Dot(&vector3Up, &dir);

	angle = acos(dot);
	D3DXMatrixRotationAxis(&matrix, &axis, angle);

	quaternion R; // 회전
	D3DXMatrixDecompose(&D3DXVECTOR3(), &R, &D3DXVECTOR3(), &matrix);

	if (dir.z >= 0)
	{
		m_rotation.y = 90 + abs(((D3DXToDegree(R.z) * 2) - 90));
	}
	else
	{
		m_rotation.y = (D3DXToDegree(R.z) * 2);
	}

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
