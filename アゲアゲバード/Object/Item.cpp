#include "Item.h"
#include "../DataBank/DataBank.h"
#include "../Engine/Input.h"


Item::Item()
{
	m_pos = DataBank::Instance()->GetCameraPos();

	m_direction.x = DataBank::Instance()->GetEyePos().x;
	m_direction.y = DataBank::Instance()->GetEyePos().y;
	m_direction.z = DataBank::Instance()->GetEyePos().z;

	vec.x = m_direction.x - m_pos.x;
	vec.y = m_direction.y - m_pos.y;
	vec.z = m_direction.z - m_pos.z;

	
	m_direction.x = m_direction.x / sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	m_direction.y = m_direction.y / sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	m_direction.z = m_direction.z / sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

	m_speed = 0.1f;

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
	m_pos.y += m_direction.y * m_speed ;
	m_pos.z += m_direction.z * m_speed;

	/*m_direction.x = DataBank::Instance()->GetEyePos().x;
	m_direction.y = DataBank::Instance()->GetEyePos().y;
	m_direction.z = DataBank::Instance()->GetEyePos().z;


	m_direction.x = m_direction.x / sqrtf((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) + (m_direction.z * m_direction.z));
	m_direction.y = m_direction.y / sqrtf((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) + (m_direction.z * m_direction.z));
	m_direction.z = m_direction.z / sqrtf((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) + (m_direction.z * m_direction.z));*/

	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);//“ª‚ÉÝ’è
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move,&m_mat_scale);
	//D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
	
	//Å‰‚¾‚¯d—Í€2
	/*m_pos.X += m_direction.X * m_speed.X;
	m_pos.Y += m_direction.Y * m_speed.Y - 9.8f/2;
	m_pos.Z += m_direction.Z * m_speed.Z;*/

	


	//while (true)
	//{
	//	//Å‰‚¾‚¯d—Í€2
	///*m_pos.X += m_direction.X * m_speed.X;
	//m_pos.Y += m_direction.Y * m_speed.Y - 9.8f/2;
	//m_pos.Z += m_direction.Z * m_speed.Z;*/

	//	m_pos.X += m_direction.X * m_provisional_speed;
	//	m_pos.Y += m_direction.Y * m_provisional_speed - 9.8f;
	//	m_pos.Z += m_direction.Z * m_provisional_speed;
	//}
	//‚à‚µ‚Ç‚±‚©‚É’…’e‚µ‚½‚ç
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


