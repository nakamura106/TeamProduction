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
	ObjectManager::Instance()->CreateObject();
	//ObjectManager::Instance()->CreateItem();
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
	if (GetKeyDown(T_KEY) || IsButtonDown(RightBButton))
	{
		SoundManager::Instance()->SoundThrow();
		ObjectManager::Instance()->CreateItem();
	}

	ObjectManager::Instance()->Update();
	UIManager::Instance()->UpDate();
	if (GetKeyDown(SPACE_KEY) || IsButtonDown(LeftBButton))
	{
		if (ObjectManager::Instance()->CreateBlock() == true)
		{
			SoundManager::Instance()->SoundClickSE();
		}
	}
	if (GetKeyDown(F_KEY) )
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
