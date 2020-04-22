#include "CSV.h"
#include <iostream>
#include <fstream>
#include <string>

int CreateFile()
{
	const char* fileName = "test.txt";

	std::ofstream ofs(fileName);
	if (!ofs)
	{
		std::cout << "ファイルが開けませんでした。" << std::endl;
		std::cin.get();
		return 0;
	}

	ofs << "player,座標,0.0,0.0,0.0\n" << std::endl;
	//ofs << "enemy1,座標 0.0,0.0,0.0\n" << std::endl;

	std::cin.get();
}

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

	std::ifstream ifs(p_file_name_, std::ios_base::in);
	std::string str;

	// ファイルを開くときに失敗したとき
	if (ifs.fail())
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	// getline()で1行ずつ読み込む
	while (getline(ifs, str))
	{
		ifs >> str;
		std::cout << str << std::endl;
	}

	// closeは使わなくても勝手に閉じてくれる
	ifs.close();

	return 0;

#pragma endregion
}
#pragma endregion

void OutPutFile()
{

}