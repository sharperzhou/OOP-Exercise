#pragma once

class BLL_API LoginManager
{
public:
    virtual ~LoginManager();
    LoginManager();
    BOOL virtual validateLogin(int &id, CString userName, CString password) = 0;
    int getInstanceCount() const;
protected:
    static int count;
};