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

	Draw();
}

void BaseScene::Draw()
{

}