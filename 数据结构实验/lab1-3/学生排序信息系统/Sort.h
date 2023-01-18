#include "Group.h"

const int NUMBER = 0;
const int NAME = 1;
const int SEX = 2;
const int SCORE_ONE = 3;
const int SCORE_TWO = 4;
const int TOTAL_SCORE = 5;

#pragma once
class Sort
{
public:

	static void stableMerge(const Group &grp, int Num);
	static void divideEmerge(Student arr[], int l, int r, Student temp[], int Num);
	static bool leftIsGreaterThanRight(Student arr[], int ii, int jj, int Num);

	static void unstableQuick(const Group& grp, int Num);
	static void quickStep(Student arr[], int l, int r, int Num);
private:
};

