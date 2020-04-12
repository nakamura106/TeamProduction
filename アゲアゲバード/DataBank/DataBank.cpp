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
// 移動前のカメラの位置
void DataBank::SetBeforeCameraPos(D3DXVECTOR3 camera_pos_)
{
	m_before_camera_pos = camera_pos_;
}
// 移動後のカメラの位置
void DataBank::SetAfterCameraPos(D3DXVECTOR3 camera_pos_)
{
	m_after_camera_pos = camera_pos_;
}

void DataBank::SetMapCenterPos(D3DXVECTOR3 map_centerpos_)
{
	m_map_centerpos = map_centerpos_;
}

void DataBank::SetMapRadius(float map_radius_)
{
	m_map_radius = map_radius_;
}

void DataBank::SetOilPos(float oilelevation_)
{
	m_oilelevation = oilelevation_;
}

void DataBank::SetBlockPos(D3DXVECTOR3 blockpos_)
{
	m_blockpos.push_back(blockpos_);
}

void DataBank::SetSceneStep(BaseScene::SceneStep scenestep_)
{
	m_scene_step = scenestep_;
}

void DataBank::SetSceneId(BaseScene::SceneId sceneid_)
{
	m_scene_id = sceneid_;
}

void DataBank::SetPlayerPos(D3DXVECTOR3 player_pos_)
{
	m_player_pos = player_pos_;
}

// プレイヤーの半径の値を取得する関数を作る
