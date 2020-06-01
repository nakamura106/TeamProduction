#include "Calculation.h"

#include <sstream>
#include <iomanip>

std::vector<std::string> Calculation::FixTheMinute(std::vector<int> veci_)
{
	std::vector<std::string> strvec;
	std::vector<std::string> minutes;
	std::vector<std::string> seconds;
	for (int i = 0; i < veci_.size(); i++)
	{
		AlignDigit(veci_[i] / 60, minutes);
		AlignDigit(veci_[i] - (stoi(minutes[i]) * 60), seconds);

		std::stringstream ss;
		ss << minutes[i] << ':' << seconds[i];
		std::string str(ss.str());
		strvec.push_back(str);
	}

	return strvec;
}

void Calculation::AlignDigit(int a_, std::vector<std::string>& strvec_)
{
	int num = a_;
	int s_num = a_;
	int min_digit = 0;
	while (s_num != 0)
	{
		s_num = s_num / 10;
		++min_digit;
	}
	if (min_digit <= 1)
	{
		std::ostringstream oss;
		oss << std::setw(2) << std::setfill('0') << num;
		std::string s(oss.str());
		strvec_.push_back(s);
	}
	else {
		std::ostringstream oss;
		oss << num;
		strvec_.push_back(oss.str());
	}
}