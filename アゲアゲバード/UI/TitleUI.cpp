#include "TitleUI.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../Scene/TitleScene.h"

TitleUi::TitleUi()
{
}

TitleUi::~TitleUi()
{
}

void TitleUi::Init()
{

	m_select_pos = D3DXVECTOR2(145.0f, 620.0f);

	m_Ui_pos[(int)Select::Solo] = D3DXVECTOR2(300.0f, 620.0f);

	m_Ui_pos[(int)Select::Option]= D3DXVECTOR2(308.0f, 732.0f);

	m_Ui_pos[(int)Select::Help]= D3DXVECTOR2(293.0f, 880.0f);

	m_Ui_pos[(int)Select::Timeattack]= D3DXVECTOR2(250.0f, 500.0f);

	m_Ui_pos[(int)Select::Freemode]= D3DXVECTOR2(250.0f, 600.0f);

	m_Ui_pos[(int)Select::Back]= D3DXVECTOR2(255.0f, 720.0f);

	m_Ui_pos[(int)Select::Title]= D3DXVECTOR2(0.0f, 0.0f);
	
	m_title_select = Select::Solo;
}

void TitleUi::LoadTex()
{
	LoadTexture("Res/Tex/�I��UI(�T�C�Y�C��).png", &m_select);
	LoadTexture("Res/Tex/UI��l�p(�T�C�Y�C��).png", &m_Ui[(int)Select::Solo]);
	LoadTexture("Res/Tex/UI�^�C���A�^�b�N.png", &m_Ui[(int)Select::Timeattack]);
	LoadTexture("Res/Tex/UI�t���[�v���C.png", &m_Ui[(int)Select::Freemode]);
	LoadTexture("Res/Tex/�I�v�V��������UI(�T�C�Y�C��).png", &m_Ui[(int)Select::Option]);
	LoadTexture("Res/Tex/UI�߂�.png", &m_Ui[(int)Select::Back]);
	LoadTexture("Res/Tex/Title_LogoOn.png", &m_Ui[(int)Select::Title]);
	LoadTexture("Res/Tex/�w���v����UI(�T�C�Y�C��).png", &m_Ui[(int)Select::Help]);
}

void TitleUi::LoadFile()
{
}

void TitleUi::Draw()
{
	DrawTitleUi(m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_page);
}

void TitleUi::UpDate()
{
	UpdateSelect();
}

void TitleUi::ReleaseTex()
{
	for (int i = 0; i<=(int)Select::SelectMax; i++)
	{
		ReleaseUITexture(&m_Ui[i]);
	}
}

void TitleUi::DrawTitleUi(int page_)
{
	DrawUITexture(&m_Ui[(int)Select::Title], m_Ui_pos[(int)Select::Title]);

	if (page_ == (int)page::page1)
	{
		DrawUITexture(&m_Ui[(int)Select::Solo], m_Ui_pos[(int)Select::Solo]);
		DrawUITexture(&m_Ui[(int)Select::Option], m_Ui_pos[(int)Select::Option]);
		DrawUITexture(&m_Ui[(int)Select::Help], m_Ui_pos[(int)Select::Help]);
		DrawUITexture(&m_select, m_select_pos);
	}
	if (page_ == (int)page::page2)
	{
		DrawUITexture(&m_Ui[(int)Select::Freemode], m_Ui_pos[(int)Select::Freemode]);
		DrawUITexture(&m_Ui[(int)Select::Timeattack], m_Ui_pos[(int)Select::Timeattack]);
		DrawUITexture(&m_Ui[(int)Select::Back], m_Ui_pos[(int)Select::Back]);
		DrawUITexture(&m_select, m_select_pos);
	}
}

void TitleUi::UpdateSelect()
{
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Solo)
	{
		m_select_pos= D3DXVECTOR2(145.0f, 620.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select ==(int)Select::Option )
	{
		m_select_pos = D3DXVECTOR2(145.0f, 735.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Help)
	{
		m_select_pos = D3DXVECTOR2(145.0f, 865.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Timeattack)
	{
		m_select_pos = D3DXVECTOR2(145.0f, 480.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Freemode)
	{
		m_select_pos = D3DXVECTOR2(145.0f, 600.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Back)
	{
		m_select_pos= D3DXVECTOR2(145.0f, 715.0f);
	}
	
}


