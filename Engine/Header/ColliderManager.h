#ifndef  CColliderManager_H
#define  CColliderManager_H

#include "Engine.h"

BEGIN(Engine)
class CColliderComponent;
class CBoxCollider;
class CSphereCollider;
class CRayCollider;
class ENGINE_DLL CColliderManager final : public CEngine
{
private:
	typedef		struct tagOBB
	{
		vector3		point[8];
		vector3		center;
		vector3		projAxis[3];		// 각 면으로 뻗어나가는 방향 벡터
		vector3		axis[3];			// 면체와 평행항 축 벡터

	}Obb;

	DECLARE_SINGLETON(CColliderManager)
private:
	std::vector<SHARED(CColliderComponent)> m_vecCollider;

	CGameObject* m_gameObject1;
	CGameObject* m_gameObject2;

	// OBB를 위한 변수------------------------
	vector3 m_obj1Vectex[4];
	vector3 m_obj2Vectex[4];

	vector3 m_box1UP;
	vector3 m_box1Right;

	vector3 m_box2UP;
	vector3 m_box2Right;

	vector3 box1Size;
	vector3 box2Size;

	vector3 m_distance;
	//-----------------------------
public:
	void	Awake(void) override;
	void	Start(void);

	_uint	FixedUpdate(void);
	_uint	Update(void);
	_uint	LateUpdate(void);

	void	OnDestroy(void);

	void	OnEnable(void);
	void	OnDisable(void);

	void	ColliderInput(SHARED(CColliderComponent) vecObject);
	bool	OnColliderEnter(CCollider* collision, CGameObject* thisObject, std::vector<CGameObject*>& returnCollision);
private:
	void BoxAndSphere(std::vector<CGameObject*>& returnCollider,
		CBoxCollider* box,
		CSphereCollider* sphere);

	void BoxAndBox(std::vector<CGameObject*>& returnCollider,
		CBoxCollider* box1,
		CBoxCollider* box2);

	void SphereAndSphere(std::vector<CGameObject*>& returnCollider,
		CSphereCollider* sphere1,
		CSphereCollider* sphere2);

	void AABB(std::vector<CGameObject*>& returnCollider, CBoxCollider* box1, CBoxCollider* box2);
	void OBB(std::vector<CGameObject*>& returnCollider, CBoxCollider* box1, CBoxCollider* box2);
	bool CheckShaft(vector3 shaft);
};

END
#endif // ! CColliderManager_H