#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include"../Scene/BaseScene.h"
#include<map>
#include<string>

//ëOï˚êÈåæ
class TitleScene;
class HelpScene;
class GameScene;
class GameEndScene;
class OptionScene;

enum class SceneId
{
	Title,
	Help,
	Option,
	Game,
	End,
	Max
};
enum class SceneStep
{
	InitStep,
	MainStep,
	EndStep,
};
class SceneManager
{
private:
	static SceneManager* p_instance;

	struct SceneInfo
	{
		SceneId m_CurrentSceneID=SceneId::Title;

		SceneStep m_CurrentSceneStep=SceneStep::InitStep;
	}m_SceneInfo;

	struct SceneInstance
	{
		TitleScene* m_title;
		GameScene* m_game;
		GameEndScene* m_gameend;
		HelpScene* m_help;
		OptionScene* m_option;
	}m_SceneInstance;
	

public:
	static SceneManager* Instance();

	void Init();

	void Update();
	void Draw();
	void RegisterScene();

	SceneInfo* SetSceneInfo() { return &m_SceneInfo; }

	const SceneInfo* GetSceneInfo()const { return &m_SceneInfo; }
	const GameScene* GetGameScene()const { return m_SceneInstance.m_game; }
	const TitleScene* GetTitleScene()const { return m_SceneInstance.m_title; }
	const OptionScene* GetOptionScene()const { return m_SceneInstance.m_option; }
	
protected:
	SceneManager();
	~SceneManager();


};


#endif // !SCENEMANAGER_H_
