#include "Tool.h"
#include "PublicTransport.h"

#include <fstream>
#include <utility>    

using std::ifstream;
using std::cout;

using std::pair;

pair<int, int> Route[4] = {
	{-1,-1}, {1,23}, {24,23}, {27,27}
};
#define start first
#define end second
const int ROUTE_ONE = 1;
const int ROUTE_TWO = 2;
const int ROUTE_THREE = 3;

class PublicTransport bus[4];
class Graph graph;

void Tool::routeInfo(const Graph& _grp) {
	for (int _line = 1; _line <= 3; ++_line) {

		auto route = Route[_line];
		cout << "路线 " << _line << "：\n";
		cout << "由 " << _grp.m_set[route.start].getName() << " --> " << _grp.m_set[route.end].getName() << "\n";

		cout << _grp.m_set[route.start].getName() << " --> ";
		for (int i = _grp.m_set[route.start].m_next[_line]; i != -2; i = _grp.m_set[i].m_next[_line]) {
			cout << _grp.m_set[i].getName();
			if (i == route.end) break;
			if (_grp.m_set[i].m_next[_line] != -2) {
				cout << " --> ";
			}
		}
		cout << "\n";
		cout << "由 " << _grp.m_set[route.end].getName() << " --> " << _grp.m_set[route.start].getName() << "\n";
		cout << _grp.m_set[route.end].getName() << " --> ";
		for (int i = _grp.m_set[route.end].m_prev[_line]; i != -2; i = _grp.m_set[i].m_prev[_line]) {
			cout << _grp.m_set[i].getName();
			if (i == route.start) break;
			if (_grp.m_set[i].m_prev[_line] != -2) {
				cout << " --> ";
			}
		}
		cout << "\n";

	}
}
void Tool::routeInfo() {
	routeInfo(graph);
}

void Tool::initBus() {
	bus[1].setInfo("shan001", "12345678990", 1);
	bus[2].setInfo("shan002", "0987654", 2);
	bus[3].setInfo("shan003", "5439453874", 3);

	//for (int i = 1; i <= 3; ++i) {
	//	//bus[i]._reHead = new PILoop;
	//	//bus[i]._reHead->m_runNext = nullptr;
	//	//bus[i]._reTail = bus[i]._reHead; // cout << bus[i]._reHead << "test add \n";
	//	//bus[i]._reTail->_head = new PassInfo;
	//	//bus[i]._reTail->_head->m_next = nullptr;
	//	//bus[i]._reTail->_tail = bus[i]._reTail->_head;
	//	//bus[i]._reTail->m_runNum = 1;
	//	//bus[i].Info();
	//}

}
void Tool::otherBus() {
	for (int _line = 1; _line <= 3; ++_line) {
		cout << "\t\t\t\t线路 " << _line << "：\n";
		bus[_line].Info();
	}
}

void Tool::initGraph() {
	graph.setStationName();
	graph.setRoute();
}
void Tool::initAllDev() {
	initBus();
	initGraph();
}
void Tool::clearBus() {
	for (int _line = 1; _line <= 3; ++_line) {
		//bus[_line]._reHead = bus[_line]._reHead; // ->m_runNext;
		while (bus[_line]._reHead) {
			PILoop* _p = bus[_line]._reHead;
			bus[_line]._reHead = bus[_line]._reHead->m_runNext;
			delete _p;
		}

		bus[_line]._reHead = new PILoop;
		bus[_line]._reHead->m_runNext = nullptr;
		bus[_line]._reTail = bus[_line]._reHead; // cout << bus[i]._reHead << "test add \n";
		bus[_line]._reTail->_head = new PassInfo;
		bus[_line]._reTail->_head->m_next = nullptr;
		bus[_line]._reTail->_tail = bus[_line]._reTail->_head;
		bus[_line]._reTail->m_runNum = 1;
		bus[_line].init();
	}
	initBus();
}

void Tool::disinfect(PublicTransport& _ptpt) {
	;
}

void Tool::readData() {
	ifstream ifs;
	ifs.open("PassengerInfo.txt", std::ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}
	int _len; ifs >> _len; int _line = -1; int _order;
	while (_len--) {
		PassInfo* _p;
		_p = new PassInfo();
		ifs >> (*_p) >> _line >> _order;
		insertPI(_p ,_line, _order);
	}
	ifs.close();
}
void Tool::readData(string _fileName) {
	ifstream ifs;
	ifs.open(_fileName, std::ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}
	int _len; ifs >> _len; int _line = -1; int _order;
	while (_len--) {
		PassInfo* _p;
		_p = new PassInfo();
		ifs >> (*_p) >> _line >> _order;
		insertPI(_p, _line, _order);
	}
	ifs.close();
}

