#include "StartProduction.h"
#include "../DataBank/DataBank.h"
#include "../Manager/SoundManager.h"

void StartProduction::Init()
{
	m_ProductionInfo.m_t_three_pos.x = 900.0f;
	m_ProductionInfo.m_t_three_pos.y = 450.0f;

	m_ProductionInfo.m_t_two_pos.x = 900.0f;
	m_ProductionInfo.m_t_two_pos.y = 450.0f;

	m_ProductionInfo.m_t_one_pos.x = 900.0f;
	m_ProductionInfo.m_t_one_pos.y = 450.0f;

	m_ProductionInfo.m_start_pos.x = 800.0f;
	m_ProductionInfo.m_start_pos.y = 500.0f;

	m_ProductionInfo.m_counttimer = 0;

	m_ProductionInfo.m_one_draw = false;
	m_ProductionInfo.m_two_draw = false;
	m_ProductionInfo.m_three_draw = false;

	m_ProductionInfo.m_uistartflag = false;

}

void StartProduction::LoadTex()
{
	LoadTexture("Res/Tex/UI 1.png", &m_ProductionInfo.m_t_one);
	LoadTexture("Res/Tex/UI 2.png", &m_ProductionInfo.m_t_two);
	LoadTexture("Res/Tex/UI 3.png", &m_ProductionInfo.m_t_three);

	LoadTexture("Res/Tex/UIスタート.png", &m_ProductionInfo.m_start);

}

void StartProduction::Draw()
{
	if (m_ProductionInfo.m_three_draw == true)
	{
		DrawUITexture(&m_ProductionInfo.m_t_three, m_ProductionInfo.m_t_three_pos);
	}
	else if (m_ProductionInfo.m_two_draw == true)
	{
		DrawUITexture(&m_ProductionInfo.m_t_two, m_ProductionInfo.m_t_two_pos);
	}
	else if (m_ProductionInfo.m_one_draw == true)
	{
		DrawUITexture(&m_ProductionInfo.m_t_one, m_ProductionInfo.m_t_one_pos);
	}
	else if (m_ProductionInfo.m_counttimer >= 240 && m_ProductionInfo.m_counttimer <= 300)
	{
		DrawUITexture(&m_ProductionInfo.m_start, m_ProductionInfo.m_start_pos);
	}
}

void StartProduction::UpDate()
{
	if (m_ProductionInfo.m_counttimer <= 300)
	{
		m_ProductionInfo.m_counttimer++;
	}
	
	if (m_ProductionInfo.m_counttimer == 60)
	{
		m_ProductionInfo.m_three_draw = true;
		SoundManager::Instance()->SoundCountSE();
	}
	if (m_ProductionInfo.m_counttimer == 120)
	{
		m_ProductionInfo.m_three_draw = false;
		m_ProductionInfo.m_two_draw = true;
		SoundManager::Instance()->SoundCountSE();

	}
	if (m_ProductionInfo.m_counttimer == 180)
	{
		m_ProductionInfo.m_two_draw = false;
		m_ProductionInfo.m_one_draw = true;
		SoundManager::Instance()->SoundCountSE();

	}
	if (m_ProductionInfo.m_counttimer == 240)
	{
		m_ProductionInfo.m_one_draw = false;
		SoundManager::Instance()->SoundStartSE();
	}
	if (m_ProductionInfo.m_counttimer == 300)
	{
		m_ProductionInfo.m_uistartflag = true;
	}
}

void StartProduction::ReleaseTex()
{
	ReleaseUITexture(&m_ProductionInfo.m_t_three);
	ReleaseUITexture(&m_ProductionInfo.m_t_two);
	ReleaseUITexture(&m_ProductionInfo.m_t_one);
	ReleaseUITexture(&m_ProductionInfo.m_start);

}

void StartProduction::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != NULL)
	{
		texture->Texture->Release();
		texture->Texture = NULL;
	}
}
