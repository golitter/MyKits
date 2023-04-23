/**
 * @author:golitter
 * @email: golitter@qq.com
 * 
 * @website: https://789ak.com
 * 
 * time: 2023年2月6日 20点32分
 * https://www.bilibili.com/video/BV1TP411p7cC/?p=2&spm_id_from=pageDriver&vd_source=13dfbe5ed2deada83969fafa995ccff6
 * 
 * new delete 易导致内存泄漏 ： 用shared_ptr
 * [](https://blog.csdn.net/bitcarmanlee/article/details/124847634)
 * 2023年2月14日 17点39分 
 *      联合体内不能使用智能指针
 *      https://blog.csdn.net/dbdxnuliba/article/details/90286748?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%9C%A8%E8%81%94%E5%90%88%E4%BD%93%E5%86%85%E4%BD%BF%E7%94%A8%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-90286748.142%5Ev73%5Econtrol
 *      联合体中就不能放智能指针了，因为智能指针是模板类，大小不是四个字节，不好估计其大小。
 * 
 * 
*/

#pragma once
#include <string>
#include <vector>
#include <map>
// 抛出logic_error的异常
#include <stdexcept>
#include <new>
#include <memory>
#include <unordered_map>

#define NDEBUG
#include <assert.h>

using std::shared_ptr;
using std::string;

// 可能跟其他的产生冲突，用命名空间进行隔离

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

    // 构造函数 
        /**
         * 字符串有两个类型，一个是const char*的原c字符串类型，一个是cpp string类型。
        */

    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char* value);
    Json(const string& value);
    /// @brief Json的空非类型默认构造
    /// @param type 选择的类型
    Json(Type type);
    /// @brief Json拷贝构造函数
    /// @param other 
    Json(const Json& other);

    // 基本类型运算符重载

    operator bool();
    operator int();
    operator double();
    operator string();

    // 重载中括号
    /**
     * 重载了数组，对象
    */
   // 数组中括号重载
    Json & operator [] (int index );
    void append(const Json & other );

    // 对象中括号重载
    Json & operator [] (const char * key);
    Json & operator [] (const string & key);
    // 赋值运算符
    void operator = (const Json & other);

    // 等号重载
    bool operator == (const Json & other);
    bool operator != (const Json & other);
    bool compare(const Json& other);
    bool compare_array(const Json& array);
    bool compare_object(const Json& object);

    // 以字符串形式返回
    string str() const;

    // 拷贝 -- 赋值
    void copy(const Json & other);
    // 深拷贝：解决浅拷贝带来的问题
    void copy_string(const string& str);
    void copy_string(const char* str);
    void copy_array(const Json& array);
    void copy_object(const Json& object);
    // 动态内存释放
    void clear();

    // 数组迭代器
    typedef std::vector<Json>::iterator iterator;

    iterator begin() {
        return (m_value.m_arrayaddress)->begin();
    }
    iterator end() {
        return (m_value.m_arrayaddress)->end();
    }

    // 判断是否为空值
    bool isNull() const {return m_type == json_null; }
    // 判断是否为布尔值
    bool isBool() const {return m_type == json_bool; }
    // 判断是否为整型
    bool isInt() const {return m_type == json_int; }
    // 判断是否为浮点数型
    bool isDouble() const {return m_type == json_double; }
    // 判断是否为字符串型
    bool isString() const {return m_type == json_string; }
    // 判断是否为数组
    bool isArray() const {return m_type == json_array; }
    // 判断是否为对象
    bool isObject() const {return m_type == json_object; }

    // 显性转换

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    string asString() const;

    // 数组有无某个索引
    bool has(int index);
    // 对象有无某个键
    bool has(const char * key);
    bool has(const string& key);

    // 删除
    void remove(int index);
    void remove(const char* key);
    void remove(const string& key);

    // 定义parser
    void parse(const string& str);

    // 析构
private:
    union Value {
        bool m_bool;
        int m_int;
        double m_double;
        std::string* m_stringaddress;
        std::vector<Json> * m_arrayaddress;
        std::unordered_map<string,Json> * m_objectaddress;
        // shared_ptr<string> m_stringaddress;
        // shared_ptr<std::vector<Json>> m_arrayaddress;
        // shared_ptr<std::map<string,Json>> m_objectaddress;
        /**
         * 结构体中，智能指针和普通指针可以并存；但是联合体中就不能放智能指针了，因为智能指针是模板类，大小不是四个字节，不好估计其大小。
         * https://blog.csdn.net/dbdxnuliba/article/details/90286748?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%9C%A8%E8%81%94%E5%90%88%E4%BD%93%E5%86%85%E4%BD%BF%E7%94%A8%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-90286748.142^v73^control,201^v4^add_ask,239^v1^insert_chatgpt&spm=1018.2226.3001.4187
        */
    };
    Type m_type;
    Value m_value;
};
}
}