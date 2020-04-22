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
		std::cout << "�t�@�C�����J���܂���ł����B" << std::endl;
		std::cin.get();
		return 0;
	}

	ofs << "player,���W,0.0,0.0,0.0\n" << std::endl;
	//ofs << "enemy1,���W 0.0,0.0,0.0\n" << std::endl;

	std::cin.get();
}

#pragma region C++�ł̓ǂݍ���
int LoadFile(const char* p_file_name_)
{
#pragma region char�^�̗��p
	/*
		�t�@�C�����J���āA1�s����char*�^�ɓǂݍ��ޏꍇ��
		char�^�̔z��̒������w�肵�Ă����K�v������
	*/

	//// ""�̒��ɊJ�������t�@�C����
	//std::ifstream ifs("test.txt");

	//// ��F1�s80�����̏ꍇ�A���s�������܂߂�̂ōŏI�I�ɂ�81�����ɂȂ�
	//char str[256];

	//// �t�@�C�����J���Ƃ��Ɏ��s�����Ƃ�
	//if (ifs.fail())
	//{
	//	std::cerr << "Failed to open file." << std::endl;
	//	return -1;
	//}

	//// getline()��1�s���ǂݍ���
	//while (ifs.getline(str, 256 - 1))
	//{
	//	std::cout << "{" << str << "}" << std::endl;
	//}

	// close�͎g��Ȃ��Ă�����ɕ��Ă����
	//ifs.close();

	//return 0;

#pragma endregion

#pragma region string�^�̗��p
	/*
		1�s�̒������ŏ��Ɏw�肷��K�v�͂Ȃ�
	*/

	std::ifstream ifs(p_file_name_, std::ios_base::in);
	std::string str;

	// �t�@�C�����J���Ƃ��Ɏ��s�����Ƃ�
	if (ifs.fail())
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	// getline()��1�s���ǂݍ���
	while (getline(ifs, str))
	{
		ifs >> str;
		std::cout << str << std::endl;
	}

	// close�͎g��Ȃ��Ă�����ɕ��Ă����
	ifs.close();

	return 0;

#pragma endregion
}
#pragma endregion

void OutPutFile()
{

}