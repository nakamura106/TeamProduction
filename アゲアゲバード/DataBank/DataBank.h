#ifndef DATABANK_H_
#define DATABANK_H_

#include <d3dx9.h>
#include<vector>
#include"../Object/ObjectBase.h"
#include"../Scene/BaseScene.h"

//情報保存クラス
class DataBank
{
public:
	static DataBank* Instance();

	void ResetData() {}

	// 移動前のカメラの位置
	void SetBeforeCameraPos(D3DXVECTOR3 camera_pos_);
	// 移動後のカメラの位置
	void SetAfterCameraPos(D3DXVECTOR3 camera_pos_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

	void SetPlayerPos(D3DXVECTOR3 player_pos_);

	// 移動前のカメラの位置を取得
	D3DXVECTOR3 GetBeforeCameraPos() {
		return m_before_camera_pos;
	}
	// 移動後のカメラの位置を取得
	D3DXVECTOR3 GetAfterCameraPos() {
		return m_after_camera_pos;
	}

	auto GetBlockPos() { return m_blockpos; }

	float GetOilPos() { return m_oilelevation; }

	BaseScene::SceneStep GetSceneStep() { return m_scene_step; }

	BaseScene::SceneId GetSceneId() { return m_scene_id; }

	D3DXVECTOR3 GetPlayerPos(D3DXVECTOR3 player_pos_) {
		return m_player_pos;
	}
	
protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	float m_oilelevation;

	D3DXVECTOR3 m_before_camera_pos;
	D3DXVECTOR3 m_after_camera_pos;
	
	D3DXVECTOR3 m_player_pos;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
