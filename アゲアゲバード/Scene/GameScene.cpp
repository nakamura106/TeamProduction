#include "GameScene.h"

GameScene::GameScene()
{

	m_CurrentSceneID = SceneId::Game;
	m_CurrentSceneStep = SceneStep::InitStep;
}

GameScene::~GameScene()
{
}

BaseScene::SceneId GameScene::Init()
{

	m_CurrentSceneID = SceneId::Game;
	m_CurrentSceneStep = SceneStep::InitStep;
	return SceneId();
}



void GameScene::Draw()
{
}

void GameScene::InitScene()
{
}

void GameScene::MainScene()
{
}

void GameScene::EndScene()
{
}
