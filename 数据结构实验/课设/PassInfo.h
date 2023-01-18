#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using std::istream;
using std::cout;
using std::string;
#pragma once
class PassInfo
{
public:
	friend class PILoop;
	friend class PublicTransport;
	friend class Tool;
	friend istream& operator>> (istream &in, PassInfo& P);
	PassInfo() = default;
	void Info() const;
	void setOrder(int order);
protected:
	string m_name;
	string m_phone;
	int m_getOnNum;
	int m_getOffNum;
	int m_order;
	PassInfo* m_next = nullptr;

};

