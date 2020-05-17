#include "CSV.h"

#include <iostream>
#include <fstream>
#include <sstream>

int CSV::CreateFile()
{
	const char* fileName = "creat.txt";

	std::ofstream ofs(fileName);
	if (!ofs)
	{
		std::cin.get();
		return 0;
	}

	ofs << "player\n" << std::endl;

	std::cin.get();
}

std::vector<std::string> CSV::Split(std::string& input_, char delimiter_)
{
	std::istringstream stream(input_);
	std::string field;
	std::vector<std::string> result;
	while (getline(stream, field, delimiter_))
	{
		result.push_back(field);
	}

	return result;
}

bool CSV::LoadData(std::string str_)
{
	std::ifstream ifs(str_.c_str(), std::ios_base::in);

	if (ifs.fail())
	{
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}
	std::string str;

	while (getline(ifs, str))
	{
		ifs >> str;
		std::vector<std::string> strvec = Split(str, ',');

		param pr;

		std::string charname = strvec[0];
		pr.m_x = std::stof(strvec[1]);
		pr.m_y = std::stof(strvec[2]);
		pr.m_z = std::stof(strvec[3]);
		pr.m_atk = std::stof(strvec[4]);
		pr.m_hp = std::stof(strvec[5]);
		pr.m_def = std::stof(strvec[6]);
		pr.m_speed = std::stof(strvec[7]);

		character_param[charname] = pr;
	}

	ifs.close();

	return false;
}