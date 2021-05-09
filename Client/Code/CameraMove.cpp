#include "stdafx.h"
#include "CameraMove.h"

CCameraMove::CCameraMove()
{
}

CCameraMove::~CCameraMove(void)
{
	OnDestroy();
}

SHARED(Engine::CComponent) CCameraMove::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CCameraMove) pClone(new CCameraMove);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);


	return pClone;
}

void CCameraMove::Awake(void)
{
	__super::Awake();

	RECT rect;

	GetClientRect(Engine::CWndApp::GetInstance()->GetHWnd(), &rect);

	POINT p1, p2;
	p1.x = rect.left;
	p1.y = rect.top;
	p2.x = rect.right;
	p2.y = rect.bottom;

	ClientToScreen(Engine::CWndApp::GetInstance()->GetHWnd(), &p1);
	ClientToScreen(Engine::CWndApp::GetInstance()->GetHWnd(), &p2);

	rect.left = p1.x;
	rect.top = p1.y;
	rect.right = p2.x;
	rect.bottom = p2.y;

	m_centerPt.x = (p1.x + p2.x) / 2;
	m_centerPt.y = (p1.y + p2.y) / 2;
	SetCursorPos(m_centerPt.x, m_centerPt.y);
}

void CCameraMove::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CCameraMove::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CCameraMove::Update(SHARED(CComponent) spThis)
{
	Sight();
	CameraCrush();
	return NO_EVENT;
}

_uint CCameraMove::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CCameraMove::OnDestroy(void)
{
}

void CCameraMove::OnEnable(void)
{
}

void CCameraMove::OnDisable(void)
{
}

void CCameraMove::Sight()
{
	POINT curPt;
	GetCursorPos(&curPt);
	SetCursorPos(m_centerPt.x, m_centerPt.y);

	// 카메라 회전
	if (curPt.y < m_centerPt.y) // mouse up look
	{
		_float angleY = deltaTime * (abs(curPt.y - m_centerPt.y) * 5) * -1;
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationX(angleY);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraX(Engine::GET_MAIN_CAM->GetOwner()->GetCameraX() + angleY);
	}

	if (curPt.y > m_centerPt.y) // mouse down look
	{
		_float angleY = deltaTime * (abs(curPt.y - m_centerPt.y) * 5);
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationX(angleY);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraX(Engine::GET_MAIN_CAM->GetOwner()->GetCameraX() + angleY);
	}

	if (curPt.x < m_centerPt.x) // mouse left look
	{
		_float angleX = (deltaTime * (abs(curPt.x - m_centerPt.x) * 5)) * -1;
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationY(angleX);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraY(Engine::GET_MAIN_CAM->GetOwner()->GetCameraY() + angleX);
	}

	if (curPt.x > m_centerPt.x) // mouse right look
	{
		_float angleX = deltaTime * (abs(curPt.x - m_centerPt.x) * 5);
		Engine::GET_MAIN_CAM->GetOwner()->AddRotationY(angleX);
		Engine::GET_MAIN_CAM->GetOwner()->SetCameraY(Engine::GET_MAIN_CAM->GetOwner()->GetCameraY() + angleX);
	}
}

void CCameraMove::CameraCrush()
{
	vector3 orgine = GetOwner()->GetPosition();
	vector3 dir = GetOwner()->GetTarget()->GetPosition() - GetOwner()->GetPosition();
	D3DXVec3Normalize(&dir, &dir);
	_float distance = Engine::Distance(orgine, GetOwner()->GetTarget()->GetPosition()) - 0.2f; //0.1f 바닥을 체크하지않기위한값
	vector3 outHit;
	Engine::CGameObject* obj = Engine::CRaycast::MeshRayCast(orgine, dir, distance, L"Map", outHit);


	if (obj == nullptr)
	{
		GetOwner()->SetCameraDirPos(vector3(0, 3, -8));
	}
	else
	{
		distance = Engine::MathfMax((Engine::Distance(outHit, GetOwner()->GetTarget()->GetPosition()) * -1), -8);
		cout << distance << endl;
		vector3 cameraDirPos = vector3(0, 3, distance);
		GetOwner()->SetCameraDirPos(cameraDirPos);
	}
}
