#include "GameUI.h"
#include"../Production/StartProduction.h"
#include"../Manager/ObjectManager.h"
#include"../Scene/TitleScene.h"
#include"../UI/TitleUI.h"
#include "../Player/Player.h"
#include <iostream>
#include <fstream>

void GameUI::Init()
{
	m_gameuiinfo.tex_pos = D3DXVECTOR2(1780.0f, 270.0f);
	m_gameuiinfo.player_pos= D3DXVECTOR2(1780.0f, 690.0f);
	m_gameuiinfo.playerbg_pos = D3DXVECTOR2(1750.0f, 200.0f);

	m_gameuiinfo.timerbg_pos = D3DXVECTOR2(750.0f, 50.0f);

	m_gameuiinfo.one_s_timer_pos= D3DXVECTOR2(1030.0f, 70.0f);
	m_gameuiinfo.ten_s_timer_pos=D3DXVECTOR2(980.0f, 70.0f);
	m_gameuiinfo.one_m_timer_pos= D3DXVECTOR2(880.0f, 70.0f);
	m_gameuiinfo.ten_m_timer_pos= D3DXVECTOR2(830.0f, 70.0f);

	m_gameuiinfo.timer_pos = D3DXVECTOR2(930.0f, 70.0f);

	m_gameuiinfo.one_block_pos = D3DXVECTOR2(45.0f, 0.0f);
	m_gameuiinfo.ten_block_pos = D3DXVECTOR2(0.0f, 0.0f);

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

	m_gameuiinfo.m_oneblock_tu = 0.0f;
	m_gameuiinfo.m_oneblock_tv = 0.0f;

	m_gameuiinfo.m_tenblock_tu = 0.18f;
	m_gameuiinfo.m_tenblock_tv = 0.0f;
}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/ˆÊ’uî•ñUI(•).png", &m_gameuiinfo.m_position);
	LoadTexture("Res/Tex/ˆÊ’uî•ñUI(ŠÛ).png", &m_gameuiinfo.m_player_pos);
	LoadTexture("Res/Tex/ˆÊ’uî•ñUI(–Ø˜g).png", &m_gameuiinfo.m_posbg);
	LoadTexture("Res/Tex/ƒ^ƒCƒ€UI_02.png", &m_gameuiinfo.m_timer);
	LoadTexture("Res/Tex/ƒ^ƒCƒ€˜gUI.png", &m_gameuiinfo.m_timerbg);


}

void GameUI::Draw()
{
	
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		
		if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
		{
			DrawUITexture(&m_gameuiinfo.m_timerbg, m_gameuiinfo.timerbg_pos);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.one_s_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_ones_tu, m_gameuiinfo.m_ones_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.ten_s_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_tens_tu, m_gameuiinfo.m_tens_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.one_m_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_onem_tu, m_gameuiinfo.m_onem_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.ten_m_timer_pos, 50.0f, 67.0f, m_gameuiinfo.m_tenm_tu, m_gameuiinfo.m_tenm_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.timer_pos, 50.0f, 67.0f, 0.88f,0.0f);

		}
		DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.one_block_pos, 50.0f, 67.0f, m_gameuiinfo.m_oneblock_tu, m_gameuiinfo.m_oneblock_tv);
		DrawUIUVTexture(&m_gameuiinfo.m_timer, m_gameuiinfo.ten_block_pos, 50.0f, 67.0f, m_gameuiinfo.m_tenblock_tu, m_gameuiinfo.m_tenblock_tv);
		DrawUITexture(&m_gameuiinfo.m_position, m_gameuiinfo.tex_pos);
		DrawUITexture(&m_gameuiinfo.m_player_pos, m_gameuiinfo.player_pos);
	}
}

void GameUI::UpDate()
{
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		UpDateTimer();
		UpDateTimer2();
	}
	UpDatePlayerPos();
	ConversionBlockStock();
}

