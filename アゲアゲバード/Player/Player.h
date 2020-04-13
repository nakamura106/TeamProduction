#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Collision.h"

enum class PlayerStatus {
	WAIT,		// �ҋ@
	WALK,		// ����
	SPRINT,		// ����
	JAMP,		// �W�����v
	THROW,		// ������
};

struct PlayerInfo {
	PlayerStatus state;			// ���

	D3DXVECTOR3 eye;			// �v���C���[�̌����Ă������

	float radius;
	//float throw_power;		// �������
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
		//void CollisionDetection();

	private:
		PlayerInfo m_pinfo;

		CAMERA* m_p_camera;

		Collision* m_p_collision;
	};
}
#endif