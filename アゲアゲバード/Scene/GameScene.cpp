#include "GameScene.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/UIManager.h"
#include"../Manager/ProductionManager.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
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

	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
}



void GameScene::Draw()
{
	ObjectManager::Instance()->Draw();

	UIManager::Instance()->Draw((int)UIManager::Scene::game);

	ProductionManager::Instance()->Draw();
}

void GameScene::InitScene()
{
	DataBank::Instance()->SetClearflag(false);

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

	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::MainStep);
}

void GameScene::MainScene()
{
	if (DataBank::Instance()->GetStartflag() == true)
	{
		UIManager::Instance()->UpDate((int)UIManager::Scene::game);
		ProductionManager::Instance()->UpDate();
	}

	ObjectManager::Instance()->Update();

	if (DataBank::Instance()->GetAfterPlayerPos().y<=DataBank::Instance()->GetOilPos() )
	{
		DataBank::Instance()->SetClearflag(false);
		SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::EndStep);
	}
	if (DataBank::Instance()->GetAfterPlayerPos().y >= DataBank::Instance()->GetMapTop().y)
	{
		DataBank::Instance()->SetClearflag(true);
		SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::EndStep);
	}
	if (GetKeyDown(F_KEY))
	{
		SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::EndStep);
	}
	
}

void GameScene::EndScene()
{
	SoundManager::Instance()->ReleaseBattleSound();

	UIManager::Instance()->Release((int)UIManager::Scene::game);

	ProductionManager::Instance()->ReleaseTex();

	ObjectManager::Instance()->AllDeleteObject();

	DataBank::Instance()->DeleteGameData();

	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
	SceneManager::Instance()->SetSceneId(BaseScene::SceneId::End);
}
