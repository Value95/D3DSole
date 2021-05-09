#include "EngineStdafx.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "DataStore.h"
#include "SceneManager.h"

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

vector3 CTransformComponent::ReturnTranslate(vector3 translation)
{
	matrix4x4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);

	return translation;
}

vector3 CTransformComponent::ReturnPosTranslate(vector3 translation)
{
	matrix4x4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);

	return m_position + translation;
}

void CTransformComponent::OutTranslate(vector3 & translation)
{
	matrix4x4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
}

// 자신의 회전축을 기준으로 이동한다.
void CTransformComponent::Translate(vector3 translation)
{
	matrix4x4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	m_position += translation * deltaTime;
}

void CTransformComponent::CameraDirTranslate(vector3 translation)
{
	matrix4x4 rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(GET_MAIN_CAM->GetOwner()->GetRotation().y), D3DXToRadian(GET_MAIN_CAM->GetOwner()->GetRotation().x), D3DXToRadian(GET_MAIN_CAM->GetOwner()->GetRotation().z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	m_position += translation * deltaTime;
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
	LookAtX(target, worldUp);
	LookAtY(target, worldUp);
}

void CTransformComponent::LookAtX(vector3 target, vector3 worldUp)
{
	matrix4x4 matrix;
	vector3 axis, dir;
	_float angle, dot;

	target.y = m_position.y;
	dir = target - m_position;

	D3DXVec3Normalize(&dir, &dir);
	D3DXVec3Cross(&axis, &vector3Up, &dir);
	D3DXVec3Normalize(&axis, &axis);

	dot = D3DXVec3Dot(&vector3Up, &dir);

	angle = acos(dot);
	D3DXMatrixRotationAxis(&matrix, &axis, angle);

	quaternion RY; // 회전
	D3DXMatrixDecompose(&D3DXVECTOR3(), &RY, &D3DXVECTOR3(), &matrix);

	if (dir.z > 0)
		m_rotation.y = 90 + abs(((D3DXToDegree(RY.z) * 2) - 90)) - 180;
	else if (dir.z < 0)
		m_rotation.y = (D3DXToDegree(RY.z) * 2) - 180;

}

void CTransformComponent::LookAtY(vector3 target, vector3 worldUp)
{
	matrix4x4 matrix;
	vector3 axis, dir;
	_float angle, dot;

	dir = target - m_position;

	D3DXVec3Normalize(&dir, &dir);
	D3DXVec3Cross(&axis, &vector3Up, &dir);
	D3DXVec3Normalize(&axis, &axis);

	dot = D3DXVec3Dot(&vector3Up, &dir);

	angle = atan(dot);
	D3DXMatrixRotationAxis(&matrix, &axis, angle);

	quaternion RX; // 회전
	D3DXMatrixDecompose(&D3DXVECTOR3(), &RX, &D3DXVECTOR3(), &matrix);

	if (target.x - m_position.x > 0)
		m_rotation.x = 90 + abs(((D3DXToDegree(RX.z) * 2) - 90)) - 180;
	else if (target.x - m_position.x < 0)
		m_rotation.x = (90 + abs(((D3DXToDegree(RX.z) * 2) - 90)) - 180) * -1;
}

void CTransformComponent::UpdateWorldmMatrix(void)
{
	if (!m_camera)
	{
		matrix4x4 scale, rotateX, rotateY, rotateZ, translation;

		D3DXMatrixScaling(&scale, m_scale.x,
			m_scale.y,
			m_scale.z);

		D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(m_rotation.z));
		D3DXMatrixRotationY(&rotateY, D3DXToRadian(m_rotation.y));
		D3DXMatrixRotationX(&rotateX, D3DXToRadian(m_rotation.x));

		D3DXMatrixTranslation(&translation, m_position.x,
			m_position.y,
			m_position.z);

		m_worldMat = scale * rotateX * rotateY * rotateZ * translation;
	}
	else if (m_camera)
	{
		matrix4x4 scale, rotateX, rotateY, rotateZ, translation;
		matrix4x4 preantRotateX, preantRotateY, preantTranslation;

		D3DXMatrixScaling(&scale, m_scale.x,
			m_scale.y,
			m_scale.z);

		D3DXMatrixRotationX(&rotateX, D3DXToRadian(m_rotation.x)); // 이건 무조건 플레이어를 바라보게
		D3DXMatrixRotationY(&rotateY, D3DXToRadian(m_rotation.y));
		D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(m_rotation.z));


		// 나중에 CameraMove로 이동시키자
		D3DXMatrixTranslation(&translation, m_cameraDirPos.x, m_cameraDirPos.y, m_cameraDirPos.z);

		D3DXMatrixRotationX(&preantRotateX, D3DXToRadian(m_cameraX));
		D3DXMatrixRotationY(&preantRotateY, D3DXToRadian(m_cameraY));

		D3DXMatrixTranslation(&preantTranslation, m_target->GetPosition().x,
			m_target->GetPosition().y,
			m_target->GetPosition().z);

		m_worldMat = scale * rotateX * rotateY * rotateZ * translation * preantRotateX * preantRotateY * preantTranslation;

		m_position.x = m_worldMat._41;
		m_position.y = m_worldMat._42;
		m_position.z = m_worldMat._43;
	}
}
