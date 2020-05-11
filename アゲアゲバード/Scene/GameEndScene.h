#ifndef ENDSCENE_H_
#define ENDSCENE_H_

#include"BaseScene.h"
#include"../Engine/Graphics.h"

class GameEndScene :public BaseScene
{
private:
	struct GameEndSceneInfo 
	{
		D3DXVECTOR2 m_end_bg_pos;
		TEXTURE_DATA m_end;
	}m_GameEndSceneInfo;

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