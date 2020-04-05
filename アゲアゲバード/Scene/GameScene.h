#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include"BaseScene.h"
#include"../Engine/FBX.h"

class GameScene :public BaseScene
{
public:
	GameScene();
	~GameScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

private:
	Fbx m_fbx;
};

#endif