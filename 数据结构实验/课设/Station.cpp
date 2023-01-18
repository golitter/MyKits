#include "Station.h"

Station::Station(string name, int number, string other): m_name(name), m_serialNumber(number), m_otherInfo(other) {}

void Station::setName(string name) {
	m_name = name;
}
string Station::getName() const { return m_name; }
void Station::setSerialNumber(int number) {
	m_serialNumber = number;
}
int Station::getSerialNumber() const { return m_serialNumber; }
void Station::setOtherInfo(string other) {
	m_otherInfo = other;
}
string Station::getOtherInfo() const { return m_otherInfo; }

void Station::setName_Number(string name, int number) {
	setName(name); setSerialNumber(number);
}
