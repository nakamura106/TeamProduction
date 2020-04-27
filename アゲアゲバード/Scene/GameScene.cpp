#include "GameScene.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/UIManager.h"
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
	UIManager::Instance()->Init();
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
}



void GameScene::Draw()
{
	ObjectManager::Instance()->Draw();
	UIManager::Instance()->Draw();
}

void GameScene::InitScene()
{
	DataBank::Instance()->SetClearflag(false);
	ObjectManager::Instance()->CreateObject();
	ObjectManager::Instance()->CreatePlayer();
	SoundManager::Instance()->RegisterGameMainSound();
	SoundManager::Instance()->SoundBGM(-1000);
    UIManager::Instance()->CreateUI();
	UIManager::Instance()->LoadTex();
	UIManager::Instance()->LoadFile();

	UIManager::Instance()->Init();
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::MainStep);
}

void GameScene::MainScene()
{

	ObjectManager::Instance()->Update();
	UIManager::Instance()->UpDate();
	
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
	ObjectManager::Instance()->AllDeleteObject();
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
	SceneManager::Instance()->SetSceneId(BaseScene::SceneId::End);
	DataBank::Instance()->DeleteGameData();
}
