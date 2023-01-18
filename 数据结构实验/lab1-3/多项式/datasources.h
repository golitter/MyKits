#pragma once

#include "polynomial.h"

#include <random>
#include <ctime>
#include <fstream>
#include <iostream>
#include <windows.h>


#ifndef ___FORMULA__
#define ___FORMULA__


#endif

const int _MAX_LENGTH = 10;
Polynomial formula[];

class DataSource {
public:
	typedef unsigned int number;
	int getIntData();
	double getDoubleData();
	void generatePolynomial();
};

void getAllPolynomial();