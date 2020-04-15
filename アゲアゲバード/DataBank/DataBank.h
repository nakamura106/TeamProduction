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
	
#pragma region Set

	// カメラの注視点を保存する
	void SetEyePos(D3DXVECTOR3 eyepos_);
	// カメラの位置を保存する
	void SetCameraPos(D3DXVECTOR3 camerapos_);
	// 移動前のカメラの位置を保存する
	void SetBeforeCameraPos(D3DXVECTOR3 camera_pos_);
	// 移動後のカメラの位置を保存する
	void SetAfterCameraPos(D3DXVECTOR3 camera_pos_);

	void SetMapCenterPos(D3DXVECTOR3 map_centerpos_);

	void SetMapRadius(float map_radius_);

	void SetMapTop(float map_top_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	// プレイヤーの位置を保存する
	void SetPlayerPos(D3DXVECTOR3 player_pos_);
	// プレイヤーの半径を保存する
	void SetPlayerRadius(float player_radius_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

	void SetForward(D3DXVECTOR3 forward_);

#pragma endregion

#pragma region Get

	// カメラの注視点を取得する
	D3DXVECTOR3 GetEyePos() {
		return m_eye_pos; 
	}
	// カメラの位置を取得する
	D3DXVECTOR3 GetCameraPos() {
		return m_Camera_Pos;
	}
	// 移動前のカメラの位置を取得する
	D3DXVECTOR3 GetBeforeCameraPos() {
		return m_before_camera_pos;
	}
	// 移動後のカメラの位置を取得する
	D3DXVECTOR3 GetAfterCameraPos() {
		return m_after_camera_pos;
	}

	// マップの中心の座標を取得する
	D3DXVECTOR3 GetMapCenterPos() {
		return m_map_centerpos;
	}
	// マップの
	float GetMapRadius() {
		return m_map_radius;
	}

	auto GetBlockPos() { return m_blockpos; }

	float GetOilPos() { return m_oilelevation; }

	// プレイヤーの位置を取得する
	D3DXVECTOR3 GetPlayerPos(D3DXVECTOR3 player_pos_) {
		return m_player_pos;
	}
	// プレイヤーの半径を取得する
	float GetPlayerRadius(float player_radius_) {
		return m_player_radius;
	}
	
	float GetMapTop() { return m_map_top; }

	D3DXVECTOR3 GetForward() { return m_Forward; }

	BaseScene::SceneStep GetSceneStep() { return m_scene_step; }

	BaseScene::SceneId GetSceneId() { return m_scene_id; }

#pragma endregion

protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	float m_oilelevation;

	D3DXVECTOR3 m_eye_pos;
	D3DXVECTOR3 m_Camera_Pos;
	D3DXVECTOR3 m_before_camera_pos;
	D3DXVECTOR3 m_after_camera_pos;
	
	D3DXVECTOR3 m_map_centerpos;

	D3DXVECTOR3 m_Forward;

	float m_map_radius;

	float m_map_top;


	D3DXVECTOR3 m_player_pos;
	float m_player_radius;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
