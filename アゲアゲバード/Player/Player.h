#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Collision.h"

enum class PlayerStatus {
	WAIT,		// 待機
	WALK,		// 歩く
	//SPRINT,	// 疾走
	JAMP,		// ジャンプ
	THROW,		// 投げる
};

struct PlayerInfo {
	PlayerStatus state;				// 状態

	D3DXVECTOR3 eye;				// プレイヤーの向いている方向
	D3DXVECTOR3 upvec;				// プレイヤーの上向きのベクトル
	D3DXVECTOR3 amount_of_movement;	// 移動量

	float walk_speed;				// 歩いているときのスピード
	float sprint_speed;				// 走っているときのスピード
	float speed;					// 移動用のスピード

	float radius;					// 半径(プレイヤーの当たり判定をとるための)

	float jamp_power;				// ジャンプ力
	//float throw_power;			// 投げる力

	D3DXVECTOR2 item;
};

namespace Character
{
	class Player : public ObjectBase {
	public:
		Player(float pos_x_, float pos_y_, float pos_z_);
		~Player() {}

	public:
		void Update()override;
		void Draw()override;

	private:
		void Move();
		void CollisionDetection();
		void Animation();
		void SetBlock();
		void ThrowingItems();

	private:
		PlayerInfo m_pinfo;			// プレイヤー情報

		CAMERA* m_p_camera;			// カメラ

		Collision* m_p_collision;	// 当たり判定

		Gravity m_grav;				// 重力

		D3DXVECTOR3 m_camera_pos;

		int m_blockstock;			//ブロックの所持数

		float m_item_effect_time;	// アイテムの効果量をはかる

		bool m_jflag;				// ジャンプした時のフラグ
		bool m_stand_flag;			// 立っている時のフラグ
		bool m_item_hit_flag;		// アイテムに当たった時のフラグ
	};
}
#endif