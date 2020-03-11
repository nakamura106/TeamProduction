#include "Camera.h"
#ifndef COLLISION_H_
#define COLLISION_H_

class Collision
{
public:
	/*�v���C���[�ƃA�C�e��(���Ƌ�)
	    ���A��A�O�����F�v���C���[���W
		��l�A�܁A�Z�����F�A�C�e�����W
		�掵�����@�@�@�@�F�v���C���[�̔��a
		�攪�����@�@�@�@�F�A�C�e���̔��a
	*/
	bool HitItem(float player_pos_x_, float player_pos_y_, float player_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float player_radius, float item_radius);


	/*�u���b�N�ƃv���C���[(���Ɨ�����)
		���A��A�O�����F�u���b�N�̍��W
		��l�A�܁A�Z�����F�v���C���[���W
		�掵�����@�@�@�@�F�u���b�N�̕�
		�攪�����@�@�@�@�F�u���b�N�̍���
		��\�����@�@�@�@�F�u���b�N�̉��s��
		��\������@�@�@�F�v���C���[�̔��a
	*/
	bool HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,
		float block_height, float block_wight_, float block_depth_, float player_radius_);

#pragma region �u���b�N�ƃv���C���[�̂��ꂼ��̎��̂����蔻��(�G��Ȃ��Ă悢) 
	//�����̂Ƌ���Y������
	bool HitBoxTopUnder(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_);

	//�����̂Ƌ���X������
	bool HitBoxRightLeft(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_);

	//�����̂Ƌ���Z������
	bool HitBoxInnerBack(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_);
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
		��܈����@�@�@�@�F�u���b�N�̍���
		��Z�����@�@�@�@�F�u���b�N�̉��s��
	*/
	bool HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth);
	//�e�����̖̂ʂƂ̂����蔻��(�G��Ȃ��Ă悢)
	bool HitBox2(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth, float x, float y, float z);
private:
	CAMERA* p_camera;
};


#endif