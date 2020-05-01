#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"BaseScene.h"
#include"../Engine/Graphics.h"
#include"../UI/TitleUI.h"

class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

private:
	void UpdateSelect();

	int m_select_flag;


	

};

#endif