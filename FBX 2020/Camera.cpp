#include "Camera.h"
#include "Input.h"
#include "Graphics.h"

void CAMERA::Update()
{
	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z); // �J�����ʒu
	D3DXVECTOR3 eye_pos(m_EyePos.x, m_EyePos.y, m_EyePos.z);// �����_
	D3DXVECTOR3 up_vector(m_CameraUp.x, m_CameraUp.y, m_CameraUp.z);	// �J�����̌���;

	D3DXMatrixLookAtLH(&m_MatView,
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��

	GetD3DDevice()->SetTransform(D3DTS_VIEW, &m_MatView);
	//�r���[���W�ϊ��p�̍s��Z�o end

	D3DXMATRIX matProj;
	D3DXMatrixIdentity(&matProj);

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	GetD3DDevice()->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	// ������̍쐬
	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		1.1f,				// near
		2000.0f);			// far
	GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}

void CAMERA::Move()
{
	// �J�����̑O�����x�N�g�����o��
	D3DXVECTOR3 forward;
	forward = m_EyePos - m_CameraPos;

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&forward, &forward);
	//forward.y = 0.0f;

	// �J�����̍������̃x�N�g��
	// �O�����̃x�N�g���ɒ��p�ȃx�N�g�����Z�o����
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

	m_Velocity.x = forward.x * m_Speed;
	m_Velocity.z = forward.z * m_Speed;

#pragma region �J�����̈ړ�
	// �O
	if (GetKey(W_KEY)) {
		m_CameraPos.x += forward.x * m_Speed;
		m_CameraPos.y += forward.y * m_Speed;
		m_CameraPos.z += forward.z * m_Speed;
	}
	// ��
	if (GetKey(S_KEY)) {
		m_CameraPos.x -= forward.x * m_Speed;
		m_CameraPos.z -= forward.z * m_Speed;
	}
	// ��
	if (GetKey(A_KEY)) {
		m_CameraPos.x -= left.x * m_Speed;
		m_CameraPos.z += left.z * m_Speed;
	}
	// �E
	if (GetKey(D_KEY)) {
		m_CameraPos.x += left.x * m_Speed;
		m_CameraPos.z -= left.z * m_Speed;
	}

#pragma endregion

}

D3DXVECTOR3 CAMERA::GetCameraForward()
{
	return D3DXVECTOR3();
}

void CAMERA::MouseRotate()
{
	SetCursorPos(960, 540);

	m_Yaw -= (GetMousePos().X - 960) / 1920 * 50;
	m_Pitch -= (GetMousePos().Y - 540) / 1080 * 20;
	if (m_Pitch > 90.0f) { m_Pitch = 180.0f - m_Pitch; }
	if (m_Pitch < -90.0f) { m_Pitch = -180.0f - m_Pitch; }

	m_EyePos.x = m_CameraPos.x + cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_EyePos.y = m_CameraPos.y + sinf(D3DXToRadian(m_Pitch));
	m_EyePos.z = m_CameraPos.z + sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
}
