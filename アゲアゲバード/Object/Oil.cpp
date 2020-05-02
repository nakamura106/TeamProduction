#include"Oil.h"
#include"../Engine/Graphics.h"
#include"../DataBank/DataBank.h"

Oil::Oil()
{
	
	m_key = "oil";
	m_pos.y = -10.0f;
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_mat_move, 0.0f, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
	
}

void Oil::Update()
{
	m_pos.y += 0.005f;
	D3DXMatrixTranslation(&m_mat_move, 0.0f, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_world,&m_mat_move);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
	DataBank::Instance()->SetOilPos(m_pos.y);
}

FillOil::FillOil()
{
	m_key = "filloil";
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scale, 10.0f, 40.0f, 10.0f);
	D3DXMatrixTranslation(&m_mat_move, 0.0f, -1.0f, 0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scale);
	
}

void FillOil::Update()
{
	//GetD3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
}