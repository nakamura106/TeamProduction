#ifndef HELPSCENE_H_
#define HELPSCENE_H_

#include"BaseScene.h"
#include"../Engine/Graphics.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"


class HelpScene :public MyBaseScene::BaseScene
{
private:
	struct HelpSceneInfo  {
		int m_help_flag;
		D3DXVECTOR2 m_help_bg_pos;
		TEXTURE_DATA m_help;
	}m_HelpSceneInfo;

	SceneManager* m_scene_manager = SceneManager::Instance();
	SoundManager* m_sound_manager = SoundManager::Instance();

public:
	HelpScene();
	~HelpScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

	const HelpSceneInfo* GetHelpSceneInfo()const { return &m_HelpSceneInfo; }
	
};

#endif