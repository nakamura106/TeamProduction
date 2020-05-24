#include "CSV.h"

#include <iostream>
#include <fstream>
#include <sstream>

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