#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include"BaseScene.h"

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
};

#endif