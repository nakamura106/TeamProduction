#include "TitleScene.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Manager/SceneManager.h"
#include"../Manager/UIManager.h"

TitleScene::TitleScene()
{

	Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	UIManager::Instance()->Init((int)UIManager::Scene::title);
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::InitStep);
}


void TitleScene::Draw()
{
	UIManager::Instance()->Draw((int)UIManager::Scene::title);

}

void TitleScene::InitScene()
{

	m_select_flag = 0;
	
	UIManager::Instance()->Init((int)UIManager::Scene::title);
	UIManager::Instance()->LoadTex((int)UIManager::Scene::title);
	UIManager::Instance()->LoadFile((int)UIManager::Scene::title);

	
	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM(-1000);
	SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::MainStep);
}

void TitleScene::MainScene()
{
	UpdateSelect();

	UIManager::Instance()->UpDate((int)UIManager::Scene::title);

}

void TitleScene::EndScene()
{
	
	SetCursorPos(960, 540);
	UIManager::Instance()->Release((int)UIManager::Scene::title);
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

void TitleScene::UpdateSelect()
{
	if (DataBank::Instance()->GetPage() == (int)TitleUi::page::page1)
	{
		if (GetKeyDown(DOWN_KEY) || IsButtonDown(L_DownStick))
		{
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Option)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Help);
				SoundManager::Instance()->SoundSelectSE();
			}
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Solo)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Option);
				SoundManager::Instance()->SoundSelectSE();
			}
			
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
		if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
		{
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Option)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Solo);
				SoundManager::Instance()->SoundSelectSE();
			}
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Help)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Option);
				SoundManager::Instance()->SoundSelectSE();
			}
			
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
	}
	if (DataBank::Instance()->GetPage() == (int)TitleUi::page::page2)
	{
		if (GetKeyDown(DOWN_KEY) || IsButtonDown(L_DownStick))
		{
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Freemode)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Back);
				SoundManager::Instance()->SoundSelectSE();
			}
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Timeattack)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Freemode);
				SoundManager::Instance()->SoundSelectSE();
			}
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
		if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
		{
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Freemode)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Timeattack);
				SoundManager::Instance()->SoundSelectSE();
			}
			if (DataBank::Instance()->GetSelect() == (int)TitleUi::Select::Back)
			{
				DataBank::Instance()->SetSelect((int)TitleUi::Select::Freemode);
				SoundManager::Instance()->SoundSelectSE();
			}
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
	}
	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		if (DataBank::Instance()->GetPage() == (int)TitleUi::page::page2)
		{
			SceneManager::Instance()->SetSceneStep(BaseScene::SceneStep::EndStep);
		}
		if (DataBank::Instance()->GetPage() == (int)TitleUi::page::page1)
		{

			SoundManager::Instance()->SoundClickSE();
			DataBank::Instance()->SetPage((int)TitleUi::page::page2);
			DataBank::Instance()->SetSelect((int)TitleUi::Select::Timeattack);
		}
	}
}


