#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include"BaseScene.h"
#include"../Engine/FBX.h"
#include"../Manager/UIManager.h"
#include"../Manager/ProductionManager.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"

class GameScene : public MyBaseScene::BaseScene
{
private:
	struct GameSceneInfo{
		bool m_ClearFlag=false;
		Fbx m_fbx;
	}m_GameSceneInfo;

	SceneManager* m_scene_manager = SceneManager::Instance();
	SoundManager* m_sound_manager = SoundManager::Instance();
	UIManager* m_ui_manager = UIManager::Instance();
	ProductionManager* m_production_manager = ProductionManager::Instance();
	ObjectManager* m_object_manager = ObjectManager::Instance();

	char debugppos[50];
	char debugcamerapos[50];

public:
	GameScene();
	~GameScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

	const GameSceneInfo* GetGameSceneInfo()const { return &m_GameSceneInfo; }

private:
	void TimeattackUpdate();
	void FreemodeUpdate();
};

#endif