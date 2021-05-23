#ifndef DIRECTIONLIGHTCOMPONENT_H
#define DIRECTIONLIGHTCOMPONENT_H


BEGIN(Engine)
class CCollider;
class ENGINE_DLL CDirectionalLightComponent final : public CComponent
{
private:
	GETTOR_SETTOR(D3DLIGHT9, m_light, {}, Light);

	vector3 m_lightDir;
	vector3 m_camPos;

	vector3 m_lightDiffuse;
	vector3 m_lightSpecular;
	vector3 m_lightAmbient;
			
	vector3 m_mtrlDiffuse;
	vector3 m_mtrlSpecular;
	vector3 m_mtrlAmbient;
			
	vector3 m_power;
	vector3 m_detail;
public:
	explicit CDirectionalLightComponent(void);
	~CDirectionalLightComponent(void);
public:
	virtual SHARED(CComponent) MakeClone(CGameObject* pObject) override;

	virtual void Awake();
	virtual void Start(SHARED(CComponent) spThis) override;

	virtual _uint FixedUpdate(SHARED(CComponent) spThis) override;
	virtual _uint Update(SHARED(CComponent) spThis) override;
	virtual _uint LateUpdate(SHARED(CComponent) spThis) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;

protected:
};
END

#endif // DIRECTIONLIGHTCOMPONENT_H