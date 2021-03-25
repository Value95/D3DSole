#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


BEGIN(Engine)
class ENGINE_DLL CGameObject : public CTransformComponent
{
	SMART_DELETER_REGISTER
protected:
	typedef std::unordered_map<std::string, SHARED(CComponent)> _COMPONENTS;

	GETTOR(_COMPONENTS, m_mComponents, {}, Components)

	GETTOR_SETTOR(_bool, m_isClone, false, IsClone)
	GETTOR_SETTOR(_bool, m_isStatic, false, IsStatic)
	GETTOR_SETTOR(_bool, m_isAwaked, false, IsAwaked)
	GETTOR_SETTOR(_bool, m_isStarted, false, IsStarted)
	GETTOR_SETTOR(_bool, m_isEnabled, true, IsEnabled)
	GETTOR_SETTOR(_bool, m_isNeedToBeDeleted, false, IsNeedToBeDeleted)

	GETTOR_SETTOR(std::wstring, m_layerKey, L"", LayerKey)
	GETTOR_SETTOR(std::wstring, m_objectKey, L"", ObjectKey)
	GETTOR_SETTOR(std::wstring, m_name, L"", Name)

protected:
	explicit CGameObject(void);
	explicit CGameObject(const CGameObject& other);
	~CGameObject(void);
public:
	static SHARED(CGameObject) Create(std::wstring layerKey = L"",
											 std::wstring objectKey = L"",
											 _bool isStatic = false);
	SHARED(CGameObject)	MakeClone(void);

	void Awake(void);
	void Start(void);

	_uint FixedUpdate(void);
	_uint Update(void);
	_uint LateUpdate(void);

	void OnDestroy(void);

	void OnEnable(void);
	void OnDisable(void);

public:
	//오브젝트에서 컴포넌트 가져오는 함수
	template <typename ComponentType>
	SHARED(ComponentType) GetComponent(void)
	{
		string typeName = typeid(ComponentType).name();

		auto& it = m_mComponents.find(typeName);
		if (it != m_mComponents.end())
			return std::dynamic_pointer_cast<ComponentType>(it->second);

		return nullptr;
	}

	//프로토 타입에 컴포넌트 추가하는 함수
	template <typename ComponentType>
	SHARED(ComponentType) AddComponent(void)
	{
		string typeName = typeid(ComponentType).name();

		SHARED(ComponentType) pNewComponent = nullptr;

		if ((pNewComponent = GetComponent<ComponentType>()) == nullptr)
		{
			pNewComponent.reset(new ComponentType);
			pNewComponent->SetOwner(this);
			pNewComponent->Awake();
			m_mComponents[typeName] = pNewComponent;

			return pNewComponent;
		}
		else
			MSG_BOX(__FILE__, (pNewComponent->GetName() + L" is already in " + this->GetName()).c_str());

		return nullptr;
	}

	//클론에 컴포넌트 추가하는 함수
	template <typename ComponentType>
	void AddComponentToClone(SHARED(ComponentType) pComponent, std::string typeName)
	{
		SHARED(CComponent) pNewComponent = pComponent->MakeClone(this);
		pNewComponent->Awake();

		m_mComponents[typeName] = pNewComponent;
	}
};
END

#endif // !GAMEOBJECT_H
