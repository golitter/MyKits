#include "PassInfo.h"


istream& operator >> (istream& in, PassInfo& P)  
{
	in >> P.m_name >> P.m_phone >> P.m_getOnNum >> P.m_getOffNum;
	return in;
}
void PassInfo::setOrder(int order) {
	m_order = order;
}

void PassInfo::Info() const {
	cout << "\t\t";
	cout << "������";
	cout.width(10); cout << std::setiosflags(std::ios_base::left)<< m_name << " ";
	cout << "�ֻ��ţ�";
	cout.width(12); cout << std::setiosflags(std::ios_base::left)<< m_phone << " ";
	cout << "�ϳ����³���";
	cout.width(4); cout << m_getOnNum << " ";
	cout.width(4); cout << m_getOffNum << " ";
	cout.width(3);cout<<"���Σ�" << m_order << "\n";
}
