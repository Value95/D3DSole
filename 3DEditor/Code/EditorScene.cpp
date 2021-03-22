#include "stdafx.h"
#include "EditorScene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

#include "3DEditorView.h"

#include "InputManager.h"
#include "TextureStore.h"
#include "Layer.h"
#include "MainFrm.h"
#include "SceneManager.h"

CEditorScene::CEditorScene()
{
}

CEditorScene::~CEditorScene()
{
}

SHARED(Engine::CScene) CEditorScene::Create(void)
{
	SHARED(CEditorScene) pCLogoScene(new CEditorScene, Engine::SmartDeleter<CEditorScene>);

	return pCLogoScene;
}

void CEditorScene::Awake(void)
{
	__super::Awake();
	InitLayers();
	InitPrototypes();
}

void CEditorScene::Start(void)
{
	__super::Start();

	m_pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pEditorView = dynamic_cast<CMy3DEditorView*>(m_pMain->m_mainSplitter.GetPane(0, 0));

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", false)->GetComponent<Engine::CCameraComponent>();
}

_uint CEditorScene::FixedUpdate(void)
{
	return _uint();
}

_uint CEditorScene::Update(void)
{
	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;

	m_pMainCamera->CameraMove();
	
	if (Engine::IMKEY_PRESS(KEY_RBUTTON))
	{
		if (Engine::IMKEY_DOWN(KEY_RBUTTON))
		{
			POINT curPt;
			GetCursorPos(&curPt);
			m_pMainCamera->SetCenterPt(curPt);
			
		}
		m_pMainCamera->CameraRotation();
	}
	
	

	BlockPicking();
	SetAddFirstCubeToListBox();
}

_uint CEditorScene::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::LateUpdate())
		return event;


	return event;
}

void CEditorScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CEditorScene::OnEnable(void)
{
}

void CEditorScene::OnDisable(void)
{
}

void CEditorScene::InitLayers(void)
{
	AddLayer(L"Camera");
}

void CEditorScene::InitPrototypes(void)
{
	SHARED(Engine::CGameObject) pCamera = Engine::CGameObject::Create(L"Camera", L"Camera", false);
	pCamera->SetPosition(vector3(0, 0, -5));
	pCamera->AddComponent<Engine::CCameraComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pCamera);
}


void CEditorScene::BlockPicking()
{
	//vector3 intersection = {};
	//
	//if (m_pListView->m_wsBlockColor == L"")
	//	return;

	//if (m_pListView->m_wsBlockColor == L"WhiteBlock")
	//{
	//	m_pListView->m_wsBlockType = L"NormalBlock";
	//}
	//else
	//{
	//	m_pListView->m_wsBlockType = L"EventBlock";
	//}

	//if (Engine::CInputManager::GetInstance()->KeyDown(KEY_TAB) && !m_isPickingMode)
	//{
	//	std::cout << "picking mode on" << std::endl;
	//	m_isPickingMode = true;
	//}
	//else if (Engine::CInputManager::GetInstance()->KeyDown(KEY_TAB) && m_isPickingMode)
	//{
	//	std::cout << "picking mode off" << std::endl;
	//	m_isPickingMode = false;
	//}

	//if (!m_isPickingMode)
	//{
	//	SelectBlock();
	//}

	//ChangeCameraYaxis();

	//// ť�� ����
	//if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_LEFT) && m_isPickingMode)
	//{
	//	CreateCubeWhenClicked();
	//}
	//// ť�� ����
	//else if (Engine::CInputManager::GetInstance()->KeyDown(KEY_DELETE) && m_isPickingMode)
	//{
	//	DeleteCubeWhenClicked();
	//}
	return;
}

void CEditorScene::SetAddFirstCubeToListBox()
{
	//if (m_AddFistCubeToListBox)
	//{
	//	std::wstring defaultCubeKey = m_pEditorView->GetGameObjects().front()->GetObjectKey();
	//	m_pListView->m_ListBox.AddString(defaultCubeKey.c_str());
	//	m_AddFistCubeToListBox = false;
	//}
}

