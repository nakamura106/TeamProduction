#include "Pot.h"
#include"../Manager/FbxManager.h"
#include"../Engine/FBX.h"


Pot::Pot()
{
	m_mapdata.m_pos.x = 0.0f;
	m_mapdata.m_pos.y = 0.0f;
	m_mapdata.m_pos.z = 0.0f;
	m_mapdata.radius = 30.0f;
	m_mapdata.m_map_top.x = 0.0f;
	m_mapdata.m_map_top.y = 100.0f;
	m_mapdata.m_map_top.z = 0.0f;
	m_mapdata.m_map_bottom.x = 0.0f;
	m_mapdata.m_map_bottom.y = 0.0f;
	m_mapdata.m_map_bottom.z = 0.0f;
	m_mapdata.m_map_centerpos.x = 0;
	m_mapdata.m_map_centerpos.y = 50.0f;
	m_mapdata.m_map_centerpos.z = 0;
	m_mapdata.m_key = "pot";
	D3DXMatrixIdentity(&m_mapdata.m_mat_world);
	D3DXMatrixScaling(&m_mapdata.m_mat_scale, 30.0f, 30.0f, 30.0f);
	D3DXMatrixTranslation(&m_mapdata.m_mat_move,0.0f,0.0f,0.0f);
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