void Tool::insertPI(PassInfo*& pi, int line, int order) {
	if (line == ROUTE_ONE) {
		if (order == bus[1].m_loopNum) {
			//pi->setOrder(bus[1].m_nowNum);
			pi->setOrder(getSite(ROUTE_ONE, *pi));
			bus[1]._reTail->_tail->m_next = pi;
			bus[1]._reTail->_tail = bus[1]._reTail->_tail->m_next;
			//bus[1]._reTail->_tail->Info();
			bus[1].m_nowNum++;

		}
		else {
			PILoop* p = new PILoop;
			p->m_runNum = ++bus[1].m_loopNum;
			p->m_runNext = nullptr;
			bus[1]._reTail->m_runNext = p;
			bus[1]._reTail = bus[1]._reTail->m_runNext;
			bus[1].m_nowNum = 1;

			clearSizeNum(ROUTE_ONE);

			bus[1]._reTail->_head = new PassInfo;
			bus[1]._reTail->_head->m_next = nullptr;
			bus[1]._reTail->_tail = bus[1]._reTail->_head;

			pi->setOrder(getSite(ROUTE_ONE, *pi));
			bus[1]._reTail->_tail->m_next = pi;
			bus[1]._reTail->_tail = bus[1]._reTail->_tail->m_next;
			bus[1].m_nowNum++;

		}
	}
	else if (line == ROUTE_TWO) {
		if (order == bus[2].m_loopNum) {
			pi->setOrder(getSite(ROUTE_TWO, *pi));
			bus[2]._reTail->_tail->m_next = pi;
			bus[2]._reTail->_tail = bus[2]._reTail->_tail->m_next;
			bus[2].m_nowNum++;

		}
		else {
			PILoop* p = new PILoop;
			p->m_runNum = ++bus[2].m_loopNum;
			p->m_runNext = nullptr;
			bus[2]._reTail->m_runNext = p;
			bus[2]._reTail = bus[2]._reTail->m_runNext;
			bus[2].m_nowNum = 1;

			clearSizeNum(ROUTE_TWO);

			bus[2]._reTail->_head = new PassInfo;
			bus[2]._reTail->_head->m_next = nullptr;
			bus[2]._reTail->_tail = bus[1]._reTail->_head;

			pi->setOrder(getSite(ROUTE_TWO, *pi));
			bus[2]._reTail->_tail->m_next = pi;
			bus[2]._reTail->_tail = bus[2]._reTail->_tail->m_next;
			bus[2].m_nowNum++;
		}
	}
	else if (line == ROUTE_THREE) {
		if (order == bus[3].m_loopNum) {
			pi->setOrder(getSite(ROUTE_THREE, *pi));
			bus[3]._reTail->_tail->m_next = pi;
			bus[3]._reTail->_tail = bus[3]._reTail->_tail->m_next;
			bus[3].m_nowNum++;

		}
		else {
			PILoop* p = new PILoop;
			p->m_runNum = ++bus[3].m_loopNum;
			p->m_runNext = nullptr;
			bus[3]._reTail->m_runNext = p;
			bus[3]._reTail = bus[3]._reTail->m_runNext;
			bus[3].m_nowNum = 1;

			clearSizeNum(ROUTE_THREE);

			bus[3]._reTail->_head = new PassInfo;
			bus[3]._reTail->_head->m_next = nullptr;
			bus[3]._reTail->_tail = bus[1]._reTail->_head;

			pi->setOrder(getSite(ROUTE_THREE, *pi));
			bus[3]._reTail->_tail->m_next = pi;
			bus[3]._reTail->_tail = bus[3]._reTail->_tail->m_next;
			bus[3].m_nowNum++;
		}
	}
	else {
		return;
	}
}

void Tool::busPassInfo() {
	for (int i = 1; i <= 3; ++i) {
		cout << i << " 路线：\n";
		PILoop* _p = bus[i]._reHead;
		while (_p) {
			PassInfo* _q = _p->_head->m_next;
			cout << "第 " << _p->m_runNum << "\n";
			while (_q) {
				_q->Info();
				_q = _q->m_next;
			}
			_p = _p->m_runNext;
		}  
	}
}

void Tool::findCloseContact(int _stRoute, int _edRoute, int _site, int _line, int _loopNum) {
	PILoop* _p = bus[_line]._reHead;
	_loopNum--;
	while (_loopNum--) {
		_p = _p->m_runNext;
	}
	PassInfo* _q = _p->_head->m_next;
	while (_q) {
		if ( isSameTime(_stRoute, _edRoute, _q->m_getOnNum, _q->m_getOffNum, _line) && isCC(*_q, _site)) {
			//cout << "test"; 
			_q->Info();
		}
		_q = _q->m_next;
	}
}
bool Tool::isCC(PassInfo& _pi, int _site) {
	int ord = _pi.m_order;
	if (ord == _site) return false;
	if (ord >= 1 && ord <= 4 && _site >= 1 && _site <= 4) return true;
	else if (ord >= 5 && ord <= 6 && _site >= 5 && _site <= 8) return true;
	else if (ord >= 7 && ord <= 8 && _site >= 5 && _site <= 10) return true;
	else if (ord >= 9 && ord <= 10 && _site >= 7 && _site <= 12) return true;
	else if (ord >= 11 && ord <= 12 && _site >= 9 && _site <= 14) return true;
	else if (ord >= 13 && ord <= 14 && _site >= 11 && _site <= 15) return true;
	else if (ord == 15 && _site >= 13 && _site <= 14) return true;
	else {
		return false;
	}
}

