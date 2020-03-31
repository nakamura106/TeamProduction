#include "TitleScene.h"
#include"../Manager/SoundManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

BaseScene::SceneId TitleScene::Init()
{
	return SceneId();
}

BaseScene::SceneId TitleScene::Update()
{
	switch (m_CurrentSceneStep)
	{
	case SceneStep::InitStep:
		InitScene();
		break;
	case SceneStep::MainStep:
		MainScene();
		break;
	case SceneStep::EndStep:
		EndScene();
		break;
	default:
		break;
	}
	return SceneId::Title;
}

void TitleScene::Draw()
{
}

void TitleScene::InitScene()
{
}

void TitleScene::MainScene()
{
}

void TitleScene::EndScene()
{
	SoundManager::Instance()->ReleaseTitleSound();
}


