#include "Search.h"

int Search::plainVersion(const Group& grp, int Num, double inpNum, std::string inpStr) {
	int length = grp.nowStuCnt;
	for (int i = 1; i <= length; ++i) {
		if (!(lookupFailureIsTrue(grp._arrStu[i], Num, inpNum, inpStr))) return i;
	}
	return 0;
	 
}

bool Search::lookupFailureIsTrue(Student stu, int Num, double inpNum, std::string inpStr) {
	if (Num == NUMBER) {
		return stu._stuNumber != inpStr;
	}
	else if (Num == NAME) {
		return stu._stuName != inpStr;
	}
	else if (Num == SCORE_ONE) {
		return stu.score1 != inpNum;
	}
	else if (Num == SCORE_TWO) {
		return stu.score2 != inpNum;
	}
	else if (Num == TOTAL_SCORE) {
		return stu.totalScore != inpNum;
	}
	else {
		// error
		return 0;
	}
}

int Search::binaryVersion(const Group& grp, int Num, double inpNum, std::string inpStr) {
	int length = grp.nowStuCnt;
	Sort::stableMerge(grp, Num);
	//grp.printInfo();

	int l = 1, r = length, mid;
	if (Num == NUMBER) {
		while (l < r) {
			//mid = l + r >> 1;
			mid = (l + r) / 2;
			if (grp._arrStu[mid]._stuNumber == inpStr) return mid;
			else if (grp._arrStu[mid]._stuNumber > inpStr) r = mid - 1;
			else l = mid + 1;
		}
		return 0;
	}
	else if (Num == NAME) {
		while (l < r) {
			// mid = l + r >> 1;
			mid = (l + r) / 2;
			if (grp._arrStu[mid]._stuName == inpStr) return mid;
			else if (grp._arrStu[mid]._stuName > inpStr) r = mid - 1;
			else l = mid + 1;
		}
		return 0;
	}
	else {
		// error!;
		return 11;
	}
}
 
void Search::printInfo(const Group& grp, int pos) {
	grp._arrStu[pos].printInfo();
}
