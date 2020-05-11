#include "HelpScene.h"
#include"../Manager/SoundManager.h"
#include"../DataBank/DataBank.h"
#include"../Engine/Graphics.h"
#include"../Manager/SceneManager.h"
#include"../Engine/Input.h"

HelpScene::HelpScene()
{
	
	Init();
}

HelpScene::~HelpScene()
{
}

void HelpScene::Init()
{

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
}


void HelpScene::Draw()
{
	if (m_HelpSceneInfo.m_help_flag==0)
	{
		DrawUITexture(&m_HelpSceneInfo.m_help1, m_HelpSceneInfo.m_help_bg_pos);
	}
	if (m_HelpSceneInfo.m_help_flag == 1)
	{
		DrawUITexture(&m_HelpSceneInfo.m_help2, m_HelpSceneInfo.m_help_bg_pos);
	}
	if (m_HelpSceneInfo.m_help_flag == 2)
	{
		DrawUITexture(&m_HelpSceneInfo.m_help3, m_HelpSceneInfo.m_help_bg_pos);
	}

}

void HelpScene::InitScene()
{
	m_HelpSceneInfo.m_help_flag = 0;
	m_HelpSceneInfo.m_help_bg_pos.x = 0;
	m_HelpSceneInfo.m_help_bg_pos.y = 0;
	LoadTexture("Res/Tex/Help1.png", &m_HelpSceneInfo.m_help1);
	LoadTexture("Res/Tex/Help2.png", &m_HelpSceneInfo.m_help2);
	LoadTexture("Res/Tex/Help3.png", &m_HelpSceneInfo.m_help3);
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void HelpScene::MainScene()
{
	if (GetKeyDown(LEFT_KEY) || IsButtonDown(LeftButton) || IsButtonDown(L_LeftStick))
	{
		if (m_HelpSceneInfo.m_help_flag == 0)
		{
			SoundManager::Instance()->SoundCancelSE();
			SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID=SceneId::Title;
		}
		else if(m_HelpSceneInfo.m_help_flag>=1)
		{
			SoundManager::Instance()->SoundSelectSE();
			m_HelpSceneInfo.m_help_flag--;
		}
	}
	else if (GetKeyDown(RIGHT_KEY) || IsButtonDown(RightButton) || IsButtonDown(L_RightStick))
	{
		if (m_HelpSceneInfo.m_help_flag == 2)
		{
			SoundManager::Instance()->SoundClickSE();
			SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID = SceneId::Title;

		}
		else if (m_HelpSceneInfo.m_help_flag <= 1)
		{
			SoundManager::Instance()->SoundSelectSE();
			m_HelpSceneInfo.m_help_flag++;
		}
	}
	else
	{
		SoundManager::Instance()->ResetSelectFlag();
	}
}

void HelpScene::EndScene()
{
	ReleaseTexture(&m_HelpSceneInfo.m_help1);
	ReleaseTexture(&m_HelpSceneInfo.m_help2);
	ReleaseTexture(&m_HelpSceneInfo.m_help3);

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID=SceneId::Title;

}
