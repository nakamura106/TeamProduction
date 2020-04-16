#include"DataBank.h"

DataBank* DataBank::p_instance = 0;

DataBank* DataBank::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new DataBank();
	}

	return p_instance;
}

DataBank::DataBank()
{
	

}

DataBank::~DataBank()
{

}

void DataBank::SetEyePos(D3DXVECTOR3 eyepos_)
{
	m_eye_pos = eyepos_;
}

void DataBank::SetCameraPos(D3DXVECTOR3 camerapos_)
{
	m_Camera_Pos = camerapos_;
}

void DataBank::SetMapCenterPos(D3DXVECTOR3 map_centerpos_)
{
	m_map_centerpos = map_centerpos_;
}

void DataBank::SetMapRadius(float map_radius_)
{
	m_map_radius = map_radius_;
}

void DataBank::SetMapTop(float map_top_)
{
	m_map_top = map_top_;
}

void DataBank::SetOilPos(float oilelevation_)
{
	m_oilelevation = oilelevation_;
}

void DataBank::SetBlockPos(D3DXVECTOR3 blockpos_)
{
	m_blockpos.push_back(blockpos_);
}

void DataBank::SetBeforePlayerPos(D3DXVECTOR3 player_pos_)
{
	m_before_player_pos = player_pos_;
}

void DataBank::SetAfterPlayerPos(D3DXVECTOR3 player_pos_)
{
	m_after_player_pos = player_pos_;
}

void DataBank::SetPlayerRadius(float player_radius_)
{
	m_player_radius = player_radius_;
}

void DataBank::SetSceneStep(BaseScene::SceneStep scenestep_)
{
	m_scene_step = scenestep_;
}

void DataBank::SetSceneId(BaseScene::SceneId sceneid_)
{
	m_scene_id = sceneid_;
}

void DataBank::SetForward(D3DXVECTOR3 forward_)
{
	m_Forward = forward_;
}
