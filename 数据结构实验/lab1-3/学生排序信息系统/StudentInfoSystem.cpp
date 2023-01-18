#include "StudentInfoSystem.h"


void StudentInfoSystem::mainFunc() const {
	while (true) {
		system("cls");
		homeScreen();
		int opt; std::cin >> opt;
		if (opt == 1) {
			viewInterface();
		}
		else if (opt == 2) {
			searchInterface();
		}
		else if (opt == 3) {
			break;
		}
		else {
			;
		}
	}
}

void StudentInfoSystem::homeScreen() const {
	std::cout << "\t\t\tWelcome to SUXT Student Information Management System!\n";
	std::cout << "\t\t\t1. View information\n";
	std::cout << "\t\t\t2. Find student information\n";
	std::cout << "\t\t\t3. exit program\n";
	std::cout << std::endl;
	std::cout << "Please enter what you want to execute.[Numerical numbering representation]: ";
}
void StudentInfoSystem::viewScreen1() const {
	std::cout << "\t\t\tYou can sort the following information:\n";
	std::cout << "\t\t\t1. student number\n";
	std::cout << "\t\t\t2. student name\n";
	std::cout << "\t\t\t3. score1\n";
	std::cout << "\t\t\t4. score2\n";
	std::cout << "\t\t\t5. total points\n";
	std::cout << "\t\t\t6. exit\n";
	std::cout << "Please enter what you want to execute.[Numerical numbering representation]: ";
}
void StudentInfoSystem::viewScreen2() const {
	std::cout << "\t\t\tSelect sort type: \n";
	std::cout << "\t\t\t1. stable sort -- merge sort\n";
	std::cout << "\t\t\t2. unstable sort -- quick sort\n";
	std::cout << "Please enter what you want to execute.[Numerical numbering representation]: ";
}

void StudentInfoSystem::viewInterface() const {
	while (true) {
		system("cls");
		viewScreen1();
		int opt1; std::cin >> opt1;
		viewScreen2();
		int opt2; std::cin >> opt2;
		if (opt1 >= 1 && opt1 <= 5 && opt2 >= 1 && opt2 <= 2) {
			selectSortMethod(opt1, opt2);
			group.printInfo();
			group.printScoreInfo();
			std::cout << "Enter any string to roll back.";
			std::string str; std::cin >> str;

		}
		else if (opt1 == 6) {
			break;
		}
	}

}

void StudentInfoSystem::selectSortMethod(int opt1, int opt2) const {
	if (opt2 == 1) {
		if (opt1 == 1) Sort::stableMerge(group, opt1 - 1);
		else if (opt1 == 2) Sort::stableMerge(group, opt1 - 1);
		else {
			Sort::stableMerge(group, opt1);
		}
	}
	else {
		if (opt1 == 1) Sort::unstableQuick(group, opt1 - 1);
		else if (opt1 == 2) Sort::unstableQuick(group, opt1 - 1);
		else {
			Sort::unstableQuick(group, opt1);
		}
	}
}

void StudentInfoSystem::searchInterface() const {
	while(true) {
		system("cls");
		searchScreen1();
		int opt1; std::cin >> opt1;
		searchScreen2();
		int opt2; std::cin >> opt2;
		if (opt1 >= 1 && opt1 <= 2 && opt2 >= 1 && opt2 <= 2) {
			std::cout << "\t\t\tPlease enter what you want to search for: ";
			std::string str; std::cin >> str;
			int pos = selectSearchMethod(opt1, opt2, str);
			if (pos == 0) {
				std::cout << "\n\t\t\tunfound!\n";
			}
			else {
				Search::printInfo(group, pos);
			}
			std::cout << "Enter any string to roll back.";
			std::string str1; std::cin >> str1;
		}
		else if (opt1 == 3) {
			break;
		}
	}
}
void StudentInfoSystem::searchScreen1() const {
	std::cout << "\t\t\tSelect the keyword to look for.\n";
	std::cout << "\t\t\t1. student number\n";
	std::cout << "\t\t\t2. student name\n";
	std::cout << "\t\t\t3. exit\n";
	std::cout << "Please enter what you want to execute.[Numerical numbering representation]: ";
}
void StudentInfoSystem::searchScreen2() const {
	std::cout << "\t\t\tChoose which algorithm to use for the search: \n";
	std::cout << "\t\t\t1. general search\n";
	std::cout << "\t\t\t2. binary search\n";
	std::cout << "Please enter what you want to execute.[Numerical numbering representation]: ";
}

int StudentInfoSystem::selectSearchMethod(int opt1, int opt2, std::string content) const {
	if (opt2 == 1) {
		return Search::plainVersion(group, opt1 - 1, -1, content);
	}
	else {
		return Search::binaryVersion(group, opt1 - 1, -1, content);
	}
}
