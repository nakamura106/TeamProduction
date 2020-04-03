#ifndef GAME_H_
#define GAME_H_

#include <d3dx9.h>
#include "../Engine/Graphics.h"
#include "UIBase.h"

class GameUI:public UIBase
{
public:
	GameUI();

	~GameUI() {}

	virtual void LoadTex()override;

	virtual void Draw()override;

	virtual void UpDate()override;

	virtual void Release()override;
private:
	D3DXVECTOR2 tex_pos;
	D3DXVECTOR2 player_pos;

	TEXTURE_DATA m_position;
	TEXTURE_DATA m_player_pos;
	
};

#endif