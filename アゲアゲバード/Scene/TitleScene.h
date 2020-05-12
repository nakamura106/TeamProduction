#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"BaseScene.h"

//ëOï˚êÈåæ


class TitleScene :public MyBaseScene::BaseScene
{
private:
	struct TitleSceneInfo
	{
		int m_now_select;
		int m_select_flag;
		int m_page;
	}m_TitleSceneInfo;

public:
	TitleScene();
	~TitleScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

	const TitleSceneInfo* GetTitleSceneInfo()const { return &m_TitleSceneInfo; }

private:

	void UpdateSelect();
	
};

#endif