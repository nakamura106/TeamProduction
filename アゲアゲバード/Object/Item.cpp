#include "Item.h"
#include "../DataBank/DataBank.h"
#include "../Engine/Input.h"


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
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//“ª‚ÉÝ’è
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

	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//“ª‚ÉÝ’è
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


