#include "Graph.h"
#include <fstream>

using std::ifstream;
using std::cout;

Graph::Graph() {
	m_length = UNDEFINED_LENGTH;
	m_set = new Station[UNDEFINED_LENGTH + 1];
}
Graph::Graph(int size) {
	m_length = size;
	m_set = new  Station[size + 1];
}

void Graph::setSize(int size) { m_length = size; delete[] m_set; m_set = new Station[size + 1]; }

void Graph::setStationName() {
	ifstream ifs;
	ifs.open("StationName.txt", std::ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}
	int _len = 0;
	ifs >> _len; m_nowLength = _len;
	string trav_string;
	int trav_int;
	for (int i = 1; i <= _len; ++i) {
		ifs >> trav_int >> trav_string;
		m_set[i].setName_Number(trav_string, i);
	}

	ifs.close();
}
void Graph::setRoute() {
	ifstream ifs;
	ifs.open("Route.txt", std::ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！\n";
		return;
	}

	for (int i = 1; i <= m_nowLength; ++i) {
		for (int j = 1; j <= 3; ++j) {
			m_set[i].m_next[j] = -2;
			m_set[i].m_prev[j] = -2;
		}
	}
	int _n; ifs >> _n;
	while (_n--) {
		int _len; ifs >> _len;
		int _v, _u, _line;
		for (int i = 1; i <= _len; ++i) {
			ifs >> _v >> _u >> _line;
			m_set[_v].m_next[_line] = _u;
			m_set[_u].m_prev[_line] = _v;
		}
	}
}

void Graph::Info() const {
	cout << "路线长度：" << this->m_length << "\n";
	for (int i = 1; i <= m_nowLength; ++i) {
		cout << m_set[i].getSerialNumber() << " - " << m_set[i].getName() << "\n";
	}
}

