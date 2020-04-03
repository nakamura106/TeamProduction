#include"BaseScene.h"
#include"../Engine/Input.h"

BaseScene::BaseScene()
{
	m_CurrentSceneID = SceneId::Title;
	m_CurrentSceneStep = SceneStep::InitStep;
}

BaseScene::~BaseScene()
{

}

BaseScene::SceneId BaseScene::Init()
{
	return SceneId();
}

BaseScene::SceneId BaseScene::Update()
{
	UpdateInput();
	switch (m_CurrentSceneStep)
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
	Draw();

	return m_CurrentSceneID;
}

void BaseScene::Draw()
{

}