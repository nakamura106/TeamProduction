#include"Block.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/FbxManager.h"

Block::Block()
{
	m_BlockData.m_key = "block";
	D3DXMatrixIdentity(&m_BlockData.m_mat_world);
	D3DXMatrixScaling(&m_BlockData.m_mat_scale, 1.0f, 1.0f, 1.0f);
	m_BlockData.m_pos = ObjectManager::Instance()->BlockInstallation(ObjectManager::Instance()->GetCamera()->GetCameraData()->m_EyePos, ObjectManager::Instance()->GetCamera()->GetCameraData()->m_Forward);
	D3DXMatrixTranslation(&m_BlockData.m_mat_move, m_BlockData.m_pos.x, m_BlockData.m_pos.y, m_BlockData.m_pos.z);
	
	D3DXMatrixMultiply(&m_BlockData.m_mat_world, &m_BlockData.m_mat_move, &m_BlockData.m_mat_scale);
}

Block::~Block()
{

}








