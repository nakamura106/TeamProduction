#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Collision.h"

enum class PlayerStatus {
	WAIT,		// 待機
	WALK,		// 歩く
	SPRINT,		// 疾走
	JAMP,		// ジャンプ
	THROW,		// 投げる
};

struct PlayerInfo {
	PlayerStatus state;			// 状態

	D3DXVECTOR3 eye;			// プレイヤーの向いている方向

	float radius;
	//float throw_power;		// 投げる力
};

namespace Character
{
	class Player : public ObjectBase {
	public:
		Player(float pos_x_, float pos_y_, float pos_z_);
		~Player() {}

	public:
		void Update()override;

	private:
		void Move();
		void CollisionDetection();

	private:
		PlayerInfo m_pinfo;

		CAMERA* m_p_camera;

		Collision* m_p_collision;
	};
}
#endif