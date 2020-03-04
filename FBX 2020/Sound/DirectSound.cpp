#include "DirectSound.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

//===============================================
	//	�I�[�f�B�I���\�[�X�Ǘ�
	//===============================================

	//--------------------------------------------
	 //�@����Ăяo���p�R���X�g���N�^
DirectSound::DirectSound(HWND hwnd) {


	DirectSoundCreate8(nullptr, &m_DSound8, nullptr);
	m_DSound8->SetCooperativeLevel(hwnd, DSSCL_NORMAL);

	DSBUFFERDESC desc = {};
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	desc.dwBufferBytes = 0;
	desc.dwReserved = 0;
	desc.lpwfxFormat = nullptr;
	desc.guid3DAlgorithm = GUID_NULL;

	m_DSound8->CreateSoundBuffer(&desc, &m_PrimaryBuffer, nullptr);
}
//-------------------------------------
//�@�f�[�^�ǂݍ���
IDirectSoundBuffer8* DirectSound::LoadWaveFile(std::string file_name) {


	HMMIO hmmio = nullptr;
	MMIOINFO mminfo = {};
	hmmio = mmioOpen((LPSTR)file_name.c_str(), &mminfo, MMIO_READ);

	//�t�@�C���̃I�[�v���Ɏ��s�����ꍇ
	if (!hmmio) {
		MessageBox(0, "wave�t�@�C���̃I�[�v���Ɏ��s", 0, MB_OK);
		return nullptr;
	}

	MMRESULT result;
	MMCKINFO rif_chunk;
	rif_chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	result = mmioDescend(hmmio, &rif_chunk, NULL, MMIO_FINDRIFF);

	//�@���t�`�����N�̌����Ɏ��s�����ꍇ
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	MMCKINFO fmt_chunk;
	fmt_chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	result = mmioDescend(hmmio, &fmt_chunk, &rif_chunk, MMIO_FINDCHUNK);

	// �t�H�[�}�b�g�`�����N�̌����Ɏ��s�����ꍇ
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//������`�����l�����̏����i�[����
	WAVEFORMATEX format;
	DWORD fmsize = fmt_chunk.cksize;
	if (mmioRead(hmmio, (HPSTR)& format, fmsize) != fmsize) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//�f�[�^�����̈׈�x�߂�
	mmioAscend(hmmio, &fmt_chunk, 0);

	MMCKINFO data_chunk;
	data_chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	result = mmioDescend(hmmio, &data_chunk, &rif_chunk, MMIO_FINDCHUNK);
	// �f�[�^�`�����N�̌����Ɏ��s�����ꍇ
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	// �g�`�f�[�^
	DWORD data_size = data_chunk.cksize;
	BYTE* wav_data = new BYTE[data_chunk.cksize];
	if (mmioRead(hmmio, (HPSTR)wav_data, data_chunk.cksize) != data_chunk.cksize) {
		delete[] wav_data;
		return nullptr;
	}


	//����ǂݍ���
	mmioClose(hmmio, 0);

	// �Z�J���_���o�b�t�@�̐ݒ�
	DSBUFFERDESC desc = {};
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	desc.dwBufferBytes = data_size;   //�������T�C�Y
	desc.dwReserved = 0;			  //�\���
	desc.lpwfxFormat = &format;     //WAVE�t�H�[�}�b�g
	desc.guid3DAlgorithm = GUID_NULL; //3D�G�t�F�N�g���g�p���Ȃ�

	IDirectSoundBuffer* buf = 0;
	m_DSound8->CreateSoundBuffer(&desc, &buf, nullptr);

	//�߂�l��IDirectSoundBuffer�ׁ̈AIDirectSoundBuffer8�ɖ߂�
	buf->QueryInterface(IID_IDirectSoundBuffer8, (void**)& m_SecBuffer);
	buf->Release();


	// WAV�f�[�^��������
	LPVOID write_data;
	DWORD len;
	m_SecBuffer->Lock(
		0,		     	//���b�N�J�n�ʒu
		0,			    //�������T�C�Y
		&write_data,	//���b�N�ʒu�̃|�C���^
		&len,		    //�傫��
		NULL,	  	    //�͈͂𒴂����ꍇ�̃������̈�w��
		NULL,
		DSBLOCK_ENTIREBUFFER //�w��̑傫���������b�N����
	);

	memcpy(write_data, wav_data, len);
	m_SecBuffer->Unlock(write_data, len, nullptr, 0);
	//�@���������폜
	delete[] wav_data;

	if (m_SecBuffer == nullptr) {
		MessageBox(0, "wave�t�@�C���̓ǂݍ��݂Ɏ��s", 0, MB_OK);
	}

	return m_SecBuffer;
}

//-----------------------------------
//�@�f�X�g���N�^
DirectSound::~DirectSound() {

	m_DSound8->Release();
	//m_PrimaryBuffer->Release();
}

