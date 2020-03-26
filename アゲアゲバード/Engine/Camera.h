#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>
#include "../Gravity.h"

class CAMERA
{
public:
	CAMERA(float camera_x, float camera_y, float camera_z) :
		m_WalkSpeed(0.5f),
		m_SprintSpeed(6.0f)
	{
		m_CameraPos.x = camera_x;
		m_CameraPos.y = camera_y;
		m_CameraPos.z = camera_z;

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

		m_jamp = 10.0f;
		jflag = false;

		D3DXMatrixIdentity(&m_MatView);
	}
	
	// �J�������W�̍X�V
	void Update();

	// �J�����̈ړ�
	void Move();

	void MouseRotate();

	// �J�����̑O�����x�N�g�����o��
	D3DXVECTOR3 GetCameraForward();

	D3DXVECTOR3 GetCamaraPos()
	{
		return m_CameraPos;
	}

	D3DXVECTOR3 GetEyePos()
	{
		return m_EyePos;
	}

	float GetYaw()
	{
		return m_Yaw;
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
	float m_jamp;
	bool jflag;
	Gravity grav;

};

#endif