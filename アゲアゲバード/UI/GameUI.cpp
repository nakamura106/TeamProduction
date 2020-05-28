#include "GameUI.h"
#include"../Production/StartProduction.h"
#include"../Scene/TitleScene.h"
#include"../UI/TitleUI.h"
#include <iostream>
#include <fstream>

GameUI::GameUI()
{
}

void GameUI::Init()
{
	tex_pos = D3DXVECTOR2(1800.0f, 200.0f);

	player_pos= D3DXVECTOR2(1795.0f, 690.0f);

	one_s_timer_pos= D3DXVECTOR2(950.0f, 50.0f);

	ten_s_timer_pos=D3DXVECTOR2(900.0f, 50.0f);

	one_m_timer_pos= D3DXVECTOR2(850.0f, 50.0f);

	ten_m_timer_pos= D3DXVECTOR2(800.0f, 50.0f);

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

	sprintf_s(m_timefont, "%d%d:%d%d", m_tenm, m_onem, m_tens, m_ones);

	
}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/UI�ʒu���(��)(�T�C�Y�C��).png", &m_position);
	LoadTexture("Res/Tex/UI�ʒu���(��)(�T�C�Y�C��).png", &m_player_pos);
	LoadTexture("Res/Tex/timer.png", &m_timer);
}

void GameUI::LoadFile()
{
	//m_filename = "Res/Tex/text.txt";

	/*std::ifstream ifs(m_filename, std::ios::in);
	if (!ifs) {
		std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		std::exit(1);
	}
	std::string buf;
	std::getline(ifs, buf);
	ifs >> buf;
	if (!ifs) {
		std::cerr << "�ǂݍ��݂Ɏ��s" << std::endl;
		std::exit(1);
	}*/
	//std::cout << m_filename << "�ɏ������݂܂����B" << std::endl;

	//std::cout << buf << std::endl;
}

//void GameUI::Init()
//{
//	m_onem = 0;
//	m_ones = 0;
//	m_tenm = 0;
//	m_tens = 0;
//}

void GameUI::Draw()
{
	
		if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
		{
			
			if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUi::Select::Timeattack)
			{
				DrawFont(1000, 0, m_timefont, FontSize::Regular, FontColor::Red);
			}
			DrawFont(10, 0, m_stockfont, FontSize::Regular, FontColor::Black);
			DrawUITexture(&m_position, tex_pos);
			DrawUITexture(&m_player_pos, player_pos);
		}
	

	/*DrawUVTexture(&m_timer, one_s_timer_pos, 50.0f, 100.0f, m_ones_tu, m_ones_tv);
	DrawUVTexture(&m_timer, ten_s_timer_pos, 50.0f, 100.0f, m_tens_tu, m_tens_tv);
	DrawUVTexture(&m_timer, one_m_timer_pos, 50.0f, 100.0f, m_onem_tu, m_onem_tv);
	DrawUVTexture(&m_timer, ten_m_timer_pos, 50.0f, 100.0f, m_tenm_tu, m_tenm_tv);*/
}

void GameUI::UpDate()
{
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUi::Select::Timeattack)
	{
		UpDateTimer();
	}
	UpDatePlayerPos();
	ConversionBlockStock();
}

//void GameUI::UpDateTimer()
//{
//	timercounter++;
//	//1�b
//	if (timercounter == 60)
//	{
//		m_ones_tu += 0.1f;
//		timercounter = 0;
//	}
//	//10�b
//	if (m_ones_tu >= 1.0f)
//	{
//		m_ones_tu = 0;
//		m_tens_tu += 0.1f;
//	}
//	//1��
//	if (m_tens_tu >= 0.6f)
//	{
//		m_tens_tu = 0;
//		m_onem_tu += 0.1f;
//	}
//	//10��
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
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		timercounter++;
	}

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
	if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 25.0f&& m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 50.0f)
	{
		player_pos.y = 581.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 50.0f && m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 75.0f)
	{
		player_pos.y = 472.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 75.0f && m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 100.0f)
	{
		player_pos.y = 363.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 100.0f)
	{
		player_pos.y = 254.0f;
	}
	////�v���C���[��oldpos��pos���r����+�Ȃ�+
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

void GameUI::ConversionBlockStock()
{
	
	sprintf_s(m_stockfont, "%d", m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_blockstock);

}



void GameUI::ReleaseTex()
{
	ReleaseUITexture(&m_position);
	ReleaseUITexture(&m_player_pos);
}
