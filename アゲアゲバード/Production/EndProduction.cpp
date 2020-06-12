#include "EndProduction.h"
#include"../Object/Pot.h"
#include"../Object/Oil.h"
#include "../Player/Player.h"

void EndProduction::Init()
{
	m_EndProductionInfo.m_finish_pos.x = 400.0f;
	m_EndProductionInfo.m_finish_pos.y = -100.0f;

	m_EndProductionInfo.m_fly_pos.x = 0.0f;
	m_EndProductionInfo.m_fly_pos.y = 0.0f;

	m_EndProductionInfo.m_oil_filter_pos = D3DXVECTOR2(0.0f, 0.0f);

	m_EndProductionInfo.speed = 5.0f;

	m_EndProductionInfo.timer = 0;
	m_EndProductionInfo.m = 30.0f;
	m_EndProductionInfo.fa = 0.3f;
	m_EndProductionInfo.e = 2.71828182845904523536f;

	m_EndProductionInfo.finishflag = false;
	m_EndProductionInfo.flyflag = false;
	m_EndProductionInfo.clear_seflag = false;
	m_EndProductionInfo.fly_seflag = false;
}

void EndProduction::LoadTex()
{
	LoadTexture("Res/Tex/�t�B�j�b�V��UI.png", &m_EndProductionInfo.m_finish);
	LoadTexture("Res/Tex/�t���C�IUI.png", &m_EndProductionInfo.m_fly);
	LoadTexture("Res/Tex/Oil_50per.png", &m_EndProductionInfo.m_oil_filter);
}

void EndProduction::Draw()
{
	if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= ObjectManager::Instance()->GetMap()->GetMapData()->m_map_top.y && ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_startflag == true)
	{
		DrawUITexture(&m_EndProductionInfo.m_finish, m_EndProductionInfo.m_finish_pos);
	}
	else if(m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y <= m_objectmanager->GetOil()->GetOilData()->m_pos.y 
		&& m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_startflag == true
		|| m_objectmanager->GetPlayer("player1")->GetPlayerData()->filloilfly == true)
	{
		DrawUITexture(&m_EndProductionInfo.m_oil_filter, m_EndProductionInfo.m_oil_filter_pos);
		DrawUITexture(&m_EndProductionInfo.m_fly, m_EndProductionInfo.m_fly_pos);
	}
}

void EndProduction::UpDate()
{
	if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y <= m_objectmanager->GetOil()->GetOilData()->m_pos.y
		|| m_objectmanager->GetPlayer("player1")->GetPlayerData()->filloilfly == true)
	{
		m_EndProductionInfo.fly_seflag = true;

		if (m_EndProductionInfo.m_fly_pos.y >= -300.0f)
		{
			m_EndProductionInfo.m_grav.ThrowingUp(m_EndProductionInfo.m_fly_pos.y, 8.0f);
			m_EndProductionInfo.m_fly_pos.y = m_EndProductionInfo.m_grav.GetPosY();
		}
		else
		{
			m_EndProductionInfo.flyflag = true;
		}
	}
	if (m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_pos.y >= m_objectmanager->GetMap()->GetMapData()->m_map_top.y 
		&& m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_startflag == true)
	{	

		m_EndProductionInfo.clear_seflag = true;

		if (m_EndProductionInfo.m_finish_pos.y <= 400.0f)
		{
			m_EndProductionInfo.timer++;

			if (m_EndProductionInfo.timer == 30)
			{
				m_EndProductionInfo.speed *= powf(m_EndProductionInfo.e, -(m_EndProductionInfo.fa / m_EndProductionInfo.m) * m_EndProductionInfo.timer);
				m_EndProductionInfo.timer = 0;
			}

			m_EndProductionInfo.m_finish_pos.y += m_EndProductionInfo.speed;
		}
		else
		{
			m_EndProductionInfo.finishflag = true;
		}
		
	}

	if (m_EndProductionInfo.clear_seflag == true)
	{
		m_soundmanager->SoundClearSE();
	}
	else if (m_EndProductionInfo.fly_seflag == true)
	{
		m_soundmanager->SoundFlySE();
	}
}

void EndProduction::ReleaseTex()
{
	ReleaseUITexture(&m_EndProductionInfo.m_finish);
	ReleaseUITexture(&m_EndProductionInfo.m_fly);
	ReleaseUITexture(&m_EndProductionInfo.m_oil_filter);
}

void EndProduction::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != NULL)
	{
		texture->Texture->Release();
		texture->Texture = NULL;
	}
}
