#include "TitleUI.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../Scene/TitleScene.h"

TitleUI::TitleUI()
{
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{

	m_select_pos = D3DXVECTOR2(145.0f, 594.0f);

	m_Ui_pos[(int)Select::Solo] = D3DXVECTOR2(300.0f, 594.0f);

	m_Ui_pos[(int)Select::Option]= D3DXVECTOR2(308.0f, 705.0f);

	m_Ui_pos[(int)Select::Help]= D3DXVECTOR2(293.0f, 808.0f);

	m_Ui_pos[(int)Select::Timeattack]= D3DXVECTOR2(250.0f, 615.0f);

	m_Ui_pos[(int)Select::Freemode]= D3DXVECTOR2(250.0f, 723.0f);

	m_Ui_pos[(int)Select::Back]= D3DXVECTOR2(255.0f, 838.0f);

	m_Ui_pos[(int)Select::Title]= D3DXVECTOR2(0.0f, 0.0f);
	
	m_title_select = Select::Solo;
}

void TitleUI::LoadTex()
{
	LoadTexture("Res/Tex/選択中UI(サイズ修正).png", &m_select);
	LoadTexture("Res/Tex/一人用UI.png", &m_Ui[(int)Select::Solo]);
	LoadTexture("Res/Tex/タイムアタックUI.png", &m_Ui[(int)Select::Timeattack]);
	LoadTexture("Res/Tex/フリープレイUI.png", &m_Ui[(int)Select::Freemode]);
	LoadTexture("Res/Tex/オプションUI.png", &m_Ui[(int)Select::Option]);
	LoadTexture("Res/Tex/戻るUI.png", &m_Ui[(int)Select::Back]);
	LoadTexture("Res/Tex/Title_3D_A.png", &m_Ui[(int)Select::Title]);
	LoadTexture("Res/Tex/ヘルプUI.png", &m_Ui[(int)Select::Help]);
}

void TitleUI::Draw()
{
	DrawTitleUi(m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_page);
}

void TitleUI::UpDate()
{
	UpdateSelect();
}

void TitleUI::ReleaseTex()
{
	for (int i = 0; i<=(int)Select::SelectMax; i++)
	{
		ReleaseUITexture(&m_Ui[i]);
	}
}

void TitleUI::DrawTitleUi(int page_)
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

void TitleUI::UpdateSelect()
{
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Solo)
	{
		m_select_pos= D3DXVECTOR2(145.0f, 580.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select ==(int)Select::Option )
	{
		m_select_pos = D3DXVECTOR2(145.0f, 670.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Help)
	{
		m_select_pos = D3DXVECTOR2(145.0f, 790.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Timeattack)
	{
		m_select_pos = D3DXVECTOR2(110.0f, 605.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Freemode)
	{
		m_select_pos = D3DXVECTOR2(110.0f, 710.0f);
	}
	if (m_scenemanager->GetTitleScene()->GetTitleSceneInfo()->m_now_select == (int)Select::Back)
	{
		m_select_pos= D3DXVECTOR2(110.0f, 810.0f);
	}
	
}


