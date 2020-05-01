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

void DataBank::DeleteBlockPos(int num)
{
	m_blockpos.erase(m_blockpos.begin() + num);
	
}

void DataBank::DeleteGameData()
{
	m_oilelevation = 0;
	m_item_pos.x=0;
	m_item_pos.y = 0;
	m_item_pos.z = 0;
	m_before_player_pos.x = 0;
	m_before_player_pos.y = 0;
	m_before_player_pos.z = 0;
	std::vector<D3DXVECTOR3>().swap(m_blockpos);

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

void DataBank::SetBlockStock(int stock_)
{
	m_blockstock = stock_;
}

void DataBank::SetMapTop(D3DXVECTOR3 map_top_)
{
	m_map_top = map_top_;
}

void DataBank::SetMapBottom(D3DXVECTOR3 map_bottom_)
{
	m_map_bottom = map_bottom_;
}

void DataBank::SetOilPos(float oilelevation_)
{
	m_oilelevation = oilelevation_;
}

void DataBank::SetBlockPos(D3DXVECTOR3 blockpos_)
{
	m_blockpos.push_back(blockpos_);
}

void DataBank::SetItemPos(D3DXVECTOR3 item_pos_)
{
	m_item_pos = item_pos_;
}

void DataBank::SetItemRadius(float item_radius_)
{
	m_item_radius = item_radius_;
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

D3DXVECTOR3 DataBank::BlockInstallation(D3DXVECTOR3 pos_)
{
	D3DXVECTOR3 blockpos;
	blockpos = pos_;
	blockpos /= 2.0f;
	blockpos.x = roundf(blockpos.x);
	blockpos.y = roundf(blockpos.y);
	blockpos.z = roundf(blockpos.z);
	blockpos *= 2.0f;
	return blockpos;
}

void DataBank::SetUIStartflag(bool uistartflag_)
{
	m_uistartflag = uistartflag_;
}

void DataBank::SetStartflag(bool startflag_)
{
	m_startflag = startflag_;
}

void DataBank::SetClearflag(bool clearflag_)
{
	m_clearflag = clearflag_;
}

void DataBank::SetPage(int page_)
{
	m_now_page = page_;
}

void DataBank::SetSelect(int sel_)
{
	m_now_select = sel_;
}
