#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "../Sound/AudioPlayer.h"
#include"../Engine/Window.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// �e�V�[�����Ƃ̉��f�ޓo�^
	void RegisterTitleSound();		// �^�C�g��
	void RegisterGameMainSound();	// �Q�[�����C��
	void RegisterEndSound();		// �Q�[���G���h

	// �炷�֐��������ƂɊ֐����K�v
	void SoundBGM(int volume_);
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundSelect2SE();
	void SoundSelect3SE();
	void SoundCancelSE();
	void SoundClickSE();
	void SoundThrow();
	void SoundCountSE();
	void SoundStartSE();
	void SoundClearSE();
	void SoundFlySE();


	//������I�������t���O�����ɖ߂��֐�
	void ResetSelectFlag();

	// ����֐�
	void ReleaseTitleSound();
	void ReleaseSelectSound();
	void ReleaseBattleSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	// selectSE�����[�v�����Ȃ����߂̃t���O
	bool m_select1_flag;	
	bool m_select2_flag;
	bool m_select3_flag;
	bool m_cancel_flag;


	// �g�p����ۂ̕ϐ���(�����ƂɕK�v)�@���������K�{
	std::string m_bgm;
	std::string m_select1_se;
	std::string m_select2_se;
	std::string m_select3_se;
	std::string m_cancel_se;
	std::string m_click_se;
	std::string m_throw_se;
	std::string m_count_se;
	std::string m_start_se;
	std::string m_clear_se;
	std::string m_fly_se;


	// flie�ǂݍ��ݗp�ϐ�(�����ƂɕK�v)
	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;
	std::string m_se3_file;
	std::string m_cancel_file;
	std::string m_click_se_file;
	std::string m_throw_se_file;
	std::string m_count_se_file;
	std::string m_start_se_file;
	std::string m_clear_se_file;
	std::string m_fly_se_file;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

