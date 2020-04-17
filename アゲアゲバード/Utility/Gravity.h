#ifndef GRAVITY_H_
#define GRAVITY_H_

struct Gravity {
public:
	Gravity();

public:
	/** private�̕ϐ���S�ď���������֐� */
	void ResetPalam();

	/** ���R�����v�Z�֐�
	* �������F�I�u�W�F�N�g��y���W
	* 
	*/
	void FreeFall(float pos_y_);

	/** �����グ�v�Z�֐�
	* �������F�I�u�W�F�N�g��y���W
	* �������F������Ɉړ������
	*/
	void ThrowingUp(float pos_y_, float v0_);

	/** �d�͂���������̈ʒu��Ԃ��֐�
	* �߂�l�Fy���W��Ԃ�
	*/
	float GetPosY() {
		return pos_y;
	}

private:
	float pos_y;	// �I�u�W�F�N�g�̍��W��ێ�
	float t;		// �b
	float flame;	// 1�t���[��������̎���
	float v0;		// �����x
	float g;		// �d�͉����x
};

#endif