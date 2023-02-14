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
    // cout<<obj.str();
    obj["wait"] = arr;
    cout<<obj.str()<<endl;
    obj.remove("school");
    cout<<obj.str()<<endl;
    obj.remove("wait");
    cout<<obj.str()<<endl;
        cout<<arr.str()<<endl;
    Json arr2 = arr;
    cout<<arr2.str()<<endl;
    // arr2["4534"] = 4;
    cout<<arr2.str()<<endl;
    cout<<arr.str()<<endl;
    if(arr2 == arr) {
        puts("==");
    } else {
        puts("!=");
    }
    
    if(obj == arr) {
        puts("==");
    } else {
        puts("!=");
    }
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
     * 
     * (用cmake时，读取文件失败)[https://blog.csdn.net/qq_41668266/article/details/105442375?ops_request_misc=&request_id=&biz_id=102&utm_term=cmakecpp%E8%AF%BB%E6%96%87%E4%BB%B6&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-105442375.142^v73^control,201^v4^add_ask,239^v1^insert_chatgpt&spm=1018.2226.3001.4187]
     * 
     * (个人写的基于当前cmake的文件相对路径)[https://789ak.com/index.php/2023/02/07/cmake%e8%af%bb%e5%8f%96%e9%9d%9ec%e6%96%87%e4%bb%b6/]
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
void test_cmake() {
    using namespace std;
    ifstream fin("./text/test.json");
    cout << fin.rdbuf();;

}
void test_number() {
    double a = -12345.233454;
    std::cout<<a<<std::endl;
}
int main()
{
    // test_cmake();
    // parser_111();
    // test_number();
    part_3();
    say_hello();
}