void CEditorScene::CreateCubeWhenClicked()
{
	//vector3 intersection = { 0.f, 0.f, 0.f };

	//Engine::CGameObject* target = Engine::CInputManager::GetInstance()->MousePicking(L"NormalBlock", intersection);

	//if (!target)
	//{
	//	target = Engine::CInputManager::GetInstance()->MousePicking(L"EventBlock", intersection);
	//}

	//if (!target)
	//{
	//	return;
	//}

	//vector3 targetPos = target->GetComponent<Engine::CTransformComponent>()->GetPosition();
	//	if (!target)
	//	{
	//		target = Engine::CInputManager::GetInstance()->MousePicking(L"EventBlock", intersection);
	//		
	//	}
	//	if (!target)
	//	{
	//		return;
	//	}
	//	targetPos = target->GetComponent<Engine::CTransformComponent>()->GetPosition();

	//std::cout << "======================================" << std::endl;
	//std::cout << "objX: " << targetPos.x << " objY: " << targetPos.y << " objZ: " << targetPos.z << std::endl;
	//std::cout << "x: " << intersection.x << " y: " << intersection.y << " z: " << intersection.z << std::endl;

	//// ť�� ũ�Ⱑ �ٸ��Ƿ� �׿� ���� �ڵ� �����ʿ���
	//vector3 newPos = targetPos;

	//if (targetPos.x + 0.49f <= intersection.x)
	//	newPos.x = targetPos.x + 1.f;
	//else if (targetPos.x - 0.49f >= intersection.x)
	//	newPos.x = targetPos.x - 1.f;

	//if (targetPos.y + 0.49f <= intersection.y)
	//	newPos.y = targetPos.y + 1.f;

	//else if (targetPos.y - 0.49f >= intersection.y)
	//	newPos.y = targetPos.y - 1.f;

	//if (targetPos.z + 0.49f <= intersection.z)
	//	newPos.z = targetPos.z + 1.f;

	//else if (targetPos.z - 0.49f >= intersection.z)
	//	newPos.z = targetPos.z - 1.f;


	//std::cout << "newX: " << newPos.x << " newY: " << newPos.y << " newZ: " << newPos.z << std::endl;
	//std::cout << "======================================" << std::endl;

	//// �̹� ��ġ�� ť�갡 �����Ѵٸ� ��������
	//auto& vBlocks = m_mLayers[target->GetLayerKey()]->GetGameObjects();


	//for (auto& iter = vBlocks.begin(); iter != vBlocks.end();)
	//{
	//	if (iter->get() == target)
	//	{
	//		if (target->GetComponent<Engine::CTransformComponent>()->GetPosition() == newPos)
	//		{
	//			std::cout << "Cube already exists.." << std::endl;
	//			return;
	//		}
	//		break;
	//	}
	//	else
	//		++iter;
	//}

	//SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(m_pListView->m_wsBlockType, m_pListView->m_wsBlockColor, false);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(newPos);

	//m_pEditorView->Set_CubeData(pObj);

	//m_pListView->m_ListBox.AddString(m_pEditorView->GetGameObjects().back()->GetObjectKey().c_str());
}

