#include "Pot.h"
#include "../DataBank/DataBank.h"

Pot::Pot()
{
	m_map_radius = 100.0f;
	DataBank::Instance()->SetMapRadius(m_map_radius);
	m_map_top.x = 0.0f;
	m_map_top.y = 1000.0f;
	m_map_top.z = 0.0f;
	DataBank::Instance()->SetMapTop(m_map_top);
	m_map_bottom.x = 0.0f;
	m_map_bottom.y = 0.0f;
	m_map_bottom.z = 0.0f;
	DataBank::Instance()->SetMapBottom(m_map_bottom);
	m_map_centerpos.x = 0;
	m_map_centerpos.y = 500.0f;
	m_map_centerpos.z = 0;
	DataBank::Instance()->SetMapCenterPos(m_map_centerpos);
	m_key = "pot";
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scale, 30.0f, 30.0f, 30.0f);
	D3DXMatrixTranslation(&m_mat_move,0.0f,0.0f,0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_scale,  & m_mat_move);	
}
