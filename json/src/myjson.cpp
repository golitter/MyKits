#include "../include/myjson.h"
#include "../include/myparser.h"
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
    // 用switch进行Json的默认类型初始化
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
    // 初始化类型指针
        m_value.m_arrayaddress = new std::vector<Json>();
        break;
    case json_object:
    // 同 初始化类型指针
        m_value.m_objectaddress = new std::unordered_map<string,Json>();
        break;
    default:
        // 其他为有错误
        assert( 0 && ("Json::Json(Type type) function has error: default ... "));
        break;
    }
}
Json::Json(const Json& other) {
    // 用Json拷贝的函数
    // 抽象出来的函数copy
    copy(other);
}

    // 基本类型运算符重载

/// @brief 向bool类型转换
Json::operator bool() {
    if(m_type != json_bool) {
        assert( m_type == json_bool && ("type error, not bool value"));
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}
/// @brief  向int类型转换
Json::operator int() {
    if(m_type != json_int) {
        assert( m_type == json_int && ("type error, not int value"));
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}
/// @brief 向double类型转换
Json::operator double() {
    if(m_type != json_double) {
        assert( m_type == json_double && ("type error, not double value"));
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}
/// @brief 向string类型转换
Json::operator string() {
    if(m_type != json_string) {
        assert(m_type == json_double && ("type error, not string value"));
        throw new std::logic_error("type error, not string value");
    }
    return *(m_value.m_stringaddress);
}

    // 重载中括号
Json& Json::operator [] (int index ) {
    /**
     * 先判断是不是数组类型，
     * 不是将类型设置为数组类型，并赋予初始化指针
    */
    if(m_type != json_array) {
        m_type = json_array;
        m_value.m_arrayaddress = new std::vector<Json>();
    }
    if(index < 0) {
        assert( index >= 0 && ("error: array index < 0 "));
        throw new std::logic_error("error: array index < 0");
    }
    /**
     * @attention:
     * index用size_t的话，会与后面 对象的中括号重载产生模糊。
     * 因为数组下标 arr[index]在书写读入时，默认是int，因而于size_t不符合，且和其他重载不同而错误。
     * https://blog.csdn.net/xinqjl/article/details/103108569/
    */
    int length = (m_value.m_arrayaddress)->size();
    /**
     * 下标数字 大于 当前数组长度，将两者中间的元素添加且赋空。
    */
    if(index >= length) {
        for(int i =  length; i <= index; ++i) {
            (m_value.m_arrayaddress)->push_back(Json());
        }
    }
    return ( (m_value.m_arrayaddress)->at(index) );
}
/// @brief 向数组类型添加Json元素。
/// @param other Json元素
void Json::append(const Json & other ) {
    /**
     * Json类型不是数组，先清除其他的内容，防止内存泄漏，
     * 再赋予为数组类型
    */
    if(m_type != json_array) {
        clear();
        m_type = json_array;
        m_value.m_arrayaddress = new std::vector<Json>();
    }
    (m_value.m_arrayaddress)->push_back(other);
}


Json& Json::operator [] (const char * key) {
    /**
     * 将const char * 的字符串转为string字符串，并调用string字符串的函数
    */
    string name(key);
    return ( *(this) )[name];
}
Json& Json::operator [] (const string & key) {
    if(m_type != json_object) {
        clear();
        m_type = json_object;
        // 对象的初始化指针
        m_value.m_objectaddress = new std::unordered_map<string, Json>();
    }
    return ( *(m_value.m_objectaddress) )[key]; // 即 (map<>)[key]
}
/// @brief Json的拷贝
/// @param other Json数据
void Json::operator = (const Json & other) {
    // 先清除，再拷贝
    clear();
    copy(other);
}

    // 等号重载
    /// 比较地址
bool Json::operator == (const Json & other) {
    return compare(other);
}
bool Json::compare(const Json& other) {

    if(m_type != other.m_type) {
        return false;
    }

    switch (m_type)
    {
    case json_null:
        return true;
        break;
    case json_bool:
        return m_value.m_bool == other.m_value.m_bool;
        break;
    case json_int:
        return m_value.m_int == other.m_value.m_int;
        break;
    case json_double:
        return m_value.m_double == other.m_value.m_double;
        break;
    case json_string:
        return *(m_value.m_stringaddress) == *(other.m_value.m_stringaddress);
        break;
    case json_array:
        {
            // return m_value.m_arrayaddress == other.m_value.m_arrayaddress;
            return compare_array(other);
        }
        break;
    case json_object:
        {
            // return m_value.m_objectaddress == other.m_value.m_objectaddress;
            return compare_object(other);
        }
        break;
    default:
        assert( (0) && ("Json::operator==(const Json& other) function has errors : default"));
        break;
    }
    return false;
}
bool Json::compare_array(const Json& array) {
    int other_length = (array.m_value.m_arrayaddress)->size();
    int this_length = (m_value.m_arrayaddress)->size();
    if(other_length != this_length) {
        return false;
    }

    for(auto other_it = (array.m_value.m_arrayaddress)->begin(), this_it = (m_value.m_arrayaddress)->begin(); this_it != (m_value.m_arrayaddress)->end(); ++other_it, ++this_it) {
        if(!this_it->compare(*other_it)) return false;
    }
    return true;

}
bool Json::compare_object(const Json& object) {
    int other_length = (object.m_value.m_objectaddress)->size();
    int this_length = (m_value.m_objectaddress)->size();
    if(other_length != this_length) {
        return false;
    }
    for(auto other_it = (object.m_value.m_objectaddress)->begin(), this_it = (m_value.m_objectaddress)->begin(); this_it != (m_value.m_objectaddress)->end();++other_it, ++this_it) {
        if(other_it->first != this_it->first) {
            return false;
        }
        if(! ((this_it->second).compare(other_it->second))) {
            return false;
        }
    }
    return true;
}
bool Json::operator != (const Json & other) {
    /// 调用等号的重载
    return !( (*this) == other);
}

    // 以字符串形式返回

/// @brief 将Json数据用字符串形式返回
/// @return Json的字符串形式
string Json::str() const {
    /**
     * stringstream ss
     * 
    */
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
            // 递归思想
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
            // 同理 递归思想
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
        // 错误
        assert( (0) && ("string Json::str() has errors : default"));
        break;
    }

    return ss.str();
}
/// @brief Json拷贝抽象出来的函数
/// @param other 要拷贝的Json数据
void Json::copy(const Json & other) {
        /**
         * @resolved: 在 m_type = other.m_type 这步没有为数组、对象、字符串分配内存。
        */
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
        // m_value.m_stringaddress = other.m_value.m_stringaddress;
        // 深拷贝
        copy_string(*(other.m_value.m_stringaddress));
        break;
    case json_array:
        // 浅拷贝
        // m_value.m_arrayaddress = other.m_value.m_arrayaddress;
        // 深拷贝
        copy_array(other);
        break;
    case json_object:
        // 浅拷贝
        // m_value.m_objectaddress = other.m_value.m_objectaddress;
        // 深拷贝
        copy_object(other);
        break;
    default:
        // error
        assert( (0) && ("void Json::copy(const Json& other) function has errors : default"));
        break;
    }
}

    // 深拷贝：解决浅拷贝带来的问题
void Json::copy_string(const string& str) {
    m_value.m_stringaddress = new string(str);
}
void Json::copy_string(const char* str) {
    string tmp(str);
    copy_string(tmp);
}
void Json::copy_array(const Json& array) {


    /**
     * 2023年2月13日 23点37分 
     * @resolved: 数组类型为空，未分配内存。
    */
   m_value.m_arrayaddress = new std::vector<Json>();
   /**
    * @resolved: 修改类型后未分配内存。
   */

    for(auto it = (array.m_value.m_arrayaddress)->begin(); it != (array.m_value.m_arrayaddress)->end(); ++it) {
        append(*it);
        // (m_value.m_arrayaddress)->push_back(Json(*it));
    }

}
void Json::copy_object(const Json& object) {

    m_value.m_objectaddress = new std::unordered_map<string,Json>();

    for(auto it = (object.m_value.m_objectaddress)->begin(); it != (object.m_value.m_objectaddress)->end(); ++it) {

        ( *(m_value.m_objectaddress) )[string(it->first)] = it->second;

    }
}
/// @brief 清除不用的内存，防止内存泄漏
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
            delete m_value.m_stringaddress;
        }
        break;
        /**
         * @attention:
         * 由于数组和对象可能是嵌套的内容，即单独的Json类型，因此，对这两个数据类型的内部要单独delete。
        */
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
        assert( (0) && ("void Json::clear() function has errors : default"));
        break;
    }
    m_type = json_null;
}

    // 显性转换

