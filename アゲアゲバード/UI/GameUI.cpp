#include "GameUI.h"

GameUI::GameUI()
{
	tex_pos.x = 1800.0f;
	tex_pos.y = 400.0f;

	player_pos.x = 1800.0f;
	player_pos.y = 900.0f;

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
	/*if (player_pos.y += 80.0f)
	{
		player_pos.y-=10.0f;
	}
	
	if (player_pos.y >= 0.0f)
	{
		player_pos.y = 0.0f;
	}*/
}

void GameUI::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != NULL)
	{
		texture->Texture->Release();
		texture->Texture = NULL;
	}
}

void GameUI::ReleaseTex()
{
	ReleaseUITexture(&m_position);
	ReleaseUITexture(&m_player_pos);

}
