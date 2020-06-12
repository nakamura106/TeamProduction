#include "../Engine/Camera.h"
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
	bool HitItemPlayer(D3DXVECTOR3 player_pos_, D3DXVECTOR3 item_pos_, float player_radius, float item_radius);


	/*ブロックとアイテム(球と立方体)
		第一、二、三引数：ブロックの座標
		第四、五、六引数：アイテムの座標
		第七引数　　　　：ブロックの幅
		第八引数　　　　：アイテムの半径
	*/
	bool HitItemBox(D3DXVECTOR3 block_pos_, D3DXVECTOR3 item_pos_, float block_width_, float item_radius_);
	

	/*ブロックとプレイヤー(球と立方体)
		第一、二、三引数：ブロックの座標
		第四、五、六引数：プレイヤー座標
		第七引数　　　　：ブロックの幅
		第八引数　　　　：プレイヤーの半径
	*/
	bool HitBox(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);

	bool HitBoxSurface(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);

	bool HitBox2(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);

	bool HitBoxVec(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);
	//ブロックの上にいるかどうか
	bool HitBoxTop(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);
	
#pragma region ブロックとプレイヤーのそれぞれの軸のあたり判定(触らなくてよい) 
	//立方体と球のY軸判定
	bool HitBoxTopUnder(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_wight_, float player_radius_);

	//立方体と球のX軸判定
	bool HitBoxRightLeft(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_width_, float player_radius_);

	//立方体と球のZ軸判定
	bool HitBoxInnerBack(D3DXVECTOR3 block_pos_, D3DXVECTOR3 player_pos_, float block_wight_, float player_radius_);
#pragma endregion

	/*プレイヤーとマップ(円と内接円のあたり判定)
		第一、二引数：プレイヤー座標
		第三、四引数：マップの座標
		第五引数　　：プレイヤーの半径
		第六引数　　：マップの半径
	*/
	bool HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_);

	/*プレイヤーと天井のあたり判定(角度であたり判定)
		第一、二、三引数：プレイヤーの座標
		第四、五、六引数：マップの頂上の中心座標
		第七、八、九引数：マップの底辺の中心座標
		第十引数　　　　：限界角度
	*/
	bool HitAngle(D3DXVECTOR3 player_pos_, D3DXVECTOR3 maptop_pos_, D3DXVECTOR3 mapunder_pos_, float flg_angle);

	bool HitOil(D3DXVECTOR3 player_pos_, D3DXVECTOR3 maptop_pos_, float player_radius_, float oil_radius_);
	/*プレイヤーの視線とブロック(線分と立方体のあたり判定)
		第一、二、三引数：ブロックの座標
		第四引数　　　　：ブロックの幅
		第五引数　　　　：ブロックの奥行き
	*/
	bool HitVisualBox(D3DXVECTOR3 block_pos_, float block_width_, float block_depth);
	
	//各立方体の面とのあたり判定(触らなくてよい)
	bool HitVisualBox2(D3DXVECTOR3 block_pos_, float block_width_, float block_depth, float x, float y, float z);


	
private:
	//CAMERA* p_camera;


};


#endif