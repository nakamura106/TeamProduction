#include "Item.h"
#include"Block.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/FbxManager.h"
#include<math.h>
#include<stdio.h>
#include<time.h>


Item::Item()
{
	m_itemdata.m_pos = ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_CameraPos;

	m_itemdata.m_direction.x = ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_Forward.x;
	m_itemdata.m_direction.y = ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_Forward.y;
	m_itemdata.m_direction.z = ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_Forward.z;

	m_itemdata.m_speed = 1.0f;

	m_itemdata.m_gravity = 0.0f;

	m_itemdata.m_radius = 2.0f;

	m_itemdata.m_hit = false;

	m_itemdata.m_key = "item";
	D3DXMatrixIdentity(&m_itemdata.m_mat_world);
	D3DXMatrixScaling(&m_itemdata.m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_itemdata.m_mat_move, m_itemdata.m_pos.x, m_itemdata.m_pos.y, m_itemdata.m_pos.z);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_itemdata.m_mat_world, &m_itemdata.m_mat_move, &m_itemdata.m_mat_scale);
	//m_object.fbxinfo.world = m_mat_world;
	m_block = ObjectManager::Instance()->GetBlock();
}


void Item::Update()
{
	
	m_itemdata.m_pos.x += m_itemdata.m_direction.x * m_itemdata.m_speed;
	m_itemdata.m_pos.y += m_itemdata.m_direction.y * m_itemdata.m_speed;
	m_itemdata.m_pos.z += m_itemdata.m_direction.z * m_itemdata.m_speed;

	m_itemdata.m_pos.y -= m_itemdata.m_gravity;
	m_itemdata.m_gravity += 0.01f;

	D3DXMatrixTranslation(&m_itemdata.m_mat_move, m_itemdata.m_pos.x, m_itemdata.m_pos.y, m_itemdata.m_pos.z);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_itemdata.m_mat_world, &m_itemdata.m_mat_move,&m_itemdata.m_mat_scale);

	UpdateHitItem();

}

void Item::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_itemdata.m_key, m_itemdata.m_mat_world);
}



bool Item::UpdateHitItem()
{
	for (const auto& itr : *m_block)
	{
		if (m_itemdata.collision->HitItemBox(itr->GetBlockData()->m_pos, m_itemdata.m_pos, 5.0f, m_itemdata.m_radius) == true)
		{
			return  true;
		}
		else
		{
			return false;
		}
	}
	
}

ItemBox::ItemBox()
{
	m_boxdata.m_rotspeed = 0.0f;
	m_boxdata.m_Upward = true;
	m_boxdata.m_key = "ItemBox";
	m_boxdata.m_pos.x = (rand() % 50 +0)-20;
	m_boxdata.m_pos.z = (rand() % 50 + +0)-20;
	m_boxdata.m_pos.y = rand() % 85 + 0;
	

	m_boxdata.m_floattime = 1;

	D3DXMatrixIdentity(&m_boxdata.m_mat_world);
	D3DXMatrixScaling(&m_boxdata.m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_boxdata.m_mat_move, m_boxdata.m_pos.x, m_boxdata.m_pos.y, m_boxdata.m_pos.z);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_boxdata.m_mat_world, &m_boxdata.m_mat_move, &m_boxdata.m_mat_scale);
}

ItemBox::~ItemBox()
{
}

void ItemBox::Update()
{
	BoxProduction();
}

void ItemBox::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_boxdata.m_key, m_boxdata.m_mat_world);
}

void ItemBox::BoxProduction()
{
	
	m_boxdata.m_rotspeed+=0.01f;
	if (m_boxdata.m_rotspeed == 360)
	{
		m_boxdata.m_rotspeed=0;
	}
	m_boxdata.m_floattime += 1;
	if (m_boxdata.m_floattime >= 60)
	{
		if (m_boxdata.m_Upward == true)
		{
			m_boxdata.m_Upward = false;
			m_boxdata.m_floattime = 1;
		}
		else
		{
			m_boxdata.m_Upward = true;
			m_boxdata.m_floattime = 1;
		}
	}
	if (m_boxdata.m_Upward == true)
	{
		m_boxdata.m_pos.y += 0.01f;
	}
	if (m_boxdata.m_Upward == false)
	{
		m_boxdata.m_pos.y -= 0.01f;
	}

	D3DXMatrixRotationY(&m_boxdata.m_mat_rot, m_boxdata.m_rotspeed);
	D3DXMatrixScaling(&m_boxdata.m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_boxdata.m_mat_move, m_boxdata.m_pos.x, m_boxdata.m_pos.y, m_boxdata.m_pos.z);//ì™Ç…ê›íË
	m_boxdata.m_mat_world = m_boxdata.m_mat_rot * m_boxdata.m_mat_scale * m_boxdata.m_mat_move;
}






