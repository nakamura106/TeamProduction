#include "Collision.h"
#include <math.h>
#include <d3dx9.h>
#include "Vec.h"
#include "../DataBank/DataBank.h"

//プレイヤーとアイテム
bool Collision::HitItemPlayer(D3DXVECTOR3 player_pos_, D3DXVECTOR3 item_pos_, float player_radius, float item_radius)
{
	float x = player_pos_.x - item_pos_.x;
	float y = player_pos_.y - item_pos_.y;
	float z = player_pos_.z - item_pos_.z;

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

//立方体と球の判定
bool Collision::HitItemBox(D3DXVECTOR3 block_pos_, D3DXVECTOR3 item_pos_, float block_width_, float item_radius_)
{
	if (item_pos_.x + item_radius_ >= block_pos_.x - (block_width_ / 2) && item_pos_.x - item_radius_ <= block_pos_.x + (block_width_ / 2)
		&& item_pos_.y + item_radius_ >= block_pos_.y - (block_width_ / 2) && item_pos_.y - item_radius_ <= block_pos_.y + (block_width_ / 2)
		&& item_pos_.z + item_radius_ >= block_pos_.z - (block_width_ / 2) && item_pos_.z - item_radius_ <= block_pos_.z + (block_width_ / 2))
	{
		return true;
	}

	return false;
}

#pragma region ブロックとプレイヤー
//立方体と球の判定
bool Collision::HitBox(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{
	if (HitBoxSurface(block_pos_, player_pos_, block_width_, player_radius_) == true)
	{
		return true;
	}
	/*else if (HitBoxVec(block_pos_, player_pos_, block_width_, player_radius_) == true)
	{
		return true;
	}*/

	return false;
}

//ブロックの上にいるかどうか
bool Collision::HitBoxTop(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{
	if (player_pos_.x + player_radius_ >= block_pos_.x - (block_width_ / 2) + 5.0f && player_pos_.x - player_radius_ <= block_pos_.x + (block_width_ / 2) + 5.0f
		&& player_pos_.y + player_radius_ >= block_pos_.y - (block_width_ / 2) + 5.0f && player_pos_.y - player_radius_ <= block_pos_.y + (block_width_ / 2) + 5.0f
		&& player_pos_.z + player_radius_ >= block_pos_.z - (block_width_ / 2) + 5.0f && player_pos_.z - player_radius_ <= block_pos_.z + (block_width_ / 2) + 5.0f
		&& player_pos_.y > block_pos_.y + (block_width_ / 2))
	{
		return true;
	}

	return false;
}

bool Collision::HitBoxSurface(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{
	if (player_pos_.x + player_radius_ >= block_pos_.x - (block_width_ / 2) && player_pos_.x - player_radius_ <= block_pos_.x + (block_width_ / 2)
		&& player_pos_.y + player_radius_ >= block_pos_.y - (block_width_ / 2) && player_pos_.y - player_radius_ <= block_pos_.y + (block_width_ / 2)
		&& player_pos_.z + player_radius_ >= block_pos_.z - (block_width_ / 2) && player_pos_.z - player_radius_ <= block_pos_.z + (block_width_ / 2))
	{
		return true;
	}

	return false;
}

bool Collision::HitBoxVec(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{

	float a = (block_pos_.x + block_width_) - player_pos_.x;
	float b = (block_pos_.y + block_width_) - player_pos_.y;
	float c = sqrtf(a * a + b * b);

	if (c <= player_radius_)
	{
		return true;
	}
	return false;

}

#pragma region 使わない
bool Collision::HitBox2(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{
	//球と立方体の上下判定
	if (HitBoxTopUnder(block_pos_, player_pos_, block_width_, player_radius_) == true)
	{
		return true;
	}
	//球と立方体の左右判定
	if (HitBoxRightLeft(block_pos_, player_pos_, block_width_, player_radius_) == true)
	{
		return true;
	}
	//球と立方体の前後判定
	if (HitBoxInnerBack(block_pos_, player_pos_, block_width_, player_radius_) == true)
	{
		return true;
	}

	return false;
}



//立方体と球のY軸判定
bool Collision::HitBoxTopUnder(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{
	if (player_pos_.x >= block_pos_.x - (block_width_ / 2) && player_pos_.x <= block_pos_.x + (block_width_ / 2)
		&& player_pos_.y + player_radius_ >= block_pos_.y - (block_width_ / 2) && player_pos_.y - player_radius_ <= block_pos_.y + (block_width_ / 2)
		&& player_pos_.z >= block_pos_.z + (block_width_ / 2) && player_pos_.z <= block_pos_.z - (block_width_ / 2))
	{
		return true;
	}

	return false;
}

//立方体と球のX軸判定
bool Collision::HitBoxRightLeft(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_)
{
	if (player_pos_.x + player_radius_ >= block_pos_.x - (block_width_ / 2) && player_pos_.x - player_radius_ <= block_pos_.x + (block_width_ / 2)
		&& player_pos_.y >= block_pos_.y - (block_width_ / 2) && player_pos_.y <= block_pos_.y + (block_width_ / 2)
		&& player_pos_.z >= block_pos_.z + (block_width_ / 2) && player_pos_.z <= block_pos_.z - (block_width_ / 2))
	{
		return true;
	}
	return false;
}

//立方体と球のZ軸判定
bool Collision::HitBoxInnerBack(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_,  float block_width_, float player_radius_)
{
	if (player_pos_.x >= block_pos_.x - (block_width_ / 2) && player_pos_.x <= block_pos_.x + (block_width_ / 2)
		&& player_pos_.y >= block_pos_.y- (block_width_ / 2) && player_pos_.y <= block_pos_.y + (block_width_ / 2)
		&& player_pos_.z + player_radius_ >= block_pos_.z - (block_width_ / 2) && player_pos_.z - player_radius_ <= block_pos_.z + (block_width_ / 2))
	{
		return true;
	}
	return false;
}
#pragma endregion

#pragma endregion

#pragma region プレイヤーとマップのあたり判定
//プレイヤーと壁のあたり判定(円と内接円)
bool Collision::HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_)
{
	//全体を上から見てプレイヤーと壁は円であるから

	float x = player_circle_pos_x_ - map_circle_pos_x_;
	float z = player_circle_pos_z_ - map_circle_pos_z_;

	float c = sqrtf(x * x + z * z);

	float sub_radius = map_circle_radius_ - player_circle_radius_;

	if (c >= sub_radius)
	{
		return true;
	}
	else
		false;
}

//プレイヤーと天井
bool Collision::HitAngle(D3DXVECTOR3 player_pos_, D3DXVECTOR3 maptop_pos_, D3DXVECTOR3 mapunder_pos_, float flg_angle)
{
	D3DXVECTOR3 player_vec;
	D3DXVECTOR3 map_vec;

	player_vec.x = player_pos_.x - maptop_pos_.x;
	player_vec.y = player_pos_.y - maptop_pos_.y;
	player_vec.z = player_pos_.z - maptop_pos_.z;

	map_vec.x = maptop_pos_.x - mapunder_pos_.x;
	map_vec.y = maptop_pos_.y - mapunder_pos_.y;
	map_vec.z = maptop_pos_.z - mapunder_pos_.z;


	float angle = acosf((player_vec.x * map_vec.x + player_vec.y * map_vec.y + player_vec.z * map_vec.z) /
		(sqrtf(player_vec.x * player_vec.x) * sqrtf(player_vec.y * player_vec.y) * sqrtf(player_vec.z * player_vec.z)));

	angle = angle + 180 / 3.1415f;

	if (angle >= flg_angle && player_pos_.y >= 85.0f)
	{
		return true;
	}
	else
		return false;
}

//プレイヤーと注がれる油
bool Collision::HitOil(D3DXVECTOR3 player_pos_, D3DXVECTOR3 maptop_pos_, float player_radius_, float oil_radius_)
{
	float x = player_pos_.x - maptop_pos_.x;
	float z = player_pos_.z - maptop_pos_.z;

	float c = sqrtf((x * x) + (z * z));

	float radius = player_radius_ + oil_radius_;

	if (c <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

//プレイヤーの視界のあたり判定
bool Collision::HitVisualBox(D3DXVECTOR3 block_pos_, float block_width_, float block_depth_)
{
	//前面
	if (HitVisualBox2(block_pos_, 0.0f, block_depth_, 0.0f, 0.0f, 1.0f) == true)
	{
		return true;
	}
	//後面
	if (HitVisualBox2(block_pos_, 0.0f, -block_depth_, 0.0f, 0.0f, -1.0f) == true)
	{
		return true;
	}
	//左面
	if (HitVisualBox2(block_pos_, -block_width_, 0.0f, -1.0f, 0.0f, 0.0f) == true)
	{
		return true;
	}
	//右面
	if (HitVisualBox2(block_pos_, block_width_, 0.0f, 1.0f, 0.0f, 0.0f) == true)
	{
		return true;
	}
}

//立方体の面とのあたり判定(触らない)
bool Collision::HitVisualBox2(D3DXVECTOR3 block_pos_, float block_width_, float block_depth, float x, float y, float z)
{
	//立方体の面の中点
	D3DXVECTOR3 P(block_pos_.x + block_width_ / 2, block_pos_.y, block_pos_.z + block_depth / 2);

	//法線ベクトル
	D3DXVECTOR3 N(x, y, z);

	//正規化
	float lenght = sqrtf(N.x * N.x + N.y * N.y * N.z * N.z);

	N.x = N.x / lenght;
	N.y = N.y / lenght;
	N.z = N.z / lenght;

	DataBank* p_db = DataBank::Instance();
	D3DXVECTOR3 camera_pos = p_db->GetCameraPos();

	//カメラPos
	//D3DXVECTOR3 PA(P.x - p_camera->GetCamaraPos().x, P.y - p_camera->GetCamaraPos().x, P.z - p_camera->GetCamaraPos().z);
	D3DXVECTOR3 PA(P.x - camera_pos.x, P.y - camera_pos.y, P.z - camera_pos.z);
	//注視点Pos
	//D3DXVECTOR3 PB(P.x - p_camera->GetEyePos().x, P.y - p_camera->GetEyePos().y, P.z - p_camera->GetEyePos().z);
	D3DXVECTOR3 PB(P.x - camera_pos.x, P.y - camera_pos.y, P.z - camera_pos.z);

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


