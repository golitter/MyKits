#include "Graph.h"
#include "PILoop.h"
#pragma once

const int MAX_NUMBER_of_PASSENGER = 16;


class PublicTransport
{
public:
	friend class Tool;
	PublicTransport() {
		m_lineNumber = -1;
		_reHead = new PILoop;
		_reHead->m_runNext = nullptr;
		_reTail = _reHead; // cout << bus[i]._reHead << "test add \n";
		_reTail->_head = new PassInfo;
		_reTail->_head->m_next = nullptr;
		_reTail->_tail = _reTail->_head;
		_reTail->m_runNum = 1;
	}
	void init();
	PublicTransport(string driver, string serialnumber, int lineNum): m_busDriver(driver), m_serialNumber(serialnumber),m_lineNumber(lineNum) {
		setStart_End();
		m_passengers[0] = true;
		m_nowNum = 1;
		PublicTransport();
		for (int i = 1; i <= MAX_NUMBER_of_PASSENGER; ++i) m_passengers[i] = false;
	}
	void setInfo(string driver, string serialnumber, int lineNum);
	void setStart_End();
	void Info() const;
	~PublicTransport() {
		_reHead = _reHead; // ->m_runNext;
		while (_reHead) {
			PILoop* _p = _reHead;
			_reHead = _reHead->m_runNext;
			delete _p;
		}
	}
private:
	string m_serialNumber;
	string m_busDriver;
	int m_lineNumber;
	int m_stNumber, m_edNumber;
	int m_loopNum;
	bool m_passengers[MAX_NUMBER_of_PASSENGER + 1];
	int m_nowNum;
	PILoop* _reHead = nullptr;
	PILoop* _reTail = nullptr;
};

