#include <iostream>
#include "Integer.h"
using namespace std;

int main()
{
    Integer intVal(10);
    Integer intVal2;
    int iVal = intVal.getValue();
    bool bRet;
    bRet = intVal.isEven();
    bRet = intVal.isOdd();
    bRet = intVal.isPrime();
    
    iVal = 5;
    bRet = Integer::isEven(iVal);
    bRet = Integer::isOdd(iVal);
    bRet = Integer::isPrime(iVal);

    intVal2 = Integer(15);
    bRet = Integer::isEven(intVal2);
    bRet = Integer::isOdd(intVal2);
    bRet = Integer::isPrime(intVal2);

    bRet = intVal2.equals(iVal);
    bRet = intVal2.equals(Integer(15));

    iVal = Integer::parseInt(string("12"));
    string str = intVal2.toString();
    return 0;
}