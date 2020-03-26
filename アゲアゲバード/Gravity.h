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

	/** 重力を加えた後の位置を返す関数
	* y座標を返す
	*/
	float GetPosY()
	{
		return pos_y;
	}

private:
	float pos_y;
	float t;
	float v0;
	float g;
};

#endif