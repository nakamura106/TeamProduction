#include "GameUI.h"
#include <iostream>
#include <fstream>

GameUI::GameUI()
{
	tex_pos.x = 1800.0f;
	tex_pos.y = 0.0f;

	player_pos.x = 1805.0f;
	player_pos.y = 700.0f;

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

	m_ones = 0;
	m_tens = 0;
	m_onem = 0;
	m_tenm = 0;
}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/UI位置情報_空ゲージ.png", &m_position);
	LoadTexture("Res/Tex/UI位置情報_現在位置B.png", &m_player_pos);
	LoadTexture("Res/Tex/timer.png", &m_timer);
}

void GameUI::LoadFile()
{
	//m_filename = "Res/Tex/text.txt";

	/*std::ifstream ifs(m_filename, std::ios::in);
	if (!ifs) {
		std::cerr << "ファイルオープンに失敗" << std::endl;
		std::exit(1);
	}
	std::string buf;
	std::getline(ifs, buf);
	ifs >> buf;
	if (!ifs) {
		std::cerr << "読み込みに失敗" << std::endl;
		std::exit(1);
	}*/
	//std::cout << m_filename << "に書き込みました。" << std::endl;

	//std::cout << buf << std::endl;
}

void GameUI::Draw()
{
	DrawUITexture(&m_position, tex_pos);
	DrawUITexture(&m_player_pos, player_pos);
	/*DrawUVTexture(&m_timer, one_s_timer_pos, 50.0f, 100.0f, m_ones_tu, m_ones_tv);
	DrawUVTexture(&m_timer, ten_s_timer_pos, 50.0f, 100.0f, m_tens_tu, m_tens_tv);
	DrawUVTexture(&m_timer, one_m_timer_pos, 50.0f, 100.0f, m_onem_tu, m_onem_tv);
	DrawUVTexture(&m_timer, ten_m_timer_pos, 50.0f, 100.0f, m_tenm_tu, m_tenm_tv);*/

	DrawFont(1000, 0, m_timefont, FontSize::Regular, FontColor::Red);
}

void GameUI::UpDate()
{
	UpDateTimer();
	UpDatePlayerPos();
}

//void GameUI::UpDateTimer()
//{
//	timercounter++;
//	//1秒
//	if (timercounter == 60)
//	{
//		m_ones_tu += 0.1f;
//		timercounter = 0;
//	}
//	//10秒
//	if (m_ones_tu >= 1.0f)
//	{
//		m_ones_tu = 0;
//		m_tens_tu += 0.1f;
//	}
//	//1分
//	if (m_tens_tu >= 0.6f)
//	{
//		m_tens_tu = 0;
//		m_onem_tu += 0.1f;
//	}
//	//10分
//	if (m_onem_tu >= 1.0f)
//	{
//		m_onem_tu = 0;
//		m_tenm_tu += 0.1f;
//	}
//
//	
//}

void GameUI::UpDateTimer()
{

	timercounter++;

	if (timercounter == 60)
	{
		m_ones++;
		timercounter = 0;
	}
	if (m_ones == 10)
	{
		m_tens++;
		m_ones = 0;
	}
	if (m_tens == 6)
	{
		m_onem++;
		m_tens = 0;
	}
	if (m_onem == 10)
	{
		m_tenm++;
		m_onem = 0;
	}

	sprintf_s(m_timefont, "%d%d:%d%d", m_tenm, m_onem, m_tens, m_ones);
}

void GameUI::UpDatePlayerPos()
{
	if (DataBank::Instance()->GetAfterPlayerPos().y >= 25.0f&& DataBank::Instance()->GetAfterPlayerPos().y < 50.0f)
	{
		player_pos.y = 525.0f;
	}
	else if (DataBank::Instance()->GetAfterPlayerPos().y >= 50.0f && DataBank::Instance()->GetAfterPlayerPos().y < 75.0f)
	{
		player_pos.y = 350.0f;
	}
	else if (DataBank::Instance()->GetAfterPlayerPos().y >= 75.0f && DataBank::Instance()->GetAfterPlayerPos().y < 100.0f)
	{
		player_pos.y = 175.0f;
	}
	else if (DataBank::Instance()->GetAfterPlayerPos().y >= 100.0f)
	{
		player_pos.y = 0.0f;
	}
	////プレイヤーのoldposとposを比較して+なら+
	//if (DataBank::Instance()->GetBeforePlayerPos().y < DataBank::Instance()->GetAfterPlayerPos().y)
	//{
	//	player_pos.y -= 1.0f;
	//}
	//else if (DataBank::Instance()->GetBeforePlayerPos().y > DataBank::Instance()->GetAfterPlayerPos().y)
	//{
	//	player_pos.y += 1.4f;
	//}
	//else
	//{
	//	player_pos.y += 0.0f;
	//}

	if (player_pos.y >= 700.0f)
	{
		player_pos.y = 700.0f;
	}
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
