#include"Oil.h"
#include"../Manager/FbxManager.h"

Oil::Oil()
{
	
	m_oildata.m_key = "oil";
	m_oildata.m_pos.y = -10.0f;
	D3DXMatrixIdentity(&m_oildata.m_mat_world);
	D3DXMatrixScaling(&m_oildata.m_mat_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&m_oildata.m_mat_move, 0.0f, m_oildata.m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_move, &m_oildata.m_mat_scale);
	
}

void Oil::Update()
{
	m_oildata.m_pos.y += 0.005f;
	D3DXMatrixTranslation(&m_oildata.m_mat_move, 0.0f, m_oildata.m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_world,&m_oildata.m_mat_move);
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_move, &m_oildata.m_mat_scale);
	
}

void Oil::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_oildata.m_key, m_oildata.m_mat_world);
}

FillOil::FillOil()
{
	m_filloildata.m_key = "filloil";
	D3DXMatrixIdentity(&m_filloildata.m_mat_world);
	D3DXMatrixScaling(&m_filloildata.m_mat_scale, 10.0f, 40.0f, 10.0f);
	D3DXMatrixTranslation(&m_filloildata.m_mat_move, 0.0f, -1.0f, 0.0f);
	D3DXMatrixMultiply(&m_filloildata.m_mat_world, &m_filloildata.m_mat_move, &m_filloildata.m_mat_scale);
	
}

void FillOil::Update()
{
	//GetD3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
}

void FillOil::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_filloildata.m_key, m_filloildata.m_mat_world);
}
