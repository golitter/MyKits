#pragma once
#include "./myjson.h"
#include <string>
#include <stdexcept>

#define NDEBUG
#include <assert.h>
using std::string;

namespace golitter{
    namespace json {
class Parser {
public:
    Parser();
    void load(const string& str);

    // 解释器返回
    Json parse();

private:
    string m_str;
    int m_idx;

    // 去空白字符
    void skip_white_space();
    // 获取下一个字符
    char get_next_token();

    // 解析

    Json parse_null();
    Json parse_bool();
    Json parse_number();
    string parse_string();
    Json parse_array();
    Json parse_object();
};

}
}