bool Tool::isSameTime(int _st, int _ed, int _otherSt, int _otherEd, int _line) {
	//cout << _st << " " << _ed << " " << _otherSt << " "<<_otherEd << "\n";
	bool fgRouteOne = false, fgRouteTwo = false;
	int _cnt = 1;
	for (int i = Route[_line].start; i != -2; i = graph.m_set[i].m_next[_line]) {
		if (_st == i) fgRouteOne = true;
		

		if (_otherSt == i) fgRouteTwo = true;
		if (fgRouteOne && fgRouteTwo) return true;
		if (i == Route[_line].end && _cnt != 1) {
			fgRouteTwo = false;
			fgRouteOne = false;
			break;
		}
		_cnt++;
		if (_ed == i) fgRouteOne = false;
		if (_otherSt == i) fgRouteTwo = false;

	}

	fgRouteOne = false, fgRouteTwo = false; _cnt = 1;
	for (int i = Route[_line].end; i != -2; i = graph.m_set[i].m_prev[_line]) {
		if (_st == i) fgRouteOne = true;

		if (_otherSt == i) fgRouteTwo = true;
		if (fgRouteOne && fgRouteTwo) return true;

		if (i == Route[_line].start && _cnt != 1) {
			fgRouteTwo = false;
			fgRouteOne = false;
			break;
		}
		_cnt++;
		if (_ed == i) fgRouteOne = false;
		if (_otherSt == i) fgRouteTwo = false;


	}
	return false;
}

void Tool::SearchPositivePatients() {
	ifstream ifs;
	ifs.open("PP.txt", std::ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}
	int _len = 0; ifs >> _len; string phone;
	while (_len--) {
		ifs >> phone;
		cout << "\n\t\t\t手机号为 " << phone << " 的密接情况：\n";
		for (int _line = 1; _line <= 3; ++_line) {
			PILoop* _p = bus[_line]._reHead;
			while (_p) {
				PassInfo* _q = _p->_head->m_next;
				while (_q) {
					if (_q->m_phone == phone) {
						cout << "\t\t\t 路线 " << _line << " :\n";
						cout << "\t\t\t 与其密接人员有：\n";
						findCloseContact(_q->m_getOnNum, _q->m_getOffNum, _q->m_order, _line, _p->m_runNum);
					}
					_q = _q->m_next;
				}
				_p = _p->m_runNext;
			}
		}
	}
}
void Tool::SearchPositivePatients(string _fileName) {
	ifstream ifs;
	ifs.open(_fileName, std::ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}
	int _len = 0; ifs >> _len; string phone;
	while (_len--) {
		ifs >> phone;
		cout << "\t\t\t手机号为 " << phone << " 的密接情况：\n";

		for (int _line = 1; _line <= 3; ++_line) {
			PILoop* _p = bus[_line]._reHead;
			while (_p) {
				PassInfo* _q = _p->_head->m_next;
				while (_q) {
					if (_q->m_phone == phone) {
						cout << "\t\t\t 路线 " << _line << " :\n";
						cout << "\t\t\t 与其密接人员有：\n";
						findCloseContact(_q->m_getOnNum, _q->m_getOffNum, _q->m_order, _line, _p->m_runNum);
					}
					_q = _q->m_next;
				}
				_p = _p->m_runNext;
			}
		}
	}
}

void Tool::inpFileCon(string _dataFile, string _ppFile) {
	clearBus();
	readData(_dataFile);
	SearchPositivePatients(_ppFile);
}

void Tool::clearSizeNum(int _line) {
	for (int i = 1; i <= MAX_NUMBER_of_PASSENGER; ++i) bus[_line].m_passengers[i] = false;
}

int Tool::getSite(const int _line, PassInfo & _pi) {
	PassInfo* _p = bus[_line]._reTail->m_next;
	while (_p) {
		if (!isSameTime(_pi.m_getOnNum, _pi.m_getOffNum, _p->m_getOnNum, _p->m_getOffNum, _line)) { 
			bus[_line].m_passengers[_p->m_order] = false; 
			bus[_line].m_nowNum--;
		}
	}

	for (int i = 1; i <= MAX_NUMBER_of_PASSENGER; ++i) {
		if (bus[_line].m_passengers[i] == false) {
			bus[_line].m_passengers[i] = true;
			return i;
		}
	}
	cout << "error!!";
	exit(1);
	return 1;
}