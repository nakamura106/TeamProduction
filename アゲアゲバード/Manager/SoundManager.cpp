#include "SoundManager.h"

SoundManager* SoundManager::p_instance = 0;

SoundManager* SoundManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new SoundManager;
	}

	return p_instance;
}

void SoundManager::RegisterTitleSound()
{
	m_bgm_file = "Res/wav/TitleBgm.wav";
	m_se1_file = "Res/wav/SelectSE.wav";
	m_click_se_file = "Res/wav/ClickSE.wav";
	m_cancel_file = "Res/wav/CancelSE.wav";
	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_select1_se, m_se1_file);
	m_pAudio->Load(m_click_se, m_click_se_file);
	m_pAudio->Load(m_cancel_se, m_cancel_file);
}

void SoundManager::RegisterGameMainSound()
{
	m_bgm_file = "Res/wav/GameBgm.wav";
	m_click_se_file = "Res/wav/putting_a_box.wav";
	m_throw_se_file = "Res/wav/throw.wav";
	m_count_se_file = "Res/wav/countdown.wav";
	m_start_se_file = "Res/wav/start.wav";
	m_clear_se_file = "Res/wav/clear.wav";
	m_fly_se_file = "Res/wav/fly.wav";

	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_click_se, m_click_se_file);
	m_pAudio->Load(m_throw_se, m_throw_se_file);
	m_pAudio->Load(m_count_se, m_count_se_file);
	m_pAudio->Load(m_start_se, m_start_se_file);
	m_pAudio->Load(m_clear_se, m_clear_se_file);
	m_pAudio->Load(m_fly_se, m_fly_se_file);

}

void SoundManager::RegisterEndSound()
{
	m_bgm_file = "Res/wav/TitleBgm2.wav";

	m_pAudio->Load(m_bgm, m_bgm_file);
}


void SoundManager::SoundBGM(int volume_)
{
	m_pAudio->Play(m_bgm, volume_, true);
}

void SoundManager::SoundSelectBGM()
{
	m_pAudio->Play(m_bgm, 0, true);
}

void SoundManager::SoundSelectSE()
{
	if (m_select1_flag == false)
	{
		m_pAudio->Play(m_select1_se, -1000, false);
		m_select1_flag = true;
		m_select2_flag = false;
		m_select3_flag = false;
		m_cancel_flag = false;
	}
}

void SoundManager::SoundSelect2SE()
{
	if (m_select2_flag == false)
	{
		m_pAudio->Play(m_select2_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = true;
		m_select3_flag = false;
		m_cancel_flag = false;
	}
}

void SoundManager::SoundSelect3SE()
{
	if (m_select3_flag == false)
	{
		m_pAudio->Play(m_select3_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = false;
		m_select3_flag = true;
		m_cancel_flag = false;
	}
}

void SoundManager::SoundCancelSE()
{
	if (m_cancel_flag == false)
	{
		m_pAudio->Play(m_cancel_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = false;
		m_select3_flag = false;
		m_cancel_flag = true;
	}
}

void SoundManager::SoundClickSE()
{
	m_pAudio->Play(m_click_se, 0, false);
}

void SoundManager::SoundThrow()
{
	m_pAudio->Play(m_throw_se,0,false);
}

void SoundManager::SoundCountSE()
{
	m_pAudio->Play(m_count_se, 0, false);
}

void SoundManager::SoundStartSE()
{
	m_pAudio->Play(m_start_se, 0, false);
}

void SoundManager::SoundClearSE()
{
	m_pAudio->Play(m_clear_se, 0, true);
}

void SoundManager::SoundFlySE()
{
	m_pAudio->Play(m_fly_se, 0, true);
}

void SoundManager::ResetSelectFlag()
{
	m_select1_flag = false;
	m_select2_flag = false;
	m_select3_flag = false;
	m_cancel_flag = false;
}

void SoundManager::ReleaseTitleSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select1_se);
	m_pAudio->Release(m_click_se);
}

void SoundManager::ReleaseSelectSound()
{
	m_pAudio->Release(m_bgm);
}

void SoundManager::ReleaseBattleSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_click_se);
	m_pAudio->Release(m_count_se);
	m_pAudio->Release(m_start_se);
	m_pAudio->Release(m_clear_se);
	m_pAudio->Release(m_fly_se);

}

void SoundManager::ReleaseBGM()
{
	m_pAudio->Release(m_bgm);
}

SoundManager::SoundManager()
{
	m_select1_flag = false;
	m_select2_flag = false;
	m_select3_flag = false;
	m_cancel_flag = false;

	m_bgm = "BGM";
	m_select1_se = "SelectSE";
	m_select2_se = "Select2SE";
	m_select3_se = "Select3SE";
	m_click_se = "ClickSE";
	m_count_se = "CountDownSE";
	m_start_se = "StartSE";
	m_clear_se = "ClearSE";
	m_fly_se = "FlySE";

}

SoundManager::~SoundManager()
{

}

