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
	m_gameuiinfo.m_Ui_pos[GameUINum::NowPosBg] = D3DXVECTOR2(1725.0f, 160.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::NowPosBg2] = D3DXVECTOR2(1750.0f, 200.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::NowPosBg3] = D3DXVECTOR2(1750.0f, 200.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::Player] = D3DXVECTOR2(1750.0f, 620.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::Block] = D3DXVECTOR2(0.0f,0.0f);

	m_gameuiinfo.m_Ui_pos[GameUINum::TimerBg] = D3DXVECTOR2(750.0f, 50.0f);

	m_gameuiinfo.m_Ui_pos[GameUINum::One_S_Timer] = D3DXVECTOR2(1030.0f, 70.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::Ten_S_Timer] = D3DXVECTOR2(980.0f, 70.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::One_M_Timer] = D3DXVECTOR2(880.0f, 70.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::Ten_M_Timer] = D3DXVECTOR2(830.0f, 70.0f);

	m_gameuiinfo.m_Ui_pos[GameUINum::Timer] = D3DXVECTOR2(930.0f, 70.0f);

	m_gameuiinfo.m_Ui_pos[GameUINum::One_Block] = D3DXVECTOR2(90.0f, 100.0f);
	m_gameuiinfo.m_Ui_pos[GameUINum::Ten_Block] = D3DXVECTOR2(45.0f, 100.0f);

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

	m_gameuiinfo.m_oneblock_tu = 0.0f;
	m_gameuiinfo.m_oneblock_tv = 0.0f;

	m_gameuiinfo.m_tenblock_tu = 0.18f;
	m_gameuiinfo.m_tenblock_tv = 0.0f;

	sprintf_s(m_gameuiinfo.m_timefont, "%d%d:%d%d", m_gameuiinfo.m_tenm, m_gameuiinfo.m_onem, m_gameuiinfo.m_tens, m_gameuiinfo.m_ones);
}

void GameUI::LoadTex()
{
	LoadTexture("Res/Tex/位置情報UI(木枠).png", &m_gameuiinfo.m_Ui[GameUINum::NowPosBg]);
	LoadTexture("Res/Tex/位置情報UI(黒).png", &m_gameuiinfo.m_Ui[GameUINum::NowPosBg2]);
	LoadTexture("Res/Tex/位置情報UI(赤).png", &m_gameuiinfo.m_Ui[GameUINum::NowPosBg3]);
	LoadTexture("Res/Tex/位置情報UI(丸).png", &m_gameuiinfo.m_Ui[GameUINum::Player]);
	LoadTexture("Res/Tex/タイムUI_02.png", &m_gameuiinfo.m_Ui[GameUINum::Timer]);
	LoadTexture("Res/Tex/ブロック個数数字UI_修正.png", &m_gameuiinfo.m_Ui[GameUINum::BlockCount]);
	LoadTexture("Res/Tex/タイム枠UI.png", &m_gameuiinfo.m_Ui[GameUINum::TimerBg]);
	LoadTexture("Res/Tex/唐揚げアイテムUI_A3.png", &m_gameuiinfo.m_Ui[GameUINum::Block]);
}

void GameUI::Draw()
{
	
	if (m_productionmanager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{

		if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
		{
			DrawUITexture(&m_gameuiinfo.m_Ui[GameUINum::TimerBg], m_gameuiinfo.m_Ui_pos[GameUINum::TimerBg]);
			DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::Timer], m_gameuiinfo.m_Ui_pos[GameUINum::One_S_Timer], 50.0f, 67.0f, m_gameuiinfo.m_ones_tu, m_gameuiinfo.m_ones_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::Timer], m_gameuiinfo.m_Ui_pos[GameUINum::Ten_S_Timer], 50.0f, 67.0f, m_gameuiinfo.m_tens_tu, m_gameuiinfo.m_tens_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::Timer], m_gameuiinfo.m_Ui_pos[GameUINum::One_M_Timer], 50.0f, 67.0f, m_gameuiinfo.m_onem_tu, m_gameuiinfo.m_onem_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::Timer], m_gameuiinfo.m_Ui_pos[GameUINum::Ten_M_Timer], 50.0f, 67.0f, m_gameuiinfo.m_tenm_tu, m_gameuiinfo.m_tenm_tv);
			DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::Timer], m_gameuiinfo.m_Ui_pos[GameUINum::Timer], 50.0f, 67.0f, 0.88f,0.0f);

		}
		DrawUITexture(&m_gameuiinfo.m_Ui[GameUINum::Block], m_gameuiinfo.m_Ui_pos[GameUINum::Block]);
		DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::BlockCount], m_gameuiinfo.m_Ui_pos[GameUINum::One_Block], 70.0f, 74.0f, m_gameuiinfo.m_oneblock_tu, m_gameuiinfo.m_oneblock_tv);
		DrawUIUVTexture(&m_gameuiinfo.m_Ui[GameUINum::BlockCount], m_gameuiinfo.m_Ui_pos[GameUINum::Ten_Block], 70.0f, 74.0f, m_gameuiinfo.m_tenblock_tu, m_gameuiinfo.m_tenblock_tv);
		//DrawFont(10, 0, m_gameuiinfo.m_stockfont, FontSize::Regular, FontColor::Black);
		//DrawUITexture(&m_gameuiinfo.m_posbg, m_gameuiinfo.playerbg_pos);
		DrawUITexture(&m_gameuiinfo.m_Ui[GameUINum::NowPosBg], m_gameuiinfo.m_Ui_pos[GameUINum::NowPosBg]);
		DrawUITexture(&m_gameuiinfo.m_Ui[GameUINum::NowPosBg2], m_gameuiinfo.m_Ui_pos[GameUINum::NowPosBg2]);
		DrawUITexture(&m_gameuiinfo.m_Ui[GameUINum::NowPosBg3], m_gameuiinfo.m_Ui_pos[GameUINum::NowPosBg3]);
		DrawUITexture(&m_gameuiinfo.m_Ui[GameUINum::Player], m_gameuiinfo.m_Ui_pos[GameUINum::Player]);
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
		m_gameuiinfo.m_Ui_pos[(int)GameUINum::Player].y = 511.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 50.0f && m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 75.0f)
	{
		m_gameuiinfo.m_Ui_pos[(int)GameUINum::Player].y = 402.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 75.0f && m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y < 100.0f)
	{
		m_gameuiinfo.m_Ui_pos[(int)GameUINum::Player].y = 293.0f;
	}
	else if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= 100.0f)
	{
		m_gameuiinfo.m_Ui_pos[(int)GameUINum::Player].y = 184.0f;
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
	/*ReleaseUITexture(&m_gameuiinfo.m_position);
	ReleaseUITexture(&m_gameuiinfo.m_player_pos);*/
}
