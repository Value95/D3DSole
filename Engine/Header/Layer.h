#ifndef LAYER_H
#define LAYER_H

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CLayer final
{
	SMART_DELETER_REGISTER; // 이거 뭐지?  // shared_ptr가 오브젝트를 가지고있는데 해당 shared_ptr을 지우면 객체가 삭제되는건지
	// 객체를 동적생성하면 주소값을 만들고 일반 포인터는 해당 주소값을 들고있는 상태에서 우리가 사용하고 딜리트로 지우는데 shared_ptr도 내부적으로 래퍼런스카운트를 지원해주고 나머지는 일반포인터랑 같은지?
	// 답 : 내부적으로 카운트가 존재하면 해당 카운트가 0이되면 자동적으로 메모리 할당이 해재된다. 즉 포인터가 자기 자신을 몇명이참고하고있든 지우면 그냐 지워지는거랑 다르게
	// shared_ptr는 누가 나를 참고하고있다면 지우고싶어도 절대 지울수없는 포인터이다.
	// 이게 맞는가?
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