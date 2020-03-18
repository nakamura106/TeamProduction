#include "Camera.h"
#ifndef COLLISION_H_
#define COLLISION_H_

class Collision
{
public:
	/*プレイヤーとアイテム(球と球)
		第一、二、三引数：プレイヤー座標
		第四、五、六引数：アイテム座標
		第七引数　　　　：プレイヤーの半径
		第八引数　　　　：アイテムの半径
	*/
	bool HitItem(float player_pos_x_, float player_pos_y_, float player_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float player_radius, float item_radius);


	/*ブロックとプレイヤー(球と立方体)
		第一、二、三引数：ブロックの座標
		第四、五、六引数：プレイヤー座標
		第七引数　　　　：ブロックの幅
		第八引数　　　　：ブロックの高さ
		第十引数　　　　：ブロックの奥行き
		第十一引数　　　：プレイヤーの半径
	*/
	bool HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,
		float block_height, float block_wight_, float block_depth_, float player_radius_);

#pragma region ブロックとプレイヤーのそれぞれの軸のあたり判定(触らなくてよい) 
	//立方体と球のY軸判定
	bool HitBoxTopUnder(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_);

	//立方体と球のX軸判定
	bool HitBoxRightLeft(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_);

	//立方体と球のZ軸判定
	bool HitBoxInnerBack(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_height_, float block_wight_, float block_depth_, float player_radius_);
#pragma endregion

	/*プレイヤーとマップ(円と内接円のあたり判定)
		第一、二引数：プレイヤー座標
		第三、四引数：マップの座標
		第五引数　　：プレイヤーの半径
		第六引数　　：マップの半径
	*/
	bool HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_);

	/*プレイヤーの視線とブロック(線分と立方体のあたり判定)
		第一、二、三引数：ブロックの座標
		第四引数　　　　：ブロックの幅
		第五引数　　　　：ブロックの高さ
		第六引数　　　　：ブロックの奥行き
	*/
	bool HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth);
	//各立方体の面とのあたり判定(触らなくてよい)
	bool HitBox2(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth, float x, float y, float z);

	/*プレイヤーと天井のあたり判定(角度であたり判定)
		第一、二、三引数：プレイヤーの座標
		第四、五、六引数：マップの頂上の中心座標
		第七、八、九引数：マップの底辺の中心座標
		第十引数　　　　：限界角度
	*/
	bool HitAngle(float player_pos_x, float player_pos_y, float player_pos_z, float maptop_pos_x, float maptop_pos_y, float maptop_pos_z, float mapunder_pos_x, float mapunder_pos_y, float mapunder_pos_z, float flg_angle);
private:
	CAMERA* p_camera;
};


#endif