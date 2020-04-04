#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"BaseScene.h"
#include"../Engine/Graphics.h"

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
	int m_select_flag;
	D3DXVECTOR2 m_title_bg_pos;
	TEXTURE_DATA m_title;
	TEXTURE_DATA m_help;
};

#endif