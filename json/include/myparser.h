#pragma once
#include "./myjson.h"
// #include <iostream>
#include <string>
#include <stdexcept>
using std::string;

namespace golitter{
    namespace json {
class Parser {
public:
    Parser();
    void load(const string& str);

    // ����������
    Json parse();

private:
    string m_str;
    int m_idx;

    // ȥ�հ��ַ�
    void skip_white_space();
    // ��ȡ��һ���ַ�
    char get_next_token();

    // ����

    Json parse_null();
    Json parse_bool();
    Json parse_number();
    string parse_string();
    Json parse_array();
    Json parse_object();
};

}
}