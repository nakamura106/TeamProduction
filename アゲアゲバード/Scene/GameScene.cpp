#include "GameScene.h"
#include"../Engine/FBX.h"
#include"../Production/EndProduction.h"
#include"../Engine/Input.h"
#include"../Production/StartProduction.h"
#include"OptionScene.h"
#include"../Manager/SceneManager.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/SoundManager.h"
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
	UIManager::Instance()->Init((int)UIManager::Scene::game);

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
}



void GameScene::Draw()
{

	//sprintf_s(debugcamerapos, "c=%f", ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_after_player_pos.y);

	//sprintf_s(debugppos, "p=%f", ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_before_player_pos.y);


	//DrawFont(100.0f, 100.0f, debugcamerapos, Regular, Red);
	//DrawFont(200.0f, 200.0f, debugppos, Regular, Red);

	UIManager::Instance()->Draw((int)UIManager::Scene::game);


	ObjectManager::Instance()->Draw();

	ProductionManager::Instance()->Draw();
}

void GameScene::InitScene()
{
	m_GameSceneInfo.m_ClearFlag = false;

	ObjectManager::Instance()->CreateObject();
	ObjectManager::Instance()->CreatePlayer();

	SoundManager::Instance()->RegisterGameMainSound();
	SoundManager::Instance()->SoundBGM(SceneManager::Instance()->GetOptionScene()->GetOptionSceneInfo()->m_sound_volume);

	UIManager::Instance()->LoadTex((int)UIManager::Scene::game);
	UIManager::Instance()->LoadFile((int)UIManager::Scene::game);
	UIManager::Instance()->Init((int)UIManager::Scene::game);

	ProductionManager::Instance()->CreateProduction();
	ProductionManager::Instance()->LoadTex();
	ProductionManager::Instance()->Init();

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void GameScene::MainScene()
{
	if (ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_startflag == true)
	{
		UIManager::Instance()->UpDate((int)UIManager::Scene::game);
		ProductionManager::Instance()->UpDate();
	}

	ObjectManager::Instance()->Update();

	
	if (ProductionManager::Instance()->GetEndProduction()->GetEndProductionInfo()->flyflag == true)
{
		m_GameSceneInfo.m_ClearFlag = false;
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::EndStep;
	}
	if (ProductionManager::Instance()->GetEndProduction()->GetEndProductionInfo()->finishflag == true)
	{
		m_GameSceneInfo.m_ClearFlag = true;
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
	if (GetKeyDown(F_KEY))
	{
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
	
}

void GameScene::EndScene()
{
	SoundManager::Instance()->ReleaseBattleSound();

	UIManager::Instance()->Release((int)UIManager::Scene::game);

	ProductionManager::Instance()->ReleaseTex();

	ObjectManager::Instance()->AllDeleteObject();

	
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID=SceneId::End;
}
