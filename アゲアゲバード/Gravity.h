#ifndef GRAVITY_H_
#define GRAVITY_H_

struct Gravity {
public:
	Gravity();

public:
	/** 重力を加えるための関数
	* 引数：オブジェクトのy座標
	*/
	void AddGravity(float pos_y_, float v0_);

	void ResetPalam();

	/** 重力を加えた後の位置を返す関数
	* y座標を返す
	*/
	float GetPosY()
	{
		return pos_y;
	}

private:
	float pos_y;	// オブジェクトの座標を保持
	float t;		// 1秒
	float flame;	// 1フレーム当たりの時間
	float v0;		// 初速度
	float g;		// 重力加速度
};

#endif