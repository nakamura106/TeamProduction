#ifndef ENDSCENE_H_
#define ENDSCENE_H_

#include"BaseScene.h"

class GameEndScene :public BaseScene
{
public:
	GameEndScene();
	~GameEndScene();

	SceneId Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();
};

#endif