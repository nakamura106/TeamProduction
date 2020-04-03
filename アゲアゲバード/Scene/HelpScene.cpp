#include "HelpScene.h"
#include"../Manager/SoundManager.h"

HelpScene::HelpScene()
{
	m_CurrentSceneID = SceneId::Help;
	m_CurrentSceneStep = SceneStep::InitStep;
}

HelpScene::~HelpScene()
{
}

BaseScene::SceneId HelpScene::Init()
{

	m_CurrentSceneID = SceneId::Help;
	m_CurrentSceneStep = SceneStep::InitStep;
	return SceneId();
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
