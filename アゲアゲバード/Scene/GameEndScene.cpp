#include "GameEndScene.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"OptionScene.h"
#include"TitleScene.h"
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
	
	if (m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == true&& m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		m_ui_manager->Draw(UIManager::Scene::end);
	}
}

void GameEndScene::InitScene()
{
	m_GameEndSceneInfo.m_end_bg_pos.x = 0;
	m_GameEndSceneInfo.m_end_bg_pos.y = 0;
<<<<<<< HEAD

	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Freemode)
	{
		LoadTexture("Res/Tex/リザルト画面_フリープレイ.png", &m_GameEndSceneInfo.m_end);
	}
	else
	{
		if (m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == false)
		{
			LoadTexture("Res/Tex/END.png", &m_GameEndSceneInfo.m_end);
		}
		if (m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == true)
		{
			LoadTexture("Res/Tex/クリア.png", &m_GameEndSceneInfo.m_end);
		}
	}
	
	m_ui_manager->Init(UIManager::Scene::end);
=======
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack&&m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == false)
	{
		m_ui_manager->Init(UIManager::Scene::end);
		LoadTexture("Res/Tex/END.png", &m_GameEndSceneInfo.m_end);
	}
	else if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack&&m_scene_manager->GetGameScene()->GetGameSceneInfo()->m_ClearFlag == true)
	{
		m_ui_manager->Init(UIManager::Scene::end);
		LoadTexture("Res/Tex/クリア.png", &m_GameEndSceneInfo.m_end);
	}
	else if(m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select==(int)TitleUI::Select::Freemode)
	{
		LoadTexture("Res/Tex/リザルト画面_フリープレイ.png", &m_GameEndSceneInfo.m_end);
	}

>>>>>>> 7465814ffd70f57bdd9086b8742809cc485003cd
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
