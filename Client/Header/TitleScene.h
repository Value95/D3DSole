#pragma once

#include "Scene.h"
class CTitleScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER;
private:
	SHARED(Engine::CScene) m_nextScene;
private:
	explicit CTitleScene(void);
	~CTitleScene(void);

public:
	static SHARED(Engine::CScene) Create(void);

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

	void NextScene();
};

