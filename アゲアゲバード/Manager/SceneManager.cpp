#include "SceneManager.h"
#include"../Scene/TitleScene.h"
#include"../Scene/HelpScene.h"
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
	m_Scene.push_back(new TitleScene);
	m_Scene.push_back(new HelpScene);
	m_Scene.push_back(new GameScene);
	m_Scene.push_back(new GameEndScene);
}

void SceneManager::Update()
{
	UpdateInput();
	KeyStateUpdate();

		switch (m_current_scene_id)
		{
		case BaseScene::SceneId::Title:
			m_Scene[0]->Update();
			break;
		case BaseScene::SceneId::Help:
			m_Scene[1]->Update();
			break;
		case BaseScene::SceneId::Game:
			m_Scene[2]->Update();
			break;
		case BaseScene::SceneId::End:
			m_Scene[3]->Update();
			break;
		default:
			break;
	}
}

void SceneManager::Draw()
{
	if (m_current_scene_step == BaseScene::SceneStep::MainStep)
	{
		DrawStart();

		SetRenderMode(ERenderMode::Normal, true);

		GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		
		SetLight();

		switch (m_current_scene_id)
		{
		case BaseScene::SceneId::Title:
			m_Scene[0]->Draw();
			break;
		case BaseScene::SceneId::Help:
			m_Scene[1]->Draw();
			break;
		case BaseScene::SceneId::Game:
			m_Scene[2]->Draw();
			break;
		case BaseScene::SceneId::End:
			m_Scene[3]->Draw();
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

void SceneManager::SetSceneId(BaseScene::SceneId sceneid_)
{
	m_current_scene_id = sceneid_;
}

void SceneManager::SetSceneStep(BaseScene::SceneStep scenestep_)
{
	m_current_scene_step = scenestep_;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (int i=0;m_Scene.size();i++)
	{
		delete m_Scene[i];
		m_Scene[i] = nullptr;
	}
}
