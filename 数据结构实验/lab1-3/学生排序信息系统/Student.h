#include <string>
#include <iostream>
#include <iomanip>

#pragma once
class Student
{
public:
	friend class Sort;
	friend class Search;
	Student() = default;
	Student(std::string number, std::string name, bool sex, double s1, double s2) :
		_stuNumber(number), _stuName(name), _stuSex(sex), score1(s1), score2(s2), totalScore(s1 + s2) {};

	void printInfo() const;
	
	void setNumber(std::string number);
	std::string getNumber() const;
	
	void setName(std::string name);
	std::string getName() const;

	void setSex(bool fg);
	std::string getSex() const;

	void setScore1(double s1);
	double getScore1() const;

	void setScore2(double s2);
	double getScore2() const;

	void setSumScore();
	double getSumScore() const;

private:
	std::string _stuNumber;
	std::string _stuName;
	bool _stuSex;
	double score1, score2, totalScore;

};

