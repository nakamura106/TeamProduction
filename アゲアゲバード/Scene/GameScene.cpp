#include "GameScene.h"
#include"../Engine/FBX.h"
#include"../Production/EndProduction.h"
#include"../Engine/Input.h"
#include"../Production/StartProduction.h"
#include"OptionScene.h"
#include"../UI/TitleUI.h"
#include"../Scene/TitleScene.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/UIManager.h"
#include"../Manager/ProductionManager.h"


#include <iostream>
#include <fstream>

GameScene::GameScene()
{

	Init();
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_ui_manager->Init(UIManager::Scene::game);

	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
}



void GameScene::Draw()
{

	//sprintf_s(debugcamerapos, "c=%f", ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_after_player_pos.y);

	//sprintf_s(debugppos, "p=%f", ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_before_player_pos.y);


	//DrawFont(100.0f, 100.0f, debugcamerapos, Regular, Red);
	//DrawFont(200.0f, 200.0f, debugppos, Regular, Red);

	m_ui_manager->Draw(UIManager::Scene::game);


	m_object_manager->Draw();

	m_production_manager->Draw();
}

void GameScene::InitScene()
{
	m_GameSceneInfo.m_ClearFlag = false;

	m_object_manager->CreateObject();
	m_object_manager->CreatePlayer();

	m_sound_manager->RegisterGameMainSound();
	m_sound_manager->SoundBGM(SceneManager::Instance()->GetOptionScene()->GetOptionSceneInfo()->m_sound_volume);

	m_ui_manager->LoadTex(UIManager::Scene::game);
	m_ui_manager->Init(UIManager::Scene::game);

	m_production_manager->CreateProduction();
	m_production_manager->LoadTex();
	m_production_manager->Init();

	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void GameScene::MainScene()
{
	int a = 0;
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		TimeattackUpdate();
	}
	else if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Freemode)
	{
		FreemodeUpdate();
	}
}

void GameScene::EndScene()
{
	m_sound_manager->ReleaseBattleSound();

	m_ui_manager->Release(UIManager::Scene::game);

	m_production_manager->ReleaseTex();

	m_object_manager->AllDeleteObject();

	
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
	m_scene_manager->SetSceneInfo()->m_CurrentSceneID=SceneId::End;
}

void GameScene::TimeattackUpdate()
{
	if (m_object_manager->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_startflag == true)
	{
		m_ui_manager->UpDate(UIManager::Scene::game);
		m_production_manager->UpDate();
	}

	m_object_manager->Update();


	if (m_production_manager->GetEndProduction()->GetEndProductionInfo()->flyflag == true)
	{
		m_GameSceneInfo.m_ClearFlag = false;
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
	if (m_production_manager->GetEndProduction()->GetEndProductionInfo()->finishflag == true)
	{
		m_GameSceneInfo.m_ClearFlag = true;
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
	if (GetKeyDown(F_KEY))
	{
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}

}

void GameScene::FreemodeUpdate()
{
	if (m_object_manager->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_startflag == true)
	{
		m_ui_manager->UpDate(UIManager::Scene::game);
			m_production_manager->UpDate();
	}

	m_object_manager->Update();


	if (m_production_manager->GetEndProduction()->GetEndProductionInfo()->flyflag == true)
	{
		m_GameSceneInfo.m_ClearFlag = false;
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
	if (m_production_manager->GetEndProduction()->GetEndProductionInfo()->finishflag == true)
	{
		m_GameSceneInfo.m_ClearFlag = true;
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
	if (GetKeyDown(F_KEY))
	{
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
}
