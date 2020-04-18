#include"Block.h"
#include"../DataBank/DataBank.h"
#include"../Manager/FbxManager.h"

Block::Block()
{
	m_key = "block";
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scale, 1.0f, 1.0f, 1.0f);
	m_pos = DataBank::Instance()->GetCameraPos()+ DataBank::Instance()->GetForward()*5.0f;	
	m_pos /= 2.0f;
	m_pos.x = roundf(m_pos.x);
	m_pos.y = roundf(m_pos.y);
	m_pos.z = roundf(m_pos.z);
	m_pos *= 2.0f;
	D3DXMatrixTranslation(&m_mat_move,m_pos.x,m_pos.y,m_pos.z);
	DataBank::Instance()->SetBlockPos(m_pos);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
}








