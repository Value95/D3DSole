#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CInputManager final : public CEngine
{
	DECLARE_SINGLETON(CInputManager)
private:
	DWORD m_key;
	DWORD m_lastFrameKey;

	GETTOR(vector3,	m_mousePos,	vector3(0, 0, 0),MousePos)
public:
	void Awake(void) override;
	void Start(void);

	_uint	FixedUpdate(void);
	_uint	Update(void);
	_uint	LateUpdate(void);	

	void OnDestroy(void);
		 		   
	void OnEnable(void);
	void OnDisable(void);
		 
	bool KeyUp(DWORD key);
	bool KeyDown(DWORD key);
	bool KeyPress (DWORD key);
private:
	void KeyUpdate(void);
	void MouseUpdate(void);

};
END

#endif