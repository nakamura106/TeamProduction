#include "GameEndScene.h"
#include"GameScene.h"
#include"OptionScene.h"
#include"../Engine/Input.h"
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
	
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
}



void GameEndScene::Draw()
{
	
	
	DrawUITexture(&m_GameEndSceneInfo.m_end, m_GameEndSceneInfo.m_end_bg_pos);
	
}

void GameEndScene::InitScene()
{
	m_GameEndSceneInfo.m_end_bg_pos.x = 0;
	m_GameEndSceneInfo.m_end_bg_pos.y = 0;
	if (m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == false)
	{
		LoadTexture("Res/Tex/END.png", &m_GameEndSceneInfo.m_end);
	}
	if (m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == true)
	{
		LoadTexture("Res/Tex/ƒNƒŠƒA.png", &m_GameEndSceneInfo.m_end);
	}
	m_sound_manager->RegisterEndSound();
	m_sound_manager->SoundBGM(SceneManager::Instance()->GetOptionScene()->GetOptionSceneInfo()->m_sound_volume);
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void GameEndScene::MainScene()
{
	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::EndStep;
	}
}

void GameEndScene::EndScene()
{

	m_sound_manager->ReleaseSelectSound();
	ReleaseTexture(&m_GameEndSceneInfo.m_end);
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
	m_scene_manager->SetSceneInfo()->m_CurrentSceneID=SceneId::Title;
}
