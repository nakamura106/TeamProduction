#ifndef GRAVITY_H_
#define GRAVITY_H_

struct Gravity {
public:
	Gravity();

public:
	/** �d�͂������邽�߂̊֐�
	* �����F�I�u�W�F�N�g��y���W
	*/
	void AddGravity(float pos_y_, float v0_);

	/** �d�͂���������̈ʒu��Ԃ��֐�
	* y���W��Ԃ�
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