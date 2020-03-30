#ifndef GAME_H_
#define GAME_H_

#include <d3dx9.h>
#include "../Engine/Graphics.h"

class GameUI
{
public:
	GameUI(){}
	~GameUI() {}

private:
	D3DXVECTOR2 tex_pos;
	D3DXVECTOR2 player_pos;

};

#endif