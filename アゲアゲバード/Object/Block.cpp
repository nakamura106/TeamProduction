#include"Block.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/FbxManager.h"

Block::Block()
{
	m_BlockData.m_key = "block";
	m_BlockData.m_pos = ObjectManager::Instance()->BlockInstallation(ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_EyePos, ObjectManager::Instance()->GetPlayer("player1")->GetPlayerData()->m_p_camera->GetCameraData()->m_Forward);
	m_BlockData.radius = 2.0f;
	D3DXMatrixIdentity(&m_BlockData.m_mat_world);
	D3DXMatrixScaling(&m_BlockData.m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_BlockData.m_mat_move, m_BlockData.m_pos.x, m_BlockData.m_pos.y, m_BlockData.m_pos.z);
	
	D3DXMatrixMultiply(&m_BlockData.m_mat_world, &m_BlockData.m_mat_move, &m_BlockData.m_mat_scale);
}

Block::~Block()
{

}

void Block::Update()
{
}

void Block::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_BlockData.m_key, m_BlockData.m_mat_world);
}








