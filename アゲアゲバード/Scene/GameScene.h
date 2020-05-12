#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include"BaseScene.h"
#include"../Engine/FBX.h"

class GameScene :public MyBaseScene::BaseScene
{
private:
	struct GameSceneInfo{
		bool m_ClearFlag=false;
		Fbx m_fbx;
	}m_GameSceneInfo;

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

};

#endif