#include "CSV.h"
//#include <stdlib.h>
//#include <memory>

//#include <fstream>
//#include <iostream>
//#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#pragma region Cでの読み込み
//void LoadFile()
//{
//	// C言語のファイル入力のための準備
//	// FILE型構造体
//	FILE* fp = NULL;
//	PlayerData* list[256];
//
//	int size = sizeof(PlayerData*);
//	memset(list, 0, sizeof(PlayerData*) * 256);
//
//	// 読み込みモードでファイルを開く
//	// 失敗するとNULLを返す
//	fopen_s(&fp, "PlayerData", "r");
//	// ファイルを開くのに失敗したときの処理
//	if (fp == NULL)
//	{
//		return;
//	}
//
//	PlayerData pd;
//	int count = 0;
//
//	// 読み込み開始
//	while (fscanf_s(fp, "%[^,],%d,%d,%d\n",
//		&pd.name, 32,
//		&pd.pos_x,
//		&pd.pos_y,
//		&pd.pos_z
//	) != EOF)
//	{
//		// 取得データを保存
//		PlayerData* p_pd = (PlayerData*)malloc(sizeof(PlayerData));
//		*p_pd = pd;
//		list[count] = p_pd;
//		count++;
//	}
//
//	// CSVファイルクローズ
//	fclose(fp);
//}
#pragma endregion

#pragma region C++での読み込み
int LoadFile()
{
#pragma region char型の利用
	/*
		ファイルを開いて、1行ずつchar*型に読み込む場合は
		char型の配列の長さを指定しておく必要がある
	*/

	//// ""の中に開きたいファイル名
	//std::ifstream ifs("test.txt");

	//// 例：1行80文字の場合、改行文字も含めるので最終的には81文字になる
	//char str[256];

	//// ファイルを開くときに失敗したとき
	//if (ifs.fail())
	//{
	//	std::cerr << "Failed to open file." << std::endl;
	//	return -1;
	//}

	//// getline()で1行ずつ読み込む
	//while (ifs.getline(str, 256 - 1))
	//{
	//	std::cout << "{" << str << "}" << std::endl;
	//}

	// closeは使わなくても勝手に閉じてくれる
	//ifs.close();

	//return 0;

#pragma endregion

#pragma region string型の利用
	/*
		1行の長さを最初に指定する必要はない
	*/

	std::ifstream ifs("test.txt");
	std::string tmp;
	std::string str;
	int num;
	int sum = 0;

	// ファイルを開くときに失敗したとき
	if (ifs.fail())
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	// getline()で1行ずつ読み込む
	while (std::getline(ifs, tmp))
	{
		std::cout << tmp << std::endl;	// そのまま出力
		std::stringstream ss;
		ss << tmp;
		ss >> str >> num;	// str == "name:"; num == number;
		sum += num;			// 値をsumに加算
	}
	std::cout << "\nsum: " << sum << std::endl;

	// closeは使わなくても勝手に閉じてくれる
	ifs.close();

	return 0;

#pragma endregion
}
#pragma endregion

void OutPutFile()
{

}