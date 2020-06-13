#include "Pot.h"
#include"../Manager/FbxManager.h"
#include"../Engine/FBX.h"


Pot::Pot()
{
	m_mapdata.m_pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_mapdata.m_map_top = D3DXVECTOR3(0.0f,100.0f,0.0f);
	m_mapdata.m_map_bottom=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_mapdata.m_map_centerpos=D3DXVECTOR3(0.0f,50.0f,0.0f);

	m_mapdata.radius = 29.0f;
	
	m_mapdata.m_key = "pot";
	
	D3DXMatrixIdentity(&m_mapdata.m_mat_world);
	D3DXMatrixScaling(&m_mapdata.m_mat_scale, 30.0f, 30.0f, 30.0f);
	D3DXMatrixTranslation(&m_mapdata.m_mat_move, m_mapdata.m_pos.x, m_mapdata.m_pos.y, m_mapdata.m_pos.z);
	D3DXMatrixMultiply(&m_mapdata.m_mat_world, &m_mapdata.m_mat_scale,  &m_mapdata.m_mat_move);
}

void Pot::Update()
{
	MyFbxManager::FbxManager::Instance()->Animation(m_mapdata.m_key, 1.0f / 60.0f);
}

void Pot::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_mapdata.m_key, m_mapdata.m_mat_world);
}
