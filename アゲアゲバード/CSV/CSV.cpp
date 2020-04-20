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
//int LoadFile(const char* p_file_name_)
//{
//	// C言語のファイル入力のための準備
//	// FILE型構造体
//	FILE* fp;
//	char str[256];
//
//	// ファイル読み込み
//	fopen_s(&fp, "Res/ReadFile/test.txt", "r");
//	// ファイルの読み込みに失敗したとき
//	if (fp == NULL)
//	{
//		return -1;
//	}
//	
//	while ()
//	{
//
//	}
//
//	// CSVファイルクローズ
//	fclose(fp);
//}
#pragma endregion

#pragma region C++での読み込み
int LoadFile(const char* p_file_name_)
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

	//std::ifstream ifs(p_file_name_);
	//std::string str;

	//// ファイルを開くときに失敗したとき
	//if (ifs.fail())
	//{
	//	std::cerr << "Failed to open file." << std::endl;
	//	return -1;
	//}

	//// getline()で1行ずつ読み込む
	//while (getline(ifs, str))
	//{
	//	std::cout << str << std::endl;
	//}

	//// closeは使わなくても勝手に閉じてくれる
	//ifs.close();

	return 0;

#pragma endregion
}
#pragma endregion

void OutPutFile()
{

}