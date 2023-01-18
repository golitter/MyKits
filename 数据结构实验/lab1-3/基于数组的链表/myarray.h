#pragma once


template<typename T>
class MyArray
{
public:
	MyArray();

	MyArray(int len);

	int getLength() const;

	bool isFull() const;

	void Insert(int pos,const T& P);

	void Delete(int pos);

	int getLocation(const T& P) const;

	void Reverse();

	void interValue(const T& Min, const T& Max);

	void Print();
	~MyArray();
private:
	int _length;
	T* _Arr;
	int _MAX_LENGTH;
};

