#include"UIManager.h"
#include "../UI/GameUI.h"
#include"../UI/TitleUI.h"
#include"../UI/ResultUI.h"

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


void UIManager::Init(Scene scene_)
{
	//m_UI[scene_]->Init();	
	if (scene_ == Scene::title)
	{
		m_titleui->Init();
	}
	else if (scene_ == Scene::game)
	{
		m_gameui->Init();
	}
	else if (scene_ == Scene::end)
	{
		m_resultui->Init();
	}
}

void UIManager::CreateUI()
{
	//m_UI.push_back(new TitleUI);
	//m_UI.push_back(new GameUI);
	//m_UI.push_back(new ResultUI);

	m_titleui = new TitleUI;
	m_gameui = new GameUI;
	m_resultui = new ResultUI;


}

void UIManager::LoadTex(Scene scene_)
{	
	//m_UI[scene_]->LoadTex();

	if (scene_ == Scene::title)
	{
		m_titleui->LoadTex();
	}
	else if (scene_ == Scene::game)
	{
		m_gameui->LoadTex();
	}
	else if (scene_ == Scene::end)
	{
		m_resultui->LoadTex();
	}
}

void UIManager::LoadFile(Scene scene_)
{
	
		//m_UI[scene_]->LoadFile();
	if (scene_ == Scene::title)
	{
		m_titleui->LoadFile();
	}
	else if (scene_ == Scene::game)
	{
		m_gameui->LoadFile();
	}
	else if (scene_ == Scene::end)
	{
		m_resultui->LoadFile();
	}	
}

void UIManager::Draw(Scene scene_)
{
	
		//m_UI[scene_]->Draw();
	if (scene_ == Scene::title)
	{
		m_titleui->Draw();
	}
	else if (scene_ == Scene::game)
	{
		m_gameui->Draw();
	}
	else if (scene_ == Scene::end)
	{
		m_resultui->Draw();
	}
}

void UIManager::UpDate(Scene scene_)
{
		//m_UI[scene_]->UpDate();
	if (scene_ == Scene::title)
	{
		m_titleui->UpDate();
	}
	else if (scene_ == Scene::game)
	{
		m_gameui->UpDate();
	}
	else if (scene_ == Scene::end)
	{
		m_resultui->UpDate();
	}
}

void UIManager::Release(Scene scene_)
{
		//m_UI[scene_]->ReleaseTex();
	if (scene_ == Scene::title)
	{
		m_titleui->ReleaseTex();
	}
	else if (scene_ == Scene::game)
	{
		m_gameui->ReleaseTex();
	}
	else if (scene_ == Scene::end)
	{
		m_resultui->ReleaseTex();
	}
}
