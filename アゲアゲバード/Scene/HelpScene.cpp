#include "HelpScene.h"
#include"../Manager/SoundManager.h"
#include"../DataBank/DataBank.h"

HelpScene::HelpScene()
{
	
	Init();
}

HelpScene::~HelpScene()
{
}

void HelpScene::Init()
{


}


void HelpScene::Draw()
{
}

void HelpScene::InitScene()
{
}

void HelpScene::MainScene()
{
}

void HelpScene::EndScene()
{
	SoundManager::Instance()->ReleaseTitleSound();

}
