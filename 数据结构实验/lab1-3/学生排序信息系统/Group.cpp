#include "Group.h"

void Group::inputStuInfo(std::string number, std::string name, bool sex, double s1, double s2) {
	if (nowStuCnt >= length) {
		std::cout << "FULL!" << std::endl;
		return;
	}
	_arrStu[++nowStuCnt].setName(name);
	_arrStu[nowStuCnt].setNumber(number);
	_arrStu[nowStuCnt].setSex(sex);
	_arrStu[nowStuCnt].setScore1(s1), _arrStu[nowStuCnt].setScore2(s2); 
	_arrStu[nowStuCnt].setSumScore();
	_scoMax = { std::max(_scoMax.first, _arrStu[nowStuCnt].getScore1()), std::max(_scoMax.second, _arrStu[nowStuCnt].getScore2()) };
	_scoMin = { std::min(_scoMax.first, _arrStu[nowStuCnt].getScore1()), std::min(_scoMax.second, _arrStu[nowStuCnt].getScore2()) };

}

void Group::printInfo() const {
	for (int i = 1; i <= nowStuCnt; ++i) _arrStu[i].printInfo();
	puts("");
}
void Group::printScoreInfo() const {
	double avg1 = 0, avg2 = 0;
	for (int i = 1; i <= nowStuCnt; ++i) {
		avg1 += _arrStu[i].getScore1();
		avg2 += _arrStu[i].getScore2();
	}
	// avg1 / nowStuCnt, avg2 / nowStuCnt 
	std::cout << "There are " << nowStuCnt << " students in all. "
		<< "The average score of score1 is " << avg1 / nowStuCnt << " \nand the average score of score2 is "
		<< avg2 / nowStuCnt << "\n The max score1 is " << _scoMax.first << " ,the min score1 is " << _scoMin.first << "\n"
		<< "The max score2 is " << _scoMax.second << " ,the min score2 is " << _scoMin.second << "\n";

}

