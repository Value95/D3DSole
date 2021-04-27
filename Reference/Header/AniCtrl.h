#ifndef AniCtrl_h__
#define AniCtrl_h__

BEGIN(Engine)

class ENGINE_DLL CAniCtrl
{
private:
	LPD3DXANIMATIONCONTROLLER m_pAniCtrl;
	_uint m_iCurrentTrack;
	_uint m_iNewTrack;
	_float m_fAccTime;
	_uint m_iOldAniIdx;
	GETTOR(_double,	m_dPeriod, 0, Period);
	GETTOR_SETTOR(_float, m_speed, 1, Speed);
private:
	explicit CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	explicit CAniCtrl(const CAniCtrl& rhs);
	virtual ~CAniCtrl(void) = default;

public:
	HRESULT		Ready_AnimationCtrl(void);
	void		Set_AnimationSet(const _uint& iIndex);
	void		Play_Animation(const _double& fTimeDelta);
	_bool		Is_AnimationSetEnd(void);
public:
	static CAniCtrl* Create(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	static CAniCtrl* Create(const CAniCtrl& rhs);
	void OnDestroy();
	_float CurentTime();
};

END
#endif // AniCtrl_h__
