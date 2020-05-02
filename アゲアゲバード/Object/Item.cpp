#include "Item.h"
#include "../DataBank/DataBank.h"
#include "../Engine/Input.h"
#include<math.h>
#include<stdio.h>
#include<time.h>


Item::Item()
{
	m_pos = DataBank::Instance()->GetCameraPos();

	m_direction.x = DataBank::Instance()->GetForward().x;
	m_direction.y = DataBank::Instance()->GetForward().y;
	m_direction.z = DataBank::Instance()->GetForward().z;

	m_speed = 1.0f;

	m_gravity = 0.0f;

	m_radius = 2.0f;

	m_hit = false;

	m_key = "item";
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
	//m_object.fbxinfo.world = m_mat_world;

}


void Item::Update()
{
	
	m_pos.x += m_direction.x * m_speed;
	m_pos.y += m_direction.y * m_speed;
	m_pos.z += m_direction.z * m_speed;

	m_pos.y -= m_gravity;
	m_gravity += 0.01f;

	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move,&m_mat_scale);

	UpdateHitItem();

}

bool Item::UpdateHitItem()
{
	for (const auto& itr : DataBank::Instance()->GetBlockPos())
	{
		if (collision->HitItemBox(itr, m_pos, 5.0f, m_radius) == true)
		{
			return m_hit = true;
		}
		else
		{
			return false;
		}
	}
	
}

GetItemBox::GetItemBox()
{
	m_rotspeed = 0.0f;
	m_Upward = true;
	m_key = "ItemBox";
	m_pos.x = (rand() % 50 +0)-25;
	m_pos.z = (rand() % 50 + +0)-25;
	m_pos.y = rand() % 90 + 0;
	
	DataBank::Instance()->BlockInstallation(m_pos);

	m_floattime = 1;

	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
}

GetItemBox::~GetItemBox()
{
}

void GetItemBox::Update()
{
	BoxProduction();
}

void GetItemBox::BoxProduction()
{
	
	m_rotspeed+=0.01f;
	if (m_rotspeed == 360)
	{
		m_rotspeed=0;
	}
	m_floattime += 1;
	if (m_floattime >= 60)
	{
		if (m_Upward == true)
		{
			m_Upward = false;
			m_floattime = 1;
		}
		else
		{
			m_Upward = true;
			m_floattime = 1;
		}
	}
	if (m_Upward == true)
	{
		m_pos.y += 0.01f;
	}
	if (m_Upward == false)
	{
		m_pos.y -= 0.01f;
	}

	D3DXMatrixRotationY(&m_mat_rot, m_rotspeed);
	D3DXMatrixScaling(&m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//ì™Ç…ê›íË
	m_mat_world = m_mat_rot * m_mat_scale * m_mat_move;
}






