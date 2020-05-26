#include"WorldBox.h"
#include"ObjectBase.h"
#include"../Manager/FbxManager.h"

WorldBox::WorldBox()
{
	m_world_box_data.m_key="WorldBox";

	m_world_box_data.m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	m_world_box_data.radius = 1000.0f;

	D3DXMatrixIdentity(&m_world_box_data.m_mat_world);
	D3DXMatrixScaling(&m_world_box_data.m_mat_scale,1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_world_box_data.m_mat_move, m_world_box_data.m_pos.x, m_world_box_data.m_pos.y, m_world_box_data.m_pos.z);
	D3DXMatrixMultiply(&m_world_box_data.m_mat_world, &m_world_box_data.m_mat_move, &m_world_box_data.m_mat_scale);

}

WorldBox::~WorldBox()
{
}

void WorldBox::Update()
{
}

void WorldBox::Draw()
{
	m_fbxmanager->DrawFbx(m_world_box_data.m_key, m_world_box_data.m_mat_world);
}
