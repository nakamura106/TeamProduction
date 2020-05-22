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

	m_select_pos.x = 145.0f;
	m_select_pos.y = 620.0f;

	m_Ui_pos[(int)Select::Solo].x = 300.0f;
	m_Ui_pos[(int)Select::Solo].y = 620.0f;

	m_Ui_pos[(int)Select::Option].x = 308.0f;
	m_Ui_pos[(int)Select::Option].y = 732.0f;

	m_Ui_pos[(int)Select::Help].x = 293.0f;
	m_Ui_pos[(int)Select::Help].y = 880.0f;

	m_Ui_pos[(int)Select::Timeattack].x = 250.0f;
	m_Ui_pos[(int)Select::Timeattack].y = 500.0f;

	m_Ui_pos[(int)Select::Freemode].x = 250.0f;
	m_Ui_pos[(int)Select::Freemode].y = 600.0f;

	m_Ui_pos[(int)Select::Back].x = 255.0f;
	m_Ui_pos[(int)Select::Back].y = 720.0f;

	m_Ui_pos[(int)Select::Title].x = 0.0f;
	m_Ui_pos[(int)Select::Title].y = 0.0f;

	
	m_title_select = Select::Solo;
}

void TitleUi::LoadTex()
{
	LoadTexture("Res/Tex/選択中UI(サイズ修正).png", &m_select);
	LoadTexture("Res/Tex/UI一人用(サイズ修正).png", &m_Ui[(int)Select::Solo]);
	LoadTexture("Res/Tex/UIタイムアタック.png", &m_Ui[(int)Select::Timeattack]);
	LoadTexture("Res/Tex/UIフリープレイ.png", &m_Ui[(int)Select::Freemode]);
	LoadTexture("Res/Tex/オプション文字UI(サイズ修正).png", &m_Ui[(int)Select::Option]);
	LoadTexture("Res/Tex/UI戻る.png", &m_Ui[(int)Select::Back]);
	LoadTexture("Res/Tex/Title_LogoOn.png", &m_Ui[(int)Select::Title]);
	LoadTexture("Res/Tex/ヘルプ文字UI(サイズ修正).png", &m_Ui[(int)Select::Help]);
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
		DrawUITexture(&m_Ui[(int)Select::Back], m_Ui_pos[(int)Select::Back]);
		DrawUITexture(&m_select, m_select_pos);
	}
}

void TitleUi::UpdateSelect()
{
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Solo)
	{
		m_select_pos.x = 145.0f;
		m_select_pos.y = 620.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select ==(int)Select::Option )
	{
		m_select_pos.x = 145.0f;
		m_select_pos.y = 735.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Help)
	{
		m_select_pos.x = 145.0f;
		m_select_pos.y = 865.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Timeattack)
	{
		m_select_pos.x = 145.0f;
		m_select_pos.y = 480.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Freemode)
	{
		m_select_pos.x = 145.0f;
		m_select_pos.y = 600.0f;
	}
	if (SceneManager::Instance()->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Back)
	{
		m_select_pos.x = 145.0f;
		m_select_pos.y = 715.0f;
	}
	
}


