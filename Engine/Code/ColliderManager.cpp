#include "EngineStdafx.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "TransformComponent.h"
#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CColliderManager)

void CColliderManager::Awake(void)
{
	__super::Awake();
}

void CColliderManager::Start(void)
{
}

_uint CColliderManager::FixedUpdate(void)
{

	return _uint();
}

_uint CColliderManager::Update(void)
{

	return _uint();
}

_uint CColliderManager::LateUpdate(void)
{
	return _uint();
}


void CColliderManager::OnDestroy(void)
{
}

void CColliderManager::OnEnable(void)
{
}

void CColliderManager::OnDisable(void)
{
}

void CColliderManager::ColliderInput(SHARED(CColliderComponent) colliderComponent)
{
	if (colliderComponent == nullptr)
		return;

	m_vecCollider.emplace_back(colliderComponent);
}

bool CColliderManager::OnColliderEnter(SHARED(CColliderComponent) collider, std::vector<CGameObject*>& returnCollider)
{
	if (collider == nullptr)
		return false;

	m_gameObject1 = collider->GetOwner();

	for (auto curCollider : collider->GetColliders()) // 현제 나의 충돌체 정보
	{
		_int curColliderType = curCollider->GetColliderType();

		for (auto& allCollider : m_vecCollider) // 전체 콜라이더 정보
		{
			m_gameObject2 = allCollider->GetOwner();

			for (auto collider : allCollider->GetColliders()) // 전체콜라이더 정보에 들어있는 충돌체들
			{
				if (curCollider == collider)
					continue;

				_int colliderType = collider->GetColliderType();

				switch (curColliderType)
				{
				case (_int)EColliderType::Box:
				{
					switch (colliderType)
					{
					case (_int)EColliderType::Box: // 박스 or 박스
						BoxAndBox(returnCollider, static_cast<CBoxCollider*>(curCollider), static_cast<CBoxCollider*>(collider));
						break;
					case (_int)EColliderType::Sphere: // 박스 or 구
						BoxAndSphere(returnCollider, static_cast<CBoxCollider*>(curCollider), static_cast<CSphereCollider*>(collider));
						break;
					}
					break;
				}
				case (_int)EColliderType::Sphere:
				{
					switch (colliderType)
					{
					case (_int)EColliderType::Box:
						// 구 or 박스
						BoxAndSphere(returnCollider, static_cast<CBoxCollider*>(collider), static_cast<CSphereCollider*>(curCollider));
						break;
					case (_int)EColliderType::Sphere:
						// 구 or 구
						SphereAndSphere(returnCollider, static_cast<CSphereCollider*>(curCollider), static_cast<CSphereCollider*>(collider));
						break;
					}
					break;
				}
				}
			}
		}
	}

	if (!returnCollider.empty())
		return true;

	return false;
}

void CColliderManager::BoxAndSphere(std::vector<CGameObject*>& returnCollider, CBoxCollider* box, CSphereCollider* sphere)
{
}

void CColliderManager::BoxAndBox(std::vector<CGameObject*>& returnCollider, CBoxCollider* box1, CBoxCollider* box2)
{
	if (m_gameObject1 == nullptr || m_gameObject2 == nullptr)
	{
		return;
	}
	AABB(returnCollider, box1, box2);

	if (m_gameObject1->GetRotation().x / 90 != 0 || m_gameObject1->GetRotation().y / 90 != 0 || m_gameObject1->GetRotation().z / 90 != 0 &&
		m_gameObject2->GetRotation().x / 90 != 0 || m_gameObject2->GetRotation().y / 90 != 0 || m_gameObject2->GetRotation().z / 90 != 0)
	{
		OBB(returnCollider, box1, box2);
	}
	else
	{
		AABB(returnCollider, box1, box2);
	}
}

void CColliderManager::SphereAndSphere(std::vector<CGameObject*>& returnCollider, CSphereCollider* sphere1, CSphereCollider* sphere2)
{
	vector3 sphere1Pos = m_gameObject1->GetPosition();
	vector3 sphere2pos = m_gameObject2->GetPosition();
	_float sumRadius = sphere1->GetRadius() + sphere2->GetRadius();
	_float distance;
	distance = sqrtf((sphere1Pos.x - sphere2pos.x) + (sphere1Pos.y - sphere2pos.y) + (sphere1Pos.z - sphere2pos.z));

	if (sumRadius >= distance)
	{
		returnCollider.emplace_back(m_gameObject2);
	}
}

void CColliderManager::AABB(std::vector<CGameObject*>& returnCollider, CBoxCollider* box1, CBoxCollider* box2)
{
	float distanceX = fabs((m_gameObject1->GetPosition().x + box1->GetOffset().x) - (m_gameObject2->GetPosition().x + box2->GetOffset().x));
	float radCX = box1->GetBoxSize().x * 0.5f + box2->GetBoxSize().x * 0.5f;

	float distanceY = fabs((m_gameObject1->GetPosition().y + box1->GetOffset().y) - (m_gameObject2->GetPosition().y + box2->GetOffset().y));
	float radCY = box1->GetBoxSize().y * 0.5f + box2->GetBoxSize().y * 0.5f;

	float distanceZ = fabs((m_gameObject1->GetPosition().z + box1->GetOffset().z) - (m_gameObject2->GetPosition().z + box2->GetOffset().z));
	float radCZ = box1->GetBoxSize().z * 0.5f + box2->GetBoxSize().z * 0.5f;

	if (distanceX <= radCX && distanceY <= radCY && distanceZ <= radCZ)
	{
		returnCollider.emplace_back(m_gameObject2);
	}

}

