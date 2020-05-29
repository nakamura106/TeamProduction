#ifndef ENDSCENE_H_
#define ENDSCENE_H_

#include"BaseScene.h"
#include"../Engine/Graphics.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/UIManager.h"

class GameEndScene :public MyBaseScene::BaseScene
{
private:
	struct GameEndSceneInfo 
	{
		D3DXVECTOR2 m_end_bg_pos;
		TEXTURE_DATA m_end;
	}m_GameEndSceneInfo;

	SceneManager* m_scene_manager=SceneManager::Instance();
	SoundManager* m_sound_manager=SoundManager::Instance();
	UIManager* m_ui_manager = UIManager::Instance();

public:
	GameEndScene();
	~GameEndScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

	const GameEndSceneInfo* GetGameEndSceneInfo()const { return &m_GameEndSceneInfo; }

};

#endif