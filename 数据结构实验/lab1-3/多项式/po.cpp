#include "po.h"

Po::Po() = default;
Po::Po(const double& value, const int& expr):_val(value), _exp(expr) {}
// input
void Po::enterVal(const double& value) {
	this->_val = value;
}

void Po::enterExp(const int& expr) {
	this->_exp = expr;
}


// output
double Po::getVal() const {
	return this->_val;
}

int Po::getExp() const {
	return this->_exp;
}

// Info
void Po::printInfo() const {
	std::cout << this->_val << " " << this->_exp << std::endl;
}