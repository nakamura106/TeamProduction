#include "GameUI.h"
#include"../Production/StartProduction.h"
#include"../Scene/TitleScene.h"
#include"../UI/TitleUI.h"
#include <iostream>
#include <fstream>

void GameUI::Init()
{
	m_gameuiinfo.tex_pos = D3DXVECTOR2(1800.0f, 200.0f);

	m_gameuiinfo.player_pos= D3DXVECTOR2(1795.0f, 690.0f);

	m_gameuiinfo.one_s_timer_pos= D3DXVECTOR2(950.0f, 50.0f);

	m_gameuiinfo.ten_s_timer_pos=D3DXVECTOR2(900.0f, 50.0f);

	m_gameuiinfo.one_m_timer_pos= D3DXVECTOR2(800.0f, 50.0f);

	m_gameuiinfo.ten_m_timer_pos= D3DXVECTOR2(750.0f, 50.0f);

	m_gameuiinfo.timer_pos = D3DXVECTOR2(850.0f, 50.0f);


	m_gameuiinfo.m_ones_tu = 0.0f;
	m_gameuiinfo.m_ones_tv = 0.0f;

	m_gameuiinfo.m_tens_tu = 0.0f;
	m_gameuiinfo.m_tens_tv = 0.0f;

	m_gameuiinfo.m_onem_tu = 0.0f;
	m_gameuiinfo.m_onem_tv = 0.0f;

	m_gameuiinfo.m_tenm_tu = 0.0f;
	m_gameuiinfo.m_tenm_tv = 0.0f;

	m_gameuiinfo.timercounter = 0;

	m_gameuiinfo.m_ones = 0;
	m_gameuiinfo.m_tens = 0;
	m_gameuiinfo.m_onem = 0;
	m_gameuiinfo.m_tenm = 0;

	sprintf_s(m_gameuiinfo.m_timefont, "%d%d:%d%d", m_gameuiinfo.m_tenm, m_gameuiinfo.m_onem, m_gameuiinfo.m_tens, m_gameuiinfo.m_ones);

	
}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/UI位置情報(黒)(サイズ修正).png", &m_gameuiinfo.m_position);
	LoadTexture("Res/Tex/UI位置情報(丸)(サイズ修正).png", &m_gameuiinfo.m_player_pos);
	LoadTexture("Res/Tex/タイムUI.png", &m_gameuiinfo.m_timer);
}

void GameUI::Draw()
{
	
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		
		if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
		{
			//DrawFont(1000, 0, m_gameuiinfo.m_timefont, FontSize::Regular, FontColor::Red);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.one_s_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_ones_tu, m_gameuiinfo.m_ones_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.ten_s_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_tens_tu, m_gameuiinfo.m_tens_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.one_m_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_onem_tu, m_gameuiinfo.m_onem_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.ten_m_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_tenm_tu, m_gameuiinfo.m_tenm_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.timer_pos, 50.0f, 67.0f, 0.88f,0.0f);

		}
		DrawFont(10, 0, m_gameuiinfo.m_stockfont, FontSize::Regular, FontColor::Black);
		DrawUITexture(&m_gameuiinfo.m_position, m_gameuiinfo.tex_pos);
		DrawUITexture(&m_gameuiinfo.m_player_pos, m_gameuiinfo.player_pos);
	}
}

void GameUI::UpDate()
{
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		UpDateTimer();
		UpDateTimer2();
	}
	UpDatePlayerPos();
	ConversionBlockStock();
}

void GameUI::UpDateTimer()
{
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		m_gameuiinfo.timercounter++;
	}
	//1秒
	if (m_gameuiinfo.timercounter == 60)
	{
		m_gameuiinfo.m_ones_tu += 0.09f;
		m_gameuiinfo.timercounter = 0;
	}
	//10秒
	if (m_gameuiinfo.m_ones_tu >= 0.9f)
	{
		m_gameuiinfo.m_ones_tu = 0;
		m_gameuiinfo.m_tens_tu += 0.09f;
	}
	//1分
	if (m_gameuiinfo.m_tens_tu >= 0.6f)
	{
		m_gameuiinfo.m_tens_tu = 0;
		m_gameuiinfo.m_onem_tu += 0.09f;
	}
	//10分
	if (m_gameuiinfo.m_onem_tu >= 0.9f)
	{
		m_gameuiinfo.m_onem_tu = 0;
		m_gameuiinfo.m_tenm_tu += 0.09f;
	}
}

void GameUI::UpDateTimer2()
{
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		m_gameuiinfo.timercounter2++;
	}

	if (m_gameuiinfo.timercounter2 == 60)
	{
		m_gameuiinfo.m_ones++;
		m_gameuiinfo.timercounter2 = 0;
	}
	if (m_gameuiinfo.m_ones == 10)
	{
		m_gameuiinfo.m_tens++;
		m_gameuiinfo.m_ones = 0;
	}
	if (m_gameuiinfo.m_tens == 6)
	{
		m_gameuiinfo.m_onem++;
		m_gameuiinfo.m_tens = 0;
	}
	if (m_gameuiinfo.m_onem == 10)
	{
		m_gameuiinfo.m_tenm++;
		m_gameuiinfo.m_onem = 0;
	}

	sprintf_s(m_gameuiinfo.m_timefont, "%d%d:%d%d", m_gameuiinfo.m_tenm, m_gameuiinfo.m_onem, m_gameuiinfo.m_tens, m_gameuiinfo.m_ones);
}

void GameUI::UpDatePlayerPos()
{
	if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 25.0f&& m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 50.0f)
	{
		m_gameuiinfo.player_pos.y = 581.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 50.0f && m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 75.0f)
	{
		m_gameuiinfo.player_pos.y = 472.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 75.0f && m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 100.0f)
	{
		m_gameuiinfo.player_pos.y = 363.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 100.0f)
	{
		m_gameuiinfo.player_pos.y = 254.0f;
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

	if (m_gameuiinfo.player_pos.y >= 700.0f)
	{
		m_gameuiinfo.player_pos.y = 700.0f;
	}
}

void GameUI::ConversionBlockStock()
{
	
	sprintf_s(m_gameuiinfo.m_stockfont, "%d", m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_blockstock);

}



void GameUI::ReleaseTex()
{
	ReleaseUITexture(&m_gameuiinfo.m_position);
	ReleaseUITexture(&m_gameuiinfo.m_player_pos);
}
