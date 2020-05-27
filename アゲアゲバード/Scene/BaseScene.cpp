#include"BaseScene.h"
#include"../Engine/Input.h"

#include"../Manager/SceneManager.h"

MyBaseScene::BaseScene::BaseScene()
{

	m_scene_manager = SceneManager::Instance();

	m_scene_manager->SetSceneInfo()->m_CurrentSceneID = SceneId::Title;
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
}

MyBaseScene::BaseScene::~BaseScene()
{

}

void MyBaseScene::BaseScene::Init()
{
	
}

void MyBaseScene::BaseScene::Update()
{
	switch (m_scene_manager->GetSceneInfo()->m_CurrentSceneStep)
	{
	case SceneStep::InitStep:
		InitScene();
		break;
	case SceneStep::MainStep:
		MainScene();
		break;
	case SceneStep::EndStep:
		EndScene();
		break;
	default:
		break;
	}


	
}

void MyBaseScene::BaseScene::Draw()
{
	Draw();
}