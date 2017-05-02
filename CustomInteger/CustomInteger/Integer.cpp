#include "Integer.h"
#include <math.h>

bool Integer::isEven(int value)
{
    return value % 2 == 0;
}

bool Integer::isEven(const Integer& value)
{
    return value.getValue() % 2 == 0;
}

bool Integer::isEven() const
{
    return m_iValue % 2 == 0;
}

bool Integer::isOdd(int value)
{
    return value % 2 != 0;
}

bool Integer::isOdd(const Integer& value)
{
    return value.getValue() % 2 != 0;
}

bool Integer::isOdd() const
{
    return m_iValue % 2 != 0;
}

bool Integer::isPrime(int value)
{
    if (value <= 3) return value > 1;

    for (int i = 2; i <= sqrt((double) value); ++i) {
        if ( value % i == 0) return false;
    }
    return true;
}

bool Integer::isPrime(const Integer& value)
{
    return Integer::isPrime(value.getValue());
}

bool Integer::isPrime() const
{
    return Integer::isPrime(m_iValue);
}

int Integer::parseInt(const string& value)
{
    return atoi(value.c_str());
}

bool Integer::equals(int value) const
{
    return m_iValue == value;
}

bool Integer::equals(const Integer& value) const
{
    return m_iValue == value.getValue();
}

string Integer::toString() const
{
    char szBuff[32];
    itoa(m_iValue, szBuff, 10);
    return string(szBuff);
}