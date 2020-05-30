#include"Oil.h"
#include"../Manager/FbxManager.h"
#include"../Production/StartProduction.h"
#include"../Scene/TitleScene.h"
#include"../UI/TitleUI.h"

Oil::Oil()
{
	
	m_oil_data.m_key = "oil";

	m_oil_data.m_pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

	m_oil_data.angle_ = D3DXVECTOR3(90.0f, 0.0f, 0.0f);

	m_oil_data.scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_oil_data.tex_tu = 0.0f;
	m_oil_data.tex_tv = 0.0f;

	m_oil_data.m_uv_counter = 0;

	/*D3DXMatrixIdentity(&m_oildata.m_mat_world);
	D3DXMatrixScaling(&m_oildata.m_mat_scale, m_oildata.scale_.x, m_oildata.scale_.y, m_oildata.scale_.z);
	D3DXMatrixTranslation(&m_oildata.m_mat_move, 0.0f, m_oildata.m_pos.y, 0.0f);
	D3DXMatrixRotationX(&m_oildata.m_mat_rot_x, D3DXToRadian(m_oildata.angle_.x));
	D3DXMatrixRotationY(&m_oildata.m_mat_rot_y, D3DXToRadian(m_oildata.angle_.y));
	D3DXMatrixRotationZ(&m_oildata.m_mat_rot_z, D3DXToRadian(m_oildata.angle_.z));

	m_oildata.m_mat_rot *= m_oildata.m_mat_rot_x * m_oildata.m_mat_rot_y * m_oildata.m_mat_rot_z;
	m_oildata.m_mat_world *= m_oildata.m_mat_scale * m_oildata.m_mat_rot * m_oildata.m_mat_move;
	D3DXMatrixMultiply(&m_oildata.m_mat_world, &m_oildata.m_mat_move, &m_oildata.m_mat_scale);*/

	LoadTexture("Res/Tex/OilFloorEx_Loop2.png", &m_oil_data.m_oiltex);
	
}

void Oil::Update()
{
	RisingOil();
}

void Oil::Draw()
{
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		if (m_production_manager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
		{
			DrawUVTexture(&m_oil_data.m_oiltex, m_oil_data.m_pos, 128.0f, 128.0f, m_oil_data.tex_tu, m_oil_data.tex_tv, 0.3f, 0.4f, m_oil_data.angle_, m_oil_data.scale_);
		}
	}
}

void Oil::UpdateUV()
{
	m_oil_data.m_uv_counter++;
	if (m_oil_data.m_uv_counter == 10)
	{
		m_oil_data.tex_tu += 0.6f;
		m_oil_data.m_uv_counter = 0;
	}

	if (m_oil_data.tex_tu >= 1.0f)
	{
		m_oil_data.tex_tu = 0.0f;
	}
}

void Oil::RisingOil()
{
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		if (m_object_manager->GetFillOil()->GetFillOilData()->m_fall_flag == false)
		{
			m_oil_data.m_pos.y += 0.005f;
			D3DXMatrixTranslation(&m_oil_data.m_mat_move, 0.0f, m_oil_data.m_pos.y, 0.0f);
			D3DXMatrixMultiply(&m_oil_data.m_mat_world, &m_oil_data.m_mat_world, &m_oil_data.m_mat_move);
			D3DXMatrixMultiply(&m_oil_data.m_mat_world, &m_oil_data.m_mat_move, &m_oil_data.m_mat_scale);
		}
		UpdateUV();
	}
}

FillOil::FillOil()
{
	m_filloildata.m_key = "filloil";

	m_filloildata.m_pos = D3DXVECTOR3(0.0f,300.0f, 0.0f);

	m_filloildata.angle_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_filloildata.angle2_ = D3DXVECTOR3(0.0f, 90.0f, 0.0f);

	m_filloildata.angle3_ = D3DXVECTOR3(0.0f, 180.0f, 0.0f);

	m_filloildata.angle4_ = D3DXVECTOR3(0.0f, -90.0f, 0.0f);

	m_filloildata.scale_ = D3DXVECTOR3(10.0f, 40.0f, 10.0f);

	m_filloildata.tex_tu = 0.0f;
	m_filloildata.tex_tv = 1.0f;

	m_filloildata.m_uv_counter = 0;

	m_filloildata.m_fall_flag = true;

	LoadTexture("Res/Tex/OilFloorEx_Loop2.png", &m_filloildata.m_filloiltex);
	
}

void FillOil::Update()
{
	FallFillOil();
}

void FillOil::Draw()
{
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		if (m_production_manager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
		{
			DrawUVTexture(&m_filloildata.m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, m_filloildata.tex_tu, m_filloildata.tex_tv, 0.3f, 1.0f, m_filloildata.angle_, m_filloildata.scale_);
			DrawUVTexture(&m_filloildata.m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, m_filloildata.tex_tu, m_filloildata.tex_tv, 0.3f, 1.0f, m_filloildata.angle2_, m_filloildata.scale_);
			DrawUVTexture(&m_filloildata.m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, m_filloildata.tex_tu, m_filloildata.tex_tv, 0.3f, 1.0f, m_filloildata.angle3_, m_filloildata.scale_);
			DrawUVTexture(&m_filloildata.m_filloiltex, m_filloildata.m_pos, 0.5f, 10.0f, m_filloildata.tex_tu, m_filloildata.tex_tv, 0.3f, 1.0f, m_filloildata.angle4_, m_filloildata.scale_);
		}
	}
}

void FillOil::UpdateUV()
{
	m_filloildata.m_uv_counter++;
	
	m_filloildata.tex_tv -= 0.0005f;
	m_filloildata.m_uv_counter = 0;
	

	if (m_filloildata.tex_tv <= 0.0f)
	{
		m_filloildata.tex_tv = 1.0f;
	}
}

void FillOil::FallFillOil()
{
	if (m_scene_manager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)TitleUI::Select::Timeattack)
	{
		if (m_production_manager->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
		{
			if (m_filloildata.m_pos.y >= 190.0f)
			{
				m_filloildata.m_pos.y -= 0.2f;
			}
			else
			{
				if (m_filloildata.m_fall_flag == true)
				{
					m_filloildata.m_fall_flag = false;
				}
				UpdateUV();
			}
		}
	}
}
