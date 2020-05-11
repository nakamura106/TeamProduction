#include "GameScene.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/UIManager.h"
#include"../Production/EndProduction.h"
#include"../Manager/ProductionManager.h"
#include"../Engine/Input.h"
#include"../Production/StartProduction.h"
#include"../Manager/SceneManager.h"
#include"../Engine/FBX.h"

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
	ObjectManager::Instance()->Draw();

	UIManager::Instance()->Draw((int)UIManager::Scene::game);

	ProductionManager::Instance()->Draw();
}

void GameScene::InitScene()
{
	m_GameSceneInfo.m_ClearFlag = false;

	ObjectManager::Instance()->CreateObject();
	ObjectManager::Instance()->CreatePlayer();

	SoundManager::Instance()->RegisterGameMainSound();
	SoundManager::Instance()->SoundBGM(-1000);

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
	if (ProductionManager::Instance()->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
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