void CColliderManager::OBB(std::vector<CGameObject*>& returnCollider, CBoxCollider* box1, CBoxCollider* box2)
{
	float distanceZ = fabs((m_gameObject1->GetPosition().z + box1->GetOffset().z) - (m_gameObject2->GetPosition().z + box2->GetOffset().z));
	float radCZ = box1->GetBoxSize().z * 0.5f + box2->GetBoxSize().z * 0.5f;

	if (distanceZ > radCZ)
	{
		return;
	}

	//------------------------------------------ 네모 박스의 각 점의 위치
	m_obj1Vectex[0] = m_gameObject1->GetPosition();
	m_obj1Vectex[0].x += box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[0].y += box1->GetBoxSize().y * 0.5f;

	m_obj1Vectex[1] = m_gameObject1->GetPosition();
	m_obj1Vectex[1].x += box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[1].y -= box1->GetBoxSize().y * 0.5f;

	m_obj1Vectex[3] = m_gameObject1->GetPosition();
	m_obj1Vectex[3].x -= box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[3].y -= box1->GetBoxSize().y * 0.5f;

	m_obj1Vectex[4] = m_gameObject1->GetPosition();
	m_obj1Vectex[3].x -= box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[3].y += box1->GetBoxSize().y * 0.5f;
	//-----------------------------------
	m_obj2Vectex[0] = m_gameObject2->GetPosition();
	m_obj2Vectex[0].x += box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[0].y += box2->GetBoxSize().y * 0.5f;

	m_obj2Vectex[1] = m_gameObject2->GetPosition();
	m_obj2Vectex[1].x += box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[1].y -= box2->GetBoxSize().y * 0.5f;

	m_obj2Vectex[2] = m_gameObject2->GetPosition();
	m_obj2Vectex[2].x -= box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[2].y -= box2->GetBoxSize().y * 0.5f;

	m_obj2Vectex[3] = m_gameObject2->GetPosition();
	m_obj2Vectex[3].x -= box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[3].y += box2->GetBoxSize().y * 0.5f;
	//---------------------------------- 축 구하기
	matrix4x4 rotation;
	D3DXMatrixRotationYawPitchRoll(&rotation, m_gameObject1->GetRotation().x, m_gameObject1->GetRotation().y, m_gameObject1->GetRotation().z);

	m_box1UP = m_obj1Vectex[0] - m_obj1Vectex[3];
	D3DXVec3TransformNormal(&m_box1UP, &m_box1UP, &rotation);
	D3DXVec3Normalize(&m_box1UP, &m_box1UP);

	m_box1Right = m_obj1Vectex[0] - m_obj1Vectex[1];
	D3DXVec3TransformNormal(&m_box1Right, &m_box1Right, &rotation);
	D3DXVec3Normalize(&m_box1Right, &m_box1Right);
	//--------------------------------------------
	D3DXMatrixRotationYawPitchRoll(&rotation, m_gameObject2->GetRotation().x, m_gameObject2->GetRotation().y, m_gameObject2->GetRotation().z);

	m_box2UP = m_obj2Vectex[0] - m_obj2Vectex[3];
	D3DXVec3TransformNormal(&m_box2UP, &m_box2UP, &rotation);
	D3DXVec3Normalize(&m_box2UP, &m_box2UP);

	m_box2Right = m_obj2Vectex[0] - m_obj2Vectex[1];
	D3DXVec3TransformNormal(&m_box2Right, &m_box2Right, &rotation);
	D3DXVec3Normalize(&m_box2Right, &m_box2Right);
	//-------------------------------------------
	box1Size = box1->GetBoxSize();
	box2Size = box2->GetBoxSize();
	m_distance = m_gameObject1->GetPosition() - m_gameObject2->GetPosition();
	if (CheckShaft(m_box1UP) && CheckShaft(m_box2UP) && CheckShaft(m_box1Right) && CheckShaft(m_box2Right))
	{
		returnCollider.emplace_back(m_gameObject2);
	}
}

bool CColliderManager::CheckShaft(vector3 shaft)
{
	_float distance = abs(D3DXVec3Dot(&shaft, &m_distance));

	if (distance > abs(D3DXVec3Dot(&shaft, &(m_box1UP * box1Size.y * 0.5)))
		+ abs(D3DXVec3Dot(&shaft, &(m_box1Right * box1Size.x * 0.5)))
		+ abs(D3DXVec3Dot(&shaft, &(m_box2UP * box2Size.y * 0.5)))
		+ abs(D3DXVec3Dot(&shaft, &(m_box2Right * box2Size.x * 0.5))))
	{

		return false;
	}

	return true;
}