#include "GameEndScene.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Input.h"
#include"../Scene/GameScene.h"
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
	
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
}



void GameEndScene::Draw()
{
	
	
	DrawUITexture(&m_GameEndSceneInfo.m_end, m_GameEndSceneInfo.m_end_bg_pos);
	
}

void GameEndScene::InitScene()
{
	m_GameEndSceneInfo.m_end_bg_pos.x = 0;
	m_GameEndSceneInfo.m_end_bg_pos.y = 0;
	if (SceneManager::Instance()->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == false)
	{
		LoadTexture("Res/Tex/END.png", &m_GameEndSceneInfo.m_end);
	}
	if (SceneManager::Instance()->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == true)
	{
		LoadTexture("Res/Tex/ƒNƒŠƒA.png", &m_GameEndSceneInfo.m_end);
	}
	SoundManager::Instance()->RegisterEndSound();
	SoundManager::Instance()->SoundBGM(-1000);
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void GameEndScene::MainScene()
{
	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::EndStep;
	}
}

void GameEndScene::EndScene()
{

	SoundManager::Instance()->ReleaseSelectSound();
	ReleaseTexture(&m_GameEndSceneInfo.m_end);
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID=SceneId::Title;
}
