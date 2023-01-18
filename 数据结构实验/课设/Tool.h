#include "Graph.h"
#include "PublicTransport.h"



#pragma once
class Tool
{
public:

	static void routeInfo(const Graph & _grp);
	static void routeInfo();
	static void disinfect(PublicTransport& _ptpt);
	static void initBus();
	static void otherBus();
	static void initGraph();
	static void initAllDev();
	static void clearBus();
	static void readData();
	static void readData(string _fileName);
	static void insertPI(PassInfo*& pi, int line, int order);
	static void busPassInfo();
	static void findCloseContact(int _stRoute, int _edRoute,int _site, int _line, int _loopNum);
	static bool isCC(PassInfo& _pi, int _site);
	static bool isSameTime(int _st, int _ed, int _otherSt, int _otherEd, int _line);
	static void SearchPositivePatients();
	static void SearchPositivePatients(string _fileName);
	static void inpFileCon(string _dataFile, string _ppFile);

	static void clearSizeNum(int _line);
	static int getSite(const int _line, PassInfo &_pi);
};

