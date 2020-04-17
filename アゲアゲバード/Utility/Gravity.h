#ifndef GRAVITY_H_
#define GRAVITY_H_

struct Gravity {
public:
	Gravity();

public:
	/** privateの変数を全て初期化する関数 */
	void ResetPalam();

	/** 自由落下計算関数
	* 第一引数：オブジェクトのy座標
	* 
	*/
	void FreeFall(float pos_y_);

	/** 投げ上げ計算関数
	* 第一引数：オブジェクトのy座標
	* 第二引数：上向きに移動する力
	*/
	void ThrowingUp(float pos_y_, float v0_);

	/** 重力を加えた後の位置を返す関数
	* 戻り値：y座標を返す
	*/
	float GetPosY() {
		return pos_y;
	}

private:
	float pos_y;	// オブジェクトの座標を保持
	float t;		// 秒
	float flame;	// 1フレーム当たりの時間
	float v0;		// 初速度
	float g;		// 重力加速度
};

#endif