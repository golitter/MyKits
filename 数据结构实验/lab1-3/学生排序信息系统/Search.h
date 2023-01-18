#include "Sort.h"

#pragma once
class Search
{
public:
	static int plainVersion(const Group& grp, int Num, double inpNum , std::string inpStr );
	static bool lookupFailureIsTrue(Student stu, int Num, double inpNum, std::string inpStr) ;
	static int binaryVersion(const Group& grp, int Num, double inpNum , std::string inpStr) ;
	static void printInfo(const Group& grp, int pos);
};

