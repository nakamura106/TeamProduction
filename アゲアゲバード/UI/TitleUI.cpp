#include "TitleUI.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../Scene/TitleScene.h"
#include"../Manager/SceneManager.h"

TitleUi::TitleUi()
{
}

TitleUi::~TitleUi()
{
}

void TitleUi::Init()
{

	m_select_pos.x = 700.0f;
	m_select_pos.y = 600.0f;

	m_Ui_pos[(int)Select::Solo].x = 300.0f;
	m_Ui_pos[(int)Select::Solo].y = 450.0f;

	m_Ui_pos[(int)Select::Option].x = 300.0f;
	m_Ui_pos[(int)Select::Option].y = 600.0f;

	m_Ui_pos[(int)Select::Help].x = 300.0f;
	m_Ui_pos[(int)Select::Help].y = 800.0f;

	m_Ui_pos[(int)Select::Timeattack].x = 400.0f;
	m_Ui_pos[(int)Select::Timeattack].y = 600.0f;

	m_Ui_pos[(int)Select::Freemode].x = 400.0f;
	m_Ui_pos[(int)Select::Freemode].y = 700.0f;

	m_Ui_pos[(int)Select::Back].x = 800.0f;
	m_Ui_pos[(int)Select::Back].y = 700.0f;

	m_Ui_pos[(int)Select::Title].x = 0.0f;
	m_Ui_pos[(int)Select::Title].y = 0.0f;

	
	m_title_select = Select::Solo;
}

void TitleUi::LoadTex()
{
	LoadTexture("Res/Tex/�I��UI.png", &m_select);
	LoadTexture("Res/Tex/UI��l�p.png", &m_Ui[(int)Select::Solo]);
	LoadTexture("Res/Tex/UI�^�C���A�^�b�N.png", &m_Ui[(int)Select::Timeattack]);
	LoadTexture("Res/Tex/UI�t���[�v���C.png", &m_Ui[(int)Select::Freemode]);
	LoadTexture("Res/Tex/�I�v�V��������UI.png", &m_Ui[(int)Select::Option]);
	LoadTexture("Res/Tex/UI�߂�.png", &m_Ui[(int)Select::Back]);
	LoadTexture("Res/Tex/�^�C�g�����.png", &m_Ui[(int)Select::Title]);
	LoadTexture("Res/Tex/�w���v����UI.png", &m_Ui[(int)Select::Help]);
}

void TitleUi::LoadFile()
{
}

void TitleUi::Draw()
{
	DrawTitleUi(SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_page);
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
		DrawUITexture(&m_select, m_select_pos);
	}
}

void TitleUi::UpdateSelect()
{
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Solo)
	{
		m_select_pos.x =-100.0f;
		m_select_pos.y = 360.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select ==(int)Select::Option )
	{
		m_select_pos.x = -100.0f;
		m_select_pos.y = 550.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Help)
	{
		m_select_pos.x = -100.0f;
		m_select_pos.y = 750.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Timeattack)
	{
		m_select_pos.x = -100.0f;
		m_select_pos.y = 500.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Freemode)
	{
		m_select_pos.x = -100.0f;
		m_select_pos.y = 610.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Back)
	{
		m_select_pos.x = -100.0f;
		m_select_pos.y = 700.0f;
	}
	
}


