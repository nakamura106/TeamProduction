#include <d3dx9.h>
#include <stdlib.h>
#include "Texture.h"

// �J�e�S�����Ƃ̃e�N�X�`���ۑ��p�z��
static Texture** g_TextureList[MAX_TEXTURE_CATEGORY] = { nullptr };

// �J�e�S���̃e�N�X�`���ő�T�C�Y�̔z��
// �V�[���ǉ����ɋL����Y��Ȃ��悤��
int TextureCaterogySize[] = {
	TitleCategoryTextureList::TitleTextureMax,
	HelpCategoryTextureList::HelpTextureMax,

};

// ID�`�F�b�N
bool IsCategoryRangeCheck(int category_id, int texture_id);

void InitTexture()
{
	AllReleaseTexture();

	for (int i = 0; i < MAX_TEXTURE_CATEGORY; i++)
	{
		g_TextureList[i] = (Texture * *)malloc(sizeof(Texture*) * TextureCaterogySize[i]);

		for (int j = 0; j < TextureCaterogySize[i]; j++)
		{
			g_TextureList[i][j] = (Texture*)malloc(sizeof(Texture));
			g_TextureList[i][j]->TextureData = nullptr;
		}
	}
}

void ReleaseCategoryTexture(int release_category)
{
	if (g_TextureList[release_category] == nullptr)
	{
		return;
	}

	for (int i = 0; i < TextureCaterogySize[release_category]; i++)
	{
		if (g_TextureList[release_category][i]->TextureData == nullptr)
		{
			continue;
		}

		g_TextureList[release_category][i]->TextureData->Release();
		g_TextureList[release_category][i]->TextureData = nullptr;
	}
}

void AllReleaseTexture()
{
	for (int i = 0; i < MAX_TEXTURE_CATEGORY; i++)
	{
		ReleaseCategoryTexture(i);

		free(g_TextureList[i]);
		g_TextureList[i] = nullptr;
	}
}

bool LoadTexture(const char* file_name, int id, int texture_id)
{
	if (IsCategoryRangeCheck(id, texture_id) == false)
	{
		return false;
	}

	return CreateTexture(file_name, g_TextureList[id][texture_id]);
}

Texture* GetTexture(int category_id, int texture_id)
{
	if (IsCategoryRangeCheck(category_id, texture_id) == false)
	{
		return nullptr;
	}
	return g_TextureList[category_id][texture_id];
}

bool IsCategoryRangeCheck(int category_id, int texture_id)
{
	if (category_id <= -1 ||
		category_id >= MAX_TEXTURE_CATEGORY)
	{
		return false;
	}

	if (texture_id <= -1 ||
		texture_id >= TextureCaterogySize[category_id])
	{
		return false;
	}

	return true;
}
