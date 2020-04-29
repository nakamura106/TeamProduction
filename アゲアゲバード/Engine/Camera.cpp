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
	//ProductionMove();
	DataBank::Instance()->SetStartflag(m_startflag);

	if (DataBank::Instance()->GetUIStartflag() == true)
	{
		Move();
	}
	MouseRotate();
	//StickRotate();

	m_Forward = m_EyePos - m_CameraPos;
	D3DXVec3Normalize(&m_Forward, &m_Forward);
	DataBank::Instance()->SetForward(m_Forward);
	DataBank::Instance()->SetEyePos(eye_pos);
}

void CAMERA::Move()
{
	
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
}

void CAMERA::ProductionMove()
{
	if (DataBank::Instance()->GetAfterPlayerPos().y <= m_CameraPos.y)
	{
		m_CameraPos.y -= 0.25f;
	}
	else
	{
		m_startflag = true;
	}
	DataBank::Instance()->SetStartflag(m_startflag);

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