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

void DataBank::SetCameraPos(D3DXVECTOR3 camerapos_)
{
	m_Camera_Pos=camerapos_;
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

