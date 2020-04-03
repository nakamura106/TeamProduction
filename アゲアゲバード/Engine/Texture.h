/**
* @file Texture.h
* @brief �e�N�X�`���̓ǂݍ��݁A����ȂǁA�e�N�X�`���Ɋւ���֐��A�萔�̐錾
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Scene/BaseScene.h"
#include "../Engine/Graphics.h"

const float PI = 3.14159265f;

/** @brief �^�C�g���p�e�N�X�`���̃��X�g */
enum TitleCategoryTextureList
{
	TitleBgTex,				//!< �w�i
	HelpSelectTex,
	TitleTextureMax			//!< ���X�g�ő吔
};

// �w���v�V�[���p���X�g
enum HelpCategoryTextureList
{
	HelpBgTex,
	HelpTextureMax
};

#define TEXTURE_CATEGORY_TITLE (int)(BaseScene::SceneId::Title)			//!< �^�C�g���J�e�S���[
#define TEXTURE_CATEGORY_HELP (int)(BaseScene::SceneId::Help)				//!< �w���v�V�[��
#define TEXTURE_CATEGORY_GAME (int)(BaseScene::SceneId::Game)				//!< �Q�[���{�҃J�e�S���[
#define TEXTURE_CATEGORY_GAMEEND (int)(BaseScene::SceneId::End)				//!< �G���h�J�e�S���[
#define MAX_TEXTURE_CATEGORY (int)(BaseScene::SceneId::Max)				//!< �J�e�S���[�ő�

/**
* @brief �e�N�X�`���f�[�^�������֐�@n
* �Q�[���Ŏg�p����e�N�X�`���f�[�^��ۑ��o����悤�ɂ���
*/
void InitTexture();

/**
* @brief �J�e�S���[�P�ʂ̃e�N�X�`������֐�@n
* �����Ŏw�肳�ꂽ�J�e�S���[�̃e�N�X�`����S�ĉ������
* @param[in] category_id ����J�e�S���[
*/
void ReleaseCategoryTexture(int category_id);

/**
* @brief �e�N�X�`���̑S���@n
* �ǂݍ���ł��邷�ׂẴe�N�X�`�����������@n
* �����̊֐���EndEngine�Ŏg�p����Ă���̂ŊJ�����ŌĂԕK�v�͂Ȃ�
*/
void AllReleaseTexture();

/**
* @brief �e�N�X�`���̓ǂݍ���@n
* �w�肵�����ꂽ�p�X�̃e�N�X�`����ǂݍ��݁A�J�e�S���ɓo�^����
* @return �ǂݍ��݌���(������true)
* @param[in] file_name �ǂݍ��ރe�N�X�`����(�p�X����)
* @param[in] category_id �o�^����J�e�S���[
* @param[in] texture_id �J�e�S���[���̃e�N�X�`��ID
*/
bool LoadTexture(const char* file_name, int category_id, int texture_id);

/**
* @brief �e�N�X�`���f�[�^�̎擾@n
* �w�肳�ꂽ�J�e�S���̃e�N�X�`���f�[�^���擾����
* @return �e�N�X�`���f�[�^(�擾���s����nullptr)
* @param[in] �擾�������e�N�X�`���̃J�e�S��
* @param[in] �擾�������e�N�X�`����ID
*/
Texture* GetTexture(int category_id, int texture_id);

#endif

