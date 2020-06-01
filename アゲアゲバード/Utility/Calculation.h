#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <vector>
#include <string>

class Calculation
{
public:
	Calculation() {}
	~Calculation() {}

public:
	std::vector<std::string> FixTheMinute(std::vector<int> veci_);

private:
	void AlignDigit(int a_, std::vector<std::string>& minutes_);

};

#endif