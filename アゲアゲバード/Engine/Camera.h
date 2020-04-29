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
		m_CameraPos.y = pos_.y;//+ 0.5;	// 今だけ(FirstPerson用)
		m_CameraPos.z = pos_.z;

		m_EyePos.x = 0.0f;
		m_EyePos.y = -300.0f;
		m_EyePos.z = 0.0f;

		m_CameraUp.x = 0.0f;
		m_CameraUp.y = 1.0f;
		m_CameraUp.z = 0.0f;

		m_RotateSpeed = 0.05f;

		m_Yaw = 0.0f;
		m_Pitch = 0.0f;
		m_Roll = 0.0f;

		m_Speed = m_WalkSpeed;

		m_startflag = true;

		D3DXMatrixIdentity(&m_MatView);
	}
	
	// カメラ座標の更新
	void Update();

	// カメラの移動
	void Move();

	void ProductionMove();

	void MouseRotate();

	void StickRotate();

	D3DXVECTOR3 GetCamaraPos() {
		return m_CameraPos;
	}

	D3DXVECTOR3 GetEyePos() {
		return m_EyePos;
	}

	D3DXVECTOR3 GetCameraUp() {
		return m_CameraUp;
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
	/* カメラの移動速度 Walk */
	const float m_WalkSpeed;

	/* カメラの移動速度 Sprint */
	const float m_SprintSpeed;

	/* カメラの位置 */
	D3DXVECTOR3 m_CameraPos;

	/* 注視点 */
	D3DXVECTOR3 m_EyePos;

	/* カメラの上向きのベクトル */
	D3DXVECTOR3 m_CameraUp;

	D3DXVECTOR3 m_Forward;

	/* カメラのビュー情報を保存する変数 */
	D3DXMATRIX m_MatView;

	/* 角度 */
	float m_Rad;

	/* 回転速度 */
	float m_RotateSpeed;

	/* X軸回転 */
	float m_Yaw;

	/* Y軸回転 */
	float m_Pitch;

	/* Z軸回転 */
	float m_Roll;

	/* スピード */
	float m_Speed;

	/* 移動速度 */
	//D3DXVECTOR3 m_Velocity;

	bool m_startflag;
};

#endif