#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Collision.h"
#include "../DataBank/Definition.h"

//前方宣言
class Item;
class Block;



namespace Character
{
	class Player : public ObjectBase {
	public:
		Player(float pos_x_, float pos_y_, float pos_z_);
		~Player() {}

	private:
		void Move();
		void CollisionDetection();
		void Animation();
		void SetBlock();
		void ThrowingItems();

	private:

		std::vector<Block*>* m_block;
		std::vector<Item*>* m_item;

		struct PlayerInfo :public ObjectData {

			//状態
			enum class PlayerStatus {
				WAIT,		// 待機
				WALK,		// 歩く
				//SPRINT,	// 疾走
				JAMP,		// ジャンプ
				THROW,		// 投げる
			}state;

			D3DXVECTOR3 eye;				// プレイヤーの向いている方向
			D3DXVECTOR3 upvec;				// プレイヤーの上向きのベクトル
			D3DXVECTOR3 amount_of_movement;	// 移動量
			D3DXVECTOR3 m_camera_pos;
			D3DXVECTOR3 m_before_player_pos;
			D3DXVECTOR3 m_after_player_pos;

			D3DXVECTOR2 item;

			CAMERA* m_p_camera;			// カメラ

			Collision* m_p_collision;	// 当たり判定

			Gravity m_grav;				// 重力

			int m_blockstock;				//ブロックの所持数
			bool m_blocset;				//ブロックの所持数


			float walk_speed;				// 歩いているときのスピード
			float sprint_speed;				// 走っているときのスピード
			float speed;					// 移動用のスピード
			float jamp_power;				// ジャンプ力
			float m_item_effect_time;	// アイテムの効果量をはかる
			//float throw_power;			// 投げる力

			bool m_jflag;				// ジャンプした時のフラグ
			bool m_stand_flag;			// 立っている時のフラグ
			bool m_item_hit_flag;		// アイテムに当たった時のフラグ
		}m_pinfo;

	public:
		void Update()override;
		void Draw()override;
		void PlusBlockStock(int plusstock_);
		D3DXVECTOR3 Amountofmovement();
		const PlayerInfo* GetPlayerData()const;
	};
}
#endif