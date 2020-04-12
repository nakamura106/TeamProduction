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

	void SetEyePos(D3DXVECTOR3 eyepos_);

	void SetCameraPos(D3DXVECTOR3 camerapos_);
	// 移動前のカメラの位置
	void SetBeforeCameraPos(D3DXVECTOR3 camera_pos_);
	// 移動後のカメラの位置
	void SetAfterCameraPos(D3DXVECTOR3 camera_pos_);

	void SetMapCenterPos(D3DXVECTOR3 map_centerpos_);

	void SetMapRadius(float map_radius_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

	void SetPlayerPos(D3DXVECTOR3 player_pos_);

	D3DXVECTOR3 GetCameraPos() {
		return m_Camera_Pos;
	}
	// 移動前のカメラの位置を取得
	D3DXVECTOR3 GetBeforeCameraPos() {
		return m_before_camera_pos;
	}
	// 移動後のカメラの位置を取得
	D3DXVECTOR3 GetAfterCameraPos() {
		return m_after_camera_pos;
	}

	D3DXVECTOR3 GetEyePos() { return m_eye_pos; }

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

	D3DXVECTOR3 m_Camera_Pos;
	D3DXVECTOR3 m_before_camera_pos;
	D3DXVECTOR3 m_after_camera_pos;
	
	D3DXVECTOR3 m_player_pos;

	D3DXVECTOR3 m_eye_pos;

	D3DXVECTOR3 m_map_centerpos;

	float m_map_radius;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
