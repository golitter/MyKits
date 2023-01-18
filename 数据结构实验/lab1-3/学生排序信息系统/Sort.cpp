#include "Sort.h"




void Sort::stableMerge(const Group &grp, int Num) {
	int length = grp.nowStuCnt;
	Student *temp = new Student[length*2];
	divideEmerge(grp._arrStu, 1, length, temp, Num);
	delete[] temp;
	//for (int i = 1; i <= length; ++i) grp._arrStu[i].printInfo();
}

void Sort::divideEmerge(Student arr[], int l, int r, Student temp[], int Num) {
	if (l >= r) return;
	int mid = (l + r) / 2;
	divideEmerge(arr, l, mid, temp, Num), divideEmerge(arr, mid + 1, r, temp, Num);

	int k = 0, i = l, j = mid + 1;

	while (i <= mid && j <= r) {
		if (leftIsGreaterThanRight(arr, i, j, Num)) temp[k++] = arr[j++];
		else temp[k++] = arr[i++];
	}
	while (i <= mid) temp[k++] = arr[i++];
	while (j <= r) temp[k++] = arr[j++];

	for (i = l, j = 0; i <= r; ++i, ++j) {
		arr[i] = temp[j]; 
		 //arr[i].printInfo();
	}
}

bool Sort::leftIsGreaterThanRight(Student arr[], int ii, int jj, int Num) {
	if (Num == NUMBER) {
		return arr[ii]._stuNumber > arr[jj]._stuNumber;
	}
	else if (Num == NAME) {
		return arr[ii]._stuName > arr[jj]._stuName;
	}
	else if (Num == SCORE_ONE) {
		return arr[ii].score1 > arr[jj].score1;
	}
	else if (Num == SCORE_TWO) {
		return arr[ii].score2 > arr[jj].score2;
	}
	else if (Num == TOTAL_SCORE) {
		return arr[ii].totalScore > arr[jj].totalScore;
	}
	else {
		// error!;
		return 0;
	}
}

void Sort::unstableQuick(const Group& grp, int Num) {
	int length = grp.nowStuCnt;
	quickStep(grp._arrStu, 1, length, Num);

}

void Sort::quickStep(Student arr[], int l, int r, int Num) {
	if (l >= r) return;
	int i = l - 1, j = r + 1;  arr[0] = arr[l + r >> 1];
	
	while (i < j) {
		do i++; while (leftIsGreaterThanRight(arr, 0, i, Num));
		do j--; while (leftIsGreaterThanRight(arr, j, 0, Num));
		if (i < j) std::swap(arr[i], arr[j]);
	}
	quickStep(arr, l, j, Num);
	quickStep(arr, j + 1, r, Num);

}