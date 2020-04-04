#ifndef HELPSCENE_H_
#define HELPSCENE_H_

#include"BaseScene.h"

class HelpScene :public BaseScene
{
public:
	HelpScene();
	~HelpScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();
};

#endif