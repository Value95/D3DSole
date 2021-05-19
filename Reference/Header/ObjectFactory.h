#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Engine.h"

BEGIN(Engine)
class CScene;
class CGameObject;
class ENGINE_DLL CObjectFactory final : public CEngine
{
	DECLARE_SINGLETON(CObjectFactory)
private:
	//�������� ���� ������ ���� ��. �� ���� �ϳ��� Scene�� �ǹ�. ������Ÿ��
	typedef std::unordered_map<std::wstring, SHARED(CGameObject)> _PROTOTYPES;
	_PROTOTYPES	m_mCurPrototypes;
	_PROTOTYPES m_mStaticPrototypes;
public:
	void Awake(void) override;
	void Start(void);
		 
	void OnDestroy(void);
		 
	void OnEnable(void);
	void OnDisable(void);

	HRESULT	AddPrototype(SHARED(CGameObject) pPrototype);
	SHARED(CGameObject)	AddClone(const std::wstring& layerKey, const std::wstring& objectKey, _bool isStatic = false);
	SHARED(CGameObject)	AddClone(const std::wstring& layerKey, const std::wstring& objectKey, SHARED(CScene) scene, _bool isStatic = false);

	void ClearCurPrototype(void);
};
END
#endif