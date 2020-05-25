#include"Oil.h"
#include"../Manager/FbxManager.h"

Oil::Oil()
{
	
	m_oildata.m_key = "oil";

	m_oildata.m_pos.x = 0.0f;
	m_oildata.m_pos.y = -10.0f;
	m_oildata.m_pos.z = 0.0f;

	m_oildata.angle_.x = 90.0f;
	m_oildata.angle_.y = 0.0f;
	m_oildata.angle_.z = 0.0f;

	m_oildata.scale_.x = 1.0f;
	m_oildata.scale_.y = 1.0f;
	m_oildata.scale_.z = 1.0f;

	tex_tu = 0.0f;
	tex_tv = 0.0f;

	m_uv_counter = 0;

	/*D3DXMatrixIdentity(&m_oildata.m_mat_world);
	D3DXMatrixScaling(&m_oildata.m_mat_scale, m_oildata.scale_.x, m_oildata.scale_.y, m_oildata.scale_.z);
	D3DXMatrixTranslation(&m_oildata.m_mat_move, 0.0f, m_oildata.m_pos.y, 0.0f);
	D3DXMatrixRotationX(&m_oildata.m_mat_rot_x, D3DXToRadian(m_oildata.angle_.x));
	D3DXMatrixRotationY(&m_oildata.m_mat_rot_y, D3DXToRadian(m_oildata.angle_.y));
	D3DXMatrixRotationZ(&m_oildata.m_mat_rot_z, D3DXToRadian(m_oildata.angle_.z));

	m_oildata.m_mat_rot *= m_oildata.m_mat_rot_x * m_oildata.m_mat_rot_y * m_oildata.m_mat_rot_z;
	m_oildata.m_mat_world *= m_oildata.m_mat_scale * m_oildata.m_mat_rot * m_oildata.m_mat_move;
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_move, &m_oildata.m_mat_scale);*/

	LoadTexture("Res/Tex/OilFloorEx_Loop2.png", &m_oiltex);
	
}

void Oil::Update()
{
	m_oildata.m_pos.y += 0.005f;
	D3DXMatrixTranslation(&m_oildata.m_mat_move, 0.0f, m_oildata.m_pos.y, 0.0f);
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_world,&m_oildata.m_mat_move);
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_move, &m_oildata.m_mat_scale);
	
	m_uv_counter++;
	if (m_uv_counter == 10)
	{
		tex_tu += 0.6f;
		m_uv_counter = 0;
	}

	if (tex_tu >= 1.0f)
	{
		tex_tu = 0.0f;
	}
}

void Oil::Draw()
{
	//MyFbxManager::FbxManager::Instance()->DrawFbx(m_oildata.m_key, m_oildata.m_mat_world);

	DrawUVTexture(&m_oiltex, m_oildata.m_pos, 128.0f, 128.0f, tex_tu, tex_tv, 0.3f, 0.4f, m_oildata.angle_, m_oildata.scale_);
}

FillOil::FillOil()
{
	m_filloildata.m_key = "filloil";

	m_filloildata.m_pos.x = 0.0f;
	m_filloildata.m_pos.y = -1.0f;
	m_filloildata.m_pos.z = 0.0f;

	m_filloildata.angle_.x = 0.0f;
	m_filloildata.angle_.y = 0.0f;
	m_filloildata.angle_.z = 0.0f;

	angle2_.x = 0.0f;
	angle2_.y = 90.0f;
	angle2_.z = 0.0f; 

	angle3_.x = 0.0f;
	angle3_.y = 180.0f;
	angle3_.z = 0.0f;

	angle4_.x = 0.0f;
	angle4_.y = -90.0f;
	angle4_.z = 0.0f;

	m_filloildata.scale_.x = 10.0f;
	m_filloildata.scale_.y = 40.0f;
	m_filloildata.scale_.z = 10.0f;

	tex_tu = 0.0f;
	tex_tv = 1.0f;

	m_uv_counter = 0;

	/*D3DXMatrixIdentity(&m_filloildata.m_mat_world);
	D3DXMatrixScaling(&m_filloildata.m_mat_scale, 10.0f, 40.0f, 10.0f);
	D3DXMatrixTranslation(&m_filloildata.m_mat_move, 0.0f, -1.0f, 0.0f);
	D3DXMatrixMultiply(&m_filloildata.m_mat_world, &m_filloildata.m_mat_move, &m_filloildata.m_mat_scale);*/

	LoadTexture("Res/Tex/OilFloorEx_Loop2.png", &m_filloiltex);
	
}

void FillOil::Update()
{
	m_uv_counter++;
	//if (m_uv_counter == 10)
	//{
		tex_tv -= 0.0005f;
		m_uv_counter = 0;
	//}

	if (tex_tv <= 0.0f)
	{
		tex_tv = 1.0f;
	}
	//GetD3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
}

void FillOil::Draw()
{
	//MyFbxManager::FbxManager::Instance()->DrawFbx(m_filloildata.m_key, m_filloildata.m_mat_world);

	DrawUVTexture(&m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, tex_tu, tex_tv, 0.3f, 1.0f, m_filloildata.angle_, m_filloildata.scale_);
	DrawUVTexture(&m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, tex_tu, tex_tv, 0.3f, 1.0f, angle2_, m_filloildata.scale_);
	DrawUVTexture(&m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, tex_tu, tex_tv, 0.3f, 1.0f, angle3_, m_filloildata.scale_);
	DrawUVTexture(&m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, tex_tu, tex_tv, 0.3f, 1.0f, angle4_, m_filloildata.scale_);


}
