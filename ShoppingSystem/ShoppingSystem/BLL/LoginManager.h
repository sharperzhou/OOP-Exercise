#pragma once
#include "../Framework/stdafx.h"

class LoginManager
{
public:
    virtual ~LoginManager() {};
    LoginManager() { ++count; }
    BOOL virtual validateLogin(int &id, CString userName, CString password) = 0;
    int getInstanceCount() const { return count; }
protected:
    static int count;
};