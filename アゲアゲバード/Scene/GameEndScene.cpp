#include "GameEndScene.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Manager/SceneManager.h"
#include"../Engine/Graphics.h"

GameEndScene::GameEndScene()
{
	Init();
}

GameEndScene::~GameEndScene()
{
}

void GameEndScene::Init()
{
	
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
}



void GameEndScene::Draw()
{
	DrawUITexture(&m_end, m_end_bg_pos);
}

void GameEndScene::InitScene()
{
	m_end_bg_pos.x = 0;
	m_end_bg_pos.y = 0;
	LoadTexture("Res/Tex/END.png", &m_end);
	SoundManager::Instance()->RegisterEndSound();
	SoundManager::Instance()->SoundBGM(-1000);
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::MainStep);
}

void GameEndScene::MainScene()
{
	if (GetKeyDown(RETURN_KEY))
	{
		SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::EndStep);
	}
}

void GameEndScene::EndScene()
{
	SoundManager::Instance()->ReleaseSelectSound();
	ReleaseTexture(&m_end);
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
	SceneManager::Instance()->SetSceneId(BaseScene::SceneId::Title);
}
