#ifndef LAYER_H
#define LAYER_H

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CLayer final
{
	SMART_DELETER_REGISTER; // �̰� ����?  // shared_ptr�� ������Ʈ�� �������ִµ� �ش� shared_ptr�� ����� ��ü�� �����Ǵ°���
	// ��ü�� ���������ϸ� �ּҰ��� ����� �Ϲ� �����ʹ� �ش� �ּҰ��� ����ִ� ���¿��� �츮�� ����ϰ� ����Ʈ�� ����µ� shared_ptr�� ���������� ���۷���ī��Ʈ�� �������ְ� �������� �Ϲ������Ͷ� ������?
	// �� : ���������� ī��Ʈ�� �����ϸ� �ش� ī��Ʈ�� 0�̵Ǹ� �ڵ������� �޸� �Ҵ��� ����ȴ�. �� �����Ͱ� �ڱ� �ڽ��� ����������ϰ��ֵ� ����� �׳� �������°Ŷ� �ٸ���
	// shared_ptr�� ���� ���� �����ϰ��ִٸ� �����; ���� ��������� �������̴�.
	// �̰� �´°�?
protected:
	typedef std::vector<SHARED(CGameObject)> _GAMEOBJECTS;
	GETTOR(_GAMEOBJECTS, m_vGameObjects, {}, GameObjects)

	GETTOR_SETTOR(std::wstring, m_name, L"", Name)
protected:
	explicit CLayer(void);
	~CLayer(void);
public:
	static SHARED(CLayer) Create(std::wstring name);

	void Awake(void);
	void Start(void);
		 
	_uint FixedUpdate(void);
	_uint Update(void);
	_uint LateUpdate(void);
		 
	void OnDestroy(void);
		 
	void OnEnable(void);
	void OnDisable(void);
};
END


#endif // !LAYER_H