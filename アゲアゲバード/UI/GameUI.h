#ifndef GAME_H_
#define GAME_H_

#include <d3dx9.h>
#include "UIBase.h"
#include "../Engine/Graphics.h"
#include "../DataBank/DataBank.h"


class GameUI:public UIBase
{
public:
	GameUI();

	~GameUI() {}

	virtual void LoadTex()override;

	virtual void Draw()override;

	virtual void UpDate()override;

	virtual void ReleaseTex()override;

	void ReleaseUITexture(TEXTURE_DATA* texture);
private:
	D3DXVECTOR2 tex_pos;
	D3DXVECTOR2 player_pos;

	TEXTURE_DATA m_position;
	TEXTURE_DATA m_player_pos;
	
};

#endif