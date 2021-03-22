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
// �ڽ��� ȸ������ �������� �̵��Ѵ�.
void CTransformComponent::Translate(vector3 translation)
{
	matrix4x4 rotate;
	
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	m_position += translation * deltaTime;
}
// Ÿ�ٱ��� ������ �ӵ��� �̵��Ѵ�.
void CTransformComponent::MoveTowards(vector3& thisPosition, vector3 targetPosition, _float speed)
{

}
// Ÿ�ٱ��� ���������Ͽ� �̵��Ѵ�.
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
// Ÿ���� �ٶ󺸰� ȸ�����ش�.
void CTransformComponent::LookAt(vector3 target, vector3 worldUp)
{
	matrix4x4 matrix;
	vector3 dir = m_position - target;
	vector3 cross;
	D3DXVec3Cross(&cross, &target, &m_position);

	D3DXMatrixRotationAxis(&matrix, &dir, 45);
	/*
	 	-z���� �ٶ󺸴� ���͸� A��� �մϴ�.
		( a, b, c ) ���͸� B��� �մϴ�.
		A�� B�� �����Ͽ� �������� C�� ���մϴ�.
		A�� B�� �����Ͽ� �� ���Ͱ��� ���� t�� ���մϴ�.
	*/
	// A���Ϳ� �ȸ�������ִϱ� B���Ͱ� ���Դ�.
	// �̶� ȸ������ ���� ���Ͻÿ�
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
