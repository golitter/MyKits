#include "datasources.h"

int DataSource::getIntData() { 
	std::default_random_engine _eg(std::time(0));
	std::uniform_int_distribution<int> _ui(-10000, 10000);
	Sleep(1000);
	return _ui(_eg);
}

double DataSource::getDoubleData() {
	std::default_random_engine _eg(std::time(0));
	std::uniform_real_distribution<double> _ur(-10000, 10000);
	Sleep(1000);
	return _ur(_eg);
}

void DataSource::generatePolynomial() {

	std::ofstream datatext;
	datatext.open("datas.txt", std::ios::out);
	if (!datatext.is_open()) {
		std::cout << "error about opening file!" << std::endl;
		exit(0);
	}

	
	datatext << 10 << "\n";

	number Number = 10;
	for (int i = 0; i < 5; ++i) {
		int P_length = (i + 1) * 5;
		datatext << P_length << "\n";

		// get error: --pre not sif--
		while (P_length--) {

			number _llnt = 1;
			while (_llnt--) {
				datatext << getDoubleData() << " " << getIntData() << " ";
			}

		}
		datatext << "\n";
	}

	for (int i = 0; i < 5; ++i) {
		int P_length = (i + 1) * 10;
		datatext << P_length << "\n";
		while (P_length --) {
			datatext << getDoubleData() << " " << getIntData() << " ";
		}

		datatext << "\n";
	}

	datatext.close();

}

Polynomial formula[_MAX_LENGTH + 1];

void getAllPolynomial() {
	std::ifstream datatext;
	datatext.open("datas.txt", std::ios::in);
	
	if (!datatext.is_open()) {
		std::cout << "error file open" << std::endl;
		return ;
	}
	else {
		std::cout << "ok" << std::endl;
	}

	int _cnt = 0;
	datatext >> _cnt;
	while (_cnt--) {
		double _val;
		int _exp;
		int _poCnt = 0;
		datatext >> _poCnt;
		
		// error poCnt
		//_poCnt--;
		while (_poCnt--) {
			datatext >> _val >> _exp;
			formula[_cnt].enterNape(_val, _exp);
			//std::cout<< _cnt <<" " << _poCnt << " " << _val << " " << _exp << std::endl;
		}
		formula[_cnt].MergeSort_FindRear();
	}

	datatext.close();
}

