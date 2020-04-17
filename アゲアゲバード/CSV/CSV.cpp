#include "CSV.h"
#include <stdlib.h>
#include <memory>

void LoadFile()
{
	FILE* fp = NULL;
	PlayerData* list[256];

	int size = sizeof(PlayerData*);
	memset(list, 0, sizeof(PlayerData*) * 256);

	// CSV�t�@�C���I�[�v��
	fopen_s(&fp, "PlayerData", "r");
	if (fp == NULL)
	{
		return;
	}

	PlayerData pd;
	int count = 0;

	// �ǂݍ��݊J�n
	while (fscanf_s(fp, "%[^,],%d,%d,%d\n",
		&pd.name, 32,
		&pd.pos_x,
		&pd.pos_y,
		&pd.pos_z
	) != EOF)
	{
		// �擾�f�[�^��ۑ�
		PlayerData* p_pd = (PlayerData*)malloc(sizeof(PlayerData));
		*p_pd = pd;
		list[count] = p_pd;
		count++;
	}

	// CSV�t�@�C���N���[�Y
	fclose(fp);
}

void OutPutFile()
{

}