#include "../include/myjson.h"
#include "../include/myparser.h"
#include <sstream>

using namespace golitter::json;

// ���캯��
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
    // ��switch����Json��Ĭ�����ͳ�ʼ��
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
    // ��ʼ������ָ��
        m_value.m_arrayaddress = new std::vector<Json>();
        break;
    case json_object:
    // ͬ ��ʼ������ָ��
        m_value.m_objectaddress = new std::map<string,Json>();
        break;
    default:
        // ����Ϊ�д���

        break;
    }
}
Json::Json(const Json& other) {
    // ��Json�����ĺ���
    // ��������ĺ���copy
    copy(other);
}

    // �����������������

/// @brief ��bool����ת��
Json::operator bool() {
    if(m_type != json_bool) {
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}
/// @brief  ��int����ת��
Json::operator int() {
    if(m_type != json_int) {
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}
/// @brief ��double����ת��
Json::operator double() {
    if(m_type != json_double) {
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}
/// @brief ��string����ת��
Json::operator string() {
    if(m_type != json_string) {
        throw new std::logic_error("type error, not string value");
    }
    return *(m_value.m_stringaddress);
}

    // ����������
Json& Json::operator [] (int index ) {
    /**
     * ���ж��ǲ����������ͣ�
     * ���ǽ���������Ϊ�������ͣ��������ʼ��ָ��
    */
    if(m_type != json_array) {
        m_type = json_array;
        m_value.m_arrayaddress = new std::vector<Json>();
    }
    if(index < 0) {
        throw new std::logic_error("error: array index < 0");
    }
    /**
     * @attention:
     * index��size_t�Ļ���������� ��������������ز���ģ����
     * ��Ϊ�����±� arr[index]����д����ʱ��Ĭ����int�������size_t�����ϣ��Һ��������ز�ͬ������
     * https://blog.csdn.net/xinqjl/article/details/103108569/
    */
    int length = (m_value.m_arrayaddress)->size();
    /**
     * �±����� ���� ��ǰ���鳤�ȣ��������м��Ԫ������Ҹ��ա�
    */
    if(index >= length) {
        for(int i =  length; i <= index; ++i) {
            (m_value.m_arrayaddress)->push_back(Json());
        }
    }
    return ( (m_value.m_arrayaddress)->at(index) );
}
/// @brief �������������JsonԪ�ء�
/// @param other JsonԪ��
void Json::append(const Json & other ) {
    /**
     * Json���Ͳ������飬��������������ݣ���ֹ�ڴ�й©��
     * �ٸ���Ϊ��������
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
     * ��const char * ���ַ���תΪstring�ַ�����������string�ַ����ĺ���
    */
    string name(key);
    return ( *(this) )[name];
}
Json& Json::operator [] (const string & key) {
    if(m_type != json_object) {
        clear();
        m_type = json_object;
        // ����ĳ�ʼ��ָ��
        m_value.m_objectaddress = new std::map<string, Json>();
    }
    return ( *(m_value.m_objectaddress) )[key]; // �� (map<>)[key]
}
/// @brief Json�Ŀ���
/// @param other Json����
void Json::operator = (const Json & other) {
    // ��������ٿ���
    clear();
    copy(other);
}

    // �Ⱥ�����
    /// �Ƚϵ�ַ
bool Json::operator == (const Json & other) {
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
            return m_value.m_arrayaddress == other.m_value.m_arrayaddress;
        }
        break;
    case json_object:
        {
            return m_value.m_objectaddress == other.m_value.m_objectaddress;
        }
        break;
    default:
        break;
    }
    return false;
}
bool Json::operator != (const Json & other) {
    /// ���õȺŵ�����
    return !( (*this) == other);
}

    // ���ַ�����ʽ����

/// @brief ��Json�������ַ�����ʽ����
/// @return Json���ַ�����ʽ
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
            // for(auto it: (*m_value.m_arrayaddress)) { // * ","û���ж��
            //     ss << it.str();
            // }
            // �ݹ�˼��
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
            // ͬ�� �ݹ�˼��
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
        // ����
        break;
    }

    return ss.str();
}
/// @brief Json������������ĺ���
/// @param other Ҫ������Json����
void Json::copy(const Json & other) {
        /**
         * @resolved: �� m_type = other.m_type �ⲽû��Ϊ���顢�����ַ��������ڴ档
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
        // ǳ����
        // m_value.m_stringaddress = other.m_value.m_stringaddress;
        // ���
        copy_string(*(other.m_value.m_stringaddress));
        break;
    case json_array:
        // ǳ����
        // m_value.m_arrayaddress = other.m_value.m_arrayaddress;
        // ���
        copy_array(other);
        break;
    case json_object:
        // ǳ����
        // m_value.m_objectaddress = other.m_value.m_objectaddress;
        // ���
        copy_object(other);
        break;
    default:
        // error
        break;
    }
}

    // ��������ǳ��������������
void Json::copy_string(const string& str) {
    m_value.m_stringaddress = new string(str);
}
void Json::copy_string(const char* str) {
    string tmp(str);
    copy_string(tmp);
}
void Json::copy_array(const Json& array) {


    /**
     * 2023��2��13�� 23��37�� 
     * @resolved: ��������Ϊ�գ�δ�����ڴ档
    */
   m_value.m_arrayaddress = new std::vector<Json>();
   /**
    * @resolved: �޸����ͺ�δ�����ڴ档
   */

    for(auto it = (array.m_value.m_arrayaddress)->begin(); it != (array.m_value.m_arrayaddress)->end(); ++it) {
        append(*it);
        // (m_value.m_arrayaddress)->push_back(Json(*it));
    }

}
void Json::copy_object(const Json& object) {

    m_value.m_objectaddress = new std::map<string,Json>();

    for(auto it = (object.m_value.m_objectaddress)->begin(); it != (object.m_value.m_objectaddress)->end(); ++it) {

        ( *(m_value.m_objectaddress) )[string(it->first)] = it->second;

    }
}
/// @brief ������õ��ڴ棬��ֹ�ڴ�й©
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
         * ��������Ͷ��������Ƕ�׵����ݣ���������Json���ͣ���ˣ����������������͵��ڲ�Ҫ����delete��
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
        break;
    }
    m_type = json_null;
}

    // ����ת��

bool Json::asBool() const {
    if(m_type != json_bool) {
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}
int Json::asInt() const {
    if(m_type != json_int) {
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}
double Json::asDouble() const {
    if(m_type != json_double) {
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}
string Json::asString() const {
    if(m_type != json_string) {
        throw new std::logic_error("type error, not string value");
    }
    return *(m_value.m_stringaddress);
}

    // ��������ĳ������
bool Json::has(int index) {
    if(m_type != json_array) {
        return false;
    }
    int length = (m_value.m_arrayaddress)->size();
    return (index >= 0 && index < length);
}

    // ��������ĳ����
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

    // ɾ��
void Json::remove(int index) {
    if(m_type != json_array) {
        return ;
    }
    int length = (m_value.m_arrayaddress)->size();
    
    if(index < 0 || index >= length) { // ��Χ����
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

    // ����parser
void Json::parse(const string& str) {
    Parser p;
    p.load(str);
    *this = p.parse();
}

