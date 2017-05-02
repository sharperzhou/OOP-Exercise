#include "String.h"
#include <iostream>
using namespace std;

int main()
{
    String str1;
    cin >> str1;

    for (int i = 0; i < str1.length(); ++i)
        cout << str1[i] << endl;

    try
    {
        str1[2] = 'A';
        char ch = str1[10];
    }
    catch (length_error& e)
    {
    	cout << e.what() << endl;
    }
    
    String str2;
    cin >> str2;

    if (str1 > str2)
        cout << str1 << endl;
    else
        cout << str2 << endl;

    String str3;
    str3 = str1.substr(2, 5);

    String str4 = "C++";
    String str5;
    str5 = "I Love " + str4 + " !";

    cout << str5 << endl;

    return 0;
}