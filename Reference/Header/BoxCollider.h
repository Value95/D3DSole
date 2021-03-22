#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CBoxCollider final : public CCollider
{
protected:
	GETTOR_SETTOR(vector3,		m_offset,			vector3Zero,	Offset)
	GETTOR_SETTOR(vector3,		m_boxSize,			vector3One,		BoxSize)

private:
	explicit						CBoxCollider		(void);
								   ~CBoxCollider		(void);
public:
	static			CBoxCollider*	Create				(vector3 boxSize, vector3 position = vector3Zero);
					void			Awake				(void) override;
					void			OnDestroy			(void)override;
															  
					void			OnEnable			(void)override;
					void			OnDisable			(void)override;
};

END

#endif // BOXCOLLIDER_H