#ifndef CSV_H_
#define CSV_H_

#include <string>
#include <vector>
#include <map>

struct param {
	float m_x, m_y, m_z;
	float m_atk, m_hp;
	float m_def;
	float m_speed;
};

class CSV
{
public:
	CSV()
	{

	}
	~CSV()
	{

	}

public:
	/**
	*	@brief テキストファイルを作成する関数
	*	@return	?????
	*/
	int CreateFile();

	bool LoadData(std::string str_);

	/**
	*	@brief コンマ区切りで文字列を分割する関数
	*	@param[in] str_			string型の文字列を入れる
	*	@param[in] delimiter_	区切りたい文字を入れる
	*	@return	vector型を返す(string型を格納して)
	*/
	std::vector<std::string> Split(std::string& str_, char delimiter_);

	param* GetParam(std::string key_) {
		std::map<std::string, param>::iterator itr = character_param.find(key_);
		if (itr == character_param.end())
		{
			return nullptr;
		}
		return &character_param[key_];
	}

private:
	std::vector<std::string> m_name;
	std::vector<float> m_param;
	std::map<std::string, param> character_param;

};

#endif