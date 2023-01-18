#pragma once
#include <iostream>
class Po
{
public:
	Po* _next;
	Po();
	Po(const double& value, const int& expr);
	// input
	void enterVal(const double& value);
	void enterExp(const int& expr);

	// output
	double getVal() const;
	int getExp() const;

	// info
	void printInfo() const;

private:
	double _val;
	int _exp;

};

