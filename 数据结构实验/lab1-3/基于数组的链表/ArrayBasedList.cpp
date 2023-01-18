// ArrayBasedList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "myarray.h"
#include "myarray.cpp"

void test() {

    MyArray<int> a(34);
    std::cout << a.isFull();
    a.Insert(0,34);
    a.Insert(2,23);
    a.Insert(3,4545);
    a.Insert(4,11111);
    a.Insert(2, 22222);
    std::cout << a.isFull() << std::endl;
    std::cout << a.getLength() << std::endl;
    a.Print();
    a.Reverse();
    a.interValue(3, 56);
    a.Print();
    std::cout << "pos: " << a.getLocation(3) << std::endl;
    a.Delete(1);
    a.Print();
    std::cout << a.getLength();
}

void testDouble() {
    MyArray<double> ab(1000);
    ab.Insert(0,3.1);
    ab.Insert(1,34.2);
    ab.Insert(2,5555.555);
    ab.Insert(3,23.9);
    ab.Print();
    ab.Reverse();
    ab.Print();

    std::cout << ab.getLocation(3.1) << std::endl;
    ab.Delete(2);
    ab.Print();
}

int main()
{
    testDouble();

}
