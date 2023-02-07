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

}
void part_3() {
    Json arr;
    arr[0] = true;
    arr[1] = 1234;
    arr[3] = "skldjf";

    for(auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout<<it->str()<<std::endl;
    }
    puts("");
    using namespace std;
    cout<<arr.has(0)<<endl;
    cout<<arr.has(34)<<endl;
    arr.remove(0);
    cout<<arr.str()<<endl;

    Json obj;
    obj["school"] = "sust";
    obj["name"] = "golitter";
    obj["age"] = 20;
    obj["wait"] = arr;
    cout<<obj.str();
    obj.remove("school");
    cout<<obj.str();
    obj.remove("wait");
    cout<<obj.str();
    /// @bug: 内存泄漏 待改
        // cout<<arr.str();
}
void parser_1() {
    string str = "null";
    Json v;
    v.parse(str);
    using namespace std;
    cout<<v.str()<<endl;
    
    Json v1;
    // str = "false";
    str = "true";
    v1.parse(str);
    cout<<v1.str()<<endl;

    str = "1234";
    v1.parse(str);
    cout<<v1.str()<<endl;
    str = "-12345.233454";
    v1.parse(str);
    cout<<v1.str()<<endl;
    str = "12345.769";
    v1.parse(str);
    cout<<v1.str()<<endl;
}
void test_number() {
    double a = -12345.233454;
    std::cout<<a<<std::endl;
}
int main()
{
    parser_1();
    // test_number();
    say_hello();
}