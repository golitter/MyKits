/**
 * time: 2023��2��6�� 20��32��
 * https://www.bilibili.com/video/BV1TP411p7cC/?p=2&spm_id_from=pageDriver&vd_source=13dfbe5ed2deada83969fafa995ccff6
*/
#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <new>
using std::string;

// ���ܸ������Ĳ�����ͻ���������ռ���и���
namespace golitter {
namespace json{

class Json 
{
public:
    enum Type {
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };

    // ���캯�� 
    
    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char* value);
    Json(const string& value);
    Json(Type type);
    Json(const Json& other);

    // �����������������

    operator bool();
    operator int();
    operator double();
    operator string();

    // ����������
    /**
     * ���������飬����
    */
   // ��������������
    Json & operator [] (int index );
    void append(const Json & other );

    // ��������������
    Json & operator [] (const char * key);
    Json & operator [] (const string & key);
    // ��ֵ�����
    void operator = (const Json & other);

    // ���ַ�����ʽ����
    string str() const;

    // ���� -- ��ֵ
    void copy(const Json & other);
    // ��̬�ڴ��ͷ�
    void clear();

private:
    union Value {
        bool m_bool;
        int m_int;
        double m_double;
        std::string* m_stringaddress;
        std::vector<Json> * m_arrayaddress;
        std::map<string,Json> * m_objectaddress;

    };
    Type m_type;
    Value m_value;
};
}
}