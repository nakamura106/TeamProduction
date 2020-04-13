#include "../Engine/Camera.h"
#ifndef COLLISION_H_
#define COLLISION_H_

//enum class HitObject :int
//{
//	Player,
//	Block,
//	Item,
//	Map,
//	MapUp,
//	PlayerEye,
//	MaxObject
//};

class Collision
{
public:
	//bool UpdateHit(HitObject tareget, HitObject tareget2);

	/*�v���C���[�ƃA�C�e��(���Ƌ�)
		���A��A�O�����F�v���C���[���W
		��l�A�܁A�Z�����F�A�C�e�����W
		�掵�����@�@�@�@�F�v���C���[�̔��a
		�攪�����@�@�@�@�F�A�C�e���̔��a
	*/
	bool HitItemPlayer(D3DXVECTOR3 player_pos_, D3DXVECTOR3 item_pos_, float player_radius, float item_radius);


	/*�u���b�N�ƃA�C�e��(���Ɨ�����)
		���A��A�O�����F�u���b�N�̍��W
		��l�A�܁A�Z�����F�A�C�e���̍��W
		�掵�����@�@�@�@�F�u���b�N�̕�
		�攪�����@�@�@�@�F�A�C�e���̔��a
	*/
	bool HitItemBox(D3DXVECTOR3 block_pos_, D3DXVECTOR3 item_pos_, float block_width_, float item_radius_);
	

	/*�u���b�N�ƃv���C���[(���Ɨ�����)
		���A��A�O�����F�u���b�N�̍��W
		��l�A�܁A�Z�����F�v���C���[���W
		�掵�����@�@�@�@�F�u���b�N�̕�
		�攪�����@�@�@�@�F�v���C���[�̔��a
	*/
	bool HitBox(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);

	//�u���b�N�̏�ɂ��邩�ǂ���
	bool HitBoxTop(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);
	
#pragma region �u���b�N�ƃv���C���[�̂��ꂼ��̎��̂����蔻��(�G��Ȃ��Ă悢) 
	//�����̂Ƌ���Y������
	//bool HitBoxTopUnder(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_wight_, float player_radius_);

	//�����̂Ƌ���X������
	//bool HitBoxRightLeft(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_wight_, float player_radius_);

	//�����̂Ƌ���Z������
	//bool HitBoxInnerBack(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_wight_, float player_radius_);
#pragma endregion

	/*�v���C���[�ƃ}�b�v(�~�Ɠ��ډ~�̂����蔻��)
		���A������F�v���C���[���W
		��O�A�l�����F�}�b�v�̍��W
		��܈����@�@�F�v���C���[�̔��a
		��Z�����@�@�F�}�b�v�̔��a
	*/
	bool HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_);


	/*�v���C���[�̎����ƃu���b�N(�����Ɨ����̂̂����蔻��)
		���A��A�O�����F�u���b�N�̍��W
		��l�����@�@�@�@�F�u���b�N�̕�
		��܈����@�@�@�@�F�u���b�N�̉��s��
	*/
	bool HitVisualBox(D3DXVECTOR3 block_pos_, float block_width_, float block_depth);
	
	//�e�����̖̂ʂƂ̂����蔻��(�G��Ȃ��Ă悢)
	bool HitVisualBox2(D3DXVECTOR3 block_pos_, float block_width_, float block_depth, float x, float y, float z);


	/*�v���C���[�ƓV��̂����蔻��(�p�x�ł����蔻��)
		���A��A�O�����F�v���C���[�̍��W
		��l�A�܁A�Z�����F�}�b�v�̒���̒��S���W
		�掵�A���A������F�}�b�v�̒�ӂ̒��S���W
		��\�����@�@�@�@�F���E�p�x
	*/
	bool HitAngle(float player_pos_x, float player_pos_y, float player_pos_z, float maptop_pos_x, float maptop_pos_y, float maptop_pos_z, float mapunder_pos_x, float mapunder_pos_y, float mapunder_pos_z, float flg_angle);
private:
	CAMERA* p_camera;


};


#endif