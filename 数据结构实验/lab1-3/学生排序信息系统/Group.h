#include "Student.h"

#pragma once
class Group
{
public:
	friend class Sort;
	friend class Search;
	typedef int Size;
	typedef Student* stucapc;
	Group() {
		length = 121;
		_arrStu = new Student[121 + 1];
	}
	Group(Size size): length(size) {
		_arrStu = new Student[size + 1];
	}

	void inputStuInfo(std::string number, std::string name, bool sex, double s1, double s2);

	void printInfo() const;
	void printScoreInfo() const;
	~Group() {
		delete[] _arrStu;
	}
private:
	stucapc _arrStu;
	//std::pair<double, double> _scoAvg;
	std::pair<double, double> _scoMax = { -1,-1 };
	std::pair<double, double> _scoMin = { 0x3f3f3f3f, 0x3f3f3f3f };
	int length;
	int nowStuCnt;
};

