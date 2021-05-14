#pragma once

#include "Scene.h"
class CLoddingScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	HANDLE m_hThread;
	GETTOR_SETTOR(std::wstring, m_nextScene, {}, NextScene);
private:
	explicit CLoddingScene(void);
	~CLoddingScene(void);

public:
	static SHARED(Engine::CScene) Create(std::wstring nextScene);

	void Awake(void) override;
	void Start(void) override;

	_uint FixedUpdate(void) override;
	_uint Update(void) override;
	_uint LateUpdate(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

private:
	void InitLayers(void) override;
	void InitPrototypes(void) override;

	static unsigned __stdcall LoadDataObject(LPVOID pArg);

};

