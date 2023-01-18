#pragma once
#include "Po.h"
#include <ostream>

class Polynomial
{
public:
	friend std::ostream& operator<<(std::ostream& out, const Polynomial& P);
	typedef Po Monom;
	typedef Po* StructOfMon;
	Polynomial();
	Polynomial(const double& poVal, const int& poExp);
	Polynomial(const Polynomial& P);


	// get 
		// _head;
	Po* get_Head() const;

	// operator
	Polynomial& operator=(const Polynomial& P);


	// input one node of polynomial
	void enterNape(const double& poVal, const int& poExp);
	// at polynomial .. add one node of polynomial
	void addPoly(Monom& M);

	// sort
	Po* merge(Po* pHead1, Po* pHead2);
	Po* mergeSort(Po* nowLink);
	// remake _rear pointer
	void MergeSort_FindRear();

	// add
	void add(const Polynomial& P1,  Polynomial& P2);
	// subtract
	void subtract(const Polynomial& P1,  Polynomial& P2);
	void negative( Polynomial& P);
	// multiply
	void multiply(const Polynomial& P1, const Polynomial& P2);

	// has number
	int retLength() const;


	// reverse
	void reverse();

	// print Info
	void printInfo() const ;

	// last clear memory
	~Polynomial();
private:
	Monom* _head = nullptr;
	Monom* _rear = nullptr;
};

std::ostream& operator<<(std::ostream& out, const Polynomial& P);

