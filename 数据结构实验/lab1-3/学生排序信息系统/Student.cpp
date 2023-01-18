#include "Student.h"

void Student::setNumber(std::string number) {
	_stuNumber = number;
}
std::string Student::getNumber() const {
	return _stuNumber;
}

void Student::setName(std::string name) {
	_stuName = name;
}
std::string Student::getName() const {
	return _stuName;
}

void Student::setSex(bool fg) {
	_stuSex = fg;
}
std::string Student::getSex() const {
	return _stuSex ? "male" : "female";
}

void Student::setScore1(double s1) {
	score1 = s1;
}
double Student::getScore1() const {
	return score1;
}

void Student::setScore2(double s2) {
	score2 = s2;
}
double Student::getScore2() const {
	return score2;
}

void Student::setSumScore() {
	totalScore = getScore1() + getScore2();
}
double Student::getSumScore() const {
	return totalScore;
}

void Student::printInfo() const {
	std::cout.width(14); ;
	std::cout << std::setiosflags(std::ios_base::fixed); std::cout << std::setprecision(2);
	std::cout << std::setiosflags(std::ios_base::left) << getName() << " ";
	std::cout.width(10); std::cout << getNumber() << " ";
	std::cout.width(7); std::cout << getSex() << " ";
	std::cout.width(7); std::cout << getScore1() << " ";
	std::cout.width(7); std::cout << getScore2() <<" ";
	std::cout.width(7); std::cout << getSumScore() << std::endl << std::resetiosflags(std::ios_base::left);
}
