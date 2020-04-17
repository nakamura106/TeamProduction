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
		void Animation();

	private:
		PlayerInfo m_pinfo;			// �v���C���[���

		CAMERA* m_p_camera;			// �J����

		Collision* m_p_collision;	// �����蔻��

		Gravity m_grav;				// �d��

		float m_item_effect_time;	// �A�C�e���̌��ʗʂ��͂���

		bool m_jflag;				// �W�����v�������̃t���O
		bool m_stand_flag;			// �����Ă��鎞�̃t���O
		bool m_item_hit_flag;		// �A�C�e���ɓ����������̃t���O
	};
}
#endif