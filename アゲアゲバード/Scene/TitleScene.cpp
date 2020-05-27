#include "TitleScene.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Engine/Graphics.h"
#include"../UI/TitleUI.h"
#include"OptionScene.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"

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
	m_ui_manager->Init((int)UIManager::Scene::title);
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
}


void TitleScene::Draw()
{
	m_ui_manager->Draw((int)UIManager::Scene::title);

}

void TitleScene::InitScene()
{
	m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
	m_TitleSceneInfo.m_page = 0;
	m_TitleSceneInfo.m_select_flag = 0;
	
	m_ui_manager->Init((int)UIManager::Scene::title);
	m_ui_manager->LoadTex((int)UIManager::Scene::title);
	m_ui_manager->LoadFile((int)UIManager::Scene::title);
	
	m_sound_manager->RegisterTitleSound();
	m_sound_manager->SoundBGM(m_scene_manager->GetOptionScene()->GetOptionSceneInfo()->m_sound_volume);
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::MainStep;
}

void TitleScene::MainScene()
{
	UpdateSelect();

	m_ui_manager->UpDate((int)UIManager::Scene::title);

}

void TitleScene::EndScene()
{
	
	SetCursorPos(960, 540);
	m_ui_manager->Release((int)UIManager::Scene::title);
	if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option)
	{
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;

		m_scene_manager->SetSceneInfo()->m_CurrentSceneID = SceneId::Option;
	}
	if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Help)
	{
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;

		m_scene_manager->SetSceneInfo()->m_CurrentSceneID = SceneId::Help;
	}
	if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Timeattack|| m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
	{
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;

		m_scene_manager->SetSceneInfo()->m_CurrentSceneID = SceneId::Game;

		m_sound_manager->ReleaseTitleSound();
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
				m_sound_manager->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Solo)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Option;
				m_sound_manager->SoundSelectSE();
			}
		}
		else
		{
			m_sound_manager->ResetSelectFlag();
		}
		if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
				m_sound_manager->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Help)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Option;
				m_sound_manager->SoundSelectSE();
			}
			
		}
		else
		{
			m_sound_manager->ResetSelectFlag();
		}
	}

	if (m_TitleSceneInfo.m_page == (int)TitleUi::page::page2)
	{
		if (GetKeyDown(DOWN_KEY) || IsButtonDown(L_DownStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Back;
				m_sound_manager->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Timeattack)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Freemode;
				m_sound_manager->SoundSelectSE();
			}
		}
		else
		{
			m_sound_manager->ResetSelectFlag();
		}
		if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
		{
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Timeattack;
				m_sound_manager->SoundSelectSE();
			}
			if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Back)
			{
				m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Freemode;
				m_sound_manager->SoundSelectSE();
			}
		}
		else
		{
			m_sound_manager->ResetSelectFlag();
		}
	}
	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		m_sound_manager->SoundClickSE();
		if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Solo)
		{
			m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Timeattack;
			m_TitleSceneInfo.m_page = (int)TitleUi::page::page2;
		}
		else if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Option || m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Help ||
			m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Timeattack || m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Freemode)
		{
			m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
		}
		else if (m_TitleSceneInfo.m_now_select == (int)TitleUi::Select::Back)
		{
			m_TitleSceneInfo.m_now_select = (int)TitleUi::Select::Solo;
			m_TitleSceneInfo.m_page = (int)TitleUi::page::page1;
		}
	}
}


