#pragma once

class BLL_API AdminManager : public LoginManager
{
public:
    AdminManager() : LoginManager() {};
    virtual ~AdminManager() {};

public:
    BOOL virtual validateLogin(int &id, CString userName, CString password);
};