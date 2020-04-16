#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Collision.h"

enum class PlayerStatus {
	WAIT,		// �ҋ@
	WALK,		// ����
	//SPRINT,	// ����
	JAMP,		// �W�����v
	THROW,		// ������
};

struct PlayerInfo {
	PlayerStatus state;				// ���

	D3DXVECTOR3 eye;				// �v���C���[�̌����Ă������
	D3DXVECTOR3 upvec;				// �v���C���[�̏�����̃x�N�g��
	D3DXVECTOR3 amount_of_movement;	// �ړ���

	float walk_speed;				// �����Ă���Ƃ��̃X�s�[�h
	float sprint_speed;				// �����Ă���Ƃ��̃X�s�[�h
	float speed;					// �ړ��p�̃X�s�[�h

	float radius;					// ���a(�v���C���[�̓����蔻����Ƃ邽�߂�)

	float jamp_power;				// �W�����v��
	//float throw_power;			// �������

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

	private:
		PlayerInfo m_pinfo;

		CAMERA* m_p_camera;

		Collision* m_p_collision;

		Gravity m_grav;		// �d��

		bool m_jflag;		// �W�����v�t���O
	};
}
#endif