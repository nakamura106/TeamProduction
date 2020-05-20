#include "TitleScene.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Engine/Graphics.h"
#include"../UI/TitleUI.h"
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
	m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
	m_TitleSceneInfo.m_page = 0;
	m_TitleSceneInfo.m_select_flag = 0;
	UIManager::Instance()->Init((int)UIManager::Scene::title);
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
}


void TitleScene::Draw()
{
	UIManager::Instance()->Draw((int)UIManager::Scene::title);

}

void TitleScene::InitScene()
{
	m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
	m_TitleSceneInfo.m_page = 0;
	m_TitleSceneInfo.m_select_flag = 0;
	
	UIManager::Instance()->Init((int)UIManager::Scene::title);
	UIManager::Instance()->LoadTex((int)UIManager::Scene::title);
	UIManager::Instance()->LoadFile((int)UIManager::Scene::title);
	
	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM(-1000);
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::MainStep;
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
	if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option)
	{
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;

		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID = SceneId::Option;
	}
	if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Help)
	{
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;

		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID = SceneId::Help;
	}
	if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Timeattack|| m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
	{
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;

		SoundManager::Instance()->ReleaseTitleSound();
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID = SceneId::Game;
	}
}

void TitleScene::UpdateSelect()
{
	if (m_TitleSceneInfo.m_page == (int)TitleUi::page::page1)
	{
		if (GetKeyDown(DOWN_KEY) || IsButtonDown(L_DownStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Help;
				SoundManager::Instance()->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Solo)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Option;
				SoundManager::Instance()->SoundSelectSE();
			}
			
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
		if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
				SoundManager::Instance()->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Help)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Option;
				SoundManager::Instance()->SoundSelectSE();
			}
			
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
	}

	if (m_TitleSceneInfo.m_page == (int)TitleUi::page::page2)
	{
		if (GetKeyDown(DOWN_KEY) || IsButtonDown(L_DownStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Back;
				SoundManager::Instance()->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Timeattack)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Freemode;
				SoundManager::Instance()->SoundSelectSE();
			}
		}
		else
		{
			SoundManager::Instance()->ResetSelectFlag();
		}
		if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Timeattack;
				SoundManager::Instance()->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Back)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Freemode;
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

		SoundManager::Instance()->SoundClickSE();
		if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Solo)
		{
			m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Timeattack;
			m_TitleSceneInfo.m_page = (int)TitleUi::page::page2;
		}
		else if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option || m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Help ||
			m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Timeattack || m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
		{
			SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
		}
		else if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Back)
		{
			m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
			m_TitleSceneInfo.m_page = (int)TitleUi::page::page1;
		}
	}
}


