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
	m_Camera_Pos = camerapos_;
}

void DataBank::SetEyePos(D3DXVECTOR3 eyepos_)
{
	m_Eye_Pos = eyepos_;
}

void DataBank::SetOilPos(float oilelevation_)
{
	m_oilelevation = oilelevation_;
}

void DataBank::SetBlockPos(D3DXVECTOR3 blockpos_)
{
	m_blockpos.push_back(blockpos_);
}

