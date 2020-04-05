#ifndef HELPSCENE_H_
#define HELPSCENE_H_

#include"BaseScene.h"
#include"../Engine/Graphics.h"

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

private:
	int m_help_flag;
	D3DXVECTOR2 m_help_bg_pos;
	TEXTURE_DATA m_help1;
	TEXTURE_DATA m_help2;
	TEXTURE_DATA m_help3;
};

#endif