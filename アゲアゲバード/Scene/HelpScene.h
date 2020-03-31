#ifndef HELPSCENE_H_
#define HELPSCENE_H_

#include"../Scene/BaseScene.h"

class HelpScene :public BaseScene
{
public:
	HelpScene();
	~HelpScene();

	SceneId Init()override;
	SceneId Update()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();
};

#endif