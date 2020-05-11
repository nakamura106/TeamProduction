#include"BaseScene.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Manager/SceneManager.h"

BaseScene::BaseScene()
{
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID = SceneId::Title;
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
}

BaseScene::~BaseScene()
{

}

void BaseScene::Init()
{
	
}

void BaseScene::Update()
{
	switch (SceneManager::Instance()->GetSceneInfo()->m_CurrentSceneStep)
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

void BaseScene::Draw()
{
	Draw();
}