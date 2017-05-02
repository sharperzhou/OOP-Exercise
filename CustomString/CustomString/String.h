#ifndef __CUSTOM_STRING_H__
#define __CUSTOM_STRING_H__
#include <iostream>
class String
{
    //构造析构
public:
    String();
    String(const char *str);
    String(const String &other);
    ~String();

    //重载运算符
public:
    String& operator=(const String &other); //赋值操作符
    String& operator=(const char* str); //赋值操作符
    char& operator[](int index);
    String operator+(const char *rhs);
    String operator+(const String &rhs);
    bool operator>(const String &rhs);
    bool operator<(const String &rhs);
    bool operator==(const String &rhs);
    bool operator!=(const String &rhs);
    operator char*() const; //强制类型转换符

    friend std::istream& operator>>(std::istream &in, String &str);
    friend std::ostream& operator<<(std::ostream &out, const String &str);
    friend String operator+(const char *lhs, const String &rhs);

    //成员函数
public:
    int length() const;
    String substr(unsigned int start, unsigned int length) const;

protected:
    char * m_str;
};

#endif


