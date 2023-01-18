#include "polynomial.h"

Polynomial::Polynomial() = default;

Polynomial::Polynomial(const double& poVal, const int& poExp) {
	Monom temp(poVal, poExp);
	addPoly(temp);
}
Polynomial::Polynomial(const Polynomial& P) {
	_head = nullptr;
	_rear = nullptr;
	Po* temp = P.get_Head();
	_head = new Monom(*temp);
	_head->_next = nullptr;
	_rear = _head;

	temp = temp->_next;
	while (temp != nullptr) {
		Po* p = new Monom(*temp);
		p->_next = _rear->_next;
		_rear->_next = p;
		_rear = _rear->_next;
		temp = temp->_next;
	}
}

std::ostream& operator<<(std::ostream& out, const Polynomial& P) {
	Po* list = P.get_Head();
	out << "Length of polynomial : "
		<< P.retLength() <<
		std::endl;
	
	out << "Polynomial (coefficient, power of exponent): \n";

	while (list) {
		out << list->getVal() << " " << list->getExp() << "  |";
		list = list->_next;
	}
	out << "\n";
	return out;
}


void Polynomial::enterNape(const double& poVal, const int& poExp) {
	Monom temp(poVal, poExp);
	addPoly(temp);
}

// get _head;
Po* Polynomial::get_Head() const {
	return _head;
}

// operator

Polynomial& Polynomial::operator=(const Polynomial& P) {
	_head = nullptr;
	_rear = nullptr;
	Po* temp = P.get_Head();
	_head = new Monom(*temp);
	_head->_next = nullptr;
	_rear = _head;

	temp = temp->_next;
	while (temp != nullptr) {
		Po* p = new Monom(*temp);
		p->_next = _rear->_next;
		_rear->_next = p;
		_rear = _rear->_next;
		temp = temp->_next;
	}
	return *this;
}



void Polynomial::addPoly(Monom& M) {

	StructOfMon tepLinkNode = new Monom(M);

	if (_head == nullptr) {
		_head = tepLinkNode;
		_head->_next = nullptr;

		_rear = _head;
	}
	else {
		tepLinkNode->_next = _rear->_next;
		_rear->_next = tepLinkNode;
		_rear = _rear->_next;
	}
}

void Polynomial::add(const Polynomial& P1,  Polynomial& P2) {
	Polynomial addP(P1);
	Polynomial addS(P2);

	addP.MergeSort_FindRear();
	addS.MergeSort_FindRear();
	Po* pp = addP.get_Head();
	Po* ps = addS.get_Head();
	
	//_head = nullptr;
	Po* ph = _head;
	while (pp != nullptr && ps != nullptr) {
		if (pp->getExp() == ps->getExp()) {
			double sum = pp->getVal() + ps->getVal();
			if (sum) {

				Po* ak = new Monom(sum, pp->getExp());
				pp = pp->_next;
				ps = ps->_next;
				ak->_next = nullptr;
				ph->_next = ak;
				ph = ak;
			}
			else {
				pp = pp->_next;
				ps = ps->_next;
			}
		}
		else {
			if (pp->getExp() > ps->getExp()) {
				Po* ak = new Monom(ps->getVal(), ps->getExp() );
				ps = ps->_next;
				ak->_next = nullptr;
				ph->_next = ak;
				ph = ak;
			}
			else {
				Po* ak = new Monom(pp->getVal(), pp->getExp());
				pp = pp->_next;
				ak->_next = nullptr;					
 				ph->_next = ak;
				ph = ak;
			}
		}
	}
	Po* np; 
	np = pp ? pp : ps;
	while (np != nullptr) {
		Po* ak = new Monom(*np);
		ak->_next = nullptr;
		ph->_next = ak;
		ph = ak;
		_rear = ak;
		np = np->_next;
	}
	_head = _head->_next;
	//while (_head) {
	//	std::cout << _head->getVal();
	//	_head = _head->_next;
	//}
	//MergeSort_FindRear();
}

