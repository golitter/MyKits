#include "../include/myjson.h"
#include <iostream>
using golitter::json::Json;
void say_hello(){
    std::cout << "Hello, from myJSON!\n";
}
void part_1() {
    Json v1;
    Json v2 = true;
    Json v3 = "hello world";
    Json v4 = string("dkfjkj");
    bool fg = v2;
    string str = v3;
    string str2 = v4;
    std::cout<<str2<<std::endl;
}
void part_2() {
    Json arr;
    arr[0] = true;
    arr[1] = 123;
    arr.append(1.34);
    arr.append("hello world");
    bool b = arr[0];
    int i = arr[1];
    using namespace std;
    cout<<b<<endl;
    cout<<i<<endl;
    string str = arr[3];
    cout<<str<<endl;
    cout<<arr.str()<<endl;

    // obj
    Json obj;
    obj["school"] = "sust";
    obj["name"] = "golitter";
    obj["grade"] = 99;
    cout<<obj.str()<<endl;
    /**
     * 
    */
}
int main()
{
    part_2();

    say_hello();
}