#include "StartProduction.h"

void StartProduction::Init()
{
	m_counttimer = 0;

	m_one_draw = false;
	m_two_draw = false;
	m_three_draw = false;

	m_startflg = false;

}

void StartProduction::LoadTex()
{
	LoadTexture("Res/Tex/UI 1.png", &m_t_one);
	LoadTexture("Res/Tex/UI 2.png", &m_t_two);
	LoadTexture("Res/Tex/UI 3.png", &m_t_three);

	LoadTexture("Res/Tex/UIスタート.png", &m_start);

}

void StartProduction::Draw()
{
	if (m_three_draw == true)
	{
		DrawUITexture(&m_t_three, m_t_three_pos);
	}
	else if (m_two_draw == true)
	{
		DrawUITexture(&m_t_two, m_t_two_pos);
	}
	else if (m_one_draw == true)
	{
		DrawUITexture(&m_t_one, m_t_one_pos);
	}
	else if (m_startflg == true)
	{
		DrawUITexture(&m_start, m_start_pos);
	}
}

void StartProduction::UpDate()
{
	m_counttimer++;
	if (m_counttimer == 60)
	{
		m_three_draw = true;
	}
	if (m_counttimer == 120)
	{
		m_three_draw = false;
		m_two_draw = true;
	}
	if (m_counttimer == 180)
	{
		m_two_draw = false;
		m_one_draw = true;
	}
	if (m_counttimer == 240)
	{
		m_one_draw = false;
		m_startflg = true;
	}
}

void StartProduction::ReleaseTex()
{
	ReleaseUITexture(&m_t_three);
	ReleaseUITexture(&m_t_two);
	ReleaseUITexture(&m_t_one);
	ReleaseUITexture(&m_start);

}

void StartProduction::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != NULL)
	{
		texture->Texture->Release();
		texture->Texture = NULL;
	}
}
