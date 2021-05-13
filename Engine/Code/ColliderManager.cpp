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

bool CColliderManager::OnColliderEnter(CCollider* collision, CGameObject* thisObject, std::vector<CGameObject*>& returnCollision)
{

	if (collision == nullptr || !collision->GetActive())
		return false;

	m_gameObject1 = thisObject;


	_int collisionType = collision->GetColliderType();

	for (auto& allCollider : m_vecCollider) // 전체 콜라이더 정보
	{
		if (allCollider == m_gameObject1->GetComponent<CColliderComponent>())
			continue;

		m_gameObject2 = allCollider->GetOwner();

		for (auto curCollision : allCollider->GetColliders()) // 전체콜라이더 정보에 들어있는 충돌체들
		{
			if (!curCollision->GetActive())
				continue;

			_int curCollisionType = curCollision->GetColliderType();

			switch (collisionType)
			{
			case (_int)EColliderType::Box:
			{
				switch (curCollisionType)
				{
				case (_int)EColliderType::Box: // 박스 or 박스
					BoxAndBox(returnCollision, static_cast<CBoxCollider*>(collision), static_cast<CBoxCollider*>(curCollision));
					break;
				case (_int)EColliderType::Sphere: // 박스 or 구
					BoxAndSphere(returnCollision, static_cast<CBoxCollider*>(collision), static_cast<CSphereCollider*>(curCollision));
					break;
				}
				break;
			}
			case (_int)EColliderType::Sphere:
			{
				switch (curCollisionType)
				{
				case (_int)EColliderType::Box:
					// 구 or 박스
					BoxAndSphere(returnCollision, static_cast<CBoxCollider*>(curCollision), static_cast<CSphereCollider*>(collision));
					break;
				case (_int)EColliderType::Sphere:
					// 구 or 구
					SphereAndSphere(returnCollision, static_cast<CSphereCollider*>(collision), static_cast<CSphereCollider*>(curCollision));
					break;
				}
				break;
			}
			}
		}
	}


	if (!returnCollision.empty())
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
	//AABB(returnCollider, box1, box2);

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
	vector3 old1 = box1->GetOffset();
	vector3 old2 = box2->GetOffset();

	m_gameObject1->OutTranslate(box1->GetOffset());
	m_gameObject2->OutTranslate(box2->GetOffset());

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

	box1->GetOffset() = old1;
	box2->GetOffset() = old2;

}

