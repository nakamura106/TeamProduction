#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"BaseScene.h"
#include"../Manager/UIManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"

//‘O•ûéŒ¾

class TitleScene :public MyBaseScene::BaseScene
{
private:
	struct TitleSceneInfo
	{
		int m_now_select;
		int m_select_flag;
		int m_page;
	}m_TitleSceneInfo;

	SceneManager* m_scene_manager = SceneManager::Instance();
	SoundManager* m_sound_manager = SoundManager::Instance();
	UIManager* m_ui_manager= UIManager::Instance();

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