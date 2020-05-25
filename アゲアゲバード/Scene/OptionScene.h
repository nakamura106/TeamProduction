#ifndef OPTIONSCENE_H_
#define OPTIONSCENE_H_

#include"../Scene/BaseScene.h"
#include<d3dx9.h>
#include<string>
#include<map>

//ëOï˚êÈåæ

struct TEXTURE_DATA;

class OptionScene :public MyBaseScene::BaseScene
{
private:
	enum class SelectNow
	{
		Sound,
		Stick,
		DeadZone,
		Back,
	};

	enum class SoundFlagState
	{
		Small,
		Midium,
		Large,
	};

	enum class StickFlagState
	{
		Low,
		Nomal,
		High,
	};

	enum class DeadZoneFlagState
	{
		None,
		Existence,
	};

	struct OptionSceneInfo
	{
		std::map<std::string, D3DXVECTOR2> m_option_scene_tex_pos;
		std::map<std::string, TEXTURE_DATA> m_select_icon_tex;
		int m_dead_zone;
		int m_sound_volume;
		float m_stick_sensitivity;
	}m_OptionSceneInfo;

	struct SelectFlag
	{
		SelectNow m_Select_Now;
		SoundFlagState m_sound_flag;
		StickFlagState m_stick_flag;
		DeadZoneFlagState m_deadzone_flag;
	}m_select_flag;

public:
	OptionScene();
	~OptionScene();

	void Init()override;
	void Draw()override;

	void InitScene();
	void MainScene();
	void EndScene();

	const OptionSceneInfo* GetOptionSceneInfo()const { return &m_OptionSceneInfo; }

private:
	void UpdateSelect();
	void DrawSelect();
	void SetInfo();
	void ReleaseTex();
};

#endif