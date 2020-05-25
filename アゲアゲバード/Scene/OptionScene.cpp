#include"OptionScene.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"

OptionScene::OptionScene()
{
	Init();
}

OptionScene::~OptionScene()
{
	/*オプション画面…
上段のボタン3つ
X：695,   820,   932
Y：430固定
一応目安
左端：緑
中間：黄
右端：赤

2つのみ…緑、赤
2段目ボタン
X:上段と同じ
Y:605固定
3段目ボタン
X:上段と同じ（中央だけ使わない）
Y820固定*/
}

void OptionScene::Init()
{
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
	m_select_flag.m_stick_flag = StickFlagState::Nomal;
	m_select_flag.m_sound_flag = SoundFlagState::Midium;
	m_select_flag.m_deadzone_flag = DeadZoneFlagState::None;
	m_OptionSceneInfo.m_dead_zone = 0;
	m_OptionSceneInfo.m_sound_volume = -1200;
	m_OptionSceneInfo.m_stick_sensitivity = 2.0f;
}

void OptionScene::Draw()
{
	DrawSelect();
}

void OptionScene::InitScene()
{

	m_OptionSceneInfo.m_option_scene_tex_pos["bg"] = D3DXVECTOR2(0.0f, 0.0f);
	LoadTexture("Res/Tex/Option_Plane.png",&m_OptionSceneInfo.m_select_icon_tex["bg"]);

	m_OptionSceneInfo.m_option_scene_tex_pos["soundsmall"] = D3DXVECTOR2(695.0f, 430.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["soundmidium"] = D3DXVECTOR2(820.0f, 430.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["soundlarge"] = D3DXVECTOR2(932.0f, 430.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["sticklow"] = D3DXVECTOR2(695.0f,605.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["sticknomal"] = D3DXVECTOR2(820.0f, 605.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["stickhigh"] = D3DXVECTOR2(932.0f, 605.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["Nonedeadzone"] = D3DXVECTOR2(695.0f, 820.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["Existencedeadzone"] = D3DXVECTOR2(932.0f, 820.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["allow"] = D3DXVECTOR2(10.0f, 420.0f);

	m_OptionSceneInfo.m_option_scene_tex_pos["back"] = D3DXVECTOR2(150.0f, 900.0f);

	LoadTexture("Res/Tex/button_green.png",&m_OptionSceneInfo.m_select_icon_tex["green"]);
	LoadTexture("Res/Tex/button_red.png", &m_OptionSceneInfo.m_select_icon_tex["red"]);
	LoadTexture("Res/Tex/button_yellow.png", &m_OptionSceneInfo.m_select_icon_tex["yellow"]);
	LoadTexture("Res/Tex/button_grey.png", &m_OptionSceneInfo.m_select_icon_tex["grey"]);

	LoadTexture("Res/Tex/選択中UI(サイズ修正).png", &m_OptionSceneInfo.m_select_icon_tex["allow"]);
	LoadTexture("Res/Tex/UI戻る.png", &m_OptionSceneInfo.m_select_icon_tex["back"]);

	m_select_flag.m_Select_Now = SelectNow::Sound;
	

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::MainStep;
}

void OptionScene::MainScene()
{
	UpdateSelect();
}

void OptionScene::EndScene()
{
	ReleaseTex();

	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::InitStep;
	SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneID = SceneId::Title;
	SetInfo();
}

void OptionScene::UpdateSelect()
{
	if (m_select_flag.m_Select_Now == SelectNow::Sound)
	{
		m_OptionSceneInfo.m_option_scene_tex_pos["allow"] = D3DXVECTOR2(10.0f, 360.0f);

		if (m_select_flag.m_sound_flag == SoundFlagState::Midium)
		{
			if (IsButtonDown(L_LeftStick) || GetKeyDown(LEFT_KEY))
			{
				m_select_flag.m_sound_flag = SoundFlagState::Small;
				m_OptionSceneInfo.m_sound_volume = -3000;
				SoundManager::Instance()->SoundSelectSE();
				SoundManager::Instance()->SoundBGM(m_OptionSceneInfo.m_sound_volume);
			}
			else if (IsButtonDown(L_RightStick) || GetKeyDown(RIGHT_KEY))
			{
				m_select_flag.m_sound_flag = SoundFlagState::Large;
				m_OptionSceneInfo.m_sound_volume = -300;
				SoundManager::Instance()->SoundSelectSE();
				SoundManager::Instance()->SoundBGM(m_OptionSceneInfo.m_sound_volume);
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
		if (m_select_flag.m_sound_flag == SoundFlagState::Large)
		{
			if (IsButtonDown(L_LeftStick) || GetKeyDown(LEFT_KEY))
			{
				m_select_flag.m_sound_flag = SoundFlagState::Midium;
				m_OptionSceneInfo.m_sound_volume = -1200;
				SoundManager::Instance()->SoundSelectSE();
				SoundManager::Instance()->SoundBGM(m_OptionSceneInfo.m_sound_volume);
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
		if (m_select_flag.m_sound_flag == SoundFlagState::Small)
		{
			if (IsButtonDown(L_RightStick) || GetKeyDown(RIGHT_KEY))
			{
				m_select_flag.m_sound_flag = SoundFlagState::Midium;
				m_OptionSceneInfo.m_sound_volume = -1000;
				SoundManager::Instance()->SoundSelectSE();
				SoundManager::Instance()->SoundBGM(m_OptionSceneInfo.m_sound_volume);
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
	}
	if (m_select_flag.m_Select_Now == SelectNow::Stick)
	{
		m_OptionSceneInfo.m_option_scene_tex_pos["allow"] = D3DXVECTOR2(10.0f, 540.0f);

		if (m_select_flag.m_stick_flag==StickFlagState::Nomal)
		{
			if (IsButtonDown(L_LeftStick) || GetKeyDown(LEFT_KEY))
			{
				m_select_flag.m_stick_flag = StickFlagState::Low;
				SoundManager::Instance()->SoundSelectSE();
			}
			else if (IsButtonDown(L_RightStick) || GetKeyDown(RIGHT_KEY))
			{
				m_select_flag.m_stick_flag = StickFlagState::High;
				SoundManager::Instance()->SoundSelectSE();
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
		if (m_select_flag.m_stick_flag == StickFlagState::High)
		{
			if (IsButtonDown(L_LeftStick) || GetKeyDown(LEFT_KEY))
			{
				m_select_flag.m_stick_flag = StickFlagState::Nomal;
				SoundManager::Instance()->SoundSelectSE();
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
		if (m_select_flag.m_stick_flag == StickFlagState::Low)
		{
			if (IsButtonDown(L_RightStick) || GetKeyDown(RIGHT_KEY))
			{
				m_select_flag.m_stick_flag = StickFlagState::Nomal;
				SoundManager::Instance()->SoundSelectSE();
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
	}
	if (m_select_flag.m_Select_Now == SelectNow::DeadZone)
	{
		m_OptionSceneInfo.m_option_scene_tex_pos["allow"] = D3DXVECTOR2(10.0f, 750.0f);

		if (m_select_flag.m_deadzone_flag == DeadZoneFlagState::Existence)
		{
			if (IsButtonDown(L_LeftStick) || GetKeyDown(LEFT_KEY))
			{
				m_select_flag.m_deadzone_flag = DeadZoneFlagState::None;
				SoundManager::Instance()->SoundSelectSE();
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
		if (m_select_flag.m_deadzone_flag == DeadZoneFlagState::None)
		{
			if (IsButtonDown(L_RightStick) || GetKeyDown(RIGHT_KEY))
			{
				m_select_flag.m_deadzone_flag = DeadZoneFlagState::Existence;
				SoundManager::Instance()->SoundSelectSE();
			}
			else
			{
				SoundManager::Instance()->ResetSelectFlag();
			}
		}
	}
	if (m_select_flag.m_Select_Now == SelectNow::Back)
	{
		m_OptionSceneInfo.m_option_scene_tex_pos["allow"] = D3DXVECTOR2(10.0f, 900.0f);
	}


	if (GetKeyDown(DOWN_KEY) || IsButtonDown(L_DownStick))
	{
		SoundManager::Instance()->SoundSelectSE();
		if (m_select_flag.m_Select_Now == SelectNow::Sound)
		{
			m_select_flag.m_Select_Now = SelectNow::Stick;
		}
		else if (m_select_flag.m_Select_Now == SelectNow::Stick)
		{
			m_select_flag.m_Select_Now = SelectNow::DeadZone;
		}
		else if (m_select_flag.m_Select_Now == SelectNow::DeadZone)
		{
			m_select_flag.m_Select_Now = SelectNow::Back;
		}
	}
	else if (GetKeyDown(UP_KEY) || IsButtonDown(L_UpStick))
	{
		SoundManager::Instance()->SoundSelectSE();
		if (m_select_flag.m_Select_Now == SelectNow::Stick)
		{
			m_select_flag.m_Select_Now = SelectNow::Sound;
		}
		else if (m_select_flag.m_Select_Now == SelectNow::DeadZone)
		{
			m_select_flag.m_Select_Now = SelectNow::Stick;
		}
		else if (m_select_flag.m_Select_Now == SelectNow::Back)
		{
			m_select_flag.m_Select_Now = SelectNow::DeadZone;
		}
	}
	else
	{
		SoundManager::Instance()->ResetSelectFlag();
	}

	if (GetKeyDown(RETURN_KEY) || IsButtonDown(BButton))
	{
		if (m_select_flag.m_Select_Now == SelectNow::Back)
		{
			SoundManager::Instance()->SoundClickSE();
			SceneManager::Instance()->SetSceneInfo()->m_CurrentSceneStep = SceneStep::EndStep;
		}
	}
}

void OptionScene::DrawSelect()
{
	DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["bg"], m_OptionSceneInfo.m_option_scene_tex_pos["bg"]);

	if (m_select_flag.m_sound_flag == SoundFlagState::Small)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["green"], m_OptionSceneInfo.m_option_scene_tex_pos["soundsmall"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["soundmidium"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["soundlarge"]);
	}
	else if (m_select_flag.m_sound_flag == SoundFlagState::Midium)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["soundsmall"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["green"], m_OptionSceneInfo.m_option_scene_tex_pos["soundmidium"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["soundlarge"]);
	}
	else if (m_select_flag.m_sound_flag == SoundFlagState::Large)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["soundsmall"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["soundmidium"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["green"], m_OptionSceneInfo.m_option_scene_tex_pos["soundlarge"]);
	}

	if (m_select_flag.m_stick_flag == StickFlagState::Low)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["yellow"], m_OptionSceneInfo.m_option_scene_tex_pos["sticklow"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["sticknomal"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["stickhigh"]);
	}
	else if (m_select_flag.m_stick_flag == StickFlagState::Nomal)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["sticklow"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["yellow"], m_OptionSceneInfo.m_option_scene_tex_pos["sticknomal"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["stickhigh"]);
	}
	else if (m_select_flag.m_stick_flag == StickFlagState::High)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["sticklow"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["sticknomal"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["yellow"], m_OptionSceneInfo.m_option_scene_tex_pos["stickhigh"]);
	}

	if (m_select_flag.m_deadzone_flag == DeadZoneFlagState::Existence)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["red"], m_OptionSceneInfo.m_option_scene_tex_pos["Existencedeadzone"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["Nonedeadzone"]);
	}
	else if (m_select_flag.m_deadzone_flag == DeadZoneFlagState::None)
	{
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["grey"], m_OptionSceneInfo.m_option_scene_tex_pos["Existencedeadzone"]);
		DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["red"], m_OptionSceneInfo.m_option_scene_tex_pos["Nonedeadzone"]);
	}

	DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["allow"], m_OptionSceneInfo.m_option_scene_tex_pos["allow"]);
	DrawUITexture(&m_OptionSceneInfo.m_select_icon_tex["back"], m_OptionSceneInfo.m_option_scene_tex_pos["back"]);
}

void OptionScene::SetInfo()
{

	if (m_select_flag.m_stick_flag == StickFlagState::Low)
	{
		m_OptionSceneInfo.m_stick_sensitivity = 1.0f;
	}
	else if (m_select_flag.m_stick_flag == StickFlagState::Nomal)
	{
		m_OptionSceneInfo.m_stick_sensitivity = 2.0f;
	}
	else if (m_select_flag.m_stick_flag == StickFlagState::High)
	{
		m_OptionSceneInfo.m_stick_sensitivity = 4.0f;
	}

	if (m_select_flag.m_deadzone_flag == DeadZoneFlagState::Existence)
	{
		m_OptionSceneInfo.m_dead_zone = 1000;
	}
	else if (m_select_flag.m_deadzone_flag == DeadZoneFlagState::None)
	{
		m_OptionSceneInfo.m_dead_zone = 0;
	}
}

void OptionScene::ReleaseTex()
{
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["bg"]);
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["green"]);
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["red"]);
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["yellow"]);
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["grey"]);
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["allow"]);
	ReleaseTexture(&m_OptionSceneInfo.m_select_icon_tex["back"]);
}

