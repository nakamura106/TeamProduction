#include "Camera.h"
#include "Input.h"
#include "Graphics.h"
#include"../DataBank/DataBank.h"

void CAMERA::Update()
{
	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z);	// �J�����ʒu
	D3DXVECTOR3 eye_pos(m_EyePos.x, m_EyePos.y, m_EyePos.z);				// �����_
	D3DXVECTOR3 up_vector(m_CameraUp.x, m_CameraUp.y, m_CameraUp.z);		// �J�����̌���;
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
		20000.0f);			// far
	GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o endMove();

	Move();
	MouseRotate();
	StickRotate();




}

void CAMERA::Move()
{
//	// �J�����̑O�����x�N�g�����o��
//	D3DXVECTOR3 forward;
//	forward = m_EyePos - m_CameraPos;
//
//	// �x�N�g���̐��K��
//	D3DXVec3Normalize(&forward, &forward);
//
//	// �J�����̍������̃x�N�g��
//	// �O�����̃x�N�g���ɒ��p�ȃx�N�g�����Z�o����
//	D3DXVECTOR3 left;
//	left = D3DXVECTOR3(forward.z, forward.y, forward.x);
//
//#pragma region �J�����̈ړ�
//	// �O
//	if (GetKey(W_KEY) || IsButtonPush(L_UpStick)) {
//		m_CameraPos.x += forward.x * m_Speed;
//		m_CameraPos.z += forward.z * m_Speed;
//	}
//	// ��
//	if (GetKey(S_KEY) || IsButtonPush(L_DownStick)) {
//		m_CameraPos.x -= forward.x * m_Speed;
//		m_CameraPos.z -= forward.z * m_Speed;
//	}
//	// ��
//	if (GetKey(A_KEY) || IsButtonPush(L_LeftStick)) {
//		m_CameraPos.x -= left.x * m_Speed;
//		m_CameraPos.z += left.z * m_Speed;
//	}
//	// �E
//	if (GetKey(D_KEY) || IsButtonPush(L_RightStick)) {
//		m_CameraPos.x += left.x * m_Speed;
//		m_CameraPos.z -= left.z * m_Speed;
//	}
//
//	// ����
//	if (GetKey(L_SHIFT) || IsButtonPush(AButton)) {
//		m_Speed = m_SprintSpeed;
//	}
//	else {
//		m_Speed = m_WalkSpeed;
//	}
//
//
//	// �f�o�b�O�p
//	// ��
//	if (GetKey(E_KEY)||IsButtonPush(UpButton) || IsButtonPush(RightTButton)) {
//		m_CameraPos.y += m_CameraUp.y * m_Speed;
//	}
//	// ��
//	if (GetKey(Q_KEY) || IsButtonPush(DownButton) || IsButtonPush(LeftTButton)) {
//		m_CameraPos.y -= m_CameraUp.y * m_Speed;
//	}
//
//	//// �W�����v
//	//if (GetKeyDown(E_KEY) && m_jflag == false)
//	//{
//	//	m_jflag = true;
//	//}
//	//if (m_jflag == true)
//	//{
//	//	m_grav.AddGravity(m_CameraPos.y, m_jamp_power);
//	//	m_CameraPos.y = m_grav.GetPosY();
//
//	//	if (m_CameraPos.y < 10.0f)
//	//	{
//	//		m_jflag = false;
//	//		m_CameraPos.y = 10.0f;
//	//		m_grav.ResetPalam();
//	//	}
//	//}

	DataBank* p_db = DataBank::Instance();

	// �ߋ��̃v���C���[�̈ʒu���擾(�ړ��O)
	D3DXVECTOR3 befor_player = p_db->GetBeforePlayerPos();
	// ���݂̃v���C���[�̈ʒu���擾(�ړ���)
	D3DXVECTOR3 after_player = p_db->GetAfterPlayerPos();
	// �v���C���[������������ = ���݂̃v���C���[�̈ʒu - �ߋ��̃v���C���[�̈ʒu
	D3DXVECTOR3 amount_of_movement = after_player - befor_player;
	// �J�����Ƀv���C���[�̈ړ��ʂ𑫂�
	m_CameraPos += amount_of_movement;

	DataBank::Instance()->SetCameraPos(m_CameraPos);
#pragma endregion
}

void CAMERA::MouseRotate()
{
	SetCursorPos(960, 540);

	m_Yaw += (GetMousePos().X - 960) / 1920 * 50;//�����ŃJ�������x�ύX�\
	m_Pitch -= (GetMousePos().Y - 540) / 1080 * 20;
	if (m_Pitch > 88.0f) { m_Pitch = 178.0f - m_Pitch; }
	if (m_Pitch < -88.0f) { m_Pitch = -178.0f - m_Pitch; }

	m_EyePos.x = m_CameraPos.x + sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_EyePos.y = m_CameraPos.y + sinf(D3DXToRadian(m_Pitch));
	m_EyePos.z = m_CameraPos.z + cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
}

void CAMERA::StickRotate()
{
	if (IsButtonPush(R_LeftStick))
	{
		m_Yaw -= 2.0f;
	}
	if (IsButtonPush(R_RightStick))
	{
		m_Yaw += 2.0f;
	}
	if (IsButtonPush(R_UpStick))
	{
		m_Pitch += 2.0f;
	}
	if (IsButtonPush(R_DownStick))
	{
		m_Pitch -= 2.0f;
	}
	if (m_Pitch > 88.0f) { m_Pitch = 178.0f - m_Pitch; }
	if (m_Pitch < -88.0f) { m_Pitch = -178.0f - m_Pitch; }
	m_EyePos.x = m_CameraPos.x + sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_EyePos.y = m_CameraPos.y + sinf(D3DXToRadian(m_Pitch));
	m_EyePos.z = m_CameraPos.z + cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
}