void Polynomial::negative( Polynomial& P) {
	Po* n_ps = P.get_Head();
	while (n_ps != nullptr) {
		n_ps->enterVal((-1) * n_ps->getVal());
		n_ps = n_ps->_next;
	}
	
}

void Polynomial::subtract(const Polynomial& P1, Polynomial& P2) {

	negative(P2);
	add(P1, P2);
	negative(P2);
}

void Polynomial::multiply(const Polynomial& P1, const Polynomial& P2) {
	Polynomial addP(P1);
	Polynomial addS(P2);
	addP.MergeSort_FindRear();
	addS.MergeSort_FindRear();
	Po* pp = addP.get_Head();
	Po* ps = addS.get_Head();

	Po* nodeLink;
	nodeLink = pp;
	Po* ph;
	ph = _head;

	while (nodeLink) {
		Po* tempLink;
		tempLink = ps;

		while (tempLink) {
			double val = nodeLink->getVal() * tempLink->getVal();
			int exp = nodeLink->getExp() + tempLink->getExp();
			Po* p = new Monom(val, exp);
			
			p->_next = nullptr;
			ph->_next = p;
			ph = p;
			tempLink = tempLink->_next;
		}

		nodeLink = nodeLink->_next;
	}
	_head = _head->_next;

	MergeSort_FindRear();
}

int Polynomial::retLength() const {
	Po* faHead;
	faHead = get_Head();
	int leng = 0;

	while (faHead) {
		leng++;
		faHead = faHead->_next;
	}
	return leng;
}



void Polynomial::reverse() {
	//
	Po* ph;
	ph = get_Head();
	Po* h;
	h = nullptr;

	while (ph) {
		Po* t = ph;
		ph = ph->_next;
		t->_next = h;
		h = t;
	}
	_head = h;
	
	ph = _head;
	while (ph) {
		_rear = ph;
		ph = ph->_next;
	}
}


void Polynomial::printInfo() const {
	StructOfMon travelLink = _head;
	while (travelLink != nullptr) {
		std::cout << travelLink->getVal() << "  " << travelLink->getExp() << std::endl;
		travelLink = travelLink->_next;
	}
}

Po* Polynomial::merge(Po* pHead1, Po* pHead2) {
	
	if (pHead1 == nullptr) {
		return pHead2;
	}
	if (pHead2 == nullptr) {
		return pHead1; 
	}
	Po* falseHead = new Po(0, 0);
	Po* cur = falseHead;
	while (pHead1 && pHead2) {
		if (pHead1->getExp() < pHead2->getExp()) {
			cur->_next = pHead1;
			pHead1 = pHead1->_next;
		}
		else if (pHead1->getExp() == pHead2->getExp()) {
			pHead1->enterVal(pHead1->getVal() + pHead2->getVal());
			
			Po* temp = pHead2;
			cur->_next = pHead1;
			pHead1 = pHead1->_next;

			pHead2 = pHead2->_next;
			delete temp;
		}
		else {
			cur->_next = pHead2;
			pHead2 = pHead2->_next;
		}

		cur = cur->_next;
	}

	cur->_next = pHead1 ? pHead1 : pHead2;
	
	Po* lastp = falseHead->_next;
	delete falseHead;
	return lastp;

}

Po* Polynomial::mergeSort(Po* nowLink) {
	if (nowLink == nullptr || nowLink->_next == nullptr) return nowLink;

	Po* left = nowLink;
	Po* mid = nowLink->_next;
	Po* right = mid->_next;

	while (right != nullptr && right->_next != nullptr) {
		left = left->_next;
		mid = mid->_next;
		right = right->_next->_next;
	}
	left->_next = nullptr;

	return merge(mergeSort(nowLink), mergeSort(mid));
}

void Polynomial::MergeSort_FindRear() {
	Po* startHead = _head;
	Po* lastHead = mergeSort(startHead);

	_head = lastHead;
	while (lastHead->_next != nullptr) {
		lastHead = lastHead->_next;
	}

	_rear = lastHead;

}


Polynomial::~Polynomial() {
	Po* temp = _head;
	while (_head != nullptr) {
		temp = _head;
		_head = _head->_next;
		delete temp;
	}
	_rear = _head;
}