void CEditorScene::DeleteCubeWhenClicked()
{
	//vector3 intersection = { 0.f, 0.f, 0.f };

	//// ���� ��Ŭ�� ���� �� LayerKey�� �ѱ� ���� ����� ť�갡 target���� ����
	//// ��, ���� ť�갡 ���� �� �� �ڿ� �Ͼ� ť�갡 �ִٰ� �սô�.
	//// �׸��� ī�޶� ���� ť�긦 �ٶ󺸰� �ΰ�, ���� ť�긦 ������� Ŭ�� ���� ��.
	//// �� �� MousePicking �Ű������� layerkey�� �Ͼ� ť�긦 ���� ť�꺸�� ���� �־��ٸ� �Ͼ� ť�갡 ������
	//// �׷��� �������� �̿��� ���� ����� ���� Ŭ���� ����� �´��� Ȯ���ϴ� ������ �ʿ���

	//// layerkey�� �ش��ϴ� ���� ����� ���� ������ ����
	//// ������ �ɸ��� layerkey�� ���ٸ� nullptr�� ����
	//Engine::CGameObject* target = nullptr;
	//Engine::CGameObject* normalBlock = Engine::CInputManager::GetInstance()->MousePicking(L"NormalBlock", intersection);
	//Engine::CGameObject* eventBlock = Engine::CInputManager::GetInstance()->MousePicking(L"EventBlock", intersection);

	//// �� layerkey�� ������ �ɷȴٸ� ���������� �� ����� ���� target�� ����
	//if (normalBlock && eventBlock)
	//{
	//	vector3 normalPos = normalBlock->GetComponent<Engine::CTransformComponent>()->GetPosition();
	//	vector3 eventPos = eventBlock->GetComponent<Engine::CTransformComponent>()->GetPosition();

	//	if (normalPos - intersection > eventPos - intersection)
	//	{
	//		target = eventBlock;
	//	}
	//	else
	//	{
	//		target = normalBlock;
	//	}
	//}
	//// �� �� �ϳ��� layerkey�� �ɸ��ٸ� �ɸ� ���� target�� ����
	//else if (!normalBlock)
	//{
	//	target = eventBlock;
	//}
	//else if (!eventBlock)
	//{
	//	target = normalBlock;
	//}

	//// target�� ����ٸ� ��ȯ
	//if (!target)
	//{
	//	return;

	//}

	//m_pCurSelectedObject = target;

	//// ����� �ʿ��� ã�Ƽ� ����	
	//std::cout << "Cube Deleted" << std::endl;
	//
	//for (size_t i = 0; i < m_pListView->m_ListBox.GetCount(); i++)
	//{
	//	if (m_pEditorView->GetGameObjects()[i]->GetComponent<Engine::CTransformComponent>()->GetPosition() ==
	//		m_pCurSelectedObject->GetComponent<Engine::CTransformComponent>()->GetPosition())
	//	{
	//		m_pListView->m_ListBox.DeleteString(i);
	//		m_pEditorView->GetGameObjects()[i]->SetIsNeedToBeDeleted(true);

	//		if (!m_pEditorView->GetGameObjects().empty())
	//		{
	//			for (auto& it = m_pEditorView->GetGameObjects().begin(); it != m_pEditorView->GetGameObjects().end();)
	//			{
	//				if ((*it)->GetIsNeedToBeDeleted() && it->get() == m_pCurSelectedObject)
	//				{
	//					it = m_pEditorView->GetGameObjects().erase(it);
	//					return;
	//				}
	//				else
	//					++it;
	//			}
	//		}
	//		else
	//			return;
	//	}
	//} 
}

void CEditorScene::SelectBlock()
{
	//vector3 intersection = {};

	//if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_LEFT))
	//{
	//	Engine::CGameObject* target = Engine::CInputManager::GetInstance()->MousePicking(L"EventBlock", intersection);

	//	if (!target)
	//	{
	//		target = Engine::CInputManager::GetInstance()->MousePicking(L"NormalBlock", intersection);
	//	}

	//	if (!target)
	//	{
	//		return;
	//	}

	//	// ����� ������ �ֿܼ� ǥ��
	//	std::wstring message_w = target->GetObjectKey();
	//	std::string message_s;
	//	message_s.assign(message_w.begin(), message_w.end());

	//	std::cout << "target: " << message_s.c_str() << std::endl;
	//	std::cout << "targetX: " << target->GetComponent<Engine::CTransformComponent>()->GetPosition().x << std::endl;
	//	std::cout << "targetY: " << target->GetComponent<Engine::CTransformComponent>()->GetPosition().y << std::endl;
	//	std::cout << "targetZ: " << target->GetComponent<Engine::CTransformComponent>()->GetPosition().z << std::endl;
	//	std::cout << "/*****************************************/ " << std::endl;
	//	target->GetComponent<Engine::CGraphicsComponent>()->SetRenderID(Engine::ERenderID::WireFrame);

	//	if (m_pPreSelectedObject)
	//	{
	//		m_pPreSelectedObject->GetComponent<Engine::CGraphicsComponent>()->SetRenderID(Engine::ERenderID::Base);
	//	}
	//	m_pPreSelectedObject = target;
	//}
}
