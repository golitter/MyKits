#include "Group.h"
#include "Sort.h"
#include "Search.h"
#pragma once
class StudentInfoSystem
{
public:
	StudentInfoSystem() {
		group.inputStuInfo("2021001", "golitter", 1, 98, 100);
		group.inputStuInfo("2021003", "kerwin", 0, 65, 76);
		group.inputStuInfo("2021002", "golemon", 1, 91, 89);
		group.inputStuInfo("2021004", "yah", 1, 86, 89);
		group.inputStuInfo("2021005", "golitter", 0, 34, 56);
		group.inputStuInfo("2021006", "golitter", 0, 99, 87);
		group.inputStuInfo("2021008", "Сок»", 1, 88, 87);
		group.inputStuInfo("2021012", "Amy", 0, 97, 64);
		group.inputStuInfo("2021013", "mike", 1, 23, 33);
		group.inputStuInfo("2021015", "oten", 0, 67, 97);
	}
	void mainFunc() const;
	void homeScreen() const;
	void viewInterface() const;
	void viewScreen1() const;
	void viewScreen2() const;
	void selectSortMethod(int opt1, int opt2) const;
	void searchInterface() const;
	void searchScreen1() const;
	void searchScreen2() const;
	int selectSearchMethod(int opt1, int opt2, std::string content) const;
	Group group;

};

