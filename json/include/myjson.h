/**
 * @author:golitter
 * @email: golitter@qq.com
 * 
 * time: 2023��2��6�� 20��32��
 * https://www.bilibili.com/video/BV1TP411p7cC/?p=2&spm_id_from=pageDriver&vd_source=13dfbe5ed2deada83969fafa995ccff6
 * 
 * new delete �׵����ڴ�й© �� ��shared_ptr
 * [](https://blog.csdn.net/bitcarmanlee/article/details/124847634)
 * 2023��2��14�� 17��39�� 
 *      �������ڲ���ʹ������ָ��
 *      https://blog.csdn.net/dbdxnuliba/article/details/90286748?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%9C%A8%E8%81%94%E5%90%88%E4%BD%93%E5%86%85%E4%BD%BF%E7%94%A8%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-90286748.142%5Ev73%5Econtrol
 *      �������оͲ��ܷ�����ָ���ˣ���Ϊ����ָ����ģ���࣬��С�����ĸ��ֽڣ����ù������С��
 * part1 part2
 * 
 * part3
*/

#pragma once
#include <string>
#include <vector>
#include <map>
// �׳�logic_error���쳣
#include <stdexcept>
#include <new>
#include <memory>

#define NDEBUG
#include <assert.h>

using std::shared_ptr;
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
        /**
         * �ַ������������ͣ�һ����const char*��ԭc�ַ������ͣ�һ����cpp string���͡�
        */

    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char* value);
    Json(const string& value);
    /// @brief Json�Ŀշ�����Ĭ�Ϲ���
    /// @param type ѡ�������
    Json(Type type);
    /// @brief Json�������캯��
    /// @param other 
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

    // �Ⱥ�����
    bool operator == (const Json & other);
    bool operator != (const Json & other);

    // ���ַ�����ʽ����
    string str() const;

    // ���� -- ��ֵ
    void copy(const Json & other);
    // ��������ǳ��������������
    void copy_string(const string& str);
    void copy_string(const char* str);
    void copy_array(const Json& array);
    void copy_object(const Json& object);
    // ��̬�ڴ��ͷ�
    void clear();

    // ���������
    typedef std::vector<Json>::iterator iterator;

    iterator begin() {
        return (m_value.m_arrayaddress)->begin();
    }
    iterator end() {
        return (m_value.m_arrayaddress)->end();
    }

    // �ж��Ƿ�Ϊ��ֵ
    bool isNull() const {return m_type == json_null; }
    // �ж��Ƿ�Ϊ����ֵ
    bool isBool() const {return m_type == json_bool; }
    // �ж��Ƿ�Ϊ����
    bool isInt() const {return m_type == json_int; }
    // �ж��Ƿ�Ϊ��������
    bool isDouble() const {return m_type == json_double; }
    // �ж��Ƿ�Ϊ�ַ�����
    bool isString() const {return m_type == json_string; }
    // �ж��Ƿ�Ϊ����
    bool isArray() const {return m_type == json_array; }
    // �ж��Ƿ�Ϊ����
    bool isObject() const {return m_type == json_object; }

    // ����ת��

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    string asString() const;

    // ��������ĳ������
    bool has(int index);
    // ��������ĳ����
    bool has(const char * key);
    bool has(const string& key);

    // ɾ��
    void remove(int index);
    void remove(const char* key);
    void remove(const string& key);

    // ����parser
    void parse(const string& str);

    // ����
private:
    union Value {
        bool m_bool;
        int m_int;
        double m_double;
        std::string* m_stringaddress;
        std::vector<Json> * m_arrayaddress;
        std::map<string,Json> * m_objectaddress;
        // shared_ptr<string> m_stringaddress;
        // shared_ptr<std::vector<Json>> m_arrayaddress;
        // shared_ptr<std::map<string,Json>> m_objectaddress;
        /**
         * �ṹ���У�����ָ�����ָͨ����Բ��棻�����������оͲ��ܷ�����ָ���ˣ���Ϊ����ָ����ģ���࣬��С�����ĸ��ֽڣ����ù������С��
         * https://blog.csdn.net/dbdxnuliba/article/details/90286748?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%9C%A8%E8%81%94%E5%90%88%E4%BD%93%E5%86%85%E4%BD%BF%E7%94%A8%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-90286748.142^v73^control,201^v4^add_ask,239^v1^insert_chatgpt&spm=1018.2226.3001.4187
        */
    };
    Type m_type;
    Value m_value;
};
}
}