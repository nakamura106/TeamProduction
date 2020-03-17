#ifndef DIRECTSOUND_H_
#define DIRECTSOUND_H_

#include <dsound.h>
#include <string>

class DirectSound {

public:


	DirectSound(HWND hwnd = nullptr);

	/*
	�@
	 wav�t�@�C���̏����o�����s���A�f�[�^��Ԃ�

	�g�p���@�F
		DirectSound("hoge.wave");
	*/
	IDirectSoundBuffer8* LoadWaveFile(std::string file_name);

	~DirectSound();

private:

	IDirectSound8* m_DSound8;			//�T�E���h�C���^�[�t�F�[�X
	IDirectSoundBuffer* m_PrimaryBuffer;//�v���C�}���[�o�b�t�@�\
	IDirectSoundBuffer8* m_SecBuffer;
};


#endif
