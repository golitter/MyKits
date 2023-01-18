#include "testitem.h"

void testSample__TimeKeeping() {
	std::clock_t startTime, endTime;
	startTime = std::clock();
	for (int i = 0; i < 343444; ++i) {
		std::cout << i << std::endl;
	}
	endTime = std::clock();
	std::cout << (double)(endTime - startTime) / CLOCKS_PER_SEC << std::endl;
}

void test_WritTxt() {
	std::ofstream datatext;
	datatext.open("resultText.txt", std::ios::out);
	if (!datatext.is_open()) {
		std::cout << "error about opening file!" << std::endl;
		exit(0);
	}

	std::ofstream datadd;
	datadd.open("hasadd.txt", std::ios::out);
	if (!datadd.is_open()) {
		std::cout << "error about opening file!" << std::endl;
		exit(0);
	}

	//std::ofstream datasub;
	//datasub.open("hassub.txt", std::ios::out);
	//if (!datasub.is_open()) {
	//	std::cout << "error about opening file!" << std::endl;
	//	exit(0);
	//}

	//std::ofstream datamulit;
	//datamulit.open("resultText.txt", std::ios::out);
	//if (!datamulit.is_open()) {
	//	std::cout << "error about opening file!" << std::endl;
	//	exit(0);
	//}

	int ___cnt = 1;
	for (int pre = 0; pre < _MAX_LENGTH; ++pre) {
		for (int sif = 0; sif < _MAX_LENGTH; ++sif) {

			if (pre == sif) continue;
			
			datatext << "------------------------"
				<< ___cnt++
				<< "--------------------------\n";
			std::clock_t _startTime, _endTime;
			datatext << "pre polynomial: \n";
			datatext << formula[pre];
			datatext << "sif polynomial \n";
			datatext << formula[sif];
			Polynomial _res(0, 0);

			datadd << formula[pre].retLength() << " + " << formula[sif].retLength() << " :";

			_startTime = std::clock();

			_res.add(formula[pre], formula[sif]);


			datatext << "add about polynomial \n";
			datatext << _res;

			_res.subtract(formula[pre], formula[sif]);
			datatext << "subtract about polynomial \n";
			datatext << _res;

			_res.multiply(formula[pre], formula[sif]);
			datatext << "multiply about polynomial \n";
			datatext << _res;

			datatext << "\n\n";

			for (int k = 0; k <= 1000; ++k) {

				_res.add(formula[pre], formula[sif]);

				_res.subtract(formula[pre], formula[sif]);

				_res.multiply(formula[pre], formula[sif]);


			}

			_endTime = std::clock();

			datadd << ((double)(_endTime - _startTime) / CLOCKS_PER_SEC) << "\n";

		}
	}

	datatext.close();


}