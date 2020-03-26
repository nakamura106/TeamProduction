#include "Collision.h"
#include <math.h>
#include <d3dx9.h>
#include "Vec.h"

//bool Collision::UpdateHit(HitObject tareget, HitObject tareget2)
//{
//	if (tareget == HitObject::Player && tareget == HitObject::Block)
//	{
//		if (HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,
//			float block_height, float block_wight_, float block_depth_, float player_radius_) == true)
//		{
//			return true;
//		}
//	}
//	if (tareget == HitObject::Player && tareget == HitObject::Item)
//	{
//		if (HitItem(float player_pos_x_, float player_pos_y_, float player_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float player_radius, float item_radius) == true)
//		{
//			return true;
//		}
//	}
//	if (tareget == HitObject::Player && tareget == HitObject::Map)
//	{
//		if (HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_) == true)
//		{
//			return true;
//		}
//		else if (HitAngle(float player_pos_x, float player_pos_y, float player_pos_z, float maptop_pos_x, float maptop_pos_y, float maptop_pos_z, float mapunder_pos_x, float mapunder_pos_y, float mapunder_pos_z, float flg_angle) == true)
//		{
//			return true;
//		}
//	}
//
//	if (tareget == HitObject::PlayerEye && tareget == HitObject::Block)
//	{
//		if (HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth_) == true)
//		{
//			return true;
//		}
//	}
//	
//}

//プレイヤーとアイテム
bool Collision::HitItem(float player_pos_x_, float player_pos_y_, float player_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float player_radius, float item_radius)
{
	float x = player_pos_x_ - item_pos_x_;
	float y = player_pos_y_ - item_pos_y_;
	float z = player_pos_z_ - item_pos_z_;

	float c = sqrtf(x * x + y * y + z * z);

	float sum_radius = player_radius + item_radius;

	//プレイヤーとアイテムの半径の合計が2つの距離より短かったらtrue
	if (c <= sum_radius)
	{
		return true;
	}
	else
		false;
}

#pragma region ブロックとプレイヤー
//bool Collision::HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,
//	float block_height, float block_wight_, float block_depth_, float player_radius_)
//{
//	//球と立方体の上下判定
//	if (HitBox(block_pos_x_, block_pos_y_, block_pos_z_, player_pos_x_, player_pos_y_, player_pos_z_, block_height, block_wight_, block_depth_, player_radius_) == true)
//	{
//		return true;
//	}
//	//球と立方体の左右判定
//	if (HitBoxRightLeft(block_pos_x_, block_pos_y_, block_pos_z_, player_pos_x_, player_pos_y_, player_pos_z_, block_height, block_wight_, block_depth_, player_radius_) == true)
//	{
//		return true;
//	}
//	//球と立方体の前後判定
//	if (HitBoxInnerBack(block_pos_x_, block_pos_y_, block_pos_z_, player_pos_x_, player_pos_y_, player_pos_z_, block_height, block_wight_, block_depth_, player_radius_) == true)
//	{
//		return true;
//	}
//}

//立方体と球の判定
bool Collision::HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_wight_, float player_radius_)
{
	if (player_pos_x_ + player_radius_ >= block_pos_x_ - (block_wight_ / 2) && player_pos_x_ - player_radius_ <= block_pos_x_ + (block_wight_ / 2)
		&& player_pos_y_ + player_radius_ >= block_pos_y_ - (block_wight_ / 2) && player_pos_y_ - player_radius_ <= block_pos_y_ + (block_wight_ / 2)
		&& player_pos_z_ + player_radius_ >= block_pos_z_ - (block_wight_ / 2) && player_pos_z_ - player_radius_ <= block_pos_z_ + (block_wight_ / 2))
	{
		return true;
	}

	return false;
}

//立方体と球のX軸判定
//bool Collision::HitBoxRightLeft(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_)
//{
//	if (player_pos_x_ + player_radius_ >= block_pos_x_ - (block_wight_ / 2) && player_pos_x_ - player_radius_ <= block_pos_x_ + (block_wight_ / 2)
//		&& player_pos_y_ >= block_pos_y_ - (block_wight_ / 2) && player_pos_y_ <= block_pos_y_ + (block_wight_ / 2)
//		&& player_pos_z_ >= block_pos_z_ + (block_depth_ / 2) && player_pos_z_ <= block_pos_z_ - (block_depth_ / 2))
//	{
//		return true;
//	}
//	return false;
//}

