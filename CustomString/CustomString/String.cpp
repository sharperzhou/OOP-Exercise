#include "String.h"

String::String()
{
    m_str = new char[2];
    strcpy(m_str, "");
}

String::String(const char *str)
{
    m_str = new char[strlen(str) + 1];
    strcpy(m_str, str);
}

String::String(const String &other)
{
    m_str = new char[other.length() + 1];
    strcpy(m_str, (char*) other);
}

String::~String()
{
    if (m_str) delete[] m_str;
    m_str = 0;
}

String& String::operator =(const String &other)
{
    if (this != &other) {
        delete[] m_str;
        m_str = new char[other.length() + 1];
        strcpy(m_str, (char*) other);
    }
    return *this;
}

String& String::operator=(const char* str)
{
    if (strcmp(m_str, str)) {
        delete[] m_str;
        m_str = new char[strlen(str) + 1];
        strcpy(m_str, str);
    }
    return *this;
}

char& String::operator [](int index)
{
    if (index < 0 || index >= length())
        throw std::length_error("String out of range!");

    return m_str[index];
}

String String::operator +(const char *rhs)
{
    int len = length() + strlen(rhs);
    char *s = new char[len + 1];
    strcpy(s, m_str);
    strcat(s, rhs);

    String newStr(s);
    delete[] s;

    return newStr;
}

String String::operator +(const String &rhs)
{
    int len = length() + rhs.length();
    char *s = new char[len + 1];
    strcpy(s, m_str);
    strcat(s, (char*) rhs);

    String newStr(s);
    delete[] s;

    return newStr;
}

bool String::operator <(const String &rhs)
{
    return strcmp(m_str, (char*) rhs) < 0;
}

bool String::operator >(const String &rhs)
{
    return strcmp(m_str, (char*) rhs) > 0;
}

bool String::operator ==(const String &rhs)
{
    return strcmp(m_str, (char*) rhs) == 0;
}

bool String::operator !=(const String &rhs)
{
    return strcmp(m_str, (char*) rhs) != 0;
}

//重载强制类型转换符
String::operator char*() const
{
    return m_str;
}

std::istream& operator>>(std::istream &in, String &str)
{
    char szBuff[1024];
    in >> szBuff;
    str = szBuff;
    return in;
}

std::ostream& operator<<(std::ostream &out, const String &str)
{
    out << (char*) str;
    return out;
}

String operator+(const char *lhs, const String &rhs)
{
    int len = strlen(lhs) + rhs.length();
    char *s = new char[len + 1];
    strcpy(s, lhs);
    strcat(s, (char*) rhs);

    String newStr(s);
    delete[] s;

    return newStr;
}

int String::length() const
{
    return strlen(m_str);
}

String String::substr(unsigned int start, unsigned int length) const
{
    if (length < 1 || start >= this->length())
        throw std::length_error("String out of range!");

    char *s = new char[length + 1];

    strncpy(s, m_str + start, length);
    s[length] = '\0';

    String newStr(s);
    delete[] s;

    return newStr;
}