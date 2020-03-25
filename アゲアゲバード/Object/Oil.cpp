#include"Oil.h"
#include"../Engine/Graphics.h"

Oil::Oil()
{
	m_object = m_manager.LoadFbxMesh("Res/FBX/FloorOil.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 50.0f, 0.0f, 50.0f);
	D3DXMatrixTranslation(&m_mat_move, 0.0f, -1.0f, 0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scall);
	m_object.fbxinfo.world = m_mat_world;
	m_oil_elevation = -1.0f;

}

void Oil::Update()
{
	m_oil_elevation += 0.01f;
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixTranslation(&m_mat_move, 0.0f,m_oil_elevation, 0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_world);
	m_object.fbxinfo.world = m_mat_world;
}

FillOil::FillOil()
{
	m_object = m_manager.LoadFbxMesh("Res/FBX/FillOil.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 10.0f, 40.0f, 10.0f);
	D3DXMatrixTranslation(&m_mat_move, 0.0f, -1.0f, 0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scall);
	m_object.fbxinfo.world = m_mat_world;
}

void FillOil::Update()
{
	//GetD3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
}