//立方体と球のZ軸判定
//bool Collision::HitBoxInnerBack(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_)
//{
//	if (player_pos_x_ >= block_pos_x_ - (block_wight_ / 2) && player_pos_x_ <= block_pos_x_ + (block_wight_ / 2)
//		&& player_pos_y_ >= block_pos_y_ - (block_wight_ / 2) && player_pos_y_ <= block_pos_y_ + (block_wight_ / 2)
//		&& player_pos_z_ + player_radius_ >= block_pos_z_ - (block_wight_ / 2) && player_pos_z_ - player_radius_ <= block_pos_z_ + (block_wight_ / 2))
//	{
//		return true;
//	}
//	return false;
//}
#pragma endregion

//円と内接円のあたり判定
bool Collision::HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_)
{
	//全体を上から見てプレイヤーと壁は円であるから

	float x = player_circle_pos_x_ - map_circle_pos_x_;
	float z = player_circle_pos_z_ - map_circle_pos_z_;

	float c = sqrtf(x * x + z * z);

	float sub_radius = player_circle_radius_ - map_circle_radius_;

	if (c >= sub_radius)
	{
		return true;
	}
	else
		false;
}


bool Collision::HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_depth_)
{
	//前面
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, 0.0f, block_depth_, 0.0f, 0.0f, 1.0f) == true)
	{
		return true;
	}
	//後面
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, 0.0f, -block_depth_, 0.0f, 0.0f, -1.0f) == true)
	{
		return true;
	}
	//左面
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, -block_width_, 0.0f, -1.0f, 0.0f, 0.0f) == true)
	{
		return true;
	}
	//右面
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, block_width_, 0.0f, 1.0f, 0.0f, 0.0f) == true)
	{
		return true;
	}
}

bool Collision::HitBox2(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_depth, float x, float y, float z)
{
	//立方体の面の中点
	D3DXVECTOR3 P(block_pos_x_ + block_width_ / 2, block_pos_y_, block_pos_z_ + block_depth / 2);

	//法線ベクトル
	D3DXVECTOR3 N(x, y, z);

	//正規化
	float lenght = sqrtf(N.x * N.x + N.y * N.y * N.z * N.z);

	N.x = N.x / lenght;
	N.y = N.y / lenght;
	N.z = N.z / lenght;

	//カメラPos
	D3DXVECTOR3 PA(P.x - p_camera->GetCamaraPos().x, P.y - p_camera->GetCamaraPos().x, P.z - p_camera->GetCamaraPos().z);
	//注視点Pos
	D3DXVECTOR3 PB(P.x - p_camera->GetEyePos().x, P.y - p_camera->GetEyePos().y, P.z - p_camera->GetEyePos().z);

	//内積を求める
	float dot_PA = (PA.x * N.x) + (PA.y * N.y) + (PA.z * N.z);
	float dot_PB = (PB.x * N.x) + (PB.y * N.y) + (PB.z * N.z);

	if (dot_PA * dot_PB <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//プレイヤーと天井
bool Collision::HitAngle(float player_pos_x, float player_pos_y, float player_pos_z, float maptop_pos_x, float maptop_pos_y, float maptop_pos_z, float mapunder_pos_x, float mapunder_pos_y, float mapunder_pos_z, float flg_angle)
{
	D3DXVECTOR3 player_vec;
	D3DXVECTOR3 map_vec;

	player_vec.x = player_pos_x - maptop_pos_x;
	player_vec.y = player_pos_y - maptop_pos_y;
	player_vec.z = player_pos_z - maptop_pos_z;

	map_vec.x = maptop_pos_x - mapunder_pos_x;
	map_vec.y = maptop_pos_y - mapunder_pos_y;
	map_vec.z = maptop_pos_z - mapunder_pos_z;


	float angle = acosf((player_vec.x * map_vec.x + player_vec.y * map_vec.y + player_vec.z * map_vec.z) /
		(sqrtf(player_vec.x * player_vec.x) * sqrtf(player_vec.y * player_vec.y) * sqrtf(player_vec.z * player_vec.z)));


	if (angle >= flg_angle)
	{
		return true;
	}
	else
		return false;
}