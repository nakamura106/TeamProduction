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
	void RegisterSelectSound();		// �Z���N�g
	void RegisterGameMainSound();	// �Q�[�����C��
	void RegisterEndSound();		// �Q�[���G���h

	// �炷�֐�
	void SoundBGM();
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundSelect2SE();
	void SoundSelect3SE();
	void SoundClickSE();
	void SoundBullet1SE();
	void SoundBullet2SE();
	void SoundBullet3SE();

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

	bool m_select1_flag;	// selectSE�����[�v�����Ȃ����߂̃t���O
	bool m_select2_flag;
	bool m_select3_flag;


	// �g�p����ۂ̕ϐ����@���������K�{
	std::string m_bgm;
	std::string m_select1_se;
	std::string m_select2_se;
	std::string m_select3_se;
	std::string m_click_se;
	std::string m_bullet1_se;
	std::string m_bullet2_se;
	std::string m_bullet3_se;

	// flie�ǂݍ��ݗp�ϐ�
	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;
	std::string m_se3_file;
	std::string m_click_se_file;
	std::string m_bullet1_se_file;
	std::string m_bullet2_se_file;
	std::string m_bullet3_se_file;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

