#include "CSV.h"
//#include <stdlib.h>
//#include <memory>

//#include <fstream>
//#include <iostream>
//#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#pragma region C�ł̓ǂݍ���
//void LoadFile()
//{
//	// C����̃t�@�C�����͂̂��߂̏���
//	// FILE�^�\����
//	FILE* fp = NULL;
//	PlayerData* list[256];
//
//	int size = sizeof(PlayerData*);
//	memset(list, 0, sizeof(PlayerData*) * 256);
//
//	// �ǂݍ��݃��[�h�Ńt�@�C�����J��
//	// ���s�����NULL��Ԃ�
//	fopen_s(&fp, "PlayerData", "r");
//	// �t�@�C�����J���̂Ɏ��s�����Ƃ��̏���
//	if (fp == NULL)
//	{
//		return;
//	}
//
//	PlayerData pd;
//	int count = 0;
//
//	// �ǂݍ��݊J�n
//	while (fscanf_s(fp, "%[^,],%d,%d,%d\n",
//		&pd.name, 32,
//		&pd.pos_x,
//		&pd.pos_y,
//		&pd.pos_z
//	) != EOF)
//	{
//		// �擾�f�[�^��ۑ�
//		PlayerData* p_pd = (PlayerData*)malloc(sizeof(PlayerData));
//		*p_pd = pd;
//		list[count] = p_pd;
//		count++;
//	}
//
//	// CSV�t�@�C���N���[�Y
//	fclose(fp);
//}
#pragma endregion

#pragma region C++�ł̓ǂݍ���
int LoadFile()
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

	std::ifstream ifs("test.txt");
	std::string tmp;
	std::string str;
	int num;
	int sum = 0;

	// �t�@�C�����J���Ƃ��Ɏ��s�����Ƃ�
	if (ifs.fail())
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	// getline()��1�s���ǂݍ���
	while (std::getline(ifs, tmp))
	{
		std::cout << tmp << std::endl;	// ���̂܂܏o��
		std::stringstream ss;
		ss << tmp;
		ss >> str >> num;	// str == "name:"; num == number;
		sum += num;			// �l��sum�ɉ��Z
	}
	std::cout << "\nsum: " << sum << std::endl;

	// close�͎g��Ȃ��Ă�����ɕ��Ă����
	ifs.close();

	return 0;

#pragma endregion
}
#pragma endregion

void OutPutFile()
{

}