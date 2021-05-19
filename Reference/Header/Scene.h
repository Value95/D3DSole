#ifndef SCENE_H
#define SCENE_H

BEGIN(Engine)
class CLayer;
class CGameObject;
class ENGINE_DLL CScene abstract
{
protected:
	typedef std::unordered_map<std::wstring, SHARED(CLayer)> _LAYERS;
	GETTOR(_LAYERS, m_mLayers, {}, Layers)

	GETTOR_SETTOR(SHARED(CCameraComponent), m_pMainCamera, nullptr, MainCamera)

	GETTOR(std::wstring, m_name, L"", Name)
	GETTOR(_bool, m_isAwaked, false, IsAwaked)
	GETTOR(_bool, m_isStarted, false, IsStarted)
	GETTOR_SETTOR(_bool, m_enable, true, Enable)
	GETTOR_SETTOR(_bool, m_SceneEvent, false, SceneEvent)
	GETTOR(_int, m_objectCount, 0, ObjectCount)

protected:
	explicit CScene(void);
	virtual ~CScene(void);

public:
	virtual void Awake(void) PURE;
	virtual void Start(void) PURE;
			 	 
	virtual _uint FixedUpdate(void) PURE;
	virtual _uint Update(void) PURE;
	virtual _uint LateUpdate(void) PURE;
			 	 
	virtual void OnDestroy(void) PURE;
			 	 
	virtual void OnEnable(void) PURE;
	virtual void OnDisable(void) PURE;

	SHARED(CGameObject) FindObjectByName(std::wstring name);
	SHARED(CGameObject)	FindObjectWithKey(std::wstring objectKey);
	SHARED(CGameObject)	FindObjectPosition(vector3 position);
	SHARED(CGameObject)	FindObjectPoint(CGameObject* object);

	void AllDelete();
	_uint FindObjectsWithKey(std::wstring objectKey, std::vector<SHARED(CGameObject)>& gameObjects);
	static void LoadObject(std::wstring path);
	static void LoadObject(std::wstring path, SHARED(CScene) scene);

	void AddObjectCount(_int value) { m_objectCount += value; }
protected:
	virtual void InitLayers(void) PURE;
	virtual void InitPrototypes(void) PURE;
	void AddLayer(std::wstring layerName);

private:
	static std::wstring LoadWstring(HANDLE* file, DWORD* dwByte);
};
END

#endif