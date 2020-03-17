#include "AudioPlayer.h"


//==========================================
//  �T�E���h�v���[���[
//==========================================

bool AudioPlayer::Load(std::string alias, std::string file_name) {

	//�܂��ǂݍ���ł��Ȃ��T�E���h�f�[�^�ł���
	/*
		std::unordered_map.count(value�j
		 value���L�[�Ƃ����v�f�̌������s���B
		 �v�f���聨�P�@�v�f�Ȃ����O
	*/
	if (m_SoundData.count(alias) == 0) {
		m_SoundData.emplace(alias, m_Sound->LoadWaveFile(file_name));
		return true;
	}
	return false;
}

//------------------------------------
// �Đ�
void AudioPlayer::Play(
	std::string alias,
	int volume,
	bool is_loop
) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}

	if (is_loop) {
		sound->SetVolume(volume);
		sound->Play(0, 0, DSBPLAY_LOOPING);
	}
	else {
		sound->SetVolume(volume);
		sound->Play(0, 0, 0);
		sound->SetCurrentPosition(0);
	}
}

//----------------------------------
// ��~
void AudioPlayer::Stop(std::string alias) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}
	sound->Stop();
}

//----------------------------------
// �{�����[������
void AudioPlayer::SetVolume(std::string alias, int volume) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}
	sound->SetVolume(volume);
}

//-------------------------------
//�������
void AudioPlayer::Release(std::string alias) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}

	if (sound) {
		sound->Release();
		sound = nullptr;
		m_SoundData.erase(alias);//�v�f�폜
	}
}

IDirectSoundBuffer8* AudioPlayer::Find(std::string alias) {

	//�T�E���h�f�[�^���L�[�Ō���
	auto data = m_SoundData.find(alias);
	//�T�E���h�f�[�^���݂������ꍇ
	if (data != m_SoundData.end()) {
		return data->second;
	}
	return nullptr;//������Ȃ������̂�null��n��
}

AudioPlayer::~AudioPlayer() {

	if (m_SoundData.empty()) {
		//�v�f�̍폜�����ׂĊ������Ă���ꍇ�̓N���A
		m_SoundData.clear();
	}
	//����R�ꂪ����ꍇ
	for (auto data : m_SoundData) {
		IDirectSoundBuffer8* sound = data.second;
		if (sound == nullptr) {
			continue;
		}
		sound->Release();
		//m_SoundData.erase(data.first);
	}
	m_SoundData.clear();

	if (m_Sound) {
		delete m_Sound;
	}
}

