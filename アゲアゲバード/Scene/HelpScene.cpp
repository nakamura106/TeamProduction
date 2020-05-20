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
	
		DrawUITexture(&m_HelpSceneInfo.m_help, m_HelpSceneInfo.m_help_bg_pos);
	

}

void HelpScene::InitScene()
{
	m_HelpSceneInfo.m_help_flag = 0;
	m_HelpSceneInfo.m_help_bg_pos.x = 0;
	m_HelpSceneInfo.m_help_bg_pos.y = 0;
	LoadTexture("Res/Tex/help.png", &m_HelpSceneInfo.m_help);
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void HelpScene::MainScene()
{
	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
}

void HelpScene::EndScene()
{
	ReleaseTexture(&m_HelpSceneInfo.m_help);

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID=SceneId::Title;

}