void GameUI::UpDateTimer()
{
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true
		&& ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_pos.y <= 100.0f)
	{
		m_gameuiinfo.timercounter++;
	}
	
	//1•b
	if (m_gameuiinfo.timercounter == 60)
	{
		m_gameuiinfo.m_ones_tu += 0.09f;
		m_gameuiinfo.timercounter = 0;
	}
	//10•b
	if (m_gameuiinfo.m_ones_tu >= 0.9f)
	{
		m_gameuiinfo.m_ones_tu = 0;
		m_gameuiinfo.m_tens_tu += 0.09f;
	}
	//1•ª
	if (m_gameuiinfo.m_tens_tu >= 0.6f)
	{
		m_gameuiinfo.m_tens_tu = 0;
		m_gameuiinfo.m_onem_tu += 0.09f;
	}
	//10•ª
	if (m_gameuiinfo.m_onem_tu >= 0.9f)
	{
		m_gameuiinfo.m_onem_tu = 0;
		m_gameuiinfo.m_tenm_tu += 0.09f;
	}
}

void GameUI::UpDateTimer2()
{
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true
		&& ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_pos.y <= 100.0f)
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
	
	if (m_gameuiinfo.player_pos.y >= 700.0f)
	{
		m_gameuiinfo.player_pos.y = 700.0f;
	}
}

void GameUI::ConversionBlockStock()
{
	sprintf_s(m_gameuiinfo.m_stockfont, "%d", m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_blockstock);
	
	if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_blockstock >= 10)
	{
		if (m_gameuiinfo.m_stockfont[0] == '0')
		{
			m_gameuiinfo.m_tenblock_tu = 0.0f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '1')
		{
			m_gameuiinfo.m_tenblock_tu = 0.09f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '2')
		{
			m_gameuiinfo.m_tenblock_tu = 0.18f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '3')
		{
			m_gameuiinfo.m_tenblock_tu = 0.27f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '4')
		{
			m_gameuiinfo.m_tenblock_tu = 0.36f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '5')
		{
			m_gameuiinfo.m_tenblock_tu = 0.45f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '6')
		{
			m_gameuiinfo.m_tenblock_tu = 0.54f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '7')
		{
			m_gameuiinfo.m_tenblock_tu = 0.63f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '8')
		{
			m_gameuiinfo.m_tenblock_tu = 0.72f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '9')
		{
			m_gameuiinfo.m_tenblock_tu = 0.81f;
		}

		if (m_gameuiinfo.m_stockfont[1] == '0')
		{
			m_gameuiinfo.m_oneblock_tu = 0.0f;

		}
		else if (m_gameuiinfo.m_stockfont[1] == '1')
		{
			m_gameuiinfo.m_oneblock_tu = 0.09f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '2')
		{
			m_gameuiinfo.m_oneblock_tu = 0.18f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '3')
		{
			m_gameuiinfo.m_oneblock_tu = 0.27f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '4')
		{
			m_gameuiinfo.m_oneblock_tu = 0.36f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '5')
		{
			m_gameuiinfo.m_oneblock_tu = 0.45f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '6')
		{
			m_gameuiinfo.m_oneblock_tu = 0.54f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '7')
		{
			m_gameuiinfo.m_oneblock_tu = 0.63f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '8')
		{
			m_gameuiinfo.m_oneblock_tu = 0.72f;
		}
		else if (m_gameuiinfo.m_stockfont[1] == '9')
		{
			m_gameuiinfo.m_oneblock_tu = 0.81f;
		}
	}
	else
	{
		m_gameuiinfo.m_tenblock_tu = 0.0f;

		if (m_gameuiinfo.m_stockfont[0] == '0')
		{
			m_gameuiinfo.m_oneblock_tu = 0.0f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '1')
		{
			m_gameuiinfo.m_oneblock_tu = 0.09f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '2')
		{
			m_gameuiinfo.m_oneblock_tu = 0.18f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '3')
		{
			m_gameuiinfo.m_oneblock_tu = 0.27f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '4')
		{
			m_gameuiinfo.m_oneblock_tu = 0.36f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '5')
		{
			m_gameuiinfo.m_oneblock_tu = 0.45f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '6')
		{
			m_gameuiinfo.m_oneblock_tu = 0.54f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '7')
		{
			m_gameuiinfo.m_oneblock_tu = 0.63f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '8')
		{
			m_gameuiinfo.m_oneblock_tu = 0.72f;
		}
		else if (m_gameuiinfo.m_stockfont[0] == '9')
		{
			m_gameuiinfo.m_oneblock_tu = 0.81f;
		}
	}
}



void GameUI::ReleaseTex()
{
	ReleaseUITexture(&m_gameuiinfo.m_position);
	ReleaseUITexture(&m_gameuiinfo.m_player_pos);
}
