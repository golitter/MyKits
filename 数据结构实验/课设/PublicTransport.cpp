#include "PublicTransport.h"
using std::cout;



void PublicTransport::Info() const {
	cout << "\t\t\t\t该公交车编号：" << this->m_serialNumber << "\n"
		<< "\t\t\t\t该公交车司机编号：" << this->m_busDriver << "\n";
	cout <<"\t\t\t\t线路编号：" << m_stNumber << " --> " << m_edNumber << "\n";

}

void PublicTransport::setInfo(string driver, string serialnumber, int lineNum) {
	PublicTransport();
	m_busDriver = driver;
	m_serialNumber = serialnumber;
	m_lineNumber = lineNum;
	m_loopNum = 1;
	setStart_End();
	m_passengers[0] = true;
	m_nowNum = 1;
	for (int i = 1; i <= MAX_NUMBER_of_PASSENGER; ++i) m_passengers[i] = false;
}

void PublicTransport::init() {
	PublicTransport();
}


void PublicTransport::setStart_End() {
	if (m_lineNumber == 1) {
		m_stNumber = 1;
		m_edNumber = 23;
	}
	else if (m_lineNumber == 2) {
		m_stNumber = 24;
		m_edNumber = 23;
	}
	else if (m_lineNumber == 3) {
		m_stNumber = 27;
		m_edNumber = 27;
	}
	else {
		cout << "错误！\n";
		return;
	}
}
