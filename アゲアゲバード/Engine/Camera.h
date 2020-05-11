#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>
#include "../Utility/Gravity.h"

class CAMERA
{
private:
	/* �J�����̈ړ����x Walk */
	const float m_WalkSpeed;

	/* �J�����̈ړ����x Sprint */
	const float m_SprintSpeed;

	struct CAMERA_DATA {
	
		/* �J�����̈ʒu */
		D3DXVECTOR3 m_CameraPos;

		/* �����_ */
		D3DXVECTOR3 m_EyePos;

		/* �J�����̏�����̃x�N�g�� */
		D3DXVECTOR3 m_CameraUp;

		D3DXVECTOR3 m_Forward;

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
		//D3DXVECTOR3 m_Velocity;

		bool m_startflag;
	}m_cameradata;

public:
	CAMERA(D3DXVECTOR3 pos_) :
		m_WalkSpeed(0.5f),
		m_SprintSpeed(6.0f)
	{
		m_cameradata.m_CameraPos.x = pos_.x;
		m_cameradata.m_CameraPos.y = pos_.y;//+ 0.5;	// ������(FirstPerson�p)
		m_cameradata.m_CameraPos.z = pos_.z;

		m_cameradata.m_EyePos.x = 0.0f;
		m_cameradata.m_EyePos.y = 0.0f;
		m_cameradata.m_EyePos.z = 0.0f;

		m_cameradata.m_CameraUp.x = 0.0f;
		m_cameradata.m_CameraUp.y = 1.0f;
		m_cameradata.m_CameraUp.z = 0.0f;

		m_cameradata.m_RotateSpeed = 0.05f;

		m_cameradata.m_Yaw = 0.0f;
		m_cameradata.m_Pitch = 0.0f;
		m_cameradata.m_Roll = 0.0f;

		m_cameradata.m_Speed = m_WalkSpeed;

		m_cameradata.m_startflag = false;

		D3DXMatrixIdentity(&m_cameradata.m_MatView);
	}
	
	// �J�������W�̍X�V
	void Update();

	// �J�����̈ړ�
	void Move();

	void ProductionMove();

	void MouseRotate();

	void StickRotate();

	CAMERA_DATA* GetCameraData() { return &m_cameradata; }


};

#endif