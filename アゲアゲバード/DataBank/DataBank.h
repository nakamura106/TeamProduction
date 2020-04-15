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

	void SetMapCenterPos(D3DXVECTOR3 map_centerpos_);

	void SetMapRadius(float map_radius_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	// 移動前のプレイヤーの位置を保存する
	void SetBeforePlayerPos(D3DXVECTOR3 player_pos_);
	// 移動後のプレイヤーの位置を保存する
	void SetAfterPlayerPos(D3DXVECTOR3 player_pos_);
	// プレイヤーの半径を保存する
	void SetPlayerRadius(float player_radius_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

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

	// 移動前のプレイヤーの位置を取得する
	D3DXVECTOR3 GetBeforePlayerPos() {
		return m_before_player_pos;
	}
	// 移動後のプレイヤーの位置を取得する
	D3DXVECTOR3 GetAfterPlayerPos() {
		return m_after_player_pos;
	}
	// プレイヤーの半径を取得する
	float GetPlayerRadius(float player_radius_) {
		return m_player_radius;
	}

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
	
	D3DXVECTOR3 m_map_centerpos;
	float m_map_radius;

	D3DXVECTOR3 m_before_player_pos;
	D3DXVECTOR3 m_after_player_pos;
	float m_player_radius;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
