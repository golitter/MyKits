#include "Station.h"

const int UNDEFINED_LENGTH = 42;
#pragma once
class Graph
{
public:
	friend class Tool;
	Graph();
	Graph(int size);

	void setStationName();
	void setRoute();

	void setSize(int size);
	void Info() const;
	~Graph() {
		delete[] m_set;
	}
private:
	Station* m_set;
	int m_length;
	int m_nowLength;
};

