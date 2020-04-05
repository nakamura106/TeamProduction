#include "TitleScene.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Manager/SceneManager.h"

TitleScene::TitleScene()
{

	Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{

	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
}


void TitleScene::Draw()
{
	if (m_select_flag == 0)
	{
		DrawUITexture(&m_title, m_title_bg_pos);
	}
	else
	{
		DrawUITexture(&m_help, m_title_bg_pos);
	}
}

void TitleScene::InitScene()
{
	SoundManager::Instance()->SoundBGM(-1000);
	m_title_bg_pos.x = 0;
	m_title_bg_pos.y = 0;
	m_select_flag = 0;
	SoundManager::Instance()->RegisterTitleSound();
	LoadTexture("Res/Tex/GameSelect.png", &m_title);
	LoadTexture("Res/Tex/HelpSelect.png", &m_help);
	SoundManager::Instance()->SoundBGM(-1000);
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::MainStep);
}

void TitleScene::MainScene()
{
	if(GetKeyDown(DOWN_KEY))
	{
		SoundManager::Instance()->SoundSelectSE();
		m_select_flag = 1;
	}
	else
	{
		SoundManager::Instance()->ResetSelectFlag();
	}
	if (GetKeyDown(UP_KEY))
	{
		SoundManager::Instance()->SoundSelectSE();

		m_select_flag = 0;
	}
	else
	{
		SoundManager::Instance()->ResetSelectFlag();
	}
	if (GetKeyDown(RETURN_KEY))
	{
		SoundManager::Instance()->SoundClickSE();
		SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::EndStep);
		
	}
}

void TitleScene::EndScene()
{
	ReleaseTexture(&m_title);
	ReleaseTexture(&m_help);
	
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
	if (m_select_flag == 0)
	{

		SoundManager::Instance()->ReleaseTitleSound();
		SceneManager::Instance()->SetSceneId(BaseScene::SceneId::Game);
	}
	if (m_select_flag == 1)
	{

		SceneManager::Instance()->SetSceneId(BaseScene::SceneId::Help);
	}
}


