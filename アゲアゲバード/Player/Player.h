#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Collision.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/ProductionManager.h"
#include"../Production/StartProduction.h"
#include"../Production/EndProduction.h"

//�O���錾
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

		ObjectManager* m_objectmanager = ObjectManager::Instance();
		StartProduction* m_startproduction = ProductionManager::Instance()->GetStartProduction();
		EndProduction* m_endproduction = ProductionManager::Instance()->GetEndProduction();

		struct PlayerInfo :public ObjectData {

			//���
			enum class PlayerStatus {
				WAIT,		// �ҋ@
				WALK,		// ����
				//SPRINT,	// ����
				JAMP,		// �W�����v
				THROW,		// ������
			}state;

			D3DXVECTOR3 eye;				// �v���C���[�̌����Ă������
			D3DXVECTOR3 upvec;				// �v���C���[�̏�����̃x�N�g��
			D3DXVECTOR3 amount_of_movement;	// �ړ���
			D3DXVECTOR3 m_camera_pos;
			D3DXVECTOR3 m_before_player_pos;
			D3DXVECTOR3 m_after_player_pos;

			D3DXVECTOR2 item;

			CAMERA* m_p_camera;			// �J����

			Collision* m_p_collision;	// �����蔻��

			Gravity m_grav;				// �d��

			int m_blockstock;				//�u���b�N�̏�����
			
			float walk_speed;				// �����Ă���Ƃ��̃X�s�[�h
			float sprint_speed;				// �����Ă���Ƃ��̃X�s�[�h
			float speed;					// �ړ��p�̃X�s�[�h
			float jamp_power;				// �W�����v��
			float m_item_effect_time;	// �A�C�e���̌��ʗʂ��͂���
			//float throw_power;			// �������

			bool m_jflag;				// �W�����v�������̃t���O
			bool m_stand_flag;			// �����Ă��鎞�̃t���O
			bool m_item_hit_flag;		// �A�C�e���ɓ����������̃t���O
			bool filloilfly;

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