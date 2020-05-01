#include"UIManager.h"
#include "../UI/GameUI.h"
#include"../UI/TitleUI.h"
#include"../DataBank/DataBank.h"

UIManager* UIManager::p_instance = 0;

UIManager* UIManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new UIManager;
	}

	return p_instance;
}

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
	
}


void UIManager::Init(int scene_)
{
	m_UI[scene_]->Init();	
}

void UIManager::CreateUI()
{
	m_UI.push_back(new TitleUi);
	m_UI.push_back(new GameUI);
}

void UIManager::LoadTex(int scene_)
{	
	m_UI[scene_]->LoadTex();
}

void UIManager::LoadFile(int scene_)
{
	
		m_UI[scene_]->LoadFile();
	

}

void UIManager::Draw(int scene_)
{
	
		m_UI[scene_]->Draw();
	
}

void UIManager::UpDate(int scene_)
{
		m_UI[scene_]->UpDate();
}

void UIManager::Release(int scene_)
{
		m_UI[scene_]->ReleaseTex();
}
