#include "Item.h"
#include "../DataBank/DataBank.h"
#include "../Engine/Input.h"


Item::Item()
{
	m_pos = DataBank::Instance()->GetCameraPos();

	m_direction.X = DataBank::Instance()->GetEyePos().x;
	m_direction.Y = DataBank::Instance()->GetEyePos().y;
	m_direction.Z = DataBank::Instance()->GetEyePos().z;

	m_speed = 5.0f;

	m_key = "item";
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//���ɐݒ�
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scall);
	m_object.fbxinfo.world = m_mat_world;

}


void Item::Update()
{
	
	m_direction.X = m_direction.X / sqrtf((m_direction.X * m_direction.X) + (m_direction.Y * m_direction.Y) + (m_direction.Z * m_direction.Z));
	m_direction.Y = m_direction.Y / sqrtf((m_direction.X * m_direction.X) + (m_direction.Y * m_direction.Y) + (m_direction.Z * m_direction.Z));
	m_direction.Z = m_direction.Z / sqrtf((m_direction.X * m_direction.X) + (m_direction.Y * m_direction.Y) + (m_direction.Z * m_direction.Z));


	if (GetKeyDown(UP_KEY))
	{
		m_pos.x += m_direction.X * m_speed;
		m_pos.y += m_direction.Y * m_speed - 9.8f;
		m_pos.z += m_direction.Z * m_speed;
	}
	//�ŏ������d�́�2
	/*m_pos.X += m_direction.X * m_speed.X;
	m_pos.Y += m_direction.Y * m_speed.Y - 9.8f/2;
	m_pos.Z += m_direction.Z * m_speed.Z;*/

	


	//while (true)
	//{
	//	//�ŏ������d�́�2
	///*m_pos.X += m_direction.X * m_speed.X;
	//m_pos.Y += m_direction.Y * m_speed.Y - 9.8f/2;
	//m_pos.Z += m_direction.Z * m_speed.Z;*/

	//	m_pos.X += m_direction.X * m_provisional_speed;
	//	m_pos.Y += m_direction.Y * m_provisional_speed - 9.8f;
	//	m_pos.Z += m_direction.Z * m_provisional_speed;
	//}
	//�����ǂ����ɒ��e������
	/*m_pos.X = 
	m_pos.Y = 
	m_pos.Z = */

}

//bool Item::UpdateHitItem()
//{
//	if (collision->HitItemPlayer(player_pos_x_, player_pos_y_, player_pos_z_, m_pos.X, m_pos.Y, m_pos.Z, player_radius, m_radius) == true)
//	{
//
//		return true;
//	}
//	else if (collision->HitItemBox( block_pos_x_,  block_pos_y_,  block_pos_z_,  item_pos_x_,  item_pos_y_,  item_pos_z_,  block_width_,  item_radius_) == true)
//	{
//		
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//
//}


