#ifndef COLLIDER_H
#define COLLIDER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CCollider abstract : public CEngine
{
protected:
	GETTOR_SETTOR(_int,					m_colliderType,		-1,			ColliderType)

public:
	explicit								CCollider		(void);
	virtual								   ~CCollider		(void);

public:
	virtual			void					Awake			(void) PURE;
	virtual			void					OnDestroy		(void) PURE;

	virtual			void					OnEnable		(void) PURE;
	virtual			void					OnDisable		(void) PURE;
};

END

#endif // COLLIDER_H