#include "TitleScene.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Graphics.h"
#include"../Engine/Texture.h"

TitleScene::TitleScene()
{
	m_CurrentSceneID = SceneId::Title;
	m_CurrentSceneStep = SceneStep::InitStep;
	SoundManager::Instance()->RegisterTitleSound();
	LoadTexture("Res/Tex/GameSelect.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleBgTex);
	LoadTexture("Res/Tex/HelpSelect.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::HelpSelectTex);

}

TitleScene::~TitleScene()
{
}

BaseScene::SceneId TitleScene::Init()
{

	m_CurrentSceneID = SceneId::Title;
	m_CurrentSceneStep = SceneStep::InitStep;
	return SceneId();
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


