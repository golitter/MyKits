#include "../include/myjson.h"
#include <sstream>

using namespace golitter::json;

// 构造函数
Json::Json(): m_type(json_null) {}

Json::Json(bool value): m_type(json_bool) {
    m_value.m_bool = value;
}

Json::Json(int value): m_type(json_int) {
    m_value.m_int = value;
}

Json::Json(double value): m_type(json_double) {
    m_value.m_double = value;
}

Json::Json(const char* value): m_type(json_string) {
    m_value.m_stringaddress = new string(value);
}

Json::Json(const string& value): m_type(json_string) {
    m_value.m_stringaddress = new string(value);
}

Json::Json(Type type): m_type(type) {
    switch (m_type)
    {
    case json_null:
            ;
        break;
    case json_bool:
        m_value.m_bool = false;
        break;
    case json_int:
        m_value.m_int = 0;
        break;
    case json_double:
        m_value.m_double = 0.0;
        break;
    case json_string:
        m_value.m_stringaddress = new string("");
        break;
    case json_array:
        m_value.m_arrayaddress = new std::vector<Json>();
        break;
    case json_object:
        m_value.m_objectaddress = new std::map<string,Json>();
        break;
    default:
        // error
        break;
    }
}
Json::Json(const Json& other) {
    copy(other);
}

    // 基本类型运算符重载
Json::operator bool() {
    if(m_type != json_bool) {
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}
Json::operator int() {
    if(m_type != json_int) {
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}
Json::operator double() {
    if(m_type != json_double) {
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}
Json::operator string() {
    if(m_type != json_string) {
        throw new std::logic_error("type error, not string value");
    }
    return *(m_value.m_stringaddress);
}

    // 重载中括号
Json & Json::operator [] (int index ) {
    if(m_type != json_array) {
        m_type = json_array;
        m_value.m_arrayaddress = new std::vector<Json>();
    }
    if(index < 0) {
        throw new std::logic_error("error: array index < 0");
    }
    int length = (m_value.m_arrayaddress)->size();
    if(index >= length) {
        for(int i =  length; i <= index; ++i) {
            (m_value.m_arrayaddress)->push_back(Json());
        }
    }
    return ( (m_value.m_arrayaddress)->at(index) );
}
void Json::append(const Json & other ) {
    if(m_type != json_array) {
        clear();
        m_type = json_array;
        m_value.m_arrayaddress = new std::vector<Json>();
    }
    (m_value.m_arrayaddress)->push_back(other);
}


Json & Json::operator [] (const char * key) {
    string name(key);
    return ( *(this) )[name];
}
Json & Json::operator [] (const string & key) {
    if(m_type != json_object) {
        clear();
        m_type = json_object;
        m_value.m_objectaddress = new std::map<string, Json>();
    }
    return ( *(m_value.m_objectaddress) )[key];
}
    
void Json::operator = (const Json & other) {
    clear();
    copy(other);
}


    // 以字符串形式返回
string Json::str() const {
    std::stringstream ss;
    switch (m_type)
    {
    case json_null:
        ss << "null";
        break;
    case json_bool:
        if(m_value.m_bool) {
            ss << "true";
        } else {
            ss << "false";
        }
        break;
    case json_int:
        ss << m_value.m_int;
        break;
    case json_double:
        ss << m_value.m_double;
        break;
    case json_string:
        ss <<'\"'<< *(m_value.m_stringaddress) <<'\"';
        break;
    case json_array:
        {
            ss << '[';
            // for(auto it: (*m_value.m_arrayaddress)) { // * ","没法判断喽
            //     ss << it.str();
            // }
            for(auto it = (m_value.m_arrayaddress)->begin(); it != (m_value.m_arrayaddress)->end(); ++it) {
                if(it != (m_value.m_arrayaddress)->begin()) {
                    ss << ',';
                }
                ss << it->str();
            }
            ss<< ']';
        }
        break;
    case json_object:
        {
            ss << '{';
            for(auto it = (m_value.m_objectaddress)->begin(); it != (m_value.m_objectaddress)->end(); ++it) {
                if(it != (m_value.m_objectaddress)->begin()) {
                    ss << ',';
                }
                ss << '\"' <<it->first<<'\"' << ':' << it->second.str();
            }
            ss << '}';
        }
        break;
    default:
        break;
    }

    return ss.str();
}

void Json::copy(const Json & other) {
     m_type = other.m_type;

    switch (m_type)
    {
    case json_null:
            ;
        break;
    case json_bool:
        m_value.m_bool = other.m_value.m_bool;
        break;
    case json_int:
        m_value.m_int = other.m_value.m_int;
        break;
    case json_double:
        m_value.m_double = other.m_value.m_double;
        break;
    case json_string:
        // 浅拷贝
        m_value.m_stringaddress = other.m_value.m_stringaddress;
        break;
    case json_array:
        // 浅拷贝
        m_value.m_arrayaddress = other.m_value.m_arrayaddress;
        break;
    case json_object:
        // 浅拷贝
        m_value.m_objectaddress = other.m_value.m_objectaddress;
        break;
    default:
        // error
        break;
    }
}

void Json::clear() {
    switch (m_type)
    {
    case json_null:
        break;
    case json_bool:
        m_value.m_bool = false;
        break;
    case json_int:
        m_value.m_int = 0;
        break;
    case json_double:
        m_value.m_double = 0.0;
        break;
    case json_string:
        {
            // debug: 裸指针
            delete m_value.m_stringaddress;
        }
        break;
    case json_array:
        {
            for(auto it = (m_value.m_arrayaddress)->begin(); it != (m_value.m_arrayaddress)->end(); ++it) {
                it->clear();
            }
            delete m_value.m_arrayaddress;
        }
        break;
    case json_object:
        {
            for(auto it = (m_value.m_objectaddress)->begin(); it != (m_value.m_objectaddress)->end(); ++it) {
                (it->second).clear();
            }
            delete m_value.m_objectaddress;
        }
        break;
    default:
        break;
    }
    m_type = json_null;
}