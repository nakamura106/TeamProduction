#include "SceneManager.h"
#include"../Scene/TitleScene.h"
#include"../Scene/HelpScene.h"
#include"../Scene/OptionScene.h"
#include"../Scene/GameScene.h"
#include"../Scene/GameEndScene.h"
#include"../Engine/Input.h"
#include"../Engine/Graphics.h"
#include"../DataBank/DataBank.h"
#include"../Manager/UIManager.h"

SceneManager* SceneManager::p_instance = 0;


SceneManager* SceneManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new SceneManager;
	}

	return p_instance;
}

void SceneManager::Init()
{
	m_SceneInstance.m_title=(new TitleScene);
	m_SceneInstance.m_help=(new HelpScene);
	m_SceneInstance.m_option = (new OptionScene);
	m_SceneInstance.m_game=(new GameScene);
	m_SceneInstance.m_gameend=(new GameEndScene);
}

void SceneManager::Update()
{
	UpdateInput();
	KeyStateUpdate();

		switch (m_SceneInfo.m_CurrentSceneID)
		{
		case SceneId::Title:
			m_SceneInstance.m_title->Update();
			break;
		case SceneId::Help:
			m_SceneInstance.m_help->Update();
			break;
		case SceneId::Option:
			m_SceneInstance.m_option->Update();
			break;
		case SceneId::Game:
			m_SceneInstance.m_game->Update();
			break;
		case SceneId::End:
			m_SceneInstance.m_gameend->Update();
			break;
		default:
			break;
		}
}

void SceneManager::Draw()
{
	if (m_SceneInfo.m_CurrentSceneStep == SceneStep::MainStep)
	{
		DrawStart();

		SetRenderMode(ERenderMode::Normal, true);

		GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		
		SetLight();

		switch (m_SceneInfo.m_CurrentSceneID)
		{
		case SceneId::Title:
			m_SceneInstance.m_title->Draw();
			break;
		case SceneId::Help:
			m_SceneInstance.m_help->Draw();
			break;
		case SceneId::Option:
			m_SceneInstance.m_option->Draw();
			break;
		case SceneId::Game:
			m_SceneInstance.m_game->Draw();
			break;
		case SceneId::End:
			m_SceneInstance.m_gameend->Draw();
			break;
		default:
			break;
		}
		DrawEnd();
	}
}

void SceneManager::RegisterScene()
{
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	if (m_SceneInstance .m_title != nullptr)
	{
		delete m_SceneInstance.m_title;
		m_SceneInstance.m_title = nullptr;
	}
	if (m_SceneInstance.m_help != nullptr)
	{
		delete m_SceneInstance.m_help;
		m_SceneInstance.m_help = nullptr;
	}
	if (m_SceneInstance.m_option != nullptr)
	{
		delete m_SceneInstance.m_option;
		m_SceneInstance.m_option = nullptr;
	}
	if (m_SceneInstance.m_game != nullptr)
	{
		delete m_SceneInstance.m_game;
		m_SceneInstance.m_game = nullptr;
	}
	if (m_SceneInstance.m_gameend != nullptr)
	{
		delete m_SceneInstance.m_gameend;
		m_SceneInstance.m_gameend = nullptr;
	}
	
}
