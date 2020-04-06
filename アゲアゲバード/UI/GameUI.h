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

	void UpDateTimer();

	virtual void ReleaseTex()override;

	void ReleaseUITexture(TEXTURE_DATA* texture);
private:
	int timercounter;
	int time;

	float m_ones_tu;
	float m_ones_tv;

	float m_tens_tu;
	float m_tens_tv;

	float m_onem_tu;
	float m_onem_tv;

	float m_tenm_tu;
	float m_tenm_tv;


	D3DXVECTOR2 tex_pos;
	D3DXVECTOR2 player_pos;
	D3DXVECTOR2 one_s_timer_pos;
	D3DXVECTOR2 ten_s_timer_pos;

	D3DXVECTOR2 one_m_timer_pos;
	D3DXVECTOR2 ten_m_timer_pos;

	
	TEXTURE_DATA m_position;
	TEXTURE_DATA m_player_pos;
	TEXTURE_DATA m_timer;

	
};

#endif