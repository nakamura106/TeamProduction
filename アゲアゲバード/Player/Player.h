#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Manager/FbxManager.h"
#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"

enum class PlayerStatus {
	WAIT,		// 待機
	WALK,		// 歩く
	SPRINT,		// 疾走
	JAMP,		// ジャンプ
	THROW,		// 投げる
};

struct PlayerInfo {
	PlayerStatus state;			// 状態

	//D3DXVECTOR3 pos;			// プレイヤーの座標
	D3DXVECTOR3 eye;			// プレイヤーの向いている方向

	float throw_power;			// 投げる力

	//float mass;				// 質量
};

struct MatrixInfo {
	D3DXMATRIX mat_world;	// ワールド
	D3DXMATRIX mat_scale;	// 拡縮
	D3DXMATRIX mat_rot;		// 回転
	D3DXMATRIX mat_rot_x;	// 回転x軸
	D3DXMATRIX mat_rot_y;	// 回転y軸
	D3DXMATRIX mat_rot_z;	// 回転z軸
	D3DXMATRIX mat_trans;	// 移動
};

namespace Character
{
	class Player : public ObjectBase {
	public:
		Player(float pos_x_, float pos_y_, float pos_z_);
		~Player();

	public:
		void Update();
		void Draw();

	private:
		void Move();

	private:

		FBXMeshData m_fbx_mesh_data;

		PlayerInfo m_pinfo;
		//MatrixInfo m_minfo;

		CAMERA* m_p_camera;
	};
}
#endif