bool Json::asBool() const {
    if(m_type != json_bool) {
        assert( (m_type == json_bool) && "type error, not bool value");
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}
int Json::asInt() const {
    if(m_type != json_int) {
        assert( (m_type == json_int) && ("type error, not int value"));
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}
double Json::asDouble() const {
    if(m_type != json_double) {
        assert( (m_type == json_double) && ("type error, not double value"));
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}
string Json::asString() const {
    if(m_type != json_string) {
        assert( (m_type == json_string) && ("type error, not string value"));
        throw new std::logic_error("type error, not string value");
    }
    return *(m_value.m_stringaddress);
}

    // 数组有无某个索引
bool Json::has(int index) {
    if(m_type != json_array) {
        return false;
    }
    int length = (m_value.m_arrayaddress)->size();
    return (index >= 0 && index < length);
}

    // 对象有无某个键
bool Json::has(const char * key) {
    // if(m_type != json_object) {
    //     return false;
    // }
    // return ( (m_value.m_objectaddress)->find(key) != (m_value.m_objectaddress)->end() );
    string name(key);
    return has(name);
}
bool Json::has(const string& key) {
    if(m_type != json_object) {
        return false;
    }
    return ( (m_value.m_objectaddress)->find(key) != (m_value.m_objectaddress)->end() );
}

    // 删除
void Json::remove(int index) {
    if(m_type != json_array) {
        return ;
    }
    int length = (m_value.m_arrayaddress)->size();
    
    if(index < 0 || index >= length) { // 范围不对
        return ;
    }
    (m_value.m_arrayaddress)->at(index).clear();
    (m_value.m_arrayaddress)->erase( (m_value.m_arrayaddress)->begin() + index );

    return ;
}
void Json::remove(const char* key) {
    string name(key);
    remove(name);
}
void Json::remove(const string& key) {
    if(m_type != json_object) {
        return ;
    }
    auto it = (m_value.m_objectaddress)->find(key);
    if(it == (m_value.m_objectaddress)->end() ) {
        return ;
    }

    ( *(m_value.m_objectaddress) )[key].clear();
    (m_value.m_objectaddress)->erase(key);
}

    // 定义parser
void Json::parse(const string& str) {
    Parser p;
    p.load(str);
    *this = p.parse();
}

