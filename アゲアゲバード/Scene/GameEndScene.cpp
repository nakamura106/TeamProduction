#include "GameEndScene.h"

GameEndScene::GameEndScene()
{

	m_CurrentSceneID = SceneId::End;
	m_CurrentSceneStep = SceneStep::InitStep;
}

GameEndScene::~GameEndScene()
{
}

BaseScene::SceneId GameEndScene::Init()
{
	m_CurrentSceneID = SceneId::End;
	m_CurrentSceneStep = SceneStep::InitStep;
	return SceneId();
}



void GameEndScene::Draw()
{
}

void GameEndScene::InitScene()
{
}

void GameEndScene::MainScene()
{
}

void GameEndScene::EndScene()
{
}
