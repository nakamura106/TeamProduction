#include "Item.h"

Item::Item()
{
	//m_object = m_manager.LoadFbxMesh("Res/FBX/nabeMaya100m.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&m_mat_move, 0.0f, -1.0f, 0.0f);//ì™Ç…ê›íË
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scall);
	m_object.fbxinfo.world = m_mat_world;

	m_pos.X = p_camera->GetCamaraPos().x;
	m_pos.Y = p_camera->GetCamaraPos().y;
	m_pos.Z = p_camera->GetCamaraPos().z;

	m_direction.X = p_camera->GetEyePos().x;
	m_direction.Y = p_camera->GetEyePos().y;
	m_direction.Z = p_camera->GetEyePos().z;

	m_speed = 5.0f;
}


void Item::UpdateSpeed()
{

	

	m_direction.X = m_direction.X / sqrtf((m_direction.X * m_direction.X) + (m_direction.Y * m_direction.Y) + (m_direction.Z * m_direction.Z));
	m_direction.Y = m_direction.Y / sqrtf((m_direction.X * m_direction.X) + (m_direction.Y * m_direction.Y) + (m_direction.Z * m_direction.Z));
	m_direction.Z = m_direction.Z / sqrtf((m_direction.X * m_direction.X) + (m_direction.Y * m_direction.Y) + (m_direction.Z * m_direction.Z));

	//ç≈èâÇæÇØèdóÕÅÄ2
	/*m_pos.X += m_direction.X * m_speed.X;
	m_pos.Y += m_direction.Y * m_speed.Y - 9.8f/2;
	m_pos.Z += m_direction.Z * m_speed.Z;*/

	m_pos.X += m_direction.X * m_speed;
	m_pos.Y += m_direction.Y * m_speed - 9.8f;
	m_pos.Z += m_direction.Z * m_speed;


	//while (true)
	//{
	//	//ç≈èâÇæÇØèdóÕÅÄ2
	///*m_pos.X += m_direction.X * m_speed.X;
	//m_pos.Y += m_direction.Y * m_speed.Y - 9.8f/2;
	//m_pos.Z += m_direction.Z * m_speed.Z;*/

	//	m_pos.X += m_direction.X * m_provisional_speed;
	//	m_pos.Y += m_direction.Y * m_provisional_speed - 9.8f;
	//	m_pos.Z += m_direction.Z * m_provisional_speed;
	//}
	//Ç‡ÇµÇ«Ç±Ç©Ç…íÖíeÇµÇΩÇÁ
	/*m_pos.X = 
	m_pos.Y = 
	m_pos.Z = */


}
