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

void DataBank::SetPlayerPos(D3DXVECTOR3 player_pos_)
{
	m_player_pos = player_pos_;
}