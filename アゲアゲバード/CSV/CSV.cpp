#include "CSV.h"
#include <stdlib.h>
#include <memory>

void LoadFile()
{
	FILE* fp = NULL;
	PlayerData* list[256];

	int size = sizeof(PlayerData*);
	memset(list, 0, sizeof(PlayerData*) * 256);

	// CSVファイルオープン
	fopen_s(&fp, "PlayerData", "r");
	if (fp == NULL)
	{
		return;
	}

	PlayerData pd;
	int count = 0;

	// 読み込み開始
	while (fscanf_s(fp, "%[^,],%d,%d,%d\n",
		&pd.name, 32,
		&pd.pos_x,
		&pd.pos_y,
		&pd.pos_z
	) != EOF)
	{
		// 取得データを保存
		PlayerData* p_pd = (PlayerData*)malloc(sizeof(PlayerData));
		*p_pd = pd;
		list[count] = p_pd;
		count++;
	}

	// CSVファイルクローズ
	fclose(fp);
}

void OutPutFile()
{

}