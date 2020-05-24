#ifndef CSV_H_
#define CSV_H_

#include "../Utility/Singleton.h"

#include <string>
#include <vector>
#include <map>

class CSV :public Singleton<CSV>
{
private:
	friend Singleton<CSV>;

public:
	/**
	*	@brief<Get> �w�肳�ꂽ�L�[�̒��̃p�����[�^�擾����֐�
	*	@param[in] key_ key�̖��O������
	*	@return	�L�[�̒��̒l��Ԃ�
	*/
	std::vector<std::string>* GetParam(std::string key_)
	{
		std::map<std::string, std::vector<std::string>>::iterator itr = character_param.find(key_);
		if (itr == character_param.end())
		{
			return nullptr;
		}

		return &character_param[key_];
	}

	/**
	*	@brief csv(txt)�t�@�C����ǂݍ��ފ֐�
	*	@param[in] str_	string�^�̕����������
	*	@return bool�^��Ԃ�
	*/
	bool LoadData(std::string str_);

private:
	/**
	*	@brief �R���}��؂�ŕ�����𕪊�����֐�
	*	@param[in] str_			string�^�̕����������
	*	@param[in] delimiter_	��؂肽������������
	*	@return	vector�^��Ԃ�(string�^���i�[����)
	*/
	std::vector<std::string> Split(std::string& str_, char delimiter_);

private:
	CSV() {}
	~CSV() {}

	CSV(const CSV&);
	CSV& operator=(const CSV&) = delete;

	CSV& operator=(const CSV&&) = delete;

private:
	static CSV* p_CSVInstance;

	std::vector<std::string> m_name;
	std::vector<float> m_param;

	std::map < std::string, std::vector<std::string> > character_param;

};

#endif