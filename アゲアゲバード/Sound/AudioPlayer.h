#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#include "DirectSound.h"
#include "../Engine/Window.h"
#include <string>
#include <unordered_map>


//============================
// �I�[�f�B�I�v���C���[�N���X
//============================

class AudioPlayer {

public:

	static AudioPlayer* GetInstance(HWND hwnd = nullptr) {
		static AudioPlayer instance(hwnd);
		return &instance;
	}

	/*
		�E�F�u�t�@�C���ǂݍ���
	�����F
		alias �T�E���h���g�p����ۂ̕ʖ�
		file_name �T�E���h�t�@�C����
	�T�v�F
		�w�肳�ꂽ�T�E���h�t�@�C����ǂݍ���
	*/
	bool Load(std::string alias, std::string file_name);

	/*
		�Đ�����
	�����F
		volumr  ���ʁi�O�ōő�@-10000�Ŗ����j
		is_loop �Đ����@�itrue=���[�v�Đ��j

	�T�v�F
	�@�@�w�肳�ꂽ���ʂŁA��Q�����ł��Ă����ꂽ
	  �@�Đ����@�ɂ��Đ�����
	*/
	void Play(
		std::string alias,
		int volume = -1000,
		bool is_loop = false);

	// ��~
	void Stop(std::string alias);

	/*
		�{�����[���ݒ�
	�����F
		volume ���ʁi0�ōő� -10000�Ŗ����j
	*/
	void SetVolume(std::string alias, int volume);

	//�������
	void Release(std::string alias);

private:

	//�R���X�g���N�^
	AudioPlayer(HWND hwnd) {
		//�Đ���̃E�B���h�E�n���h�����擾
		m_Sound = new DirectSound(hwnd);
		ZeroMemory(&m_SoundData, 0, sizeof(IDirectSoundBuffer8));
	}

	/*
		�T�E���h�t�@�C������
	�����F
		alias �ǂݍ��ݎ��ɐݒ肵���T�E���h�t�@�C���̕ʖ�
	�߂�l�F
		�����@���@�T�E���h�f�[�^
		���s�@���@null
	*/
	IDirectSoundBuffer8* Find(std::string alias);

	~AudioPlayer();

private:


	DirectSound* m_Sound;
	std::unordered_map<std::string, IDirectSoundBuffer8*> m_SoundData; //�Z�J���_���o�b�t�@
	WAVEFORMATEX m_format;			  //�f�[�^�t�H�[�}�b�g�\����
	DWORD m_size;					  //wave�t�@�C���̃T�C�Y


};



#endif
