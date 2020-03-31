#include"UIManager.h"
#include "../UI/GameUI.h"
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


void UIManager::CreateUI()
{
	m_UI.push_back(new GameUI);
}

void UIManager::LoadTex()
{
	for (int i = 0; i < m_UI.size(); i++)
	{
		m_UI[i]->LoadTex();
	}
	
}

void UIManager::Draw()
{
	for (int i = 0; i < m_UI.size(); i++)
	{
		m_UI[i]->Draw();
	}
}

void UIManager::UpDate()
{
	for (int i = 0; i < m_UI.size(); i++)
	{
		m_UI[i]->UpDate();
	}
}
