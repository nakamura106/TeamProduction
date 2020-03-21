#include"Block.h"
#include"../DataBank/DataBank.h"

Block::Block()
{
	m_object = m_manager.LoadFbxMesh("Res/FBX/tenkasu.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	//D3DXMatrixScaling(&m_mat_scall, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_mat_move, DataBank::Instance()->GetCameraPos().x, DataBank::Instance()->GetCameraPos().y, DataBank::Instance()->GetCameraPos().z);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_world);
	m_object.fbxinfo.world = m_mat_world;
}



