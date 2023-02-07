#include "../include/myparser.h"
using namespace golitter::json;

Parser::Parser(): m_str(""), m_idx(0) {}
void Parser::load(const string& str) {
    m_str = str;
    m_idx = 0;
}

    // 去空白字符
void Parser::skip_white_space() {
    while(m_str[m_idx] == ' ' ||
        m_str[m_idx] == '\n' || m_str[m_idx] == '\r' ||  m_str[m_idx] == '\t'
    ) {
        m_idx++;
    }
}
    // 获取下一个字符
char Parser::get_next_token() {

    skip_white_space();
    return m_str[m_idx++];
}
    

Json Parser::parse() {
    char ch = get_next_token();

    switch (ch)
    {
    case 'n':
    m_idx--;
        return parse_null();
        break;
    case 't':
    case 'f':
        m_idx--;
        return parse_bool();
        break;
    case '-':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        m_idx--;
        return parse_number();
        break;
    case '"':
        return Json(parse_string());
        break;
    case '[':
        return parse_array();
        break;
    case '{':
        return parse_object();
        break;
    
    default:
        break;
    }
    
    // 如果都不是，抛出异常
    throw new std::logic_error("unexpected char");
}

Json Parser::parse_null() {
    if(m_str.compare(m_idx,4,"null") == 0) {
         return Json{};
    }
    throw new std::logic_error("parse null error");
}
Json Parser::parse_bool() {
    if(m_str.compare(m_idx, 4, "true") == 0) {
        return Json(true);
    } else if(m_str.compare(m_idx, 5, "false") == 0) {
        return Json(false);
    } else {
        throw new std::logic_error("pasre bool error");
    }
}
Json Parser::parse_number() {
    /// @attention: 可改进 ...
    /// @bug: 全是整数 
    /// @note： 数字和字符弄混了
    /**
     * @note:
     * ( atof(),atoi(),itoa()和stoi(),c_str()函数的用法 )[https://blog.csdn.net/Ven21959/article/details/101431256]
    */
    int pos = m_idx;
    
    if(m_str[m_idx] == '-') {
        m_idx++;
    }
    if(m_str[m_idx] < '0' || m_str[m_idx] > '9') {
        throw new std::logic_error("parse number error");
    }
    while(m_str[m_idx] >= '0' && m_str[m_idx] <= '9') {
        m_idx++;
    }
    // '.' 小数点 
    if(m_str[m_idx] != '.') {
        int i = std::atoi(m_str.c_str() + pos);
        return Json(i);
    }

    m_idx++;
    if(m_str[m_idx] < '0' || m_str[m_idx] > '9') {
        throw new std::logic_error("parse number error");
    }
    while(m_str[m_idx] >= '0' && m_str[m_idx] <= '9') {
        m_idx++;
    }
    double f = std::atof(m_str.c_str() + pos);
    /**
     * @bug:
     * 关于浮点数精度的bug，浮点数的转换是正确的。
     * 原因在于 printf 和 cout的默认打印。
    */

    // std::clog<<f<<"double"<<std::endl;
    // printf("%.6f test\n",f);
    // std::cout<<f<<std::endl;
    return Json(f);
}
string Parser::parse_string() {
    return Json{};

}
Json Parser::parse_array() {
    return Json{};

}
Json Parser::parse_object() {
    return Json{};

}