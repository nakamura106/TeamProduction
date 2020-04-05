#include"BaseScene.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Manager/SceneManager.h"

BaseScene::BaseScene()
{
	m_CurrentSceneID = SceneId::Title;
	m_CurrentSceneStep = SceneStep::InitStep;
	DataBank::Instance()->SetSceneStep(m_CurrentSceneStep);
}

BaseScene::~BaseScene()
{

}

void BaseScene::Init()
{
	
}

void BaseScene::Update()
{
	switch (SceneManager::Instance()->GetSceneStep())
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