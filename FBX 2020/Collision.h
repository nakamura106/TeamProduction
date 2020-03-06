#include "Camera.h"
#ifndef COLLISION_H_
#define COLLISION_H_

class Collision
{
public:
	bool HitItem(float circleA_pos_x, float circleA_pos_y, float circleA_pos_z, float circleB_pos_x, float circleB_pos_y, float circleB_pos_z, float circleA_radius, float circleB_radius);

	bool HitBox(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z,
		float block_height, float block_wight, float block_depth, float ball_radius_top, float ball_radius_under, float ball_radius_left, float ball_radius_right,
		float ball_radius_inner, float ball_radius_back);

	bool HitBoxInnerBack(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z, float block_height, float block_wight, float block_depth, float ball_radius_inner, float ball_radius_back);

	bool HitBoxTopUnder(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z, float block_height, float block_wight, float block_depth, float ball_radius_top, float ball_radius_under);

	bool HitBoxRightLeft(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z, float block_height, float block_wight, float block_depth, float ball_radius_left, float ball_radius_right);

	bool HitMap(float circleA_pos_x, float circleA_pos_z, float circleB_pos_x, float circleB_pos_z, float circleA_radius, float circleB_radius);

	bool HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth, float x, float y, float z);

	bool HitBox2(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth, float x, float y, float z);
private:
	CAMERA* p_camera;
};


#endif