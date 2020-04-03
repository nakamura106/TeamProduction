#include "GameUI.h"

GameUI::GameUI()
{
	tex_pos.x = 1800.0f;
	tex_pos.y = 0.0f;

	player_pos.x = 1800.0f;
	player_pos.y = 0.0f;

}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/現在位置.png", &m_position);
	LoadTexture("Res/Tex/プレイヤー位置.png", &m_player_pos);
}

void GameUI::Draw()
{
	DrawUITexture(&m_position, tex_pos);
	DrawUITexture(&m_player_pos, player_pos);
}

void GameUI::UpDate()
{
	player_pos.y++;
	tex_pos.y++;
	if (player_pos.y == 500.0f)
	{
		player_pos.y = 500.0f;
	}
}

void GameUI::Release()
{
	ReleaseTexture(&m_position);
	ReleaseTexture(&m_player_pos);

}