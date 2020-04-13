#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>
#include "../Utility/Gravity.h"

class CAMERA
{
public:
	CAMERA(D3DXVECTOR3 pos_) :
		m_WalkSpeed(0.5f),
		m_SprintSpeed(6.0f)
	{
		m_CameraPos.x = pos_.x;
		m_CameraPos.y = pos_.y + 0.5;	// ������(FirstPerson�p)
		m_CameraPos.z = pos_.z;

		m_EyePos.x = 0.0f;
		m_EyePos.y = 5.0f;
		m_EyePos.z = -.0f;

		m_CameraUp.x = 0.0f;
		m_CameraUp.y = 1.0f;
		m_CameraUp.z = 0.0f;

		m_RotateSpeed = 0.05f;

		m_Yaw = 0.0f;
		m_Pitch = 0.0f;
		m_Roll = 0.0f;

		m_Speed = m_WalkSpeed;

		m_jamp_power = 3.0f;
		m_jflag = false;

		D3DXMatrixIdentity(&m_MatView);
	}
	
	// �J�������W�̍X�V
	void Update();

	// �J�����̈ړ�
	void Move();

	void MouseRotate();

	void StickRotate();

	D3DXVECTOR3 GetCamaraPos() {
		return m_CameraPos;
	}

	D3DXVECTOR3 GetEyePos() {
		return m_EyePos;
	}

	float GetYaw() {
		return m_Yaw;
	}
	float GetPitch() {
		return m_Pitch;
	}
	float GetRoll() {
		return m_Roll;
	}


private:
	/* �J�����̈ړ����x Walk */
	const float m_WalkSpeed;

	/* �J�����̈ړ����x Sprint */
	const float m_SprintSpeed;

	/* �J�����̈ʒu */
	D3DXVECTOR3 m_CameraPos;

	/* �����_ */
	D3DXVECTOR3 m_EyePos;

	/* �J�����̏�����̃x�N�g�� */
	D3DXVECTOR3 m_CameraUp;

	/* �J�����̃r���[����ۑ�����ϐ� */
	D3DXMATRIX m_MatView;

	/* �p�x */
	float m_Rad;

	/* ��]���x */
	float m_RotateSpeed;

	/* X����] */
	float m_Yaw;

	/* Y����] */
	float m_Pitch;

	/* Z����] */
	float m_Roll;

	/* �X�s�[�h */
	float m_Speed;

	/* �ړ����x */
	D3DXVECTOR3 m_Velocity;


	/* �W�����v�� */
	float m_jamp_power;
	/* �W�����v�t���O */
	bool m_jflag;
	/* �d�� */
	Gravity m_grav;
	
};

#endif