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
	
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
}



void GameScene::Draw()
{
	ObjectManager::Instance()->Draw();
	UIManager::Instance()->Draw();
}

void GameScene::InitScene()
{
	ObjectManager::Instance()->CreateObject();
	SoundManager::Instance()->RegisterGameMainSound();
	SoundManager::Instance()->SoundBGM(-1000);
    UIManager::Instance()->CreateUI();
	UIManager::Instance()->LoadTex();
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::MainStep);
}

void GameScene::MainScene()
{
	ObjectManager::Instance()->Update();
	UIManager::Instance()->UpDate();
	if (GetKeyDown(SPACE_KEY))
	{
		SoundManager::Instance()->SoundClickSE();
		ObjectManager::Instance()->CreateBlock();
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

}
