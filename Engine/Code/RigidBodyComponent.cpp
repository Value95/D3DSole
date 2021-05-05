#include "EngineStdafx.h"
#include "GameObject.h"
#include "ColliderManager.h"

USING(Engine)
CRigidBodyComponent::CRigidBodyComponent(void)
{
}

CRigidBodyComponent::~CRigidBodyComponent(void)
{
}

SHARED(CComponent) CRigidBodyComponent::MakeClone(CGameObject * pObject)
{
	SHARED(CRigidBodyComponent) pClone(new CRigidBodyComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetMass(m_mass);
	pClone->SetDrag(m_drag);
	pClone->SetUseGravity(m_useGravity);
	pClone->SetFreezePosition(m_freezePosition);
	pClone->SetFreezeRotation(m_freezeRotation);
	pClone->SetGroundCheck(m_groundCheck);
	pClone->SetVelocity(m_velocity);
	pClone->SetBounciness(m_bounciness);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CRigidBodyComponent::Awake()
{
	__super::Awake();
}

void CRigidBodyComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_mass = MathfMin(m_mass, 100);
	m_mass /= 100;
	m_bounciness = MathfMin(m_bounciness, 1);
	m_separatingVelocity = vector3Zero;
}

_uint CRigidBodyComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	std::vector<CGameObject*> col;
	SHARED(CColliderComponent) spCC = m_pOwner->GetComponent<CColliderComponent>();

	bool crushCheck = false;
	if (spCC->GetIsStarted())
	{
		CColliderManager::GetInstance()->OnColliderEnter(spCC->GetColliders()[0], m_pOwner, col);

		for (auto& check : col)
		{
			if (check->GetComponent<CColliderComponent>()->GetIsTrigger())
			{
				crushCheck = true;
			}
		}
	}

	if (crushCheck)
	{
		DecelerationFunction(col);

		ElasticCollision(col);

		GetOwner()->AddPosition(deltaTime * m_velocity);
	}
	else if (!crushCheck || !m_groundCheck)
	{
		m_groundCheck = false;
		GravityDrag(m_velocity);

		m_separatingVelocity = GetOwner()->GetPosition();
		GetOwner()->AddPosition(deltaTime * m_velocity);
		m_separatingVelocity = GetOwner()->GetPosition() - m_separatingVelocity;
	}

	m_netForce = vector3Zero;
	return _uint();
}

_uint CRigidBodyComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CRigidBodyComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CRigidBodyComponent::OnDestroy(void)
{
}

void CRigidBodyComponent::OnEnable(void)
{
}

void CRigidBodyComponent::OnDisable(void)
{
}

void CRigidBodyComponent::GravityDrag(vector3 & velocity)
{
	vector3 drag = velocity;
	D3DXVec3Normalize(&drag, &drag);

	velocity.y += GRAVITY.y * deltaTime;

	/*drag.y = -drag.y * ((1 - drag.y) + (10 * (drag.y * drag.y)));
	velocity.y -= drag.y;*/
}

void CRigidBodyComponent::AddForce(vector3 force)
{
	m_netForce += force;

	_float xForce = (force.x / abs(m_mass));
	_float yForce = (force.y / abs(m_mass));
	_float zForce = (force.z / abs(m_mass));

	// F = ma 
	// a = F / m

	vector3 a = vector3(xForce, yForce, zForce);
	m_velocity += a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	GetOwner()->AddPosition(deltaTime * m_velocity);
}

void CRigidBodyComponent::SetForce(vector3 force)
{
	_float xForce = (force.x / m_mass);
	_float yForce = (force.y / m_mass);
	_float zForce = (force.z / m_mass);

	vector3 a = vector3(xForce, yForce, zForce);
	m_velocity = a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	GetOwner()->AddPosition(deltaTime * m_velocity);
}

void CRigidBodyComponent::TranslateForce(vector3 force)
{
	_float xForce = (force.x / m_mass);
	_float yForce = (force.y / m_mass);
	_float zForce = (force.z / m_mass);

	vector3 a = vector3(xForce, yForce, zForce);

	matrix4x4 rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(GetOwner()->GetRotation().y), D3DXToRadian(GetOwner()->GetRotation().x), D3DXToRadian(GetOwner()->GetRotation().z));
	D3DXVec3TransformCoord(&a, &a, &rotate);

	m_velocity = a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	GetOwner()->AddPosition(deltaTime * m_velocity);

}



void CRigidBodyComponent::ElasticCollision(std::vector<CGameObject*>& obj)
{
	if (m_velocity.y == 0)
		return;

	bool init = false;

	for (auto& collisionObj : obj)
	{
		if (collisionObj == GetOwner())
			continue;

		SHARED(CRigidBodyComponent) rigdbody = collisionObj->GetComponent<CRigidBodyComponent>();
		if (rigdbody != nullptr)
		{
			_float m1 = m_mass;
			vector3 v1i = m_velocity;
			_float m2 = rigdbody->GetMass();
			vector3 v2i = rigdbody->GetVelocity();
			vector3 value1 = v1i - v2i;
			vector3 value2 = (-1 * v1i) + v2i;
			vector3 value3 = value1 + value2;

			v1i = value3 / 2;
			v2i = (-1 * v1i) - value1;

			rigdbody->SetVelocity(v2i);
			m_velocity = v1i;
			init = true;
			break;
		}
	}

	if (!init)
	{
		m_velocity = (-1 * m_velocity) * m_bounciness;

		if (m_velocity.y <= 0.4f)
		{
			m_velocity.y = 0;
			m_groundCheck = true;
		}
	}
}

void CRigidBodyComponent::DecelerationFunction(std::vector<CGameObject*>& col)
{
	if (m_separatingVelocity != vector3Zero)
	{
		if (m_separatingVelocity.y >= -0.1f && m_separatingVelocity.y < 0)
			m_separatingVelocity.y = 0;

		GetOwner()->AddPosition(m_separatingVelocity * -1);
		m_separatingVelocity = vector3Zero;
	}

	if (m_velocity != vector3Zero)
	{
		if (m_velocity.z > 0)
			m_velocity.z = MathfMax(m_velocity.z - (deltaTime * m_damping), 0);
		else if (m_velocity.z < 0)
			m_velocity.z = MathfMin(m_velocity.z + (deltaTime * m_damping), 0);

		if (m_velocity.x > 0)
			m_velocity.x = MathfMax(m_velocity.x - (deltaTime * m_damping), 0);
		else if (m_velocity.x < 0)
			m_velocity.x = MathfMin(m_velocity.x + (deltaTime * m_damping), 0);
	}
}