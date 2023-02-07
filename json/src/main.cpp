#include "../include/myjson.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
void parser_11() {
    // 转义测试
    string str = "\"hello world\"";
    Json v;
    v.parse(str);
    using namespace std;
    cout<<v.str()<<endl;
    /// @attention: 一定要有空格
    str = "[\"a\", 1, 2, 3, false, true, 1.23]";
    v.parse(str);
    cout<<v.str()<<endl;

    Json obj;
    str = "{\"a\": 1, \"b\": 2, \"c\": 3}";
    v.parse(str);
    cout<<v.str()<<endl;
}
void parser_111() {
    using namespace std;
    /**
     * (用cmake时，读取文件失败)[https://blog.csdn.net/qq_41668266/article/details/105442375?ops_request_misc=&request_id=&biz_id=102&utm_term=cmakecpp%E8%AF%BB%E6%96%87%E4%BB%B6&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-105442375.142^v73^control,201^v4^add_ask,239^v1^insert_chatgpt&spm=1018.2226.3001.4187]
    */
    ifstream fin("./text/test.json");
    stringstream ss;
    ss<< fin.rdbuf();
    string str = ss.str();
    Json v;
    v.parse(str);
    cout<<str;

    cout<<v.str()<<endl;
}
void test_number() {
    double a = -12345.233454;
    std::cout<<a<<std::endl;
}
int main()
{
    parser_111();
    // test_number();
    say_hello();
}