void CColliderManager::OBB(std::vector<CGameObject*>& returnCollider, CBoxCollider* box1, CBoxCollider* box2)
{
	vector3 old1 = box1->GetOffset();
	vector3 old2 = box2->GetOffset();

	m_gameObject1->OutTranslate(box1->GetOffset());
	m_gameObject2->OutTranslate(box2->GetOffset());

	//------------------------------------------ 네모 박스의 각 점의 위치
	m_obj1Vectex[0] = m_gameObject1->GetPosition();
	m_obj1Vectex[0].x += box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[0].y += box1->GetBoxSize().y * 0.5f;
	m_obj1Vectex[0].z = 0;

	m_obj1Vectex[1] = m_gameObject1->GetPosition();
	m_obj1Vectex[1].x += box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[1].y -= box1->GetBoxSize().y * 0.5f;
	m_obj1Vectex[1].z = 0;

	m_obj1Vectex[2] = m_gameObject1->GetPosition();
	m_obj1Vectex[2].x -= box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[2].y -= box1->GetBoxSize().y * 0.5f;
	m_obj1Vectex[2].z = 0;

	m_obj1Vectex[3] = m_gameObject1->GetPosition();
	m_obj1Vectex[3].x -= box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[3].y += box1->GetBoxSize().y * 0.5f;
	m_obj1Vectex[3].z = 0;

	m_obj1Vectex[4] = m_gameObject1->GetPosition();
	m_obj1Vectex[4].x += box1->GetBoxSize().x * 0.5f;
	m_obj1Vectex[4].y += box1->GetBoxSize().y * 0.5f;
	m_obj1Vectex[4].z -= box1->GetBoxSize().z * 0.5f;
	//-----------------------------------
	m_obj2Vectex[0] = m_gameObject2->GetPosition();
	m_obj2Vectex[0].x += box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[0].y += box2->GetBoxSize().y * 0.5f;
	m_obj2Vectex[0].z = 0;

	m_obj2Vectex[1] = m_gameObject2->GetPosition();
	m_obj2Vectex[1].x += box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[1].y -= box2->GetBoxSize().y * 0.5f;
	m_obj2Vectex[1].z = 0;

	m_obj2Vectex[2] = m_gameObject2->GetPosition();
	m_obj2Vectex[2].x -= box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[2].y -= box2->GetBoxSize().y * 0.5f;
	m_obj2Vectex[2].z = 0;

	m_obj2Vectex[3] = m_gameObject2->GetPosition();
	m_obj2Vectex[3].x -= box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[3].y += box2->GetBoxSize().y * 0.5f;
	m_obj2Vectex[3].z = 0;

	m_obj2Vectex[4] = m_gameObject2->GetPosition();
	m_obj2Vectex[4].x += box2->GetBoxSize().x * 0.5f;
	m_obj2Vectex[4].y += box2->GetBoxSize().y * 0.5f;
	m_obj2Vectex[4].z -= box2->GetBoxSize().z * 0.5f;

	//---------------------------------- 축 구하기
	matrix4x4 rotation;
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(m_gameObject1->GetRotation().y), D3DXToRadian(m_gameObject1->GetRotation().x), D3DXToRadian(m_gameObject1->GetRotation().z));

	m_box1UP = m_obj1Vectex[1] - m_obj1Vectex[0];
	D3DXVec3TransformNormal(&m_box1UP, &m_box1UP, &rotation);
	D3DXVec3Normalize(&m_box1UP, &m_box1UP);

	m_box1Right = m_obj1Vectex[3] - m_obj1Vectex[0]; 
	D3DXVec3TransformNormal(&m_box1Right, &m_box1Right, &rotation);
	D3DXVec3Normalize(&m_box1Right, &m_box1Right);

	vector3 T1 = m_obj1Vectex[0];
	T1.z += box1->GetBoxSize().z * 0.5f;
	m_box1Forward = m_obj1Vectex[4] - T1;
	D3DXVec3TransformNormal(&m_box1Forward, &m_box1Forward, &rotation);
	D3DXVec3Normalize(&m_box1Forward, &m_box1Forward);

	//--------------------------------------------
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(m_gameObject2->GetRotation().y), D3DXToRadian(m_gameObject2->GetRotation().x), D3DXToRadian(m_gameObject2->GetRotation().z));
	
	m_box2UP = m_obj2Vectex[1] - m_obj2Vectex[0];
	D3DXVec3TransformNormal(&m_box2UP, &m_box2UP, &rotation);
	D3DXVec3Normalize(&m_box2UP, &m_box2UP);

	m_box2Right = m_obj2Vectex[3] - m_obj2Vectex[0];
	D3DXVec3TransformNormal(&m_box2Right, &m_box2Right, &rotation);
	D3DXVec3Normalize(&m_box2Right, &m_box2Right);

	vector3 T2 = m_obj2Vectex[0];
	T2.z += box2->GetBoxSize().z * 0.5f;
	m_box2Forward = m_obj2Vectex[4] - T2;
	D3DXVec3TransformNormal(&m_box2Forward, &m_box2Forward, &rotation);
	D3DXVec3Normalize(&m_box2Forward, &m_box2Forward);
	//-------------------------------------------
	box1Size = box1->GetBoxSize();
	box2Size = box2->GetBoxSize();
	m_distance = (m_gameObject1->GetPosition() + box1->GetOffset()) - (m_gameObject2->GetPosition() + box2->GetOffset());
	//m_distance.z = 0;

	if (CheckShaft(m_box1UP) && CheckShaft(m_box2UP) && CheckShaft(m_box1Right) && CheckShaft(m_box2Right) && CheckShaft(m_box1Forward) && CheckShaft(m_box2Forward))
	{
		returnCollider.emplace_back(m_gameObject2);
	}

	box1->GetOffset() = old1;
	box2->GetOffset() = old2;

}

bool CColliderManager::CheckShaft(vector3 shaft)
{
	_float distance = abs(D3DXVec3Dot(&shaft, &m_distance));

	_float T = abs(D3DXVec3Dot(&shaft, &(m_box1UP * box1Size.y * 0.5)))
			 + abs(D3DXVec3Dot(&shaft, &(m_box1Right * box1Size.x * 0.5)))
			 + abs(D3DXVec3Dot(&shaft, &(m_box1Forward * box1Size.z * 0.5)))
			 + abs(D3DXVec3Dot(&shaft, &(m_box2UP * box2Size.y * 0.5)))
			 + abs(D3DXVec3Dot(&shaft, &(m_box2Right * box2Size.x * 0.5)))
			 + abs(D3DXVec3Dot(&shaft, &(m_box2Forward * box2Size.z * 0.5)));

	if (distance > T)
	{
		return false;
	}

	return true;
}