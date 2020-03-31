#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"BaseScene.h"

class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	SceneId Init()override;
	SceneId Update()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();
};

#endif