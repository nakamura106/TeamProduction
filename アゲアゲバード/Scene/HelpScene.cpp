#include "HelpScene.h"
#include"../Engine/Graphics.h"
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
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::InitStep;
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
	LoadTexture("Res/Tex/ƒwƒ‹ƒv‰æ–Ê_C³2.png", &m_HelpSceneInfo.m_help);
	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep=SceneStep::MainStep;
}

void HelpScene::MainScene()
{
	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		m_sound_manager->SoundClickSE();
		m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
	}
}

void HelpScene::EndScene()
{
	ReleaseTexture(&m_HelpSceneInfo.m_help);

	m_scene_manager->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
	m_scene_manager->SetSceneInfo()->m_CurrentSceneID=SceneId::Title;

}
