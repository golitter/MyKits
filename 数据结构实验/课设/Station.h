#include <string>
#include <iostream>
using std::string;
#pragma once
class Station
{
public:
	friend class Tool;
	friend class Graph;
	Station() = default;
	Station(string name, int number, string other);

	void setName_Number(string name, int number);
	void setName(string name);
	string getName() const;
	void setSerialNumber(int number);
	int getSerialNumber() const;
	void setOtherInfo(string other);
	string getOtherInfo() const;
private:
	string m_name;
	int m_serialNumber;
	string m_otherInfo;
	int m_next[4];
	int m_prev[4];
};

