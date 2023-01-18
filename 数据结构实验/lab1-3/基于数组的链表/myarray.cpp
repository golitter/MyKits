#include "myarray.h"


#include <iostream>

template<typename T>
MyArray<T>::MyArray() : _MAX_LENGTH(1000) {
	_Arr = new T[_MAX_LENGTH];
	_length = 0;
}

template<typename T>
MyArray<T>::MyArray(int len) : _MAX_LENGTH(len) {
	_Arr = new T[_MAX_LENGTH];
	_length = 0;

}

template<typename T>
int MyArray<T>::getLength() const {
	return _length;
}

template<typename T>
bool MyArray<T>::isFull() const {
	return _length == _MAX_LENGTH - 1;
}

template<typename T>
void MyArray<T>::Insert(int pos, const T& P) {
	if (isFull()) {
		std::cout << "Now Array is Full" << std::endl;
		return;
	}

	if (pos >= _length) {
		_Arr[ _length++] = P;
	}
	else {
		pos--;
		for (int i = _length - 1; i >= pos; --i) {
			_Arr[i + 1] = _Arr[i];
		}
		_Arr[pos] = P;
		_length++;
	}

}

template<typename T>
void MyArray<T>::Delete(int pos) {
	pos--;
	if (pos < 0 || pos >= _MAX_LENGTH) {
		std::cout << "Incorrect location of deleted element" << std::endl;
		return;
	}

	for (int i = pos; i < _length; ++i) {
		_Arr[i] = _Arr[i + 1];
	}

	_length--;
}

template<typename T>
int MyArray<T>::getLocation(const T& P) const {
	// maybe mulit answer
	for (int i = 0; i < _length; ++i) {
		if (P == _Arr[i]) return i + 1;
	}
	return 0;
}

template<typename T>
void MyArray<T>::Reverse() {
	int Mid = _length / 2;
	for (int i = 0; i < Mid; ++i) {
		T temp = _Arr[i];
		_Arr[i] = _Arr[_length - 1 - i];
		_Arr[_length - 1 - i] = temp;
	}
}

template<typename T>
void MyArray<T>::interValue(const T& Min, const T& Max) {
	T* preArr = _Arr;
	T* sifArr = new T[_MAX_LENGTH];
	int cnt = 0;

	for (int i = 0; i < _length; ++i) {
		if (_Arr[i] >= Min && _Arr[i] <= Max) {
			sifArr[cnt++] = _Arr[i];
		}
	}
	delete[] preArr;
	_Arr = sifArr;
	_length = cnt;
}





template<typename T>
void MyArray<T>::Print() {
	for (int i = 0; i < _length; ++i) {
		std::cout << _Arr[i] << " ";
	}
	std::cout << "\n";
}



template<typename T>
MyArray<T>::~MyArray() {
	delete[] _Arr;
}