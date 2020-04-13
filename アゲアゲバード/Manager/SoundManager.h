#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "../Sound/AudioPlayer.h"
#include"../Engine/Window.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// 各シーンごとの音素材登録
	void RegisterTitleSound();		// タイトル
	void RegisterGameMainSound();	// ゲームメイン
	void RegisterEndSound();		// ゲームエンド

	// 鳴らす関数※音ごとに関数が必要
	void SoundBGM(int volume_);
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundSelect2SE();
	void SoundSelect3SE();
	void SoundCancelSE();
	void SoundClickSE();

	//音が鳴り終わったらフラグを元に戻す関数
	void ResetSelectFlag();

	// 解放関数
	void ReleaseTitleSound();
	void ReleaseSelectSound();
	void ReleaseBattleSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	// selectSEをループさせないためのフラグ
	bool m_select1_flag;	
	bool m_select2_flag;
	bool m_select3_flag;
	bool m_cancel_flag;


	// 使用する際の変数名(音ごとに必要)　※初期化必須
	std::string m_bgm;
	std::string m_select1_se;
	std::string m_select2_se;
	std::string m_select3_se;
	std::string m_cancel_se;
	std::string m_click_se;

	// flie読み込み用変数(音ごとに必要)
	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;
	std::string m_se3_file;
	std::string m_cancel_file;
	std::string m_click_se_file;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

