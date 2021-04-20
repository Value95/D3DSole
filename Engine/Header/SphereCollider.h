#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CSphereCollider final : public CCollider
{
protected:
	GETTOR_SETTOR(_float, m_radius, 0.f, Radius)
private:
	explicit CSphereCollider (void);
	~CSphereCollider (void);
public:
	static CSphereCollider*	Create (_float radius, _bool active = true);
	void Awake (void) override;
	void OnDestroy (void) override;
		 			   
	void OnEnable (void) override;
	void OnDisable (void) override;
};
END

#endif // SPHERECOLLIDER_H