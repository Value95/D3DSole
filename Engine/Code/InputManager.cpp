#include "EngineStdafx.h"
#include "InputManager.h"
#include "WndApp.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Layer.h"
USING(Engine)
IMPLEMENT_SINGLETON(CInputManager)

void CInputManager::Awake(void)
{
	__super::Awake();
}


void CInputManager::Start(void)
{
}

_uint CInputManager::FixedUpdate(void)
{
	return NO_EVENT;
}

_uint CInputManager::Update(void)
{
	KeyUpdate();
	MouseUpdate();

	return NO_EVENT;
}

_uint CInputManager::LateUpdate(void)
{
	return NO_EVENT;
}

void CInputManager::OnDestroy(void)
{
}

void CInputManager::OnEnable(void)
{
}

void CInputManager::OnDisable(void)
{
}
bool CInputManager::KeyUp(DWORD key)
{
	if ((m_lastFrameKey & key) && !(m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyDown(DWORD key)
{
	if (!(m_lastFrameKey & key) && (m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyPress(DWORD key)
{
	if (m_key & key)
		return true;

	return false;
}

void CInputManager::KeyUpdate(void)
{
	m_lastFrameKey = m_key;
	m_key = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_key |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_key |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_key |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_key |= KEY_DOWN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_key |= KEY_SPACE;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_key |= KEY_RETURN;
	if (GetAsyncKeyState(VK_F1) & 0x8000)
		m_key |= KEY_F1;
	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_key |= KEY_F2;
	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_key |= KEY_F3;
	if (GetAsyncKeyState(VK_F4) & 0x8000)
		m_key |= KEY_F4;
	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_key |= KEY_F5;
	if (GetAsyncKeyState(0x57) & 0x8000)
		m_key |= KEY_W;
	if (GetAsyncKeyState(0x41) & 0x8000)
		m_key |= KEY_A;
	if (GetAsyncKeyState(0x53) & 0x8000)
		m_key |= KEY_S;
	if (GetAsyncKeyState(0x44) & 0x8000)
		m_key |= KEY_D;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_key |= KEY_SHIFT;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_key |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_key |= KEY_LBUTTON;
	if (GetAsyncKeyState('1') & 0x8000)
		m_key |= KEY_1;
	if (GetAsyncKeyState('2') & 0x8000)
		m_key |= KEY_2;
	if (GetAsyncKeyState('3') & 0x8000)
		m_key |= KEY_3;
	if (GetAsyncKeyState('4') & 0x8000)
		m_key |= KEY_4;
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_key |= KEY_TAB;
	if (GetAsyncKeyState(VK_DELETE) & 0x8000)
		m_key |= KEY_DELETE;
	if (GetAsyncKeyState('Q') & 0x8000)
		m_key |= KEY_Q;
	if (GetAsyncKeyState('X') & 0x8000)
		m_key |= KEY_X;
	if (GetAsyncKeyState('E') & 0x8000)
		m_key |= KEY_E;
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_key |= KEY_CTRL;
	if (GetAsyncKeyState('F') & 0x8000)
		m_key |= KEY_F;
	if (GetAsyncKeyState(VK_DELETE) & 0x8000)
		m_key |= KEY_DEL;
}

void CInputManager::MouseUpdate(void)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GET_HANDLE, &p);

	m_mousePos = D3DXVECTOR3((float)p.x, (float)p.y, 0);

	m_mousePos.x -= GET_WND_WIDTH / 2.f;
	m_mousePos.y = (m_mousePos.y * -1) + GET_WND_HEIGHT / 2.f;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_key |= MOUSE_LEFT;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_key |= MOUSE_RIGHT;
}
