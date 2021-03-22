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
// 타겟까지 일정한 속도로 이동한다.
void CTransformComponent::MoveTowards(vector3& thisPosition, vector3 targetPosition, _float speed)
{

}
// 타겟까지 선형보간하여 이동한다.
void CTransformComponent::Lerp(vector3& thisPosition, vector3 targetPosition, _float speed)
{
	vector3 dir = targetPosition - thisPosition;
	D3DXVec3Normalize(&dir, &dir);
	
	if (Engine::Distance(targetPosition, thisPosition) >= 0.01f)
	{
		thisPosition += dir * speed * deltaTime;
	}
	else
	{
		thisPosition = targetPosition;
	}

}
// 타겟을 바라보게 회전해준다.
void CTransformComponent::LookAt(vector3 target, vector3 worldUp)
{
	matrix4x4 matrix;
	vector3 dir = m_position - target;
	vector3 cross;
	D3DXVec3Cross(&cross, &target, &m_position);

	D3DXMatrixRotationAxis(&matrix, &dir, 45);
	/*
	 	-z축을 바라보는 벡터를 A라고 합니다.
		( a, b, c ) 벡터를 B라고 합니다.
		A와 B를 외적하여 오른벡터 C를 구합니다.
		A와 B를 내적하여 두 벡터간의 각도 t를 구합니다.
	*/
	// A벡터에 어떤회전값을주니까 B벡터가 나왔다.
	// 이때 회전값의 값을 구하시오
	// (0,0,1) -> (0.5,0.5,0.5)

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
