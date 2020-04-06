#include "GameUI.h"

GameUI::GameUI()
{
	tex_pos.x = 1800.0f;
	tex_pos.y = 400.0f;

	player_pos.x = 1800.0f;
	player_pos.y = 900.0f;

	one_s_timer_pos.x = 950.0f;
	one_s_timer_pos.y = 50.0f;

	ten_s_timer_pos.x = 900.0f;
	ten_s_timer_pos.y = 50.0f;

	one_m_timer_pos.x = 850.0f;
	one_m_timer_pos.y = 50.0f;

	ten_m_timer_pos.x = 800.0f;
	ten_m_timer_pos.y = 50.0f;

	m_ones_tu = 0.0f;
	m_ones_tv = 0.0f;

	m_tens_tu = 0.0f;
	m_tens_tv = 0.0f;

	m_onem_tu = 0.0f;
	m_onem_tv = 0.0f;

	m_tenm_tu = 0.0f;
	m_tenm_tv = 0.0f;

	timercounter = 0;
}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/現在位置.png", &m_position);
	LoadTexture("Res/Tex/プレイヤー位置.png", &m_player_pos);
	LoadTexture("Res/Tex/timer.png", &m_timer);
	/*for (int i = 0; i < 10; i++)
	{
		LoadTexture("Res/Tex/プレイヤー位置.png", &m_timer[i]);
	}*/
}

void GameUI::Draw()
{
	DrawUITexture(&m_position, tex_pos);
	DrawUITexture(&m_player_pos, player_pos);
	DrawUVTexture(&m_timer, one_s_timer_pos, 50.0f, 100.0f, m_ones_tu, m_ones_tv);
	DrawUVTexture(&m_timer, ten_s_timer_pos, 50.0f, 100.0f, m_tens_tu, m_tens_tv);
	DrawUVTexture(&m_timer, one_m_timer_pos, 50.0f, 100.0f, m_onem_tu, m_onem_tv);
	DrawUVTexture(&m_timer, ten_m_timer_pos, 50.0f, 100.0f, m_tenm_tu, m_tenm_tv);
}

void GameUI::UpDate()
{
	UpDateTimer();
	//プレイヤーのoldposとposを比較して+なら+
	//if (player_pos.y += 80.0f)
	//{
	//	player_pos.y-=10.0f;
	//}
	//
	//if (player_pos.y >= 0.0f)
	//{
	//	player_pos.y = 0.0f;
	//}
}

void GameUI::UpDateTimer()
{
	timercounter++;
	//1秒
	if (timercounter == 60)
	{
		m_ones_tu += 0.1f;
		timercounter = 0;
	}
	//10秒
	if (m_ones_tu >= 1.0f)
	{
		m_ones_tu = 0;
		m_tens_tu += 0.1f;
	}
	//1分
	if (m_tens_tu >= 0.6f)
	{
		m_tens_tu = 0;
		m_onem_tu += 0.1f;
	}
	//10分
	if (m_onem_tu >= 1.0f)
	{
		m_onem_tu = 0;
		m_tenm_tu += 0.1f;
	}

	/*if (m_tenm_tu == 1.0f)
	{

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
