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

	void DeleteBlockPos(int num);

	void DeleteGameData();
	
#pragma region Set

	// カメラの注視点を保存する
	void SetEyePos(D3DXVECTOR3 eyepos_);
	// カメラの位置を保存する
	void SetCameraPos(D3DXVECTOR3 camerapos_);

	void SetMapCenterPos(D3DXVECTOR3 map_centerpos_);

	void SetMapRadius(float map_radius_);

	// マップ(ポット)の頂上の中心座標を保存する
	void SetMapTop(D3DXVECTOR3 map_top_);
	// マップ(ポット)の底辺の中心座標を保存する
	void SetMapBottom(D3DXVECTOR3 map_bottom_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	// アイテムの位置を保存する
	void SetItemPos(D3DXVECTOR3 item_pos_);
	// アイテムの半径を保存する
	void SetItemRadius(float item_radius_);

	// 移動前のプレイヤーの位置を保存する
	void SetBeforePlayerPos(D3DXVECTOR3 player_pos_);
	// 移動後のプレイヤーの位置を保存する
	void SetAfterPlayerPos(D3DXVECTOR3 player_pos_);
	// プレイヤーの半径を保存する
	void SetPlayerRadius(float player_radius_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

	void SetForward(D3DXVECTOR3 forward_);

	D3DXVECTOR3 BlockInstallation(D3DXVECTOR3 pos_);

	void SetClearflag(bool clearflag_);

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
	// マップの半径
	float GetMapRadius() {
		return m_map_radius;
	}

	auto GetBlockPos() { return m_blockpos; }

	float GetOilPos() { return m_oilelevation; }

	// アイテムの位置を取得する
	D3DXVECTOR3 GetItemPos() {
		return m_item_pos;
	}
	// アイテムの半径を取得する
	float GetItemRadius() {
		return m_item_radius;
	}

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
	
	D3DXVECTOR3 GetMapTop() { return m_map_top; }
	D3DXVECTOR3 GetMapBottom() {
		return m_map_bottom;
	}

	D3DXVECTOR3 GetForward() { return m_Forward; }

	BaseScene::SceneStep GetSceneStep() { return m_scene_step; }

	BaseScene::SceneId GetSceneId() { return m_scene_id; }

	bool GetClearflag() { return m_clearflag; }

#pragma endregion

protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	bool m_clearflag;

	float m_oilelevation;

	D3DXVECTOR3 m_eye_pos;
	D3DXVECTOR3 m_Camera_Pos;
	
	D3DXVECTOR3 m_map_centerpos;

	D3DXVECTOR3 m_Forward;

	float m_map_radius;

	D3DXVECTOR3 m_map_top;
	D3DXVECTOR3 m_map_bottom;

	D3DXVECTOR3 m_item_pos;
	float m_item_radius;

	D3DXVECTOR3 m_before_player_pos;
	D3DXVECTOR3 m_after_player_pos;
	float m_player_radius;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
