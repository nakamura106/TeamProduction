#include "GameUI.h"

GameUI::GameUI()
{
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;

	player_pos.x = 0.0f;
	player_pos.y = 0.0f;

}

void GameUI::LoadTex()
{
	LoadTexture("���݈ʒu.png", &m_position);
	LoadTexture("�v���C���[�ʒu.png", &m_player_pos);
}

void GameUI::Draw()
{
	DrawUITexture(&m_position, tex_pos);
	DrawUITexture(&m_player_pos, player_pos);
}

void GameUI::UpDate()
{
	player_pos.y++;
	if (player_pos.y == 500.0f)
	{
		player_pos.y = 500.0f;
	}
}