#include "CSV.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

int CSV::CreateFile_()
{
	const char* fileName = "test.txt";
	std::ofstream ofs(fileName);
	if (!ofs)
	{
		std::cout << "ファイルが開けませんでした。" << std::endl;
		std::cin.get();
		return 0;
	}
	ofs << "player\n" << std::endl;       // 題名とかがいいかも
	std::cout << fileName << "に書き込みました。" << std::endl;
	std::cin.get();
}

bool CSV::LoadData(std::string str_)
{
	std::ifstream ifs(str_.c_str(), std::ios_base::in);

	if (ifs.fail())
	{
		return -1;
	}

	std::string str;
	while (getline(ifs, str))
	{
		ifs >> str;

		std::vector<std::string> strvec = Split(str, ',');

		if (strvec.empty() == false)
		{
			std::string key_name = strvec[0];
			auto itr = character_param.find(key_name);
			if (itr != character_param.end())
			{
				// キーが設定されている場合
				//要素をいったん消してからpush_back
				character_param.erase(key_name);
				for (int i = 1; i < strvec.size(); ++i)
				{
					character_param[key_name].push_back(strvec[i]);
				}
			}
			else {
				// キーが設定されていない場合
				for (int i = 1; i < strvec.size(); ++i)
				{
					character_param[key_name].push_back(strvec[i]);
				}
			}
		}
	}

	ifs.close();

	return false;
}

bool CSV::WriteData(std::string str_, std::vector<std::string> strvec_)
{
	std::ofstream ofs(str_, std::ios_base::out);

	if (ofs.fail())
	{
		return -1;
	}

	std::vector<int> score_table;
	for (int i = 0; i < strvec_.size(); i++)
	{
		std::vector<int> num;
		for (int j = 0; j < strvec_[i].size(); j++)
		{
			if (strvec_[i][j] == ':')
			{
				continue;
			}
			else {
				num.push_back(strvec_[i][j] - '0');
			}
		}
		score_table.push_back((num[0] * 600) + (num[1] * 60) + (num[2] * 10) + (num[3]));
	}

	std::sort(score_table.begin(), score_table.end());

	int count = 0;
	for (int i = 0; i < score_table.size(); i++)
	{
		if (score_table[i] == 0)
		{
			score_table.erase(score_table.begin() + i);
			score_table.push_back(0);
			i--;
		}
		count++;
		if (count >= score_table.size())
		{
			break;
		}
	}

	std::vector<std::string> ranking;

	ranking = m_calculation.FixTheMinute(score_table);

	ofs << "RANKING" << std::endl;
	ofs << "Ranking" << ','
		<< ranking[0] << ','
		<< ranking[1] << ','
		<< ranking[2]
		<< std::endl;

	ofs.close();
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