#include "Pot.h"
#include "../DataBank/DataBank.h"

Pot::Pot()
{
	m_mapdata.m_map_radius = 100.0f;
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
