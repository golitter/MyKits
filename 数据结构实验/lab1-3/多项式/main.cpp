#include <iostream>
#include "po.h"
#include "polynomial.h"
#include "datasources.h"
#include "testitem.h"
#include <windows.h>
#include <ctime>

void test() {
	
	getAllPolynomial();

	for (int i = 0; i < 10; ++i) {
		std::cout << formula[i].retLength() << std::endl;
	}
}
void tes() {
	getAllPolynomial();
	//test_WritTxt();
	//std::cout << formula[2];
	//std::cout << formula[2];
	//Polynomial a(0, 0);
	//a.subtract(formula[2], formula[2]);
	//std::cout << a;

	//Polynomial a(0, 0), b(0, 0);
	//a.enterNape(1, 1);
	//b.enterNape(-1, 1);
	//Polynomial c(0, 0); c.add(a, b);
	//std::cout << c;
	//c.add(a, b);
	std::cout << formula[9];
	//std::cout << formula[9];
	//Polynomial a(0, 0);
	//a.add(formula[9], formula[9]);
	//std::cout << a;
	//a.subtract(formula[9], formula[9]);
	//std::cout << a;
	//std::cout << formula[9];
	//formula[9].negative(formula[9]);
	//std::cout << formula[9];
	Polynomial a(0, 0);
	a.subtract(formula[9], formula[9]);
	std::cout << a;
}


int main()
{

	tes();

	